#!/usr/bin/env python3
"""
Compare JavaScript test results BEFORE and AFTER infrastructure fixes
"""

import json
from pathlib import Path
from collections import defaultdict

# Paths
snapshot_dir = Path("/Users/piccoletto/Desktop/Everything/pisa/tesi/Sustainable-Code-Refactoring-with-LLMs/src/run_tests_on_clusters/effective_js_debug/js_base_results_snapshot")
current_dir = Path("/Users/piccoletto/Desktop/Everything/pisa/tesi/Sustainable-Code-Refactoring-with-LLMs/src/execution_outputs")

def load_results(results_dir):
    """Load all JavaScript base results from a directory"""
    results = {}

    for result_file in results_dir.glob("*_results_*.json"):
        # Extract cluster name and run number
        name = result_file.stem
        parts = name.split('_results_')
        if len(parts) != 2:
            continue

        cluster_name = parts[0]
        run_num = parts[1]

        try:
            with open(result_file) as f:
                data = json.load(f)

            # Filter only JavaScript entries
            js_entries = {k: v for k, v in data.items() if k.startswith('javascript_')}

            if js_entries:
                if cluster_name not in results:
                    results[cluster_name] = {}
                results[cluster_name][run_num] = js_entries

        except Exception as e:
            continue

    return results

def analyze_pass_rates(results):
    """Calculate pass rates from results"""
    stats = {
        'total_tests': 0,
        'passed_tests': 0,
        'failed_tests': 0,
        'pass_rate': 0.0,
        'clusters_tested': 0,
        'entries_tested': 0,
    }

    entries_seen = set()

    for cluster_name, runs in results.items():
        stats['clusters_tested'] += 1

        for run_num, entries in runs.items():
            for entry_id, entry_data in entries.items():
                # Count each unique entry only once
                if entry_id not in entries_seen:
                    stats['entries_tested'] += 1
                    entries_seen.add(entry_id)

                stats['total_tests'] += 1

                if entry_data.get('regressionTestPassed', False):
                    stats['passed_tests'] += 1
                else:
                    stats['failed_tests'] += 1

    if stats['total_tests'] > 0:
        stats['pass_rate'] = (stats['passed_tests'] / stats['total_tests']) * 100

    return stats

def compare_results(before_stats, after_stats):
    """Compare before and after statistics"""
    print("=" * 80)
    print("JAVASCRIPT INFRASTRUCTURE FIX - RESULTS COMPARISON")
    print("=" * 80)
    print()

    print("BEFORE (with infrastructure errors):")
    print("-" * 80)
    print(f"  Clusters tested:      {before_stats['clusters_tested']:5d}")
    print(f"  Unique entries:       {before_stats['entries_tested']:5d}")
    print(f"  Total test runs:      {before_stats['total_tests']:5d}")
    print(f"  Tests passed:         {before_stats['passed_tests']:5d}")
    print(f"  Tests failed:         {before_stats['failed_tests']:5d}")
    print(f"  Pass rate:            {before_stats['pass_rate']:5.2f}%")
    print()

    print("AFTER (infrastructure fixes applied):")
    print("-" * 80)
    print(f"  Clusters tested:      {after_stats['clusters_tested']:5d}")
    print(f"  Unique entries:       {after_stats['entries_tested']:5d}")
    print(f"  Total test runs:      {after_stats['total_tests']:5d}")
    print(f"  Tests passed:         {after_stats['passed_tests']:5d}")
    print(f"  Tests failed:         {after_stats['failed_tests']:5d}")
    print(f"  Pass rate:            {after_stats['pass_rate']:5.2f}%")
    print()

    print("IMPROVEMENT:")
    print("-" * 80)

    # Calculate changes
    cluster_change = after_stats['clusters_tested'] - before_stats['clusters_tested']
    entry_change = after_stats['entries_tested'] - before_stats['entries_tested']
    test_change = after_stats['total_tests'] - before_stats['total_tests']
    pass_change = after_stats['passed_tests'] - before_stats['passed_tests']
    rate_change = after_stats['pass_rate'] - before_stats['pass_rate']

    print(f"  Clusters change:      {cluster_change:+5d}")
    print(f"  Entries change:       {entry_change:+5d}")
    print(f"  Test runs change:     {test_change:+5d}")
    print(f"  Passed tests change:  {pass_change:+5d}")
    print(f"  Pass rate change:     {rate_change:+5.2f} percentage points")
    print()

    if rate_change > 0:
        print(f"✅ PASS RATE IMPROVED by {rate_change:.2f}%")
    elif rate_change < 0:
        print(f"⚠️  Pass rate decreased by {abs(rate_change):.2f}%")
    else:
        print("➡️  Pass rate unchanged")
    print()

    # Relative improvement
    if before_stats['pass_rate'] > 0:
        relative_improvement = (rate_change / before_stats['pass_rate']) * 100
        print(f"Relative improvement: {relative_improvement:+.2f}% of original pass rate")
    print()

    print("=" * 80)
    print("SUMMARY")
    print("=" * 80)
    print()
    print("Infrastructure fixes applied:")
    print("  1. ✅ Jest config updated to recognize *_testSuite.js pattern")
    print("  2. ✅ Added chai dependency to package.json")
    print("  3. ✅ Added big-integer dependency to package.json")
    print("  4. ✅ Rebuilt Docker containers with new dependencies")
    print("  5. ✅ Filtered out 12 clusters with empty JavaScript arrays")
    print()

    # Check if we actually tested more
    if after_stats['total_tests'] > before_stats['total_tests']:
        print(f"✅ Successfully executed {test_change} MORE test runs than before!")
        print(f"   This means the infrastructure fixes allowed tests to run that")
        print(f"   were previously failing due to missing dependencies or config issues.")
    else:
        print(f"⚠️  Test count similar - may need further investigation")
    print()

if __name__ == "__main__":
    print("\nLoading BEFORE results (snapshot)...")
    before_results = load_results(snapshot_dir)
    before_stats = analyze_pass_rates(before_results)

    print(f"Loaded {before_stats['clusters_tested']} clusters from snapshot")

    print("\nLoading AFTER results (current)...")
    after_results = load_results(current_dir)
    after_stats = analyze_pass_rates(after_results)

    print(f"Loaded {after_stats['clusters_tested']} clusters from current execution")

    print("\n")
    compare_results(before_stats, after_stats)
