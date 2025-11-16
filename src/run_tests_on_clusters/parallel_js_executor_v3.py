#!/usr/bin/env python3
"""
Parallel JavaScript Test Executor - V3: Smart Docker Limit

Strategy:
- Use multiprocessing.Pool for parallel execution
- Global semaphore limits TOTAL Docker containers (not workers)
- Each cluster has ~20 entries × 5 runs = ~100 containers potential
- Limit to 20 concurrent Docker containers globally
- This allows ~2-3 workers active at once safely
"""

import json
import subprocess
import multiprocessing as mp
from multiprocessing import Pool, Semaphore, Manager
import time
import sys
from datetime import datetime
from pathlib import Path
import signal
import argparse

# Global semaphore for Docker container limiting
docker_semaphore = None

def init_worker(sem):
    """Initialize worker with shared semaphore"""
    global docker_semaphore
    docker_semaphore = sem
    # Ignore SIGINT in workers (parent will handle it)
    signal.signal(signal.SIGINT, signal.SIG_IGN)

def get_remaining_work():
    """Calculate remaining work: timeouts from v1/v2 + all of v3/v4"""
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

    # Build work list
    work_items = []

    # 1. Add timeout failures from v1 and v2 (high priority)
    for cluster, versions in sorted(timeout_failures.items()):
        for version in sorted(versions):
            work_items.append({
                'cluster': cluster,
                'version': version,
                'priority': 1,
                'type': 'retry'
            })

    # 2. Add all clusters for v3 and v4
    for cluster in sorted(clusters):
        for version in ['v3', 'v4']:
            work_items.append({
                'cluster': cluster,
                'version': version,
                'priority': 2,
                'type': 'new'
            })

    # Sort by priority (retries first, then by cluster name for consistency)
    work_items.sort(key=lambda x: (x['priority'], x['cluster'], x['version']))

    return work_items

def execute_test_with_docker_limit(work_item):
    """
    Execute a single test with intelligent Docker container limiting

    The key insight: We don't limit at the worker level, but at the
    Docker container level. Each cluster run creates ~20 entries × 5 runs
    = ~100 containers. We acquire the semaphore BEFORE running the cluster
    and hold it for the entire cluster execution.

    This ensures we never have more than N clusters running simultaneously,
    which limits total Docker containers to N × 100 max.
    """
    cluster = work_item['cluster']
    version = work_item['version']
    ver_num = version.replace('v', '')

    start = time.time()

    # CRITICAL: Acquire semaphore BEFORE starting cluster execution
    # This limits concurrent CLUSTERS, not workers
    global docker_semaphore
    if docker_semaphore:
        docker_semaphore.acquire()

    try:
        cmd = [
            'python3', 'run_tests_on_cluster.py',
            '--languages', 'javascript',
            '--run-quantity', '5',
            '--selective-rerun',
            '--overwrite-results',
            '--cluster-name', cluster,
            '--llm-only',
            '--prompt-version', ver_num
        ]

        # Execute WITHOUT timeout - let it complete
        result = subprocess.run(
            cmd,
            capture_output=True,
            text=True
        )

        elapsed = time.time() - start
        success = result.returncode == 0

        return {
            'cluster': cluster,
            'version': version,
            'type': work_item['type'],
            'success': success,
            'elapsed': elapsed,
            'exit_code': result.returncode,
            'stdout_tail': result.stdout[-500:] if result.stdout else '',
            'stderr_tail': result.stderr[-500:] if result.stderr else ''
        }

    except Exception as e:
        elapsed = time.time() - start if 'start' in locals() else 0
        return {
            'cluster': cluster,
            'version': version,
            'type': work_item['type'],
            'success': False,
            'elapsed': elapsed,
            'error': str(e)
        }

    finally:
        # Release semaphore AFTER cluster completes
        if docker_semaphore:
            docker_semaphore.release()

def log_result(result, completed, total, start_time, log_file):
    """Log a single result"""
    status = "✓" if result['success'] else "✗"
    elapsed_total = time.time() - start_time
    progress = completed * 100 / total

    msg = (f"[{datetime.now().strftime('%H:%M:%S')}] "
           f"[{completed}/{total} {progress:.1f}%] "
           f"{status} {result['cluster']} {result['version']} "
           f"({result['elapsed']:.1f}s) "
           f"[{result['type']}] "
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
            f.write(f"Type: {result['type']}\n")
            f.write(f"Exit code: {result.get('exit_code', 'N/A')}\n")
            f.write(f"Elapsed: {result['elapsed']:.1f}s\n")
            f.write(f"\nError: {result.get('error', 'N/A')}\n")
            f.write(f"\nSTDOUT (last 500 chars):\n{result.get('stdout_tail', '')}\n")
            f.write(f"\nSTDERR (last 500 chars):\n{result.get('stderr_tail', '')}\n")

def main():
    parser = argparse.ArgumentParser(description='Parallel JavaScript Test Executor V3')
    parser.add_argument('--yes', '-y', action='store_true',
                       help='Skip confirmation prompt')
    parser.add_argument('--max-concurrent-clusters', type=int, default=3,
                       help='Maximum concurrent clusters (default: 3)')
    args = parser.parse_args()

    print("="*80)
    print("PARALLEL JAVASCRIPT EXECUTION - V3 (Smart Docker Limiting)")
    print("="*80)
    print(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print()

    # Get CPU count
    cpu_count = mp.cpu_count()
    print(f"System CPUs: {cpu_count}")

    # Set max concurrent clusters (conservative to avoid Docker overload)
    max_concurrent_clusters = args.max_concurrent_clusters
    print(f"Max concurrent clusters: {max_concurrent_clusters}")
    print(f"Estimated max Docker containers: ~{max_concurrent_clusters * 20} at peak")
    print()

    # Get work items
    work_items = get_remaining_work()

    if not work_items:
        print("✓ No work remaining!")
        return 0

    # Count by type
    retries = sum(1 for w in work_items if w['type'] == 'retry')
    new_items = sum(1 for w in work_items if w['type'] == 'new')

    print(f"Work Summary:")
    print(f"  Retries (v1/v2 timeouts): {retries}")
    print(f"  New (v3/v4 full):         {new_items}")
    print(f"  TOTAL:                    {len(work_items)}")
    print()

    # Estimate time
    # Average 2-3 minutes per cluster (conservative)
    avg_time_per_cluster = 150  # seconds (2.5 min)
    estimated_seconds = (len(work_items) * avg_time_per_cluster) / max_concurrent_clusters
    estimated_hours = estimated_seconds / 3600

    print(f"Estimated completion time:")
    print(f"  Sequential: ~{len(work_items) * avg_time_per_cluster / 3600:.1f} hours")
    print(f"  Parallel ({max_concurrent_clusters} concurrent): ~{estimated_hours:.1f} hours ({int(estimated_seconds/60)} minutes)")
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
    log_file = open('parallel_execution_v3.log', 'w', buffering=1)

    # Create semaphore for Docker container limiting
    # This limits concurrent CLUSTERS, which indirectly limits Docker containers
    manager = Manager()
    sem = manager.Semaphore(max_concurrent_clusters)

    # Create process pool with MORE workers than semaphore allows
    # Workers will queue up waiting for semaphore
    num_workers = max_concurrent_clusters + 3  # Extra workers to keep pipeline full

    completed = 0
    success_count = 0
    failed_count = 0

    try:
        with Pool(processes=num_workers, initializer=init_worker, initargs=(sem,)) as pool:
            # Use imap_unordered for immediate result processing
            for result in pool.imap_unordered(execute_test_with_docker_limit, work_items):
                completed += 1

                if result['success']:
                    success_count += 1
                else:
                    failed_count += 1

                log_result(result, completed, len(work_items), start_time, log_file)

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
    print(f"Total tasks: {len(work_items)}")
    print(f"  ✓ Success: {success_count} ({success_count*100//len(work_items)}%)")
    print(f"  ✗ Failed: {failed_count}")
    print(f"Total time: {total_minutes}min {total_seconds}s")
    print(f"Average: {total_time/len(work_items):.1f}s per task")
    if max_concurrent_clusters > 1:
        print(f"Speedup: {len(work_items)*avg_time_per_cluster/total_time:.1f}x vs sequential")
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
