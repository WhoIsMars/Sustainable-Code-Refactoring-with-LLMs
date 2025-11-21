"""
Analyze failures from CPP LLM regeneration.

This script analyzes execution report files to identify patterns in failures.
"""

import json
from pathlib import Path
from collections import defaultdict

def analyze_execution_reports(execution_dir: Path):
    """Analyze all entry execution reports to identify failure patterns."""

    stats = {
        'total_reports': 0,
        'reports_with_errors': 0,
        'error_types': defaultdict(int),
        'failed_entries': defaultdict(set),  # entry_id -> set of error types
        'failed_by_model': defaultdict(int),
        'failed_by_cluster': defaultdict(int),
        'successful_tests': 0,
        'failed_tests': 0,
    }

    # Find all entry execution reports
    report_files = list(execution_dir.glob("*_entry_execution_*.json"))

    print(f"Found {len(report_files)} execution reports\n")

    for report_file in report_files:
        stats['total_reports'] += 1

        try:
            with open(report_file) as f:
                report = json.load(f)
        except:
            continue

        cluster_name = report.get('cluster', 'unknown')

        # Check language reports for errors
        lang_reports = report.get('language_reports', {})

        for lang, lang_data in lang_reports.items():
            errors = lang_data.get('errors', [])

            if errors:
                stats['reports_with_errors'] += 1
                stats['failed_by_cluster'][cluster_name] += len(errors)

                for error in errors:
                    error_type = error.get('error_type', 'unknown')
                    entry_id = error.get('entry_id', 'unknown')

                    stats['error_types'][error_type] += 1
                    stats['failed_entries'][entry_id].add(error_type)

                    # Extract model from error message if available
                    error_msg = error.get('error_message', '')
                    if 'claude' in error_msg.lower():
                        stats['failed_by_model']['claude'] += 1
                    elif 'openai' in error_msg.lower():
                        stats['failed_by_model']['openAI'] += 1
                    elif 'gemini' in error_msg.lower():
                        stats['failed_by_model']['gemini'] += 1

            # Count successes
            validation = lang_data.get('validation', {})
            stats['successful_tests'] += validation.get('valid_new_results', 0)
            stats['failed_tests'] += validation.get('invalid_new_results', 0)

    # Print analysis
    print("=" * 80)
    print("FAILURE ANALYSIS")
    print("=" * 80)
    print(f"Total execution reports: {stats['total_reports']}")
    print(f"Reports with errors: {stats['reports_with_errors']}")
    print(f"Successful tests: {stats['successful_tests']}")
    print(f"Failed tests: {stats['failed_tests']}")
    print(f"Success rate: {stats['successful_tests'] / (stats['successful_tests'] + stats['failed_tests']) * 100:.1f}%")
    print()

    print("Error types:")
    for error_type, count in sorted(stats['error_types'].items(), key=lambda x: x[1], reverse=True):
        print(f"  {error_type}: {count}")
    print()

    print("Failures by model:")
    for model, count in sorted(stats['failed_by_model'].items(), key=lambda x: x[1], reverse=True):
        print(f"  {model}: {count}")
    print()

    print(f"Unique entries with failures: {len(stats['failed_entries'])}")
    print()

    print("Top 20 clusters with most failures:")
    for cluster, count in sorted(stats['failed_by_cluster'].items(), key=lambda x: x[1], reverse=True)[:20]:
        print(f"  {cluster}: {count} failures")
    print()

    # Identify entries that failed completely (no successful tests)
    print("\nEntries that may need debugging (multiple failure types):")
    problematic = [(entry, errors) for entry, errors in stats['failed_entries'].items()
                   if len(errors) > 1]
    for entry, errors in sorted(problematic, key=lambda x: len(x[1]), reverse=True)[:20]:
        print(f"  {entry}: {', '.join(errors)}")

    return stats


if __name__ == "__main__":
    execution_dir = Path("../execution_outputs")
    analyze_execution_reports(execution_dir)
