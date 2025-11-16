#!/usr/bin/env python3
"""
Script to complete missing JavaScript LLM variants for v3 and v4.

The problem: run_tests_on_cluster.py tracks completed entries by entry_id only,
but each entry should have 3 LLM variants (openAI, claude, gemini).
If one variant is completed, the others are skipped.

This script:
1. Identifies which (entry_id, llm_type) combinations are missing for v3/v4
2. For each missing combination, adds the result to the output file
3. Preserves existing results

Usage:
    python3 complete_javascript_llm_variants.py --analyze
    python3 complete_javascript_llm_variants.py --execute --prompt-version 3
    python3 complete_javascript_llm_variants.py --execute --prompt-version 4
    python3 complete_javascript_llm_variants.py --execute --all-versions
"""

import json
import subprocess
import sys
import argparse
from pathlib import Path
from collections import defaultdict
from datetime import datetime
import shutil
import time


def get_clusters_with_javascript():
    """Find all cluster names that have JavaScript entries."""
    clusters_dir = Path(__file__).parent.parent / "clusters"
    js_clusters = {}

    for cluster_file in sorted(clusters_dir.glob("cluster_*.json")):
        if "debug" in cluster_file.name or "test" in cluster_file.name:
            continue
        try:
            with open(cluster_file, 'r') as f:
                data = json.load(f)
                if 'javascript' in data and len(data['javascript']) > 0:
                    cluster_name = cluster_file.stem.replace("cluster_", "")
                    js_clusters[cluster_name] = data['javascript']
        except Exception as e:
            print(f"Error reading {cluster_file}: {e}")

    return js_clusters


def analyze_missing_llm_variants(prompt_version):
    """
    Analyze which (entry_id, llm_type) combinations are missing.

    Returns:
        dict: {cluster_name: [(entry_id, llm_type), ...]}
    """
    outputs_dir = Path(__file__).parent.parent / "execution_outputs"
    js_clusters = get_clusters_with_javascript()

    missing_by_cluster = defaultdict(list)
    total_expected = 0
    total_found = 0

    expected_llm_types = ['openAI', 'claude', 'gemini']

    for cluster_name, cluster_js_entries in js_clusters.items():
        # Get expected (entry_id, llm_type) combinations from cluster file
        expected_combinations = set()
        for entry in cluster_js_entries:
            entry_id = entry['id']
            for llm_info in entry.get('LLMs', []):
                llm_type = llm_info.get('type', '')
                filename = llm_info.get('filename', '')
                # Check if this LLM variant is for the requested prompt version
                if f"_v{prompt_version}" in filename:
                    expected_combinations.add((entry_id, llm_type))

        total_expected += len(expected_combinations)

        # Get actually completed combinations from output file
        completed_combinations = set()
        result_file = outputs_dir / f"{cluster_name}_results_v{prompt_version}_1.json"

        if result_file.exists():
            try:
                with open(result_file, 'r') as f:
                    data = json.load(f)
                    if 'results' in data and 'javascript' in data['results']:
                        for entry_result in data['results']['javascript']:
                            entry_id = entry_result['id']
                            if entry_result.get('LLM_results'):
                                for llm_result in entry_result['LLM_results']:
                                    llm_type = llm_result.get('LLM_type', '')
                                    completed_combinations.add((entry_id, llm_type))
            except Exception as e:
                print(f"Error reading {result_file}: {e}")

        total_found += len(completed_combinations)

        # Find missing combinations
        missing = expected_combinations - completed_combinations
        if missing:
            missing_by_cluster[cluster_name] = sorted(list(missing))

    return missing_by_cluster, total_expected, total_found


def add_missing_llm_results(cluster_name, entry_id, llm_type, prompt_version, run_number=1):
    """
    Execute a single missing LLM variant and add it to the output file.

    This function:
    1. Runs the test for the specific (entry_id, llm_type) combination
    2. Merges the result into the existing output file
    """
    outputs_dir = Path(__file__).parent.parent / "execution_outputs"
    clusters_dir = Path(__file__).parent.parent / "clusters"

    result_file = outputs_dir / f"{cluster_name}_results_v{prompt_version}_{run_number}.json"

    # Load cluster data to get entry info
    cluster_file = clusters_dir / f"cluster_{cluster_name}.json"
    with open(cluster_file, 'r') as f:
        cluster_data = json.load(f)

    # Find the specific entry and LLM info
    entry_info = None
    llm_info = None

    for entry in cluster_data.get('javascript', []):
        if entry['id'] == entry_id:
            entry_info = entry
            for llm in entry.get('LLMs', []):
                if llm.get('type') == llm_type and f"_v{prompt_version}" in llm.get('filename', ''):
                    llm_info = llm
                    break
            break

    if not entry_info or not llm_info:
        print(f"    ✗ Could not find entry/LLM info for {entry_id} {llm_type}")
        return False

    # Create a temporary cluster file with just this one entry
    temp_cluster_dir = Path(__file__).parent / "temp_clusters"
    temp_cluster_dir.mkdir(exist_ok=True)

    temp_cluster_file = temp_cluster_dir / f"cluster_{cluster_name}_temp.json"

    # Modify the entry to have only the specific LLM we want to run
    temp_entry = entry_info.copy()
    temp_entry['LLMs'] = [llm_info]

    temp_cluster_data = {'javascript': [temp_entry]}

    with open(temp_cluster_file, 'w') as f:
        json.dump(temp_cluster_data, f, indent=2)

    try:
        # Run the test using run_tests_on_cluster.py
        script_path = Path(__file__).parent / "run_tests_on_cluster.py"

        cmd = [
            "python3", str(script_path),
            "--cluster-name", f"{cluster_name}_temp",
            "--clusters-dir", str(temp_cluster_dir),
            "--run-quantity", str(run_number),
            "--llm-only",
            "--prompt-version", str(prompt_version),
            "--languages", "javascript",
            "--overwrite-results"
        ]

        result = subprocess.run(
            cmd,
            capture_output=True,
            text=True,
            timeout=300,  # 5 minute timeout
            cwd=Path(__file__).parent
        )

        if result.returncode != 0:
            print(f"    ✗ Execution failed: {result.stderr[:200]}")
            return False

        # Read the temp output file
        temp_output = outputs_dir / f"{cluster_name}_temp_results_v{prompt_version}_{run_number}.json"

        if not temp_output.exists():
            print(f"    ✗ Temp output file not created")
            return False

        with open(temp_output, 'r') as f:
            temp_results = json.load(f)

        # Merge into the main output file
        if result_file.exists():
            with open(result_file, 'r') as f:
                main_results = json.load(f)
        else:
            main_results = {'results': {}}

        # Add the new result
        if 'results' in temp_results and 'javascript' in temp_results['results']:
            if 'javascript' not in main_results['results']:
                main_results['results']['javascript'] = []

            main_results['results']['javascript'].extend(temp_results['results']['javascript'])

        # Save merged results
        with open(result_file, 'w') as f:
            json.dump(main_results, f, indent=2)

        # Clean up temp files
        temp_output.unlink()

        return True

    except subprocess.TimeoutExpired:
        print(f"    ✗ Timeout")
        return False
    except Exception as e:
        print(f"    ✗ Error: {e}")
        return False
    finally:
        # Clean up temp cluster file
        if temp_cluster_file.exists():
            temp_cluster_file.unlink()


def execute_missing_variants(prompt_version, dry_run=False, max_clusters=None):
    """Execute all missing LLM variants for a specific prompt version."""

    print(f"\n{'='*70}")
    print(f"COMPLETING MISSING JAVASCRIPT LLM VARIANTS FOR v{prompt_version}")
    print(f"{'='*70}")
    print(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")

    missing_by_cluster, total_expected, total_found = analyze_missing_llm_variants(prompt_version)

    total_missing = sum(len(items) for items in missing_by_cluster.values())

    print(f"\nExpected combinations: {total_expected}")
    print(f"Found combinations: {total_found}")
    print(f"Missing combinations: {total_missing}")
    print(f"Clusters with missing data: {len(missing_by_cluster)}")

    if total_missing == 0:
        print("\n✓ No missing variants found!")
        return 0

    if dry_run:
        print("\n--- DRY RUN MODE ---")
        for cluster_name, missing in list(missing_by_cluster.items())[:10]:
            print(f"\n{cluster_name}:")
            for entry_id, llm_type in missing[:5]:
                print(f"  - {entry_id[-50:]} ({llm_type})")
            if len(missing) > 5:
                print(f"  ... and {len(missing) - 5} more")
        if len(missing_by_cluster) > 10:
            print(f"\n... and {len(missing_by_cluster) - 10} more clusters")
        return 0

    # Execute missing variants
    print(f"\n{'='*70}")
    print("EXECUTING MISSING VARIANTS")
    print(f"{'='*70}")

    successful = 0
    failed = 0

    clusters_to_process = list(missing_by_cluster.items())
    if max_clusters:
        clusters_to_process = clusters_to_process[:max_clusters]

    for i, (cluster_name, missing_items) in enumerate(clusters_to_process, 1):
        print(f"\n[{i}/{len(clusters_to_process)}] {cluster_name} ({len(missing_items)} missing)")

        for entry_id, llm_type in missing_items:
            print(f"  Processing {entry_id[-40:]} ({llm_type})...")

            # Process all 5 runs
            all_runs_success = True
            for run_num in range(1, 6):
                if not add_missing_llm_results(cluster_name, entry_id, llm_type, prompt_version, run_num):
                    all_runs_success = False
                    break

            if all_runs_success:
                print(f"    ✓ Success (all 5 runs)")
                successful += 1
            else:
                print(f"    ✗ Failed")
                failed += 1

    print(f"\n{'='*70}")
    print("EXECUTION COMPLETE")
    print(f"{'='*70}")
    print(f"Successful: {successful}")
    print(f"Failed: {failed}")
    print(f"Total: {successful + failed}")
    print(f"Completed: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")

    return 0 if failed == 0 else 1


def main():
    parser = argparse.ArgumentParser(description="Complete missing JavaScript LLM variants")
    parser.add_argument("--analyze", action="store_true", help="Only analyze missing variants")
    parser.add_argument("--execute", action="store_true", help="Execute missing variants")
    parser.add_argument("--prompt-version", type=int, choices=[3, 4], help="Prompt version (3 or 4)")
    parser.add_argument("--all-versions", action="store_true", help="Process both v3 and v4")
    parser.add_argument("--dry-run", action="store_true", help="Show what would be done without executing")
    parser.add_argument("--max-clusters", type=int, help="Limit number of clusters to process")

    args = parser.parse_args()

    if args.analyze:
        print("=" * 70)
        print("ANALYSIS OF MISSING JAVASCRIPT LLM VARIANTS")
        print("=" * 70)
        print()

        for version in [3, 4]:
            missing_by_cluster, total_expected, total_found = analyze_missing_llm_variants(version)
            total_missing = sum(len(items) for items in missing_by_cluster.values())

            print(f"PROMPT VERSION {version}:")
            print(f"  Expected (entry_id, llm_type) combinations: {total_expected}")
            print(f"  Found in output files: {total_found}")
            print(f"  Missing: {total_missing} ({total_missing * 100 / total_expected:.1f}%)")
            print(f"  Clusters with missing data: {len(missing_by_cluster)}")
            print()

        return 0

    if args.execute:
        if args.all_versions:
            for version in [3, 4]:
                result = execute_missing_variants(version, args.dry_run, args.max_clusters)
                if result != 0:
                    return result
        elif args.prompt_version:
            return execute_missing_variants(args.prompt_version, args.dry_run, args.max_clusters)
        else:
            print("Error: Must specify --prompt-version or --all-versions")
            return 1

    parser.print_help()
    return 1


if __name__ == "__main__":
    sys.exit(main())
