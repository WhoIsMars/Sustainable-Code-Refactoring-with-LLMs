#!/usr/bin/env python3
"""
Real-time monitor for parallel execution
Tracks actual file changes in execution_outputs/
"""

import time
import subprocess
import json
import sys
from pathlib import Path
from datetime import datetime
from collections import defaultdict

def count_result_files():
    """Count actual result files that have been updated recently"""
    results_dir = Path('../execution_outputs')

    # Count files modified in last 30 minutes
    recent_threshold = time.time() - 1800  # 30 minutes

    counts = {
        'v1': 0, 'v2': 0, 'v3': 0, 'v4': 0,
        'total': 0,
        'recent': 0
    }

    for f in results_dir.glob('*_results_v*.json'):
        mtime = f.stat().st_mtime

        # Extract version
        for v in ['v1', 'v2', 'v3', 'v4']:
            if f'_results_{v}' in f.name:
                counts[v] += 1
                counts['total'] += 1
                if mtime > recent_threshold:
                    counts['recent'] += 1
                break

    return counts

def count_active_workers():
    """Count active run_tests_on_cluster.py processes"""
    try:
        result = subprocess.run(
            ['ps', 'aux'],
            capture_output=True,
            text=True
        )

        workers = [line for line in result.stdout.split('\n')
                   if 'run_tests_on_cluster.py' in line and 'grep' not in line]

        return len(workers), workers
    except:
        return 0, []

def get_worker_info(workers):
    """Extract cluster names from worker processes"""
    clusters = []
    for w in workers:
        if '--cluster-name' in w:
            parts = w.split('--cluster-name')
            if len(parts) > 1:
                cluster = parts[1].strip().split()[0]
                clusters.append(cluster)
    return clusters

def main():
    print("="*80)
    print("REAL-TIME PARALLEL EXECUTION MONITOR")
    print("="*80)
    print(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print()
    print("Monitoring:")
    print("  - Active worker processes")
    print("  - Result files in ../execution_outputs/")
    print("  - Error files in errors/")
    print()
    print("Press Ctrl+C to stop monitoring")
    print("="*80)
    print()

    start_time = time.time()
    last_total = 0

    try:
        while True:
            # Count active workers
            worker_count, workers = count_active_workers()

            # Count result files
            counts = count_result_files()

            # Count errors
            error_dir = Path('errors')
            error_count = len(list(error_dir.glob('parallel_*.log'))) if error_dir.exists() else 0

            # Calculate progress
            total_tasks = 220
            completed = counts['recent']  # Files modified recently
            elapsed = time.time() - start_time

            # Show new completions
            if completed > last_total:
                print(f"\n✓ {completed - last_total} new tasks completed!")
                last_total = completed

            # Get current clusters being processed
            current_clusters = get_worker_info(workers)

            # Status line
            timestamp = datetime.now().strftime('%H:%M:%S')
            elapsed_min = int(elapsed / 60)

            # Calculate ETA
            if completed > 0:
                rate = completed / elapsed  # tasks per second
                remaining = total_tasks - completed
                eta_seconds = remaining / rate if rate > 0 else 0
                eta_min = int(eta_seconds / 60)
                eta_msg = f"ETA: ~{eta_min}min"
            else:
                eta_msg = "Calculating..."

            status = (
                f"\r[{timestamp}] "
                f"Workers: {worker_count}/6 | "
                f"Completed: {completed}/{total_tasks} ({completed*100//total_tasks if total_tasks > 0 else 0}%) | "
                f"Errors: {error_count} | "
                f"Elapsed: {elapsed_min}min | "
                f"{eta_msg}"
            )

            print(status, end='', flush=True)

            # Show current clusters every 10 seconds
            if int(elapsed) % 10 == 0 and current_clusters:
                print(f"\n  Active: {', '.join(current_clusters[:3])}{' ...' if len(current_clusters) > 3 else ''}", end='')

            # Check if done
            if worker_count == 0 and completed >= total_tasks * 0.95:  # 95% threshold
                print("\n\n✅ Execution appears complete!")
                print(f"   Completed: {completed}/{total_tasks}")
                print(f"   Total time: {elapsed_min} minutes")
                break

            time.sleep(2)

    except KeyboardInterrupt:
        print("\n\nMonitoring stopped by user")
        print(f"\nFinal status:")
        print(f"  Workers active: {worker_count}")
        print(f"  Tasks completed: {completed}/{total_tasks}")
        print(f"  Errors: {error_count}")

    print("\n" + "="*80)
    print("MONITORING COMPLETE")
    print("="*80)

    # Show summary
    print("\nResults by version:")
    for v in ['v1', 'v2', 'v3', 'v4']:
        print(f"  {v}: {counts[v]} files")

    if error_count > 0:
        print(f"\n⚠️  {error_count} errors detected. Check errors/ directory")

if __name__ == '__main__':
    sys.exit(main())
