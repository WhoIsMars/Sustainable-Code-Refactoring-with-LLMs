#!/usr/bin/env python3
"""
Run JavaScript LLM tests for all clusters and all prompt versions.
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
            continue

    return clusters

def run_prompt_version(clusters, prompt_version):
    """Run all clusters for a specific prompt version"""
    print("="*80)
    print(f"PROMPT VERSION: {prompt_version}")
    print("="*80)
    print(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print(f"Total clusters: {len(clusters)}")
    print()

    success_count = 0
    failed_count = 0

    # Extract version number (v1 -> 1)
    ver_num = prompt_version.replace('v', '')

    for i, cluster in enumerate(clusters, 1):
        print(f"[{datetime.now().strftime('%H:%M:%S')}] [{i}/{len(clusters)}] {prompt_version} - Processing: {cluster}")

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

        try:
            result = subprocess.run(
                cmd,
                capture_output=True,
                text=True,
                timeout=900  # 15 minutes per cluster for LLM
            )

            if result.returncode == 0:
                print(f"  ✓ Success")
                success_count += 1
            else:
                print(f"  ✗ Failed (exit code: {result.returncode})")
                failed_count += 1
                # Log error
                error_log = Path(f'errors/cluster_{cluster}_{prompt_version}_error.log')
                error_log.parent.mkdir(exist_ok=True)
                with open(error_log, 'w') as f:
                    f.write(f"STDOUT:\n{result.stdout}\n\n")
                    f.write(f"STDERR:\n{result.stderr}\n")

        except subprocess.TimeoutExpired:
            print(f"  ✗ Timeout (>15 min)")
            failed_count += 1
        except Exception as e:
            print(f"  ✗ Error: {e}")
            failed_count += 1

    print()
    print("-"*80)
    print(f"{prompt_version} COMPLETED")
    print(f"  ✓ Success: {success_count}/{len(clusters)}")
    print(f"  ✗ Failed: {failed_count}/{len(clusters)}")
    print(f"Completed: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print("-"*80)
    print()

    return success_count, failed_count

def main():
    if len(sys.argv) > 1:
        # Run specific prompt version
        prompt_version = sys.argv[1]
        if not prompt_version.startswith('v'):
            prompt_version = f'v{prompt_version}'

        print("="*80)
        print("JAVASCRIPT LLM EXECUTION - SINGLE PROMPT VERSION")
        print("="*80)
        print(f"Prompt version: {prompt_version}")
        print()

        clusters = get_js_clusters()
        success, failed = run_prompt_version(clusters, prompt_version)

        return 0 if failed == 0 else 1

    else:
        # Run all prompt versions
        print("="*80)
        print("JAVASCRIPT LLM EXECUTION - ALL PROMPT VERSIONS")
        print("="*80)
        print(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
        print()

        clusters = get_js_clusters()
        print(f"Found {len(clusters)} JavaScript clusters")
        print()

        total_success = 0
        total_failed = 0

        for pv in ['v1', 'v2', 'v3', 'v4']:
            success, failed = run_prompt_version(clusters, pv)
            total_success += success
            total_failed += failed

        print("="*80)
        print("ALL LLM EXECUTIONS COMPLETED")
        print("="*80)
        print(f"Total clusters per version: {len(clusters)}")
        print(f"Total executions: {len(clusters) * 4}")
        print(f"  ✓ Success: {total_success}")
        print(f"  ✗ Failed: {total_failed}")
        print(f"  Success rate: {total_success*100//(total_success+total_failed) if (total_success+total_failed) > 0 else 0}%")
        print(f"Completed: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
        print("="*80)

        return 0 if total_failed == 0 else 1

if __name__ == '__main__':
    sys.exit(main())
