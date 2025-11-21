#!/usr/bin/env python3
"""
Analyze JavaScript test failures to categorize error types.
"""

import json
import os
import re
from collections import Counter, defaultdict
from pathlib import Path

def analyze_diagnostic_file(filepath):
    """Analyze a single diagnostic JSON file."""
    try:
        with open(filepath, 'r') as f:
            data = json.load(f)

        entry_id = data.get("entry_id", "unknown")
        exit_code = data.get("docker_exit_code", 0)
        stdout = data.get("docker_stdout_full", "")
        error_category = data.get("error_category", "unknown")

        # Try to find the actual log file for complete output
        log_path = None
        log_dir = Path(filepath).parent
        base_name = Path(filepath).stem.replace("_diagnostic", "")
        potential_log = log_dir / f"{base_name}.log"

        if potential_log.exists() and potential_log.stat().st_size > 0:
            with open(potential_log, 'r') as f:
                log_content = f.read()
        else:
            log_content = stdout

        return {
            "entry_id": entry_id,
            "exit_code": exit_code,
            "error_category": error_category,
            "stdout": stdout,
            "log_content": log_content
        }
    except Exception as e:
        return None

def categorize_error(entry_data):
    """Categorize the type of error based on log content."""
    stdout = entry_data["stdout"]
    log = entry_data["log_content"]
    exit_code = entry_data["exit_code"]

    # Success
    if exit_code == 0:
        return "SUCCESS"

    # Check for specific error patterns
    if "No tests found" in stdout or "No tests found" in log:
        return "JEST_NO_TESTS_FOUND"

    if "Cannot find module" in log or "MODULE_NOT_FOUND" in log:
        return "MODULE_NOT_FOUND"

    if "FAIL" in log and "Test Suites: " in log:
        # Tests ran but some failed
        return "TEST_ASSERTION_FAILURES"

    if "SyntaxError" in log:
        return "SYNTAX_ERROR"

    if "timeout" in log.lower() or "TIMEOUT" in log:
        return "TIMEOUT"

    if "pull access denied" in stdout or "Unable to find image" in stdout:
        return "DOCKER_IMAGE_MISSING"

    if exit_code == 125:
        return "DOCKER_ERROR"

    if exit_code == 1 and len(log) < 100:
        return "EMPTY_OUTPUT"

    return "OTHER_ERROR"

def extract_module_errors(log_content):
    """Extract module names that couldn't be found."""
    pattern = r"Cannot find module '([^']+)'"
    matches = re.findall(pattern, log_content)
    return matches

def main():
    logs_dir = Path("/Users/piccoletto/Desktop/Everything/pisa/tesi/Sustainable-Code-Refactoring-with-LLMs/src/logs")

    print("Analyzing JavaScript test failures...")
    print("=" * 80)

    # Collect all diagnostic files
    diagnostic_files = list(logs_dir.glob("*javascript*diagnostic.json"))
    print(f"\nFound {len(diagnostic_files)} JavaScript diagnostic files")

    # Analyze all files
    categories = Counter()
    module_errors = Counter()
    error_examples = defaultdict(list)

    for filepath in diagnostic_files:
        entry_data = analyze_diagnostic_file(filepath)
        if entry_data is None:
            continue

        category = categorize_error(entry_data)
        categories[category] += 1

        # Collect examples (max 3 per category)
        if len(error_examples[category]) < 3:
            error_examples[category].append(entry_data["entry_id"])

        # Extract module errors
        if category == "MODULE_NOT_FOUND":
            modules = extract_module_errors(entry_data["log_content"])
            for mod in modules:
                module_errors[mod] += 1

    # Print results
    print("\n" + "=" * 80)
    print("ERROR CATEGORY BREAKDOWN")
    print("=" * 80)

    total = sum(categories.values())
    for category, count in categories.most_common():
        percentage = (count / total) * 100
        print(f"\n{category}:")
        print(f"  Count: {count} ({percentage:.1f}%)")
        print(f"  Examples: {', '.join(error_examples[category][:3])}")

    # Print module errors
    if module_errors:
        print("\n" + "=" * 80)
        print("TOP MODULE NOT FOUND ERRORS")
        print("=" * 80)
        for module, count in module_errors.most_common(15):
            print(f"  {module}: {count} times")

    print("\n" + "=" * 80)
    print("SUMMARY")
    print("=" * 80)
    print(f"Total entries analyzed: {total}")
    print(f"Success rate: {categories['SUCCESS']} ({categories['SUCCESS']/total*100:.1f}%)")
    print(f"Failure rate: {total - categories['SUCCESS']} ({(total - categories['SUCCESS'])/total*100:.1f}%)")

    # Key findings
    print("\n" + "=" * 80)
    print("KEY FINDINGS")
    print("=" * 80)

    jest_no_tests = categories["JEST_NO_TESTS_FOUND"]
    module_not_found = categories["MODULE_NOT_FOUND"]
    test_failures = categories["TEST_ASSERTION_FAILURES"]

    print(f"\n1. JEST_NO_TESTS_FOUND: {jest_no_tests} ({jest_no_tests/total*100:.1f}%)")
    print("   - Jest cannot find test files due to naming convention mismatch")
    print("   - Tests are named *_testSuite.js but Jest expects *.test.js or *.spec.js")
    print("   - FIX: Update jest.config.js to include testMatch pattern for *_testSuite.js")

    print(f"\n2. MODULE_NOT_FOUND: {module_not_found} ({module_not_found/total*100:.1f}%)")
    print("   - Test files cannot import the actual code files")
    print("   - Usually due to incorrect import paths or file extensions")
    print("   - FIX: Adjust import paths or ensure files are properly copied to Docker container")

    print(f"\n3. TEST_ASSERTION_FAILURES: {test_failures} ({test_failures/total*100:.1f}%)")
    print("   - Tests run successfully but assertions fail")
    print("   - This is expected behavior - base code has bugs")
    print("   - NO FIX NEEDED: These should be filtered in analysis")

if __name__ == "__main__":
    main()
