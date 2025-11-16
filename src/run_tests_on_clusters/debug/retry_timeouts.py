#!/usr/bin/env python3
"""
Retry clusters that failed due to timeout WITHOUT any timeout limit.
Reads timeout_failures.json and re-executes each failed cluster+version.
"""

import json
import subprocess
import sys
from datetime import datetime
from pathlib import Path

def load_timeout_failures():
    """Load timeout failures from JSON file"""
    try:
        with open('timeout_failures.json') as f:
            data = json.load(f)
        return data['failures']
    except FileNotFoundError:
        print("Error: timeout_failures.json not found")
        print("Run ./extract_timeout_failures.sh first")
        return {}

def retry_cluster(cluster, version):
    """Retry a single cluster+version WITHOUT timeout"""
    ver_num = version.replace('v', '')

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

    print(f"  Command: python3 run_tests_on_cluster.py --cluster-name {cluster} --prompt-version {ver_num}")

    try:
        # CRITICAL: NO TIMEOUT - let it run as long as needed
        result = subprocess.run(
            cmd,
            capture_output=True,
            text=True
            # NO timeout parameter!
        )

        return result.returncode == 0, result

    except Exception as e:
        print(f"  ✗ Error: {e}")
        return False, None

def main():
    print("="*80)
    print("RETRY TIMEOUT FAILURES (NO TIMEOUT LIMIT)")
    print("="*80)
    print(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print()

    # Load failures
    failures = load_timeout_failures()

    if not failures:
        print("✓ No timeout failures to retry")
        return 0

    total_retries = sum(len(versions) for versions in failures.values())
    print(f"Total timeout failures: {total_retries}")
    print(f"Clusters affected: {len(failures)}")
    print()

    # Show what will be retried
    print("Clusters to retry:")
    for cluster, versions in sorted(failures.items()):
        print(f"  - {cluster}: {', '.join(versions)}")
    print()

    user_input = input("Proceed with retry? (y/n): ")
    if user_input.lower() != 'y':
        print("Retry cancelled by user")
        return 1

    print("\n" + "="*80)
    print("STARTING RETRIES")
    print("="*80)
    print()

    retry_count = 0
    success_count = 0
    failed_count = 0

    retry_log = open('retry_timeouts.log', 'w', buffering=1)  # Line buffered

    for cluster, versions in sorted(failures.items()):
        for version in sorted(versions):
            retry_count += 1

            timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
            print(f"[{timestamp}] [{retry_count}/{total_retries}] Retrying {cluster} - {version}")
            retry_log.write(f"[{timestamp}] [{retry_count}/{total_retries}] Retrying {cluster} - {version}\n")

            success, result = retry_cluster(cluster, version)

            if success:
                print(f"  ✓ Success")
                retry_log.write(f"  ✓ Success\n")
                success_count += 1
            else:
                print(f"  ✗ Failed")
                retry_log.write(f"  ✗ Failed\n")
                failed_count += 1

                # Save error details
                if result:
                    error_file = Path(f'errors/retry_{cluster}_{version}_error.log')
                    error_file.parent.mkdir(exist_ok=True)
                    with open(error_file, 'w') as f:
                        f.write(f"RETRY FAILED\n")
                        f.write(f"Cluster: {cluster}\n")
                        f.write(f"Version: {version}\n")
                        f.write(f"Exit code: {result.returncode}\n\n")
                        f.write(f"STDOUT:\n{result.stdout}\n\n")
                        f.write(f"STDERR:\n{result.stderr}\n")
                    print(f"  Error details saved to: {error_file}")
                    retry_log.write(f"  Error details saved to: {error_file}\n")

            print()
            retry_log.write("\n")

    retry_log.close()

    print("="*80)
    print("RETRY COMPLETED")
    print("="*80)
    print(f"Total retries: {total_retries}")
    print(f"  ✓ Success: {success_count}")
    print(f"  ✗ Failed: {failed_count}")
    print(f"  Success rate: {success_count*100//total_retries if total_retries > 0 else 0}%")
    print(f"Completed: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print("="*80)
    print()

    if failed_count == 0:
        print("✅ All timeout failures successfully re-executed!")
        return 0
    else:
        print(f"⚠️  {failed_count} retries still failed. Check error logs in errors/")
        return 1

if __name__ == '__main__':
    sys.exit(main())
