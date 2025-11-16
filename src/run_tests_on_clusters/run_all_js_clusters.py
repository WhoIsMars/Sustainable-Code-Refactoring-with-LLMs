#!/usr/bin/env python3
"""
Run JavaScript tests for all clusters sequentially.
This replaces the problematic bash loop with a Python loop.
"""

import json
import glob
import subprocess
import sys
from datetime import datetime
from pathlib import Path

def get_js_clusters():
    """Get list of JavaScript clusters"""
    clusters = []
    skip_patterns = ['debug', 'test', 'bad_entries', 'focused_', 'with_metrics']

    clusters_dir = Path('../clusters')

    for f in sorted(clusters_dir.glob('cluster_*.json')):
        # Skip patterns in filename
        if any(skip in f.name for skip in skip_patterns):
            continue

        try:
            with open(f) as fp:
                data = json.load(fp)
                if 'javascript' in data and len(data['javascript']) > 0:
                    cluster_name = f.stem.replace('cluster_', '')
                    # Double-check cluster name
                    if not any(skip in cluster_name for skip in skip_patterns):
                        clusters.append(cluster_name)
        except Exception as e:
            print(f"Warning: Could not process {f}: {e}")
            continue

    return clusters

def main():
    print("="*80)
    print("PYTHON-BASED JAVASCRIPT RE-EXECUTION")
    print("="*80)
    print(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print()

    clusters = get_js_clusters()
    total = len(clusters)

    print(f"Found {total} JavaScript clusters to process")
    print()

    success_count = 0
    failed_count = 0

    for i, cluster in enumerate(clusters, 1):
        print(f"[{datetime.now().strftime('%H:%M:%S')}] [{i}/{total}] Processing cluster: {cluster}")

        cmd = [
            'python3', 'run_tests_on_cluster.py',
            '--languages', 'javascript',
            '--run-quantity', '5',
            '--selective-rerun',
            '--overwrite-results',
            '--cluster-name', cluster,
            '--base-only'
        ]

        try:
            result = subprocess.run(
                cmd,
                capture_output=True,
                text=True,
                timeout=600  # 10 minutes per cluster
            )

            if result.returncode == 0:
                print(f"  ✓ Success")
                success_count += 1
            else:
                print(f"  ✗ Failed (exit code: {result.returncode})")
                failed_count += 1
                # Log error details
                error_log = Path(f'errors/cluster_{cluster}_error.log')
                error_log.parent.mkdir(exist_ok=True)
                with open(error_log, 'w') as f:
                    f.write(f"STDOUT:\n{result.stdout}\n\n")
                    f.write(f"STDERR:\n{result.stderr}\n")

        except subprocess.TimeoutExpired:
            print(f"  ✗ Timeout (>10 min)")
            failed_count += 1
        except Exception as e:
            print(f"  ✗ Error: {e}")
            failed_count += 1

        print()

    print("="*80)
    print("EXECUTION COMPLETED")
    print("="*80)
    print(f"Total clusters: {total}")
    print(f"  ✓ Success: {success_count}")
    print(f"  ✗ Failed: {failed_count}")
    print(f"  Success rate: {success_count*100//total}%")
    print(f"Completed: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print("="*80)

    return 0 if failed_count == 0 else 1

if __name__ == '__main__':
    sys.exit(main())
