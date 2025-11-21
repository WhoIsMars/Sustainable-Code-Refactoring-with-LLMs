"""
Analyze build/compilation failures from diagnostic logs.
"""

import json
from pathlib import Path
from collections import defaultdict
import re

def analyze_diagnostic_logs(logs_dir: Path, since_timestamp: float = None):
    """Analyze diagnostic logs to identify build failure patterns."""

    stats = {
        'total_diagnostics': 0,
        'error_categories': defaultdict(int),
        'failed_entries': defaultdict(set),  # entry_id -> set of error categories
        'failed_by_model': defaultdict(int),
        'build_errors': defaultdict(int),  # type of build error -> count
        'entries_by_error': defaultdict(list),  # error type -> list of entries
    }

    # Find diagnostic files
    diagnostic_files = list(logs_dir.glob("*_diagnostic.json"))

    # Filter by timestamp if provided
    if since_timestamp:
        diagnostic_files = [f for f in diagnostic_files if f.stat().st_mtime > since_timestamp]

    print(f"Analyzing {len(diagnostic_files)} diagnostic logs...\n")

    for diag_file in diagnostic_files:
        stats['total_diagnostics'] += 1

        try:
            with open(diag_file) as f:
                diag = json.load(f)
        except:
            continue

        entry_id = diag.get('entry_id', 'unknown')
        error_category = diag.get('error_category', 'unknown')
        llm_type = diag.get('llm_type', 'unknown')
        exit_code = diag.get('exit_code', 0)
        docker_output = diag.get('docker_output', '')

        stats['error_categories'][error_category] += 1
        stats['failed_entries'][entry_id].add(error_category)
        stats['failed_by_model'][llm_type] += 1

        # Parse build errors from docker output
        if 'error:' in docker_output.lower():
            # Extract error messages
            error_lines = [line for line in docker_output.split('\n') if 'error:' in line.lower()]

            for error_line in error_lines[:1]:  # Take first error
                # Common error patterns
                if 'ambiguating new declaration' in error_line:
                    stats['build_errors']['type_mismatch'] += 1
                    stats['entries_by_error']['type_mismatch'].append((entry_id, llm_type))
                elif 'was not declared in this scope' in error_line:
                    stats['build_errors']['undeclared_identifier'] += 1
                    stats['entries_by_error']['undeclared_identifier'].append((entry_id, llm_type))
                elif 'no matching function' in error_line:
                    stats['build_errors']['no_matching_function'] += 1
                    stats['entries_by_error']['no_matching_function'].append((entry_id, llm_type))
                elif 'undefined reference' in error_line:
                    stats['build_errors']['undefined_reference'] += 1
                    stats['entries_by_error']['undefined_reference'].append((entry_id, llm_type))
                elif "cannot convert" in error_line:
                    stats['build_errors']['type_conversion'] += 1
                    stats['entries_by_error']['type_conversion'].append((entry_id, llm_type))
                else:
                    stats['build_errors']['other_compile_error'] += 1

    # Print analysis
    print("=" * 80)
    print("BUILD FAILURE ANALYSIS")
    print("=" * 80)
    print(f"Total diagnostic logs: {stats['total_diagnostics']}")
    print()

    print("Error categories:")
    for category, count in sorted(stats['error_categories'].items(), key=lambda x: x[1], reverse=True):
        print(f"  {category}: {count}")
    print()

    print("Failures by model:")
    for model, count in sorted(stats['failed_by_model'].items(), key=lambda x: x[1], reverse=True):
        print(f"  {model}: {count}")
    print()

    print(f"Unique entries with failures: {len(stats['failed_entries'])}")
    print()

    print("Build error types:")
    for error_type, count in sorted(stats['build_errors'].items(), key=lambda x: x[1], reverse=True):
        print(f"  {error_type}: {count}")
    print()

    # Show examples for most common error
    if stats['entries_by_error']:
        most_common = max(stats['entries_by_error'].items(), key=lambda x: len(x[1]))
        error_type, examples = most_common
        print(f"\nExamples of '{error_type}' ({len(examples)} occurrences):")
        unique_entries = list(set(entry_id for entry_id, _ in examples))
        for entry_id in unique_entries[:10]:
            models = [model for eid, model in examples if eid == entry_id]
            print(f"  {entry_id}: {', '.join(set(models))}")
        if len(unique_entries) > 10:
            print(f"  ... and {len(unique_entries) - 10} more entries")

    return stats


if __name__ == "__main__":
    logs_dir = Path("../logs")

    # Get timestamp of all_your_base result file to filter recent logs
    marker_file = Path("../execution_outputs/all_your_base_results_v1_1.json")
    since_timestamp = marker_file.stat().st_mtime if marker_file.exists() else None

    analyze_diagnostic_logs(logs_dir, since_timestamp)
