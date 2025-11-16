#!/usr/bin/env python3
"""
Monitor LLM execution and track timeout failures.
After completion, re-execute only failed clusters WITHOUT timeout.
"""

import json
import subprocess
import sys
import time
import re
from pathlib import Path
from datetime import datetime
from collections import defaultdict

class TimeoutMonitor:
    def __init__(self, log_file='full_js_llm_all_rerun.log', pid_file='js_llm_rerun.pid'):
        self.log_file = Path(log_file)
        self.pid_file = Path(pid_file)
        self.timeout_failures = defaultdict(list)  # {cluster: [versions]}
        self.all_failures = defaultdict(list)

    def monitor_execution(self, check_interval=60):
        """Monitor the running LLM execution"""
        print("="*80)
        print("TIMEOUT MONITOR - JavaScript LLM Execution")
        print("="*80)
        print(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
        print(f"Log file: {self.log_file}")
        print(f"Check interval: {check_interval} seconds")
        print()

        last_size = 0

        while True:
            # Check if process is still running
            try:
                with open(self.pid_file) as f:
                    pid = int(f.read().strip())

                result = subprocess.run(['ps', '-p', str(pid)], capture_output=True)
                process_running = result.returncode == 0

            except (FileNotFoundError, ValueError):
                process_running = False

            # Parse log for timeout failures
            if self.log_file.exists():
                current_size = self.log_file.stat().st_size

                if current_size != last_size:
                    self.parse_log()
                    last_size = current_size

                    # Show current status
                    total_timeouts = sum(len(v) for v in self.timeout_failures.values())
                    total_failures = sum(len(v) for v in self.all_failures.values())

                    if total_timeouts > 0 or total_failures > 0:
                        print(f"\r[{datetime.now().strftime('%H:%M:%S')}] "
                              f"Timeout failures: {total_timeouts} | "
                              f"Other failures: {total_failures - total_timeouts}",
                              end='', flush=True)

            # Check for completion
            if not process_running:
                print(f"\n\n✓ Main execution completed at {datetime.now().strftime('%H:%M:%S')}")
                break

            time.sleep(check_interval)

        return self.timeout_failures, self.all_failures

    def parse_log(self):
        """Parse log file to identify timeout and other failures"""
        try:
            with open(self.log_file, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()

            # Pattern: [HH:MM:SS] [N/103] vX - Processing: cluster_name
            #          ✗ Timeout (>15 min)
            # or
            #          ✗ Failed (exit code: X)

            lines = content.split('\n')
            current_cluster = None
            current_version = None

            for i, line in enumerate(lines):
                # Detect cluster being processed
                match = re.search(r'\[(v\d+)\] - Processing: (\w+)', line)
                if match:
                    current_version = match.group(1)
                    current_cluster = match.group(2)
                    continue

                # Detect timeout failure
                if '✗ Timeout' in line and current_cluster and current_version:
                    if current_version not in self.timeout_failures[current_cluster]:
                        self.timeout_failures[current_cluster].append(current_version)
                    if current_version not in self.all_failures[current_cluster]:
                        self.all_failures[current_cluster].append(current_version)
                    current_cluster = None
                    current_version = None

                # Detect other failures
                elif '✗ Failed' in line and current_cluster and current_version:
                    if current_version not in self.all_failures[current_cluster]:
                        self.all_failures[current_cluster].append(current_version)
                    current_cluster = None
                    current_version = None

        except Exception as e:
            print(f"\nWarning: Error parsing log: {e}")

    def print_timeout_report(self):
        """Print detailed report of timeout failures"""
        print("\n" + "="*80)
        print("TIMEOUT FAILURES REPORT")
        print("="*80)

        if not self.timeout_failures:
            print("✓ No timeout failures detected!")
            return

        total_timeouts = sum(len(v) for v in self.timeout_failures.values())
        print(f"Total clusters affected by timeout: {len(self.timeout_failures)}")
        print(f"Total timeout failures: {total_timeouts}")
        print()

        # Group by version
        by_version = defaultdict(list)
        for cluster, versions in sorted(self.timeout_failures.items()):
            for version in versions:
                by_version[version].append(cluster)

        for version in sorted(by_version.keys()):
            clusters = by_version[version]
            print(f"\n{version}: {len(clusters)} clusters")
            for cluster in sorted(clusters):
                print(f"  - {cluster}")

        print("\n" + "="*80)

    def retry_timeout_clusters(self):
        """Re-execute clusters that failed due to timeout WITHOUT timeout limit"""
        if not self.timeout_failures:
            print("\n✓ No timeout failures to retry!")
            return True

        print("\n" + "="*80)
        print("RE-EXECUTING TIMEOUT FAILURES (NO TIMEOUT LIMIT)")
        print("="*80)
        print(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
        print()

        total_retries = sum(len(v) for v in self.timeout_failures.values())
        retry_count = 0
        success_count = 0
        failed_count = 0

        for cluster, versions in sorted(self.timeout_failures.items()):
            for version in sorted(versions):
                retry_count += 1
                ver_num = version.replace('v', '')

                print(f"[{retry_count}/{total_retries}] Retrying {cluster} - {version}")

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
                    # NO TIMEOUT - let it run as long as needed
                    result = subprocess.run(
                        cmd,
                        capture_output=True,
                        text=True
                        # NO timeout parameter!
                    )

                    if result.returncode == 0:
                        print(f"  ✓ Success")
                        success_count += 1
                    else:
                        print(f"  ✗ Failed (exit code: {result.returncode})")
                        failed_count += 1
                        # Log error
                        error_log = Path(f'errors/retry_{cluster}_{version}_error.log')
                        error_log.parent.mkdir(exist_ok=True)
                        with open(error_log, 'w') as f:
                            f.write(f"RETRY FAILED\n")
                            f.write(f"Cluster: {cluster}\n")
                            f.write(f"Version: {version}\n")
                            f.write(f"Exit code: {result.returncode}\n\n")
                            f.write(f"STDOUT:\n{result.stdout}\n\n")
                            f.write(f"STDERR:\n{result.stderr}\n")

                except Exception as e:
                    print(f"  ✗ Error: {e}")
                    failed_count += 1

        print("\n" + "="*80)
        print("RETRY COMPLETED")
        print("="*80)
        print(f"Total retries: {total_retries}")
        print(f"  ✓ Success: {success_count}")
        print(f"  ✗ Failed: {failed_count}")
        print(f"Completed: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
        print("="*80)

        return failed_count == 0

def main():
    monitor = TimeoutMonitor()

    try:
        # Step 1: Monitor ongoing execution
        print("Monitoring LLM execution for timeout failures...")
        print("Press Ctrl+C to stop monitoring and proceed with retry")
        print()

        timeout_failures, all_failures = monitor.monitor_execution()

        # Step 2: Print report
        monitor.print_timeout_report()

        # Step 3: Retry timeout failures
        if timeout_failures:
            user_input = input("\nProceed with retry of timeout failures? (y/n): ")
            if user_input.lower() == 'y':
                success = monitor.retry_timeout_clusters()

                if success:
                    print("\n✅ All timeout failures successfully re-executed!")
                    return 0
                else:
                    print("\n⚠️  Some retries still failed. Check error logs in errors/")
                    return 1
            else:
                print("\nRetry skipped by user")
                return 1
        else:
            print("\n✅ No timeout failures detected - execution completed successfully!")
            return 0

    except KeyboardInterrupt:
        print("\n\n⚠️  Monitoring interrupted by user")
        monitor.print_timeout_report()

        if monitor.timeout_failures:
            print("\nYou can run the retry manually later with this script")

        return 1

    except Exception as e:
        print(f"\n\n❌ Error: {e}")
        import traceback
        traceback.print_exc()
        return 1

if __name__ == '__main__':
    sys.exit(main())
