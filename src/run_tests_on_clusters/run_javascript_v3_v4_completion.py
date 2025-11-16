#!/usr/bin/env python3
"""
Run JavaScript LLM tests for v3 and v4 to complete missing variants.

This script uses the fixed run_tests_on_cluster.py which now properly tracks
(entry_id, llm_type) combinations instead of just entry_id, ensuring all
LLM variants (openAI, claude, gemini) are executed.

Usage:
    python3 run_javascript_v3_v4_completion.py --prompt-version 3
    python3 run_javascript_v3_v4_completion.py --prompt-version 4
    python3 run_javascript_v3_v4_completion.py --all  # Both v3 and v4
    python3 run_javascript_v3_v4_completion.py --dry-run --prompt-version 3
"""

import json
import subprocess
import sys
import argparse
from datetime import datetime
from pathlib import Path


def get_js_clusters():
    """Get list of JavaScript clusters"""
    clusters = []
    skip_patterns = ['debug', 'test', 'bad_entries', 'focused_', 'with_metrics']

    clusters_dir = Path(__file__).parent.parent / 'clusters'

    for f in sorted(clusters_dir.glob('cluster_*.json')):
        if any(skip in f.name for skip in skip_patterns):
            continue

        try:
            with open(f) as fp:
                data = json.load(fp)
                if 'javascript' in data and len(data['javascript']) > 0:
                    cluster_name = f.stem.replace('cluster_', '')
                    if not any(skip in cluster_name for skip in skip_patterns):
                        clusters.append(cluster_name)
        except Exception:
            continue

    return clusters


def analyze_current_state(prompt_version):
    """Analyze current JavaScript LLM entries for a prompt version."""
    outputs_dir = Path(__file__).parent.parent / "execution_outputs"
    clusters_dir = Path(__file__).parent.parent / "clusters"

    # Get expected (entry_id, llm_type) from cluster files
    expected_combos = 0
    js_clusters = get_js_clusters()

    for cluster_name in js_clusters:
        cluster_file = clusters_dir / f"cluster_{cluster_name}.json"
        try:
            with open(cluster_file) as f:
                data = json.load(f)
                for entry in data.get('javascript', []):
                    for llm_info in entry.get('LLMs', []):
                        if f"_v{prompt_version}" in llm_info.get('filename', ''):
                            expected_combos += 1
        except Exception:
            pass

    # Count actual combos in output files
    found_combos = 0
    for cluster_name in js_clusters:
        result_file = outputs_dir / f"{cluster_name}_results_v{prompt_version}_1.json"
        if result_file.exists():
            try:
                with open(result_file) as f:
                    data = json.load(f)
                    if 'results' in data and 'javascript' in data['results']:
                        found_combos += len(data['results']['javascript'])
            except Exception:
                pass

    missing = expected_combos - found_combos
    percent_complete = (found_combos / expected_combos * 100) if expected_combos > 0 else 0

    return {
        'expected': expected_combos,
        'found': found_combos,
        'missing': missing,
        'percent_complete': percent_complete,
        'num_clusters': len(js_clusters)
    }


def run_prompt_version(prompt_version, dry_run=False):
    """Run JavaScript tests for a specific prompt version."""

    print("=" * 80)
    print(f"JAVASCRIPT LLM COMPLETION - PROMPT VERSION {prompt_version}")
    print("=" * 80)
    print(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print()

    # Analyze current state
    state = analyze_current_state(prompt_version)
    print(f"Current State for v{prompt_version}:")
    print(f"  Expected (entry_id, llm_type) combinations: {state['expected']}")
    print(f"  Found in output files: {state['found']}")
    print(f"  Missing: {state['missing']} ({100 - state['percent_complete']:.1f}%)")
    print(f"  JavaScript clusters: {state['num_clusters']}")
    print()

    if state['missing'] == 0:
        print(f"✓ All JavaScript LLM variants already complete for v{prompt_version}!")
        return 0

    clusters = get_js_clusters()

    if dry_run:
        print("DRY RUN MODE - No execution will occur")
        print(f"Would execute {len(clusters)} clusters for v{prompt_version}")
        return 0

    print(f"Executing {len(clusters)} clusters...")
    print()

    success_count = 0
    failed_count = 0
    failed_clusters = []

    # Extract version number (e.g., 3)
    ver_num = str(prompt_version)

    for i, cluster in enumerate(clusters, 1):
        timestamp = datetime.now().strftime('%H:%M:%S')
        print(f"[{timestamp}] [{i}/{len(clusters)}] Processing: {cluster}")

        cmd = [
            'python3', 'run_tests_on_cluster.py',
            '--languages', 'javascript',
            '--run-quantity', '5',
            '--selective-rerun',
            '--cluster-name', cluster,
            '--llm-only',
            '--prompt-version', ver_num
        ]

        try:
            result = subprocess.run(
                cmd,
                capture_output=False,
                text=True,
                #timeout=900,  # 15 minutes per cluster
                cwd=Path(__file__).parent
            )

            if result.returncode == 0:
                print(f"  ✓ Success")
                success_count += 1
            else:
                print(f"  ✗ Failed (exit code: {result.returncode})")
                failed_count += 1
                failed_clusters.append(cluster)

                # Log error
                error_log = Path(__file__).parent / 'errors' / f'cluster_{cluster}_v{prompt_version}_error.log'
                error_log.parent.mkdir(exist_ok=True)
                with open(error_log, 'w') as f:
                    f.write(f"STDOUT:\n{result.stdout}\n\n")
                    f.write(f"STDERR:\n{result.stderr}\n")

        except subprocess.TimeoutExpired:
            print(f"  ✗ Timeout (>15 min)")
            failed_count += 1
            failed_clusters.append(cluster)
        except Exception as e:
            print(f"  ✗ Error: {e}")
            failed_count += 1
            failed_clusters.append(cluster)

    print()
    print("-" * 80)
    print(f"v{prompt_version} COMPLETED")
    print(f"  ✓ Success: {success_count}/{len(clusters)}")
    print(f"  ✗ Failed: {failed_count}/{len(clusters)}")

    # Final state analysis
    final_state = analyze_current_state(prompt_version)
    print(f"\nFinal State:")
    print(f"  Found combinations: {final_state['found']}/{final_state['expected']}")
    print(f"  Completion: {final_state['percent_complete']:.1f}%")

    if failed_clusters:
        print(f"\nFailed clusters:")
        for c in failed_clusters[:10]:
            print(f"  - {c}")
        if len(failed_clusters) > 10:
            print(f"  ... and {len(failed_clusters) - 10} more")

    print(f"\nCompleted: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print("-" * 80)
    print()

    return 0 if failed_count == 0 else 1


def main():
    parser = argparse.ArgumentParser(
        description="Complete missing JavaScript LLM variants for v3/v4"
    )
    parser.add_argument(
        '--prompt-version',
        type=int,
        choices=[3, 4],
        help='Prompt version to run (3 or 4)'
    )
    parser.add_argument(
        '--all',
        action='store_true',
        help='Run both v3 and v4'
    )
    parser.add_argument(
        '--dry-run',
        action='store_true',
        help='Show what would be done without executing'
    )
    parser.add_argument(
        '--analyze-only',
        action='store_true',
        help='Only analyze current state without executing'
    )

    args = parser.parse_args()

    if args.analyze_only:
        print("=" * 80)
        print("ANALYSIS OF JAVASCRIPT LLM COMPLETION STATUS")
        print("=" * 80)
        print()

        for version in [3, 4]:
            state = analyze_current_state(version)
            print(f"Prompt Version {version}:")
            print(f"  Expected combinations: {state['expected']}")
            print(f"  Found: {state['found']}")
            print(f"  Missing: {state['missing']}")
            print(f"  Completion: {state['percent_complete']:.1f}%")
            print()

        return 0

    if args.all:
        result = 0
        for version in [3, 4]:
            r = run_prompt_version(version, args.dry_run)
            if r != 0:
                result = r
        return result
    elif args.prompt_version:
        return run_prompt_version(args.prompt_version, args.dry_run)
    else:
        parser.print_help()
        return 1


if __name__ == '__main__':
    sys.exit(main())
