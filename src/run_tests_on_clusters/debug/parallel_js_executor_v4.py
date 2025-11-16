#!/usr/bin/env python3
"""
Parallel JavaScript Test Executor - V4: Cluster-based Parallelization

Strategy:
- Divide clusters among N parallel processes
- Each process handles ALL versions (v1/v2/v3/v4) of its assigned clusters
- This ensures: N processes = max N Docker containers at any time
- No container conflicts since each process works on different clusters
"""

import json
import subprocess
import multiprocessing as mp
from multiprocessing import Pool
import time
import sys
from datetime import datetime
from pathlib import Path
import signal
import argparse

def init_worker():
    """Initialize worker"""
    # Ignore SIGINT in workers (parent will handle it)
    signal.signal(signal.SIGINT, signal.SIG_IGN)

def get_clusters_and_versions():
    """Get all clusters and determine which versions need execution"""
    # Load timeout failures
    timeout_failures = {}
    try:
        with open('timeout_failures.json') as f:
            data = json.load(f)
            timeout_failures = data['failures']
    except FileNotFoundError:
        pass

    # Get all JS clusters
    clusters = []
    skip_patterns = ['debug', 'test', 'bad_entries', 'focused_', 'with_metrics']
    clusters_dir = Path('../clusters')

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
        except:
            continue

    # Build cluster->versions mapping
    cluster_versions = {}

    for cluster in sorted(clusters):
        versions_needed = []

        # Check if this cluster had timeouts in v1/v2
        if cluster in timeout_failures:
            for v in timeout_failures[cluster]:
                versions_needed.append(v)

        # Always add v3 and v4
        versions_needed.extend(['v3', 'v4'])

        cluster_versions[cluster] = sorted(set(versions_needed))

    return cluster_versions

def execute_cluster_all_versions(cluster_name, versions):
    """
    Execute ALL versions of a single cluster sequentially

    This is the key: each worker process handles one cluster at a time,
    running all its versions sequentially. This ensures only ONE Docker
    container per worker process at any given time.

    Args:
        cluster_name: Name of cluster to process
        versions: List of versions to execute (e.g., ['v1', 'v2', 'v3', 'v4'])

    Returns:
        List of results, one per version
    """
    results = []

    for version in versions:
        ver_num = version.replace('v', '')
        start = time.time()

        try:
            cmd = [
                'python3', 'run_tests_on_cluster.py',
                '--languages', 'javascript',
                '--run-quantity', '5',
                '--selective-rerun',
                '--overwrite-results',
                '--cluster-name', cluster_name,
                '--llm-only',
                '--prompt-version', ver_num
            ]

            # Execute WITHOUT timeout
            result = subprocess.run(
                cmd,
                capture_output=True,
                text=True
            )

            elapsed = time.time() - start
            success = result.returncode == 0

            results.append({
                'cluster': cluster_name,
                'version': version,
                'success': success,
                'elapsed': elapsed,
                'exit_code': result.returncode,
                'stdout_tail': result.stdout[-500:] if result.stdout else '',
                'stderr_tail': result.stderr[-500:] if result.stderr else ''
            })

        except Exception as e:
            elapsed = time.time() - start if 'start' in locals() else 0
            results.append({
                'cluster': cluster_name,
                'version': version,
                'success': False,
                'elapsed': elapsed,
                'error': str(e)
            })

    return results

def worker_task(work_item):
    """
    Worker task: process one cluster with all its versions

    Args:
        work_item: dict with 'cluster' and 'versions' keys

    Returns:
        List of results for all versions of this cluster
    """
    cluster = work_item['cluster']
    versions = work_item['versions']

    return execute_cluster_all_versions(cluster, versions)

def log_result(result, completed_versions, total_versions, start_time, log_file):
    """Log a single version result"""
    status = "✓" if result['success'] else "✗"
    elapsed_total = time.time() - start_time
    progress = completed_versions * 100 / total_versions

    msg = (f"[{datetime.now().strftime('%H:%M:%S')}] "
           f"[{completed_versions}/{total_versions} {progress:.1f}%] "
           f"{status} {result['cluster']} {result['version']} "
           f"({result['elapsed']:.1f}s) "
           f"| Elapsed: {int(elapsed_total/60)}min")

    print(msg)
    log_file.write(msg + '\n')
    log_file.flush()

    # Save errors
    if not result['success']:
        error_file = Path(f"errors/parallel_{result['cluster']}_{result['version']}_error.log")
        error_file.parent.mkdir(exist_ok=True)
        with open(error_file, 'w') as f:
            f.write(f"Cluster: {result['cluster']}\n")
            f.write(f"Version: {result['version']}\n")
            f.write(f"Exit code: {result.get('exit_code', 'N/A')}\n")
            f.write(f"Elapsed: {result['elapsed']:.1f}s\n")
            f.write(f"\nError: {result.get('error', 'N/A')}\n")
            f.write(f"\nSTDOUT (last 500 chars):\n{result.get('stdout_tail', '')}\n")
            f.write(f"\nSTDERR (last 500 chars):\n{result.get('stderr_tail', '')}\n")

def main():
    parser = argparse.ArgumentParser(description='Parallel JavaScript Test Executor V4')
    parser.add_argument('--yes', '-y', action='store_true',
                       help='Skip confirmation prompt')
    parser.add_argument('--workers', '-w', type=int, default=4,
                       help='Number of parallel workers (default: 4)')
    args = parser.parse_args()

    print("="*80)
    print("PARALLEL JAVASCRIPT EXECUTION - V4 (Cluster-based)")
    print("="*80)
    print(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print()

    # Get CPU count
    cpu_count = mp.cpu_count()
    num_workers = min(args.workers, cpu_count - 1) if cpu_count > 2 else 2

    print(f"System CPUs: {cpu_count}")
    print(f"Parallel workers: {num_workers}")
    print(f"Max Docker containers: {num_workers} (one per worker)")
    print()

    # Get cluster-version mappings
    cluster_versions = get_clusters_and_versions()

    if not cluster_versions:
        print("✓ No work remaining!")
        return 0

    # Create work items (one per cluster)
    work_items = []
    total_versions = 0

    for cluster, versions in cluster_versions.items():
        work_items.append({
            'cluster': cluster,
            'versions': versions
        })
        total_versions += len(versions)

    print(f"Work Summary:")
    print(f"  Clusters to process: {len(work_items)}")
    print(f"  Total versions: {total_versions}")
    print(f"  Average versions/cluster: {total_versions/len(work_items):.1f}")
    print()

    # Estimate time
    # Average 2 minutes per version
    avg_time_per_version = 120  # seconds
    estimated_seconds_seq = total_versions * avg_time_per_version
    estimated_seconds_par = estimated_seconds_seq / num_workers
    estimated_hours = estimated_seconds_par / 3600

    print(f"Estimated completion time:")
    print(f"  Sequential: ~{estimated_seconds_seq / 3600:.1f} hours")
    print(f"  Parallel ({num_workers} workers): ~{estimated_hours:.1f} hours ({int(estimated_seconds_par/60)} minutes)")
    print()

    if not args.yes:
        user_input = input("Start parallel execution? (y/n): ")
        if user_input.lower() != 'y':
            print("Cancelled by user")
            return 1
    else:
        print("Auto-starting (--yes flag provided)")

    print("\n" + "="*80)
    print("EXECUTION STARTED")
    print("="*80)
    print()

    start_time = time.time()
    log_file = open('parallel_execution_v4.log', 'w', buffering=1)

    completed_versions = 0
    success_count = 0
    failed_count = 0

    try:
        with Pool(processes=num_workers, initializer=init_worker) as pool:
            # Use imap_unordered for immediate result processing
            # Each result is a LIST of version results for one cluster
            for cluster_results in pool.imap_unordered(worker_task, work_items):
                # Log each version result
                for result in cluster_results:
                    completed_versions += 1

                    if result['success']:
                        success_count += 1
                    else:
                        failed_count += 1

                    log_result(result, completed_versions, total_versions, start_time, log_file)

    except KeyboardInterrupt:
        print("\n\n⚠️  Interrupted by user - waiting for active tasks to complete...")
        pool.terminate()
        pool.join()
        log_file.close()
        return 1

    log_file.close()

    # Final summary
    total_time = time.time() - start_time
    total_minutes = int(total_time / 60)
    total_seconds = int(total_time % 60)

    print("\n" + "="*80)
    print("PARALLEL EXECUTION COMPLETED")
    print("="*80)
    print(f"Clusters processed: {len(work_items)}")
    print(f"Total versions: {total_versions}")
    print(f"  ✓ Success: {success_count} ({success_count*100//total_versions if total_versions > 0 else 0}%)")
    print(f"  ✗ Failed: {failed_count}")
    print(f"Total time: {total_minutes}min {total_seconds}s")
    print(f"Average: {total_time/total_versions:.1f}s per version")
    if num_workers > 1:
        print(f"Speedup: {total_versions*avg_time_per_version/total_time:.1f}x vs sequential")
    print(f"Completed: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print("="*80)
    print()

    if failed_count > 0:
        print(f"⚠️  {failed_count} tasks failed. Check errors/ directory for details")
        return 1
    else:
        print("✅ All tasks completed successfully!")
        return 0

if __name__ == '__main__':
    sys.exit(main())
