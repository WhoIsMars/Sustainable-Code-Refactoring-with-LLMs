#!/usr/bin/env python3
"""
Analyze error categories from diagnostic files to verify infrastructure fixes
"""

import json
from pathlib import Path
from collections import Counter
import time

logs_dir = Path("/Users/piccoletto/Desktop/Everything/pisa/tesi/Sustainable-Code-Refactoring-with-LLMs/src/logs")

def analyze_diagnostics(minutes_ago=5):
    """Analyze diagnostic files created in the last N minutes"""

    cutoff_time = time.time() - (minutes_ago * 60)
    recent_diagnostics = []

    for diag_file in logs_dir.glob("*_diagnostic.json"):
        try:
            if diag_file.stat().st_mtime >= cutoff_time:
                with open(diag_file) as f:
                    data = json.load(f)
                    recent_diagnostics.append(data)
        except Exception as e:
            continue

    if not recent_diagnostics:
        print(f"No diagnostic files found in the last {minutes_ago} minutes")
        return

    # Count error categories
    error_categories = Counter(d.get('error_category', 'unknown') for d in recent_diagnostics)

    # Check for infrastructure errors
    infrastructure_errors = {
        'JEST_NO_TESTS_FOUND': 0,
        'MODULE_NOT_FOUND_chai': 0,
        'MODULE_NOT_FOUND_big_integer': 0,
        'JEST_CONFIG_ERROR': 0,
    }

    for diag in recent_diagnostics:
        stdout = diag.get('docker_stdout_full', '')
        stderr = diag.get('docker_stderr_full', '')
        combined = (stdout + stderr).lower()

        if 'no tests found' in combined:
            infrastructure_errors['JEST_NO_TESTS_FOUND'] += 1
        if "cannot find module 'chai'" in combined or 'error: cannot find module \'chai\'' in combined:
            infrastructure_errors['MODULE_NOT_FOUND_chai'] += 1
        if "cannot find module 'big-integer'" in combined:
            infrastructure_errors['MODULE_NOT_FOUND_big_integer'] += 1
        if 'test suite failed to run' in combined and 'config' in combined:
            infrastructure_errors['JEST_CONFIG_ERROR'] += 1

    print("=" * 80)
    print(f"DIAGNOSTIC ANALYSIS - Last {minutes_ago} minutes")
    print("=" * 80)
    print(f"\nTotal diagnostics analyzed: {len(recent_diagnostics)}")
    print()

    print("Error Category Breakdown:")
    print("-" * 80)
    for category, count in error_categories.most_common():
        pct = (count / len(recent_diagnostics)) * 100
        print(f"  {category:30s}: {count:4d} ({pct:5.1f}%)")
    print()

    print("Infrastructure Error Check:")
    print("-" * 80)
    any_infra_errors = False
    for error_type, count in infrastructure_errors.items():
        status = "❌ FOUND" if count > 0 else "✅ NONE"
        print(f"  {error_type:30s}: {count:4d} {status}")
        if count > 0:
            any_infra_errors = True
    print()

    if not any_infra_errors:
        print("✅ ✅ ✅ NO INFRASTRUCTURE ERRORS - FIXES ARE WORKING! ✅ ✅ ✅")
    else:
        print("❌ Infrastructure errors still present - investigation needed")
    print()

    # Show metrics availability
    with_metrics = sum(1 for d in recent_diagnostics if d.get('metrics_found'))
    print(f"Tests with valid metrics: {with_metrics}/{len(recent_diagnostics)} ({with_metrics/len(recent_diagnostics)*100:.1f}%)")
    print()

if __name__ == "__main__":
    print("\nAnalyzing recent diagnostic files...")
    print("(Will update every 30 seconds)\n")

    try:
        while True:
            analyze_diagnostics(minutes_ago=10)
            print("Waiting 30 seconds for next check...\n")
            time.sleep(30)
    except KeyboardInterrupt:
        print("\n\nAnalysis stopped by user.")
