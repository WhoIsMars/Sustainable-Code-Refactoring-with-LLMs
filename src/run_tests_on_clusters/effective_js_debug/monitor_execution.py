#!/usr/bin/env python3
"""
Real-time monitoring of JavaScript test execution to categorize errors.
Monitors diagnostic files as they are created to track fix effectiveness.
"""

import json
import time
import sys
import os
from pathlib import Path
from collections import defaultdict
from datetime import datetime

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", ".."))
from utility_dir import utility_paths

LOGS_DIR = utility_paths.SRC_DIR / "logs"

def categorize_error_from_diagnostic(diag_file):
    """Categorize error from diagnostic JSON file."""
    try:
        with open(diag_file, 'r') as f:
            data = json.load(f)

        stdout = data.get("docker_stdout_full", "")
        exit_code = data.get("docker_exit_code", -1)

        # Categorize
        if "No tests found" in stdout:
            return "JEST_NO_TESTS_FOUND"
        elif "Cannot find module 'chai'" in stdout or "Cannot find module 'big-integer'" in stdout:
            return "MODULE_NOT_FOUND_FIXED_DEPS"
        elif "Cannot find module" in stdout or "MODULE_NOT_FOUND" in stdout:
            return "MODULE_NOT_FOUND_OTHER"
        elif exit_code == 0:
            return "SUCCESS"
        elif "FAIL" in stdout and "Test Suites:" in stdout:
            return "TEST_ASSERTION_FAILURES"
        elif exit_code == 1:
            return "OTHER_ERROR"
        else:
            return "UNKNOWN"

    except Exception as e:
        return "PARSE_ERROR"

def monitor_execution(duration_minutes=120):
    """Monitor diagnostic files for the specified duration."""

    print("=" * 80)
    print("JavaScript Execution Monitoring")
    print("=" * 80)
    print(f"Monitoring diagnostic files in: {LOGS_DIR}")
    print(f"Duration: {duration_minutes} minutes")
    print(f"Start time: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print()

    # Track files we've already processed
    seen_files = set(LOGS_DIR.glob("*javascript*diagnostic.json"))
    initial_count = len(seen_files)

    print(f"Found {initial_count} existing diagnostic files (will be skipped)")
    print()
    print("Waiting for new diagnostic files...")
    print("-" * 80)
    print()

    start_time = time.time()
    end_time = start_time + (duration_minutes * 60)

    error_counts = defaultdict(int)
    last_update = time.time()
    new_file_count = 0

    try:
        while time.time() < end_time:
            # Find new diagnostic files
            current_files = set(LOGS_DIR.glob("*javascript*diagnostic.json"))
            new_files = current_files - seen_files

            for diag_file in new_files:
                category = categorize_error_from_diagnostic(diag_file)
                error_counts[category] += 1
                new_file_count += 1
                seen_files.add(diag_file)

                # Print individual file result
                entry_id = diag_file.stem.split("_javascript_")[1].split("_17")[0] if "_javascript_" in diag_file.stem else "unknown"
                timestamp = datetime.now().strftime('%H:%M:%S')
                print(f"[{timestamp}] {entry_id[:50]:<50} → {category}")

            # Print summary every 30 seconds
            if time.time() - last_update > 30 and new_file_count > 0:
                print()
                print("-" * 80)
                print(f"Summary after {new_file_count} new tests:")
                for category in sorted(error_counts.keys()):
                    count = error_counts[category]
                    pct = (count / new_file_count * 100) if new_file_count > 0 else 0
                    print(f"  {category:30s}: {count:4d} ({pct:5.1f}%)")
                print("-" * 80)
                print()
                last_update = time.time()

            time.sleep(2)  # Check every 2 seconds

    except KeyboardInterrupt:
        print("\n\nMonitoring interrupted by user")

    # Final summary
    elapsed = time.time() - start_time
    print()
    print("=" * 80)
    print(f"Monitoring Complete - Elapsed time: {elapsed/60:.1f} minutes")
    print("=" * 80)
    print()
    print(f"Total new diagnostics processed: {new_file_count}")
    print()

    if new_file_count > 0:
        print("Final Error Category Breakdown:")
        print("-" * 80)
        for category in sorted(error_counts.keys()):
            count = error_counts[category]
            pct = (count / new_file_count * 100)
            print(f"  {category:30s}: {count:4d} ({pct:5.1f}%)")
        print("-" * 80)
        print()

        # Check if fixes are effective
        jest_errors = error_counts.get("JEST_NO_TESTS_FOUND", 0)
        module_fixed_deps = error_counts.get("MODULE_NOT_FOUND_FIXED_DEPS", 0)

        print("Fix Effectiveness Analysis:")
        print(f"  Jest 'No tests found' errors: {jest_errors}")
        print(f"  Module not found (chai/big-integer): {module_fixed_deps}")

        if jest_errors > 0:
            print("  ⚠️  WARNING: Still seeing 'No tests found' - Jest config may need review")
        else:
            print("  ✓  Jest config fix appears effective")

        if module_fixed_deps > 0:
            print("  ⚠️  WARNING: Still missing chai/big-integer - dependencies may not be installed")
        else:
            print("  ✓  Dependency fix appears effective")
    else:
        print("No new diagnostic files were created during monitoring period")
        print("The execution may have completed before monitoring started, or not started yet.")

    return error_counts

if __name__ == "__main__":
    monitor_execution(duration_minutes=120)
