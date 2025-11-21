"""
Failure Log Analyzer Script

This script analyzes execution logs for failed entries to classify errors into
categories and identify recoverable vs unrecoverable failures.

Error Categories:
- Compilation errors (missing headers, linker issues)
- Runtime errors (segfault, timeout, OOM)
- Test framework issues (test discovery, assertion format)
- Docker/environment issues (path problems, permissions)
- Flaky tests (timing, randomness, external deps)
- Base code bugs (logic errors, edge cases)

Author: Dataset Rebalancing Pipeline
Date: 2025-11-18
"""

import json
import re
from pathlib import Path
from collections import defaultdict
from typing import Dict, List, Tuple
import os


class FailureLogAnalyzer:
    """Analyzes failure logs to classify errors and identify recovery strategies."""

    def __init__(self, samples_dir: str = "samples", reports_dir: str = "reports"):
        """
        Initialize the analyzer.

        Args:
            samples_dir: Directory containing sampled failed entries
            reports_dir: Directory for output reports
        """
        self.samples_dir = Path(samples_dir)
        self.reports_dir = Path(reports_dir)
        self.reports_dir.mkdir(parents=True, exist_ok=True)

        self.target_languages = ['c', 'java', 'python', 'javascript']

        # Error patterns for classification
        self.error_patterns = {
            'compilation_errors': [
                (r'fatal error.*No such file or directory', 'Missing header file'),
                (r'undefined reference to', 'Linker error - missing library'),
                (r'error:.*was not declared in this scope', 'Undeclared identifier'),
                (r'CMake Error', 'CMake configuration error'),
                (r'Makefile.*No such file', 'Missing build file'),
                (r'error:.*expected.*before', 'Syntax error'),
                (r'ld returned.*exit status', 'Linker failure'),
                (r'cannot find -l', 'Missing library'),
                (r'collect2: error: ld returned', 'Linking failed'),
            ],
            'runtime_errors': [
                (r'Segmentation fault', 'Segfault'),
                (r'TIMEOUT EXCEEDED', 'Test timeout'),
                (r'killed by signal', 'Process killed'),
                (r'core dumped', 'Core dump'),
                (r'MemoryError', 'Out of memory'),
                (r'RecursionError', 'Stack overflow'),
                (r'Killed', 'Process killed (likely OOM)'),
            ],
            'test_framework_issues': [
                (r'No tests found', 'Test discovery failed'),
                (r'pytest.*No module named', 'Missing pytest dependency'),
                (r'jest.*Cannot find module', 'Missing Jest dependency'),
                (r'JUnit.*ClassNotFoundException', 'JUnit class not found'),
                (r'Test.*not found', 'Test not found'),
                (r'AssertionError', 'Test assertion failed'),
                (r'FAILED.*test_', 'Test failure'),
            ],
            'docker_environment_issues': [
                (r'Permission denied', 'Permission error'),
                (r'No space left on device', 'Disk full'),
                (r'docker.*error', 'Docker error'),
                (r'/bin/sh.*not found', 'Shell script error'),
                (r'command not found', 'Missing command'),
                (r'.*CMakeLists.txt.*not found', 'CMake path issue'),
            ],
            'flaky_tests': [
                (r'random', 'Randomness in test'),
                (r'time.*differ', 'Timing sensitivity'),
                (r'network', 'Network dependency'),
                (r'sleep', 'Time-based test'),
            ],
            'base_code_bugs': [
                (r'Expected.*but got', 'Logic error'),
                (r'failed.*expected', 'Incorrect output'),
                (r'IndexError', 'Index out of bounds'),
                (r'KeyError', 'Key not found'),
                (r'ValueError', 'Invalid value'),
                (r'division by zero', 'Math error'),
            ]
        }

    def load_samples(self, language: str) -> Dict:
        """
        Load sample data for a language.

        Args:
            language: Programming language

        Returns:
            Sample data dictionary
        """
        sample_file = self.samples_dir / f"failed_entries_{language}.json"
        if not sample_file.exists():
            print(f"Warning: Sample file not found for {language}")
            return {'entries': []}

        with open(sample_file, 'r') as f:
            return json.load(f)

    def read_log_file(self, log_path: str) -> str:
        """
        Read content from a log file.

        Args:
            log_path: Path to log file

        Returns:
            Log content as string, or empty string if file not found
        """
        # Convert to absolute path if relative
        if not log_path.startswith('/'):
            # Try to find the log in the logs directory
            logs_dir = Path("../logs")
            potential_path = logs_dir / log_path
            if potential_path.exists():
                log_path = str(potential_path)

        log_file = Path(log_path)
        if not log_file.exists():
            return ""

        try:
            with open(log_file, 'r', errors='ignore') as f:
                return f.read()
        except Exception as e:
            print(f"Warning: Could not read log {log_file}: {e}")
            return ""

    def classify_error(self, log_content: str, error_message: str = None) -> Tuple[str, str, str]:
        """
        Classify error based on log content and error message.

        Args:
            log_content: Full log file content
            error_message: Error message from execution result

        Returns:
            Tuple of (category, pattern_matched, description)
        """
        # Combine log and error message for analysis
        combined_text = log_content
        if error_message:
            combined_text += "\n" + error_message

        # Check each category
        for category, patterns in self.error_patterns.items():
            for pattern, description in patterns:
                if re.search(pattern, combined_text, re.IGNORECASE):
                    return category, pattern, description

        # If no pattern matched, classify as "unknown"
        return 'unknown', None, 'Unclassified error'

    def analyze_entry_logs(self, entry: Dict) -> Dict:
        """
        Analyze logs for a single entry.

        Args:
            entry: Entry data with log paths

        Returns:
            Analysis result dictionary
        """
        log_paths = entry.get('log_paths', [])
        error_messages = entry.get('error_messages', [])

        # Read all logs
        log_contents = []
        for log_path in log_paths:
            if log_path:
                content = self.read_log_file(log_path)
                if content:
                    log_contents.append(content)

        # Combine all logs and errors
        combined_log = "\n".join(log_contents)
        combined_error = "\n".join([str(e) for e in error_messages if e])

        # Classify error
        category, pattern, description = self.classify_error(combined_log, combined_error)

        return {
            'entry_id': entry['entry_id'],
            'cluster': entry['cluster'],
            'pass_rate': entry['pass_rate'],
            'category': category,
            'pattern': pattern,
            'description': description,
            'log_snippet': combined_log[:500] if combined_log else combined_error[:500],
            'recoverable': self.is_recoverable(category)
        }

    def is_recoverable(self, category: str) -> bool:
        """
        Determine if an error category is likely recoverable.

        Args:
            category: Error category

        Returns:
            True if likely recoverable with config fixes
        """
        recoverable_categories = {
            'compilation_errors',  # Can fix with better build config
            'docker_environment_issues',  # Can fix with Docker/script changes
            'test_framework_issues',  # Can fix with dependencies
        }

        return category in recoverable_categories

    def analyze_language(self, language: str) -> Dict:
        """
        Analyze all sampled entries for a language.

        Args:
            language: Programming language

        Returns:
            Analysis report dictionary
        """
        print(f"\n{'='*80}")
        print(f"ANALYZING {language.upper()} FAILURES")
        print(f"{'='*80}")

        # Load samples
        sample_data = self.load_samples(language)
        entries = sample_data.get('entries', [])

        if not entries:
            print(f"No entries to analyze for {language}")
            return {
                'language': language,
                'entries_analyzed': 0,
                'error_categories': {},
                'recoverable_count': 0,
                'unrecoverable_count': 0
            }

        print(f"Analyzing {len(entries)} entries...")

        # Analyze each entry
        results = []
        for i, entry in enumerate(entries, 1):
            print(f"  [{i}/{len(entries)}] {entry['entry_id'][:50]}...", end='\r')
            result = self.analyze_entry_logs(entry)
            results.append(result)

        print()  # New line after progress

        # Aggregate results by category
        by_category = defaultdict(list)
        for result in results:
            by_category[result['category']].append(result)

        # Count recoverable vs unrecoverable
        recoverable = [r for r in results if r['recoverable']]
        unrecoverable = [r for r in results if not r['recoverable']]

        # Build report
        report = {
            'language': language,
            'entries_analyzed': len(entries),
            'error_categories': {},
            'recoverable_count': len(recoverable),
            'unrecoverable_count': len(unrecoverable),
            'recoverable_entries': [r['entry_id'] for r in recoverable],
            'unrecoverable_entries': [r['entry_id'] for r in unrecoverable]
        }

        # Add category details
        for category, category_results in by_category.items():
            # Find most common pattern in this category
            patterns = [r['description'] for r in category_results]
            pattern_counts = defaultdict(int)
            for p in patterns:
                pattern_counts[p] += 1

            most_common_pattern = max(pattern_counts, key=pattern_counts.get) if pattern_counts else "N/A"

            report['error_categories'][category] = {
                'count': len(category_results),
                'entries': [r['entry_id'] for r in category_results],
                'common_pattern': most_common_pattern,
                'example_snippet': category_results[0]['log_snippet'] if category_results else ""
            }

        # Print summary
        self.print_language_summary(report)

        return report

    def print_language_summary(self, report: Dict):
        """Print a summary of the language analysis."""
        lang = report['language'].upper()
        print(f"\n{lang} ANALYSIS SUMMARY:")
        print(f"  Entries analyzed: {report['entries_analyzed']}")
        print(f"  Recoverable: {report['recoverable_count']} ✅")
        print(f"  Unrecoverable: {report['unrecoverable_count']} ❌")
        print()
        print(f"  Error categories:")

        for category, details in report['error_categories'].items():
            count = details['count']
            pattern = details['common_pattern']
            icon = "✅" if category in ['compilation_errors', 'docker_environment_issues', 'test_framework_issues'] else "❌"
            print(f"    {icon} {category}: {count} entries")
            print(f"       Most common: {pattern}")

    def save_reports(self, reports: Dict[str, Dict]):
        """
        Save analysis reports to JSON files.

        Args:
            reports: Dictionary mapping language to report
        """
        print(f"\n{'='*80}")
        print("SAVING ANALYSIS REPORTS")
        print(f"{'='*80}")

        for language, report in reports.items():
            # Save full report
            report_file = self.reports_dir / f"root_cause_{language}.json"
            with open(report_file, 'w') as f:
                json.dump(report, f, indent=2)
            print(f"  {language.upper()}: {report_file}")

            # Save recoverable entry IDs
            if report['recoverable_entries']:
                recoverable_file = self.samples_dir / f"recoverable_entries_{language}.txt"
                with open(recoverable_file, 'w') as f:
                    for entry_id in report['recoverable_entries']:
                        f.write(f"{entry_id}\n")
                print(f"  {language.upper()} recoverable IDs: {recoverable_file}")

            # Save unrecoverable entry IDs
            if report['unrecoverable_entries']:
                unrecoverable_file = self.samples_dir / f"unrecoverable_entries_{language}.txt"
                with open(unrecoverable_file, 'w') as f:
                    for entry_id in report['unrecoverable_entries']:
                        f.write(f"{entry_id}\n")
                print(f"  {language.upper()} unrecoverable IDs: {unrecoverable_file}")

        # Save combined summary
        summary_file = self.reports_dir / "root_cause_summary.json"
        summary = {
            'analysis_date': '2025-11-18',
            'languages_analyzed': list(reports.keys()),
            'summary': {}
        }

        for language, report in reports.items():
            summary['summary'][language] = {
                'entries_analyzed': report['entries_analyzed'],
                'recoverable': report['recoverable_count'],
                'unrecoverable': report['unrecoverable_count'],
                'categories': {cat: details['count'] for cat, details in report['error_categories'].items()}
            }

        with open(summary_file, 'w') as f:
            json.dump(summary, f, indent=2)

        print(f"\n  Combined summary: {summary_file}")
        print("\n✅ All reports saved successfully!")

    def generate_fix_recommendations(self, reports: Dict[str, Dict]):
        """
        Generate Docker/script fix recommendations based on error patterns.

        Args:
            reports: Analysis reports per language
        """
        print(f"\n{'='*80}")
        print("FIX RECOMMENDATIONS")
        print(f"{'='*80}")

        recommendations = {}

        for language, report in reports.items():
            lang_recommendations = []

            for category, details in report['error_categories'].items():
                if category == 'compilation_errors':
                    lang_recommendations.append({
                        'issue': 'Missing headers or libraries',
                        'affected_entries': details['count'],
                        'fix': f'Update {language}/Dockerfile to include missing dependencies',
                        'script_change': f'Modify {language}/run.sh to add -lm -lpthread to linker flags',
                        'priority': 'HIGH'
                    })

                elif category == 'docker_environment_issues':
                    lang_recommendations.append({
                        'issue': 'CMake/build path issues',
                        'affected_entries': details['count'],
                        'fix': f'Improve {language}/run.sh path resolution',
                        'script_change': 'Add better fallback mechanisms for build systems',
                        'priority': 'HIGH'
                    })

                elif category == 'test_framework_issues':
                    lang_recommendations.append({
                        'issue': 'Test discovery or framework problems',
                        'affected_entries': details['count'],
                        'fix': f'Install missing {language} test framework dependencies',
                        'script_change': 'Add auto-detection of test framework version',
                        'priority': 'MEDIUM'
                    })

            recommendations[language] = lang_recommendations

            # Print recommendations
            print(f"\n{language.upper()}:")
            if not lang_recommendations:
                print("  No actionable recommendations (errors are mostly base code bugs)")
            else:
                for i, rec in enumerate(lang_recommendations, 1):
                    print(f"  {i}. {rec['issue']} [{rec['priority']}]")
                    print(f"     Affects: {rec['affected_entries']} entries")
                    print(f"     Fix: {rec['fix']}")
                    print(f"     Change: {rec['script_change']}")

        # Save recommendations
        rec_file = self.reports_dir / "fix_recommendations.json"
        with open(rec_file, 'w') as f:
            json.dump(recommendations, f, indent=2)

        print(f"\n  Recommendations saved to: {rec_file}")


def main():
    """Main execution function."""
    analyzer = FailureLogAnalyzer()

    reports = {}

    # Analyze each language
    for language in analyzer.target_languages:
        report = analyzer.analyze_language(language)
        reports[language] = report

    # Save all reports
    analyzer.save_reports(reports)

    # Generate fix recommendations
    analyzer.generate_fix_recommendations(reports)

    print(f"\n{'='*80}")
    print("ROOT CAUSE ANALYSIS COMPLETE")
    print(f"{'='*80}")
    print("\nNext steps:")
    print("  1. Review reports in analysis/reports/")
    print("  2. Apply recommended fixes to Docker/run.sh files")
    print("  3. Re-test recoverable entries to validate fixes")
    print()


if __name__ == "__main__":
    main()
