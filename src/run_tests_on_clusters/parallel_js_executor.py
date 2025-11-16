#!/usr/bin/env python3
"""
Parallel JavaScript Test Executor with Docker Container Management

Features:
- Multi-process parallelization (NOT threading due to GIL)
- Unique container names to avoid conflicts
- Intelligent batching and resource management
- Progress tracking and error handling
- NO timeout limits on individual executions
"""

import json
import subprocess
import multiprocessing as mp
import time
import os
import sys
from datetime import datetime
from pathlib import Path
from collections import defaultdict
import signal

class ParallelExecutor:
    def __init__(self, max_workers=4):
        """
        Initialize parallel executor

        Args:
            max_workers: Number of parallel processes (default: 4 for balanced CPU/memory)
        """
        self.max_workers = max_workers
        self.results = mp.Manager().dict()
        self.lock = mp.Lock()
        self.start_time = time.time()

    def get_remaining_work(self):
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

        # 1. Add timeout failures from v1 and v2
        for cluster, versions in timeout_failures.items():
            for version in versions:
                work_items.append({
                    'cluster': cluster,
                    'version': version,
                    'priority': 1  # High priority - these already failed
                })

        # 2. Add all clusters for v3 and v4
        for cluster in clusters:
            for version in ['v3', 'v4']:
                work_items.append({
                    'cluster': cluster,
                    'version': version,
                    'priority': 2  # Normal priority
                })

        return work_items

    def execute_single_test(self, work_item, worker_id):
        """
        Execute a single cluster+version test

        Args:
            work_item: Dict with cluster, version, priority
            worker_id: Unique worker identifier for container naming
        """
        cluster = work_item['cluster']
        version = work_item['version']
        ver_num = version.replace('v', '')

        # Create unique container prefix using worker_id and timestamp
        # This prevents container name conflicts
        container_prefix = f"js_worker{worker_id}_{int(time.time()*1000) % 1000000}"

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

        # Set environment variable for unique container naming
        env = os.environ.copy()
        env['CONTAINER_PREFIX'] = container_prefix

        start = time.time()

        try:
            # NO TIMEOUT - critical fix
            result = subprocess.run(
                cmd,
                capture_output=True,
                text=True,
                env=env
                # NO timeout parameter!
            )

            elapsed = time.time() - start
            success = result.returncode == 0

            return {
                'cluster': cluster,
                'version': version,
                'success': success,
                'elapsed': elapsed,
                'exit_code': result.returncode,
                'worker_id': worker_id
            }

        except Exception as e:
            elapsed = time.time() - start
            return {
                'cluster': cluster,
                'version': version,
                'success': False,
                'elapsed': elapsed,
                'error': str(e),
                'worker_id': worker_id
            }

    def worker_process(self, work_queue, result_queue, worker_id):
        """Worker process that executes tests from queue"""
        while True:
            try:
                work_item = work_queue.get(timeout=1)
                if work_item is None:  # Poison pill
                    break

                result = self.execute_single_test(work_item, worker_id)
                result_queue.put(result)

            except Exception as e:
                if 'Empty' not in str(type(e)):
                    print(f"Worker {worker_id} error: {e}")
                break

    def run_parallel(self, work_items):
        """Execute work items in parallel using multiprocessing"""
        print("="*80)
        print("PARALLEL JAVASCRIPT EXECUTION")
        print("="*80)
        print(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
        print(f"Workers: {self.max_workers}")
        print(f"Total tasks: {len(work_items)}")
        print()

        # Sort by priority (timeout failures first)
        work_items.sort(key=lambda x: x['priority'])

        # Create queues
        work_queue = mp.Queue()
        result_queue = mp.Queue()

        # Add work items to queue
        for item in work_items:
            work_queue.put(item)

        # Add poison pills for workers
        for _ in range(self.max_workers):
            work_queue.put(None)

        # Start workers
        workers = []
        for i in range(self.max_workers):
            p = mp.Process(
                target=self.worker_process,
                args=(work_queue, result_queue, i)
            )
            p.start()
            workers.append(p)

        # Collect results
        completed = 0
        success_count = 0
        failed_count = 0

        results_log = open('parallel_execution.log', 'w', buffering=1)

        while completed < len(work_items):
            try:
                result = result_queue.get(timeout=10)
                completed += 1

                if result['success']:
                    success_count += 1
                    status = "✓"
                else:
                    failed_count += 1
                    status = "✗"

                elapsed_total = time.time() - self.start_time
                progress = completed * 100 / len(work_items)

                msg = (f"[{datetime.now().strftime('%H:%M:%S')}] "
                       f"[{completed}/{len(work_items)} {progress:.1f}%] "
                       f"{status} {result['cluster']} {result['version']} "
                       f"({result['elapsed']:.1f}s) "
                       f"| Total: {int(elapsed_total/60)}min | "
                       f"Success: {success_count}/{completed}")

                print(msg)
                results_log.write(msg + '\n')

                # Save failed attempts
                if not result['success']:
                    error_file = Path(f"errors/parallel_{result['cluster']}_{result['version']}_error.log")
                    error_file.parent.mkdir(exist_ok=True)
                    with open(error_file, 'w') as f:
                        f.write(f"Cluster: {result['cluster']}\n")
                        f.write(f"Version: {result['version']}\n")
                        f.write(f"Worker: {result['worker_id']}\n")
                        f.write(f"Exit code: {result.get('exit_code', 'N/A')}\n")
                        f.write(f"Error: {result.get('error', 'N/A')}\n")

            except Exception as e:
                if 'Empty' not in str(type(e)):
                    print(f"Result collection error: {e}")

        # Wait for all workers to finish
        for p in workers:
            p.join(timeout=30)
            if p.is_alive():
                p.terminate()

        results_log.close()

        # Final summary
        total_time = time.time() - self.start_time

        print("\n" + "="*80)
        print("PARALLEL EXECUTION COMPLETED")
        print("="*80)
        print(f"Total tasks: {len(work_items)}")
        print(f"  ✓ Success: {success_count} ({success_count*100//len(work_items)}%)")
        print(f"  ✗ Failed: {failed_count}")
        print(f"Total time: {int(total_time/60)} minutes {int(total_time%60)} seconds")
        print(f"Average: {total_time/len(work_items):.1f}s per task")
        print(f"Completed: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
        print("="*80)

        return failed_count == 0

def main():
    # Determine optimal worker count
    # Conservative: 4 workers to avoid overwhelming Docker/system
    # Each worker runs 1 container at a time with unique naming
    cpu_count = mp.cpu_count()
    max_workers = min(4, cpu_count)  # Cap at 4 for stability

    print(f"System CPUs: {cpu_count}")
    print(f"Using {max_workers} parallel workers")
    print()

    executor = ParallelExecutor(max_workers=max_workers)

    # Get remaining work
    work_items = executor.get_remaining_work()

    if not work_items:
        print("✓ No work remaining!")
        return 0

    print(f"Total work items: {len(work_items)}")

    # Estimate time
    # Assuming ~30-45 seconds per task with 4 workers
    estimated_minutes = (len(work_items) * 40) / (max_workers * 60)
    print(f"Estimated completion: ~{int(estimated_minutes)} minutes ({estimated_minutes/60:.1f} hours)")
    print()

    user_input = input("Start parallel execution? (y/n): ")
    if user_input.lower() != 'y':
        print("Cancelled by user")
        return 1

    success = executor.run_parallel(work_items)

    return 0 if success else 1

if __name__ == '__main__':
    # Handle Ctrl+C gracefully
    def signal_handler(sig, frame):
        print('\n\nExecution interrupted by user')
        sys.exit(1)

    signal.signal(signal.SIGINT, signal_handler)

    sys.exit(main())
