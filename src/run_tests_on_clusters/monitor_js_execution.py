#!/usr/bin/env python3
"""
JavaScript Execution Monitor

Monitors the JavaScript re-execution log in real-time and categorizes errors:
1. Legitimate code/test issues (acceptable)
2. Environment/configuration issues (need fixing)

Usage: python3 monitor_js_execution.py <log_file>
"""

import sys
import time
import re
from collections import defaultdict, Counter
from pathlib import Path

class ExecutionMonitor:
    def __init__(self, log_file):
        self.log_file = Path(log_file)
        self.error_categories = defaultdict(list)
        self.cluster_stats = {
            'total': 0,
            'success': 0,
            'failed': 0,
            'in_progress': 0
        }
        self.error_patterns = {
            # Legitimate errors (code issues)
            'import_export_mismatch': r'Your test suite must contain at least one test',
            'assertion_failure': r'expect\(.*\).to',
            'syntax_error': r'SyntaxError:',
            'reference_error': r'ReferenceError:',
            'type_error': r'TypeError:',
            'undefined_function': r'is not a function',

            # Environment errors (need fixing)
            'docker_error': r'docker:.*error|Cannot connect to the Docker daemon',
            'permission_error': r'Permission denied|EACCES',
            'file_not_found': r'ENOENT|no such file|cannot find',
            'npm_install_failure': r'npm ERR!.*install',
            'jest_config_error': r'Jest.*configuration|Cannot find module.*jest',
            'timeout': r'timeout|Timeout',
        }

    def categorize_error(self, log_line):
        """Categorize error based on patterns"""
        for category, pattern in self.error_patterns.items():
            if re.search(pattern, log_line, re.IGNORECASE):
                return category
        return 'unknown'

    def parse_cluster_result(self, line):
        """Parse cluster execution result"""
        if '✓ Success' in line:
            self.cluster_stats['success'] += 1
            self.cluster_stats['in_progress'] -= 1
        elif '✗ Failed' in line:
            self.cluster_stats['failed'] += 1
            self.cluster_stats['in_progress'] -= 1
        elif 'Processing cluster:' in line:
            self.cluster_stats['total'] += 1
            self.cluster_stats['in_progress'] += 1
            cluster_match = re.search(r'Processing cluster: \x1b\[0;32m(\w+)', line)
            if cluster_match:
                return cluster_match.group(1)
        return None

    def monitor(self, follow=True, interval=2):
        """Monitor log file in real-time"""
        print("="*80)
        print("JavaScript Execution Monitor")
        print("="*80)
        print(f"Monitoring: {self.log_file}")
        print(f"Follow mode: {follow}")
        print()

        if not self.log_file.exists():
            print(f"Waiting for log file to be created...")
            while not self.log_file.exists():
                time.sleep(1)

        with open(self.log_file, 'r') as f:
            # Read existing content
            lines = f.readlines()

            # Process existing lines
            for line in lines:
                self._process_line(line)

            if follow:
                # Follow new lines
                while True:
                    line = f.readline()
                    if line:
                        self._process_line(line)
                    else:
                        time.sleep(interval)
                        # Check if process is still running
                        if self._is_execution_complete():
                            print("\n" + "="*80)
                            print("Execution complete - generating final report")
                            print("="*80)
                            self.print_report()
                            break

    def _process_line(self, line):
        """Process a single log line"""
        # Check for cluster result
        cluster = self.parse_cluster_result(line)
        if cluster:
            self._print_progress()

        # Check for errors
        if 'error' in line.lower() or 'failed' in line.lower() or 'exception' in line.lower():
            category = self.categorize_error(line)
            self.error_categories[category].append(line.strip())

    def _print_progress(self):
        """Print current progress"""
        total = self.cluster_stats['total']
        success = self.cluster_stats['success']
        failed = self.cluster_stats['failed']
        in_progress = self.cluster_stats['in_progress']

        if total > 0:
            success_rate = (success / (success + failed) * 100) if (success + failed) > 0 else 0
            print(f"\rProgress: {success + failed}/{total} clusters | "
                  f"Success: {success} | Failed: {failed} | "
                  f"Success Rate: {success_rate:.1f}%", end='', flush=True)

    def _is_execution_complete(self):
        """Check if execution is complete"""
        # Check if log file contains completion marker
        try:
            with open(self.log_file, 'r') as f:
                content = f.read()
                return 'Execution Complete' in content or 'Done!' in content
        except:
            return False

    def print_report(self):
        """Print final error analysis report"""
        print("\n\n" + "="*80)
        print("ERROR ANALYSIS REPORT")
        print("="*80)

        print(f"\nCluster Statistics:")
        print(f"  Total clusters: {self.cluster_stats['total']}")
        print(f"  Successful: {self.cluster_stats['success']}")
        print(f"  Failed: {self.cluster_stats['failed']}")
        print(f"  Success rate: {(self.cluster_stats['success'] / self.cluster_stats['total'] * 100):.1f}%")

        print(f"\nError Categories:")

        # Separate legitimate vs environment errors
        legitimate_errors = ['import_export_mismatch', 'assertion_failure', 'syntax_error',
                            'reference_error', 'type_error', 'undefined_function']
        environment_errors = ['docker_error', 'permission_error', 'file_not_found',
                             'npm_install_failure', 'jest_config_error', 'timeout']

        print(f"\n  ✅ LEGITIMATE ERRORS (code/test issues):")
        legitimate_count = 0
        for category in legitimate_errors:
            if category in self.error_categories:
                count = len(self.error_categories[category])
                legitimate_count += count
                print(f"    - {category}: {count}")

        print(f"\n  ❌ ENVIRONMENT ERRORS (need fixing):")
        environment_count = 0
        for category in environment_errors:
            if category in self.error_categories:
                count = len(self.error_categories[category])
                environment_count += count
                print(f"    - {category}: {count}")
                # Print first few examples
                for example in self.error_categories[category][:2]:
                    print(f"        Example: {example[:100]}...")

        print(f"\n  ⚠️  UNKNOWN ERRORS:")
        if 'unknown' in self.error_categories:
            unknown_count = len(self.error_categories['unknown'])
            print(f"    - Count: {unknown_count}")
            for example in self.error_categories['unknown'][:3]:
                print(f"        {example[:100]}...")

        print(f"\n" + "="*80)
        print(f"SUMMARY:")
        print(f"  Legitimate errors: {legitimate_count} (expected)")
        print(f"  Environment errors: {environment_count} {'⚠️  NEEDS ATTENTION' if environment_count > 0 else '✅ OK'}")
        print(f"  Unknown errors: {len(self.error_categories.get('unknown', []))}")
        print("="*80)

        # Save report to file
        report_file = self.log_file.parent / f"error_analysis_{time.strftime('%Y%m%d_%H%M%S')}.txt"
        with open(report_file, 'w') as f:
            f.write(self._generate_detailed_report())
        print(f"\nDetailed report saved to: {report_file}")

    def _generate_detailed_report(self):
        """Generate detailed text report"""
        lines = []
        lines.append("="*80)
        lines.append("DETAILED ERROR ANALYSIS REPORT")
        lines.append("="*80)
        lines.append(f"\nGenerated: {time.strftime('%Y-%m-%d %H:%M:%S')}")
        lines.append(f"Log file: {self.log_file}")

        lines.append(f"\n\nCLUSTER STATISTICS:")
        for key, value in self.cluster_stats.items():
            lines.append(f"  {key}: {value}")

        lines.append(f"\n\nERROR CATEGORIES:")
        for category, errors in sorted(self.error_categories.items()):
            lines.append(f"\n{category.upper()} ({len(errors)} occurrences):")
            for i, error in enumerate(errors[:10], 1):  # First 10 examples
                lines.append(f"  {i}. {error}")
            if len(errors) > 10:
                lines.append(f"  ... and {len(errors) - 10} more")

        return '\n'.join(lines)


def main():
    if len(sys.argv) < 2:
        print("Usage: python3 monitor_js_execution.py <log_file>")
        sys.exit(1)

    log_file = sys.argv[1]
    follow = '--no-follow' not in sys.argv

    monitor = ExecutionMonitor(log_file)

    try:
        monitor.monitor(follow=follow)
    except KeyboardInterrupt:
        print("\n\nMonitoring interrupted by user")
        monitor.print_report()


if __name__ == "__main__":
    main()
