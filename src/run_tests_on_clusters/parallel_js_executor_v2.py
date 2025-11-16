#!/usr/bin/env python3
"""
Parallel JavaScript Test Executor - Simplified Approach

Strategy:
- Use multiprocessing.Pool for parallel execution
- Each process runs in isolation with process ID tracking
- Docker containers are ephemeral (--rm flag) so no naming conflicts
- Semaphore to limit concurrent Docker operations
- NO timeout on individual executions
"""

import json
import subprocess
import multiprocessing as mp
from multiprocessing import Pool, Semaphore
import time
import sys
from datetime import datetime
from pathlib import Path
import signal
import argparse

# Global semaphore for Docker rate limiting
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

def execute_test(work_item):
    """
    Execute a single test - designed to run in parallel

    Args:
        work_item: Dict with cluster, version, priority, type

    Returns:
        Dict with execution results
    """
    cluster = work_item['cluster']
    version = work_item['version']
    ver_num = version.replace('v', '')

    # Acquire semaphore to limit concurrent Docker operations
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

        start = time.time()

        # Execute WITHOUT timeout
        result = subprocess.run(
            cmd,
            capture_output=True,
            text=True
            # CRITICAL: NO timeout parameter
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
        # Release semaphore
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
    parser = argparse.ArgumentParser(description='Parallel JavaScript Test Executor')
    parser.add_argument('--yes', '-y', action='store_true',
                       help='Skip confirmation prompt')
    args = parser.parse_args()

    print("="*80)
    print("PARALLEL JAVASCRIPT EXECUTION - V2")
    print("="*80)
    print(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print()

    # Get CPU count and determine worker count
    cpu_count = mp.cpu_count()
    # Use 4 workers for optimal balance (can handle Docker overhead)
    max_workers = min(6, cpu_count - 1) if cpu_count > 4 else 4

    print(f"System CPUs: {cpu_count}")
    print(f"Parallel workers: {max_workers}")
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
    # Realistic: 45-60 seconds per task
    avg_time_per_task = 50  # seconds
    estimated_seconds = (len(work_items) * avg_time_per_task) / max_workers
    estimated_hours = estimated_seconds / 3600

    print(f"Estimated completion time:")
    print(f"  Sequential: ~{len(work_items) * avg_time_per_task / 3600:.1f} hours")
    print(f"  Parallel ({max_workers} workers): ~{estimated_hours:.1f} hours ({int(estimated_seconds/60)} minutes)")
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
    log_file = open('parallel_execution_v2.log', 'w', buffering=1)

    # Create semaphore for Docker rate limiting
    # Limit to max_workers concurrent Docker operations
    sem = Semaphore(max_workers)

    # Create process pool
    completed = 0
    success_count = 0
    failed_count = 0

    try:
        with Pool(processes=max_workers, initializer=init_worker, initargs=(sem,)) as pool:
            # Use imap_unordered for immediate result processing
            for result in pool.imap_unordered(execute_test, work_items):
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
    print(f"Speedup: {len(work_items)*50/total_time:.1f}x vs sequential")
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
