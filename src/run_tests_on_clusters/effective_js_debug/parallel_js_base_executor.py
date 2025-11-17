#!/usr/bin/env python3
"""
Parallel JavaScript Base Code Executor

This script executes JavaScript base code from clusters, specifically targeting
clusters that are missing JavaScript base code results. It performs the following:
1. Identifies JS clusters that need base code execution
2. Checks both execution_outputs and backup_executions for existing valid base results
3. Executes missing base code using run_tests_on_cluster.py
4. Restores results from backup if available
5. Calls cleanup_docker.sh at the end

Usage:
    python3 parallel_js_base_executor.py
    python3 parallel_js_base_executor.py --analyze  # Only show what needs execution
    python3 parallel_js_base_executor.py --dry-run  # Show commands without executing
"""

import json
import subprocess
import sys
import os
import argparse
from datetime import datetime
from pathlib import Path
from typing import Dict, List, Tuple


# Add parent directory to path for imports
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", ".."))
from utility_dir import utility_paths


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


def is_valid_base_result(entry: dict) -> bool:
    """Check if a base result has all valid metrics."""
    return (entry.get('execution_time_ms') is not None and
            entry.get('CPU_usage') is not None and
            entry.get('RAM_usage') is not None and
            entry.get('RAM_usage') != 0 and
            entry.get('execution_time_ms', 0) > 0)


def copy_backup_result_to_outputs(
    cluster_name: str,
    entry_id: str,
    exec_number: int,
    backup_entry_data: dict
) -> bool:
    """
    Copy a valid backup base result to the execution_outputs file.

    Args:
        cluster_name: Name of the cluster
        entry_id: ID of the entry
        exec_number: Execution number (1-5)
        backup_entry_data: The entry data from the backup file

    Returns:
        True if successfully copied, False otherwise.
    """
    outputs_dir = utility_paths.OUTPUT_DIR_FILEPATH
    result_file = outputs_dir / f"{cluster_name}_results_{exec_number}.json"

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
                    "test_type": "base"
                },
                "results": {}
            }

        # Ensure results structure exists
        if 'results' not in output_data:
            output_data['results'] = {}
        if 'javascript' not in output_data['results']:
            output_data['results']['javascript'] = []

        # Check if this entry_id already exists
        found = False
        for existing_entry in output_data['results']['javascript']:
            if existing_entry.get('id') == entry_id:
                # Already exists, don't overwrite
                found = True
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


def check_entry_has_valid_base_results(
    cluster_name: str,
    entry_id: str,
    exec_number: int
) -> bool:
    """
    Check if an entry has valid base results for a specific execution.

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
    result_file = outputs_dir / f"{cluster_name}_results_{exec_number}.json"
    found_in_outputs = False

    if result_file.exists():
        try:
            with open(result_file, 'r') as f:
                data = json.load(f)
                if 'results' in data and 'javascript' in data['results']:
                    for entry in data['results']['javascript']:
                        if entry.get('id') == entry_id:
                            if is_valid_base_result(entry):
                                found_in_outputs = True
                                return True
        except Exception:
            pass

    # Check 2: Look in backup_executions
    # Pattern: {cluster_name}_results_{exec_number}_backup_*.json
    backup_pattern = f"{cluster_name}_results_{exec_number}_backup_*.json"

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
                            if is_valid_base_result(entry):
                                # Valid result found in backup but not in outputs
                                # Copy it to the output file
                                if not found_in_outputs:
                                    if copy_backup_result_to_outputs(
                                        cluster_name, entry_id, exec_number, entry
                                    ):
                                        print(f"    Restored from backup: {entry_id} exec#{exec_number}")
                                return True
        except Exception:
            pass

    return False


def get_clusters_needing_base_execution() -> Tuple[List[str], Dict[str, int]]:
    """
    Get clusters that need base code execution.

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

        # Check each entry for base code results across all 5 executions
        for entry in js_entries:
            entry_id = entry.get('id')

            # Check all 5 executions
            for exec_num in range(1, 6):
                if not check_entry_has_valid_base_results(
                    cluster_name, entry_id, exec_num
                ):
                    missing_count += 1

        if missing_count > 0:
            clusters_to_execute.append(cluster_name)
            cluster_missing_counts[cluster_name] = missing_count

    return clusters_to_execute, cluster_missing_counts


def run_base_execution(cluster_names: List[str]) -> int:
    """
    Execute base code for all specified clusters using run_tests_on_cluster.py.

    Args:
        cluster_names: List of cluster names to execute

    Returns:
        Exit code (0 for success, non-zero for failure)
    """
    print("=" * 80)
    print("JAVASCRIPT BASE CODE EXECUTION")
    print("=" * 80)
    print(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print(f"Clusters to process: {len(cluster_names)}")
    print()

    if not cluster_names:
        print("✓ No clusters need base code execution!")
        return 0

    # List clusters
    print("Clusters:")
    for i, name in enumerate(cluster_names[:20], 1):
        print(f"  {i}. {name}")
    if len(cluster_names) > 20:
        print(f"  ... and {len(cluster_names) - 20} more")
    print()

    # Build command using --cluster-names with force-missing-language-entries flag
    container_prefix = "test_runner_js_base"
    cmd = [
        'python3', '../run_tests_on_cluster.py',
        '--base-only',
        '--languages', 'javascript',
        '--run-quantity', '5',
        '--force-missing-language-entries',  # CRITICAL: Force execution of missing JS entries
        '--container-prefix', container_prefix,
        '--cluster-names'
    ] + cluster_names

    print("Executing command:")
    print(f"  {' '.join(cmd[:10])}... [+{len(cluster_names)} cluster names]")
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
        print(f"\nBase code execution: {status}")
        print(f"Completed: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
        print("=" * 80)

        return result.returncode

    except Exception as e:
        print(f"\nBase code execution: ✗ ERROR: {e}")
        print("=" * 80)
        return 1


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
    print("ANALYSIS OF MISSING JAVASCRIPT BASE CODE EXECUTIONS")
    print("=" * 80)
    print(f"Analysis time: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print()

    clusters, missing_counts = get_clusters_needing_base_execution()
    total_missing = sum(missing_counts.values())

    print(f"Clusters needing base code execution: {len(clusters)}")
    print(f"Total missing (entry, exec_num) combinations: {total_missing}")
    print()

    if clusters:
        print("Top 20 clusters by missing count:")
        # Sort by missing count
        sorted_clusters = sorted(clusters, key=lambda c: missing_counts[c], reverse=True)
        for i, name in enumerate(sorted_clusters[:20], 1):
            print(f"  {i:2d}. {name}: {missing_counts[name]} missing")
        if len(sorted_clusters) > 20:
            print(f"  ... and {len(sorted_clusters) - 20} more clusters")

    print()
    print("=" * 80)


def main():
    parser = argparse.ArgumentParser(
        description="JavaScript Base Code Executor with Backup Restoration"
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

    args = parser.parse_args()

    # Analysis mode
    if args.analyze:
        analyze_missing_executions()
        return 0

    print("=" * 80)
    print("JAVASCRIPT BASE CODE EXECUTION WITH BACKUP RESTORATION")
    print("=" * 80)
    print(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print()

    # Get clusters needing execution
    clusters, missing_counts = get_clusters_needing_base_execution()
    total_missing = sum(missing_counts.values())

    print(f"Clusters needing base code execution: {len(clusters)}")
    print(f"Total missing combinations: {total_missing}")
    print()

    # Dry run mode
    if args.dry_run:
        print("DRY RUN - Command that would be executed:")
        print()
        if clusters:
            container_prefix = "test_runner_js_base"
            cmd = [
                'python3', '../run_tests_on_cluster.py',
                '--base-only',
                '--languages', 'javascript',
                '--run-quantity', '5',
                '--force-missing-language-entries',
                '--container-prefix', container_prefix,
                '--cluster-names'
            ] + clusters
            print(f"{' '.join(cmd[:10])}... [+{len(clusters)} cluster names]")
        else:
            print("No execution needed")
        print()
        print("Cleanup: bash cleanup_docker.sh")
        return 0

    # Check if there's anything to execute
    if len(clusters) == 0:
        print("✓ All JavaScript base code entries already have valid results!")
        print("No execution needed.")
        return 0

    # Execute base code
    exitcode = run_base_execution(clusters)

    # Run Docker cleanup
    run_cleanup_docker()

    print()
    print("=" * 80)
    print("BASE CODE EXECUTION COMPLETE")
    print("=" * 80)
    print(f"Completed: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")

    if exitcode == 0:
        print("✓ Execution completed successfully!")
    else:
        print("⚠ Execution failed. Check logs above for details.")

    return exitcode


if __name__ == '__main__':
    sys.exit(main())
