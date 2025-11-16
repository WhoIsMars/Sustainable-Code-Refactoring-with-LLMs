#!/usr/bin/env python3
"""
Parallel JavaScript LLM Executor for Prompt Versions 3 and 4

This script executes JavaScript entries from clusters, running only versions 3 and 4 of the prompt.
It performs the following:
1. Identifies JS clusters that need execution (missing valid results)
2. Checks both execution_outputs and backup_executions for existing valid results
3. Executes missing entries using run_tests_on_cluster.py with the --cluster-names flag
4. Runs v3 and v4 in parallel processes without resource conflicts
5. Calls cleanup_docker.sh at the end

Usage:
    python3 parallel_js_v3_v4_executor.py
    python3 parallel_js_v3_v4_executor.py --analyze  # Only show what needs execution
    python3 parallel_js_v3_v4_executor.py --dry-run  # Show commands without executing
"""

import json
import subprocess
import sys
import os
import argparse
import multiprocessing as mp
from datetime import datetime
from pathlib import Path
from typing import Dict, List, Set, Tuple, Optional
from collections import defaultdict


# Add parent directory to path for imports
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", ".."))
from utility_dir import utility_paths, general_utils


def get_all_js_clusters() -> List[str]:
    """Get list of all JavaScript clusters (clusters containing JS entries)."""
    clusters = []
    skip_patterns = ['debug', 'test', 'bad_entries', 'focused_', 'with_metrics']

    clusters_dir = utility_paths.CLUSTERS_DIR_FILEPATH

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
        except Exception as e:
            print(f"Warning: Could not read {f.name}: {e}")
            continue

    return clusters


def is_valid_llm_result(llm_result: dict) -> bool:
    """Check if an LLM result has all valid metrics."""
    return (llm_result.get('execution_time_ms') is not None and
            llm_result.get('CPU_usage') is not None and
            llm_result.get('RAM_usage') is not None and
            llm_result.get('RAM_usage') != 0 and
            llm_result.get('execution_time_ms', 0) > 0)


def copy_backup_result_to_outputs(
    cluster_name: str,
    entry_id: str,
    llm_type: str,
    prompt_version: int,
    exec_number: int,
    backup_entry_data: dict
) -> bool:
    """
    Copy a valid backup result to the execution_outputs file.

    Args:
        cluster_name: Name of the cluster
        entry_id: ID of the entry
        llm_type: Type of LLM (claude, gemini, openAI)
        prompt_version: Prompt version (3 or 4)
        exec_number: Execution number (1-5)
        backup_entry_data: The entry data from the backup file

    Returns:
        True if successfully copied, False otherwise.
    """
    outputs_dir = utility_paths.OUTPUT_DIR_FILEPATH
    result_file = outputs_dir / f"{cluster_name}_results_v{prompt_version}_{exec_number}.json"

    try:
        # Load or create the output file
        if result_file.exists():
            with open(result_file, 'r') as f:
                output_data = json.load(f)
        else:
            # Create new structure
            output_data = {
                "execution_date": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
                "execution_metadata": {
                    "total_tests": 0,
                    "successful_tests": 0,
                    "execution_time": "restored_from_backup",
                    "cluster": f"cluster_{cluster_name}",
                    "test_type": f"llm_v{prompt_version}"
                },
                "results": {}
            }

        # Ensure results structure exists
        if 'results' not in output_data:
            output_data['results'] = {}
        if 'javascript' not in output_data['results']:
            output_data['results']['javascript'] = []

        # Check if this (entry_id, llm_type) combination already exists
        found = False
        for existing_entry in output_data['results']['javascript']:
            if existing_entry.get('id') == entry_id:
                for existing_llm_result in existing_entry.get('LLM_results', []):
                    if existing_llm_result.get('LLM_type') == llm_type:
                        # Already exists, don't overwrite
                        found = True
                        break
                if not found:
                    # Same entry_id but different llm_type - this shouldn't happen for our case
                    # Just add the new entry as a separate one
                    pass
                break

        if not found:
            # Add the backup entry to the output file
            output_data['results']['javascript'].append(backup_entry_data)

            # Save the updated file
            with open(result_file, 'w') as f:
                json.dump(output_data, f, indent=2, ensure_ascii=False)

            return True

        return False

    except Exception as e:
        print(f"Warning: Failed to copy backup result to outputs: {e}")
        return False


def check_entry_has_valid_results(
    cluster_name: str,
    entry_id: str,
    llm_type: str,
    prompt_version: int,
    exec_number: int
) -> bool:
    """
    Check if an entry has valid results for a specific execution.

    Checks:
    1. execution_outputs for existing valid results
    2. backup_executions for backup files

    If valid results are found in backup but not in execution_outputs,
    they are automatically copied to execution_outputs.

    Returns True if valid results exist (or were restored), False otherwise.
    """
    outputs_dir = utility_paths.OUTPUT_DIR_FILEPATH
    backup_dir = utility_paths.SRC_DIR / "backup_executions"

    # Check 1: Look in execution_outputs
    result_file = outputs_dir / f"{cluster_name}_results_v{prompt_version}_{exec_number}.json"
    found_in_outputs = False

    if result_file.exists():
        try:
            with open(result_file, 'r') as f:
                data = json.load(f)
                if 'results' in data and 'javascript' in data['results']:
                    for entry in data['results']['javascript']:
                        if entry.get('id') == entry_id:
                            for llm_result in entry.get('LLM_results', []):
                                if llm_result.get('LLM_type') == llm_type:
                                    if is_valid_llm_result(llm_result):
                                        found_in_outputs = True
                                        return True
        except Exception:
            pass

    # Check 2: Look in backup_executions
    # Pattern: {cluster_name}_results_v{prompt_version}_{exec_number}_backup_*.json
    backup_pattern = f"{cluster_name}_results_v{prompt_version}_{exec_number}_backup_*.json"

    # Search directly in backup_executions and in subdirectories
    backup_files = list(backup_dir.glob(backup_pattern))

    # Also check subdirectories named after the cluster
    cluster_backup_dir = backup_dir / cluster_name
    if cluster_backup_dir.exists():
        backup_files.extend(list(cluster_backup_dir.glob(backup_pattern)))

    for backup_file in backup_files:
        try:
            with open(backup_file, 'r') as f:
                data = json.load(f)
                if 'results' in data and 'javascript' in data['results']:
                    for entry in data['results']['javascript']:
                        if entry.get('id') == entry_id:
                            for llm_result in entry.get('LLM_results', []):
                                if llm_result.get('LLM_type') == llm_type:
                                    if is_valid_llm_result(llm_result):
                                        # Valid result found in backup but not in outputs
                                        # Copy it to the output file
                                        if not found_in_outputs:
                                            if copy_backup_result_to_outputs(
                                                cluster_name, entry_id, llm_type,
                                                prompt_version, exec_number, entry
                                            ):
                                                print(f"    Restored from backup: {entry_id} ({llm_type}) v{prompt_version} exec#{exec_number}")
                                        return True
        except Exception:
            pass

    return False


def get_clusters_needing_execution(prompt_version: int) -> Tuple[List[str], Dict[str, int]]:
    """
    Get clusters that need execution for a given prompt version.

    Returns:
        Tuple of (list of cluster names, dict of cluster_name -> missing_count)
    """
    js_clusters = get_all_js_clusters()
    clusters_to_execute = []
    cluster_missing_counts = {}

    clusters_dir = utility_paths.CLUSTERS_DIR_FILEPATH

    for cluster_name in js_clusters:
        cluster_file = clusters_dir / f"cluster_{cluster_name}.json"

        if not cluster_file.exists():
            continue

        try:
            with open(cluster_file) as f:
                cluster_data = json.load(f)
        except Exception:
            continue

        js_entries = cluster_data.get('javascript', [])
        if not js_entries:
            continue

        missing_count = 0

        # Check each entry and each LLM type for this prompt version
        for entry in js_entries:
            entry_id = entry.get('id')

            for llm_info in entry.get('LLMs', []):
                filename = llm_info.get('filename', '')
                if f"_v{prompt_version}" not in filename:
                    continue

                llm_type = llm_info.get('type', 'unknown')

                # Check all 5 executions
                for exec_num in range(1, 6):
                    if not check_entry_has_valid_results(
                        cluster_name, entry_id, llm_type, prompt_version, exec_num
                    ):
                        missing_count += 1

        if missing_count > 0:
            clusters_to_execute.append(cluster_name)
            cluster_missing_counts[cluster_name] = missing_count

    return clusters_to_execute, cluster_missing_counts


def run_version_execution(prompt_version: int, cluster_names: List[str]) -> int:
    """
    Execute all clusters for a specific prompt version using run_tests_on_cluster.py.

    Args:
        prompt_version: The prompt version (3 or 4)
        cluster_names: List of cluster names to execute

    Returns:
        Exit code (0 for success, non-zero for failure)
    """
    print("=" * 80)
    print(f"JAVASCRIPT LLM EXECUTION - PROMPT VERSION {prompt_version}")
    print("=" * 80)
    print(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print(f"PID: {mp.current_process().pid}")
    print(f"Clusters to process: {len(cluster_names)}")
    print()

    if not cluster_names:
        print(f"✓ No clusters need execution for v{prompt_version}!")
        return 0

    # List clusters
    print("Clusters:")
    for i, name in enumerate(cluster_names[:20], 1):
        print(f"  {i}. {name}")
    if len(cluster_names) > 20:
        print(f"  ... and {len(cluster_names) - 20} more")
    print()

    # Build command using --cluster-names
    # Use a unique container prefix to avoid conflicts between v3 and v4
    container_prefix = f"test_runner_v{prompt_version}"
    cmd = [
        'python3', '../run_tests_on_cluster.py',
        '--languages', 'javascript',
        '--run-quantity', '5',
        '--llm-only',
        '--prompt-version', str(prompt_version),
        '--container-prefix', container_prefix,
        '--cluster-names'
    ] + cluster_names

    print(f"Executing command:")
    print(f"  {' '.join(cmd[:12])}... [+{len(cluster_names)} cluster names]")
    print(f"  Container prefix: {container_prefix}")
    print()

    # Execute with real-time output (no capture)
    try:
        result = subprocess.run(
            cmd,
            cwd=Path(__file__).parent,
            # No timeout - let it run as long as needed
        )

        status = "✓ SUCCESS" if result.returncode == 0 else f"✗ FAILED (code {result.returncode})"
        print(f"\nv{prompt_version} execution: {status}")
        print(f"Completed: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
        print("=" * 80)

        return result.returncode

    except Exception as e:
        print(f"\nv{prompt_version} execution: ✗ ERROR: {e}")
        print("=" * 80)
        return 1


def _run_version_wrapper(version: int, cluster_names: List[str]):
    """Wrapper function for multiprocessing - must be top-level for pickle."""
    sys.exit(run_version_execution(version, cluster_names))


def run_cleanup_docker():
    """Execute cleanup_docker.sh to clean up Docker containers and processes."""
    print("\n" + "=" * 80)
    print("DOCKER CLEANUP")
    print("=" * 80)

    cleanup_script = Path(__file__).parent.parent / "cleanup_docker.sh"

    if not cleanup_script.exists():
        print(f"Warning: Cleanup script not found at {cleanup_script}")
        return

    try:
        result = subprocess.run(
            ['bash', str(cleanup_script)],
            cwd=cleanup_script.parent,
        )

        if result.returncode == 0:
            print("✓ Docker cleanup completed successfully")
        else:
            print(f"⚠ Docker cleanup finished with code {result.returncode}")

    except Exception as e:
        print(f"✗ Docker cleanup failed: {e}")

    print("=" * 80)


def analyze_missing_executions():
    """Analyze and display what needs to be executed."""
    print("=" * 80)
    print("ANALYSIS OF MISSING JAVASCRIPT EXECUTIONS (v3 and v4)")
    print("=" * 80)
    print(f"Analysis time: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print()

    total_missing = 0

    for version in [3, 4]:
        clusters, missing_counts = get_clusters_needing_execution(version)
        total_missing_for_version = sum(missing_counts.values())
        total_missing += total_missing_for_version

        print(f"Prompt Version {version}:")
        print(f"  Clusters needing execution: {len(clusters)}")
        print(f"  Total missing (entry, llm_type, exec_num) combinations: {total_missing_for_version}")

        if clusters:
            print(f"  Top 10 clusters by missing count:")
            # Sort by missing count
            sorted_clusters = sorted(clusters, key=lambda c: missing_counts[c], reverse=True)
            for name in sorted_clusters[:10]:
                print(f"    - {name}: {missing_counts[name]} missing")
            if len(sorted_clusters) > 10:
                print(f"    ... and {len(sorted_clusters) - 10} more clusters")
        print()

    print(f"TOTAL MISSING ACROSS v3 AND v4: {total_missing}")
    print("=" * 80)


def main():
    parser = argparse.ArgumentParser(
        description="Parallel JavaScript LLM Executor for v3 and v4"
    )
    parser.add_argument(
        '--analyze',
        action='store_true',
        help='Only analyze what needs to be executed (no actual execution)'
    )
    parser.add_argument(
        '--dry-run',
        action='store_true',
        help='Show commands that would be executed without running them'
    )
    parser.add_argument(
        '--version',
        type=int,
        choices=[3, 4],
        help='Execute only a specific version (3 or 4)'
    )

    args = parser.parse_args()

    # Analysis mode
    if args.analyze:
        analyze_missing_executions()
        return 0

    print("=" * 80)
    print("PARALLEL JAVASCRIPT LLM EXECUTION (v3 & v4)")
    print("=" * 80)
    print(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print()

    # Get clusters needing execution for each version
    if args.version:
        versions_to_run = [args.version]
    else:
        versions_to_run = [3, 4]

    version_clusters = {}
    for version in versions_to_run:
        clusters, missing_counts = get_clusters_needing_execution(version)
        version_clusters[version] = clusters

        print(f"Version {version}:")
        print(f"  Clusters needing execution: {len(clusters)}")
        total_missing = sum(missing_counts.values())
        print(f"  Total missing combinations: {total_missing}")
        print()

    # Dry run mode
    if args.dry_run:
        print("DRY RUN - Commands that would be executed:")
        print()
        for version in versions_to_run:
            clusters = version_clusters[version]
            if clusters:
                container_prefix = f"test_runner_v{version}"
                cmd = [
                    'python3', '../run_tests_on_cluster.py',
                    '--languages', 'javascript',
                    '--run-quantity', '5',
                    '--llm-only',
                    '--prompt-version', str(version),
                    '--container-prefix', container_prefix,
                    '--cluster-names'
                ] + clusters
                print(f"v{version}: {' '.join(cmd[:12])}... [+{len(clusters)} cluster names]")
            else:
                print(f"v{version}: No execution needed")
        print()
        print("Cleanup: bash cleanup_docker.sh")
        return 0

    # Check if there's anything to execute
    total_clusters = sum(len(clusters) for clusters in version_clusters.values())
    if total_clusters == 0:
        print("✓ All JavaScript entries already have valid results for v3 and v4!")
        print("No execution needed.")
        return 0

    # Execute versions
    results = {}

    if len(versions_to_run) == 2:
        # Parallel execution of v3 and v4
        print("Starting parallel execution of v3 and v4...")
        print("Note: Each version runs in its own process to avoid resource conflicts.")
        print()

        processes = []

        for version in versions_to_run:
            clusters = version_clusters[version]
            if clusters:
                p = mp.Process(
                    target=_run_version_wrapper,
                    args=(version, clusters)
                )
                p.start()
                processes.append((version, p))
                print(f"Started v{version} process (PID: {p.pid})")

        print()
        print("Waiting for all processes to complete...")
        print("Monitor progress in the output above.")
        print()

        # Wait for all processes
        for version, p in processes:
            p.join()
            results[version] = p.exitcode
            print(f"v{version} completed with exit code {p.exitcode}")

    else:
        # Single version execution
        version = versions_to_run[0]
        clusters = version_clusters[version]
        if clusters:
            results[version] = run_version_execution(version, clusters)
        else:
            print(f"✓ No clusters need execution for v{version}")
            results[version] = 0

    # Summary
    print()
    print("=" * 80)
    print("EXECUTION SUMMARY")
    print("=" * 80)

    all_success = True
    for version, exitcode in results.items():
        status = "✓ SUCCESS" if exitcode == 0 else f"✗ FAILED (code {exitcode})"
        print(f"  v{version}: {status}")
        if exitcode != 0:
            all_success = False

    print()

    # Run Docker cleanup
    run_cleanup_docker()

    print()
    print("=" * 80)
    print("PARALLEL EXECUTION COMPLETE")
    print("=" * 80)
    print(f"Completed: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")

    if all_success:
        print("✓ All executions completed successfully!")
    else:
        print("⚠ Some executions failed. Check logs above for details.")

    return 0 if all_success else 1


if __name__ == '__main__':
    sys.exit(main())
