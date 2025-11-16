#!/usr/bin/env python3
"""
Smart Monitor for JavaScript Re-Execution

This script:
1. Monitors base code execution in real-time
2. Analyzes errors to distinguish legitimate vs environment issues
3. Generates periodic reports (every 10 clusters)
4. Automatically launches LLM execution after base completes
5. Continues monitoring until all phases complete

Author: Created for JavaScript pass rate investigation
Date: 2025-01-14
"""

import sys
import time
import re
import json
import subprocess
from pathlib import Path
from collections import defaultdict, Counter
from datetime import datetime, timedelta

class SmartMonitor:
    def __init__(self, base_log="full_js_base_rerun.log"):
        self.base_log = Path(base_log)
        self.start_time = time.time()
        self.last_report_cluster = 0
        self.report_interval = 10  # Report every 10 clusters

        # Statistics
        self.stats = {
            'base': {'total': 0, 'success': 0, 'failed': 0, 'entries_passed': 0, 'entries_failed': 0},
            'llm': {'total': 0, 'success': 0, 'failed': 0, 'v1': 0, 'v2': 0, 'v3': 0, 'v4': 0}
        }

        # Error categorization
        self.errors = {
            'legitimate': defaultdict(list),  # Code/test issues (acceptable)
            'environment': defaultdict(list),  # Config issues (need fixing)
            'unknown': []
        }

        # Error patterns
        self.legitimate_patterns = {
            'import_export_mismatch': r'Your test suite must contain at least one test',
            'assertion_failure': r'expect\(.*\)\.to|Expected.*but received',
            'syntax_error': r'SyntaxError:',
            'reference_error': r'ReferenceError:.*is not defined',
            'type_error': r'TypeError:',
            'undefined_function': r'is not a function',
            'module_not_found': r'Cannot find module.*(?!jest)',  # But not jest itself
        }

        self.environment_patterns = {
            'docker_error': r'docker:.*error|Cannot connect to the Docker daemon',
            'permission_error': r'Permission denied|EACCES',
            'npm_install_failure': r'npm ERR!.*code E',
            'jest_config_error': r'Cannot find module.*jest-config',
            'timeout': r'ETIMEDOUT|execution timed out',
            'disk_space': r'ENOSPC|No space left',
        }

        print("="*80)
        print("SMART JAVASCRIPT EXECUTION MONITOR")
        print("="*80)
        print(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
        print(f"Base log: {self.base_log}")
        print(f"Report interval: Every {self.report_interval} clusters")
        print()

    def categorize_error(self, log_content):
        """Categorize error from log content"""
        # Check legitimate patterns
        for category, pattern in self.legitimate_patterns.items():
            if re.search(pattern, log_content, re.IGNORECASE):
                return ('legitimate', category)

        # Check environment patterns
        for category, pattern in self.environment_patterns.items():
            if re.search(pattern, log_content, re.IGNORECASE):
                return ('environment', category)

        return ('unknown', 'unclassified')

    def parse_log(self, log_file):
        """Parse log file and extract statistics"""
        if not log_file.exists():
            return False

        try:
            with open(log_file, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()

            # Count clusters
            success = content.count('✓ Success')
            failed = content.count('✗ Failed')

            # Extract detailed test results
            test_results = re.findall(r'Total tests executed: (\d+).*?Successful tests: (\d+)',
                                     content, re.DOTALL)

            entries_tested = sum(int(total) for total, _ in test_results)
            entries_passed = sum(int(passed) for _, passed in test_results)
            entries_failed = entries_tested - entries_passed

            self.stats['base']['total'] = success + failed
            self.stats['base']['success'] = success
            self.stats['base']['failed'] = failed
            self.stats['base']['entries_passed'] = entries_passed
            self.stats['base']['entries_failed'] = entries_failed

            # Extract errors from detailed log
            if 'javascript_rerun_' in content:
                log_filename = re.search(r'Logging to: (javascript_rerun_\d+_\d+\.log)', content)
                if log_filename:
                    detailed_log = Path(log_filename.group(1))
                    if detailed_log.exists():
                        self._analyze_detailed_errors(detailed_log)

            return True

        except Exception as e:
            print(f"Error parsing log: {e}")
            return False

    def _analyze_detailed_errors(self, log_file):
        """Analyze detailed log for error patterns"""
        try:
            with open(log_file, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()

            # Find error indicators in log
            error_lines = []
            for line in content.split('\n'):
                if any(keyword in line.lower() for keyword in ['error', 'failed', 'exception', 'fail']):
                    error_lines.append(line)

            # Analyze error patterns
            for line in error_lines[:100]:  # Limit to first 100 errors
                error_type, category = self.categorize_error(line)
                if error_type and category:
                    self.errors[error_type][category].append({
                        'entry_id': 'unknown',
                        'context': line[:200]
                    })

        except Exception as e:
            # Silently continue if error analysis fails
            pass

    def print_progress_report(self):
        """Print current progress report"""
        total = self.stats['base']['total']
        success = self.stats['base']['success']
        failed = self.stats['base']['failed']

        elapsed = time.time() - self.start_time
        elapsed_str = str(timedelta(seconds=int(elapsed)))

        print("\n" + "="*80)
        print(f"PROGRESS REPORT - {datetime.now().strftime('%H:%M:%S')}")
        print("="*80)
        print(f"Phase: BASE CODE")
        print(f"Elapsed time: {elapsed_str}")
        print()
        print(f"Clusters: {total}/103 ({total*100//103}%)")
        print(f"  ✓ Success: {success}")
        print(f"  ✗ Failed: {failed}")

        if total > 0:
            cluster_rate = total / (elapsed / 60)  # clusters per minute
            remaining = 103 - total
            eta_minutes = remaining / cluster_rate if cluster_rate > 0 else 0
            eta_str = str(timedelta(minutes=int(eta_minutes)))

            print(f"  Success rate: {success*100//(success+failed) if (success+failed) > 0 else 0}%")
            print(f"  Rate: {cluster_rate:.2f} clusters/min")
            print(f"  ETA: {eta_str}")

        # Entry-level statistics
        entries_passed = self.stats['base']['entries_passed']
        entries_failed = self.stats['base']['entries_failed']
        entries_total = entries_passed + entries_failed

        if entries_total > 0:
            print()
            print(f"Entries tested: {entries_total}")
            print(f"  ✓ Passed: {entries_passed} ({entries_passed*100//entries_total}%)")
            print(f"  ✗ Failed: {entries_failed} ({entries_failed*100//entries_total}%)")

        # Error analysis
        legitimate_count = sum(len(errors) for errors in self.errors['legitimate'].values())
        environment_count = sum(len(errors) for errors in self.errors['environment'].values())
        unknown_count = len(self.errors['unknown'])

        if legitimate_count + environment_count + unknown_count > 0:
            print()
            print("Error Analysis:")
            print(f"  ✅ Legitimate (code issues): {legitimate_count}")
            for category, errors in self.errors['legitimate'].items():
                if errors:
                    print(f"     - {category}: {len(errors)}")

            if environment_count > 0:
                print(f"  ❌ Environment (config issues): {environment_count} ⚠️  NEEDS ATTENTION")
                for category, errors in self.errors['environment'].items():
                    if errors:
                        print(f"     - {category}: {len(errors)}")
                        # Print first example
                        if errors:
                            example = errors[0]
                            print(f"       Example: {example['entry_id']}")

            if unknown_count > 0:
                print(f"  ⚠️  Unknown: {unknown_count}")

        print("="*80)

    def monitor_base(self):
        """Monitor base code execution"""
        print("Monitoring BASE CODE execution...")
        print(f"Waiting for log file: {self.base_log}")

        # Wait for log file
        while not self.base_log.exists():
            time.sleep(5)

        print("✓ Log file found, monitoring started\n")

        last_total = 0

        while True:
            # Parse current state
            self.parse_log(self.base_log)
            total = self.stats['base']['total']

            # Print report if we crossed a milestone
            if total >= self.last_report_cluster + self.report_interval:
                self.print_progress_report()
                self.last_report_cluster = (total // self.report_interval) * self.report_interval

            # Check for completion
            with open(self.base_log, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
                if 'Execution Complete' in content or ('Done!' in content and total >= 100):
                    print("\n" + "="*80)
                    print("✅ BASE CODE EXECUTION COMPLETED!")
                    print("="*80)
                    self.print_progress_report()
                    self.save_report('base_execution_report.json')
                    return True

            # Show live progress (compact)
            if total != last_total:
                success_rate = self.stats['base']['success'] * 100 // total if total > 0 else 0
                print(f"\rClusters: {total}/103 ({total*100//103}%) | "
                      f"Success: {self.stats['base']['success']} | "
                      f"Failed: {self.stats['base']['failed']} | "
                      f"Rate: {success_rate}%", end='', flush=True)
                last_total = total

            time.sleep(30)  # Check every 30 seconds

    def launch_llm_execution(self):
        """Launch LLM execution after base completes"""
        print("\n" + "="*80)
        print("LAUNCHING LLM CODE EXECUTION")
        print("="*80)
        print(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
        print()

        for prompt_version in ['v1', 'v2', 'v3', 'v4']:
            print(f"\n🚀 Starting LLM execution for {prompt_version}...")

            log_file = f"full_js_llm_{prompt_version}_rerun.log"

            cmd = f"yes y | ./rerun_javascript.sh --llm-only --prompt {prompt_version} > {log_file} 2>&1"

            print(f"Command: {cmd}")
            print(f"Log: {log_file}")

            try:
                subprocess.run(cmd, shell=True, check=True)
                print(f"✓ {prompt_version} completed")
                self.stats['llm'][prompt_version] = 1
            except subprocess.CalledProcessError as e:
                print(f"✗ {prompt_version} failed: {e}")

        print("\n" + "="*80)
        print("✅ LLM EXECUTION COMPLETED")
        print("="*80)

    def save_report(self, filename):
        """Save detailed report to file"""
        report = {
            'timestamp': datetime.now().isoformat(),
            'elapsed_time_seconds': time.time() - self.start_time,
            'statistics': self.stats,
            'errors': {
                'legitimate': {k: len(v) for k, v in self.errors['legitimate'].items()},
                'environment': {k: len(v) for k, v in self.errors['environment'].items()},
                'unknown': len(self.errors['unknown'])
            },
            'error_details': {
                'legitimate': {k: [e['entry_id'] for e in v[:10]]
                              for k, v in self.errors['legitimate'].items()},
                'environment': {k: [{'id': e['entry_id'], 'context': e['context'][:100]}
                               for e in v[:5]]
                               for k, v in self.errors['environment'].items()}
            }
        }

        with open(filename, 'w') as f:
            json.dump(report, f, indent=2)

        print(f"\n✓ Detailed report saved: {filename}")

def main():
    monitor = SmartMonitor()

    try:
        # Phase 1: Monitor base code
        base_completed = monitor.monitor_base()

        if not base_completed:
            print("❌ Base code execution did not complete properly")
            return 1

        # Phase 2: Launch and monitor LLM code
        user_input = input("\nProceed with LLM execution? (y/n): ")
        if user_input.lower() == 'y':
            monitor.launch_llm_execution()
            monitor.save_report('full_execution_report.json')
        else:
            print("LLM execution skipped by user")

        return 0

    except KeyboardInterrupt:
        print("\n\n⚠️  Monitoring interrupted by user")
        monitor.print_progress_report()
        monitor.save_report('interrupted_report.json')
        return 1
    except Exception as e:
        print(f"\n\n❌ Error: {e}")
        import traceback
        traceback.print_exc()
        return 1

if __name__ == "__main__":
    sys.exit(main())
