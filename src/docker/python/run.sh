#!/bin/bash
set -e

echo "==> Working dir:"
pwd

echo "==> File structure:"
ls -R .

echo "==> Looking for Python test files..."
find . -name "*test*.py"

echo "==> Detecting test framework..."
# Controlla se ci sono classi unittest.TestCase
if grep -rq "class .*Test.*(unittest.TestCase)" .; then
    echo "✓ Detected unittest-based tests"
    TEST_FRAMEWORK="unittest"
elif grep -rq "import pytest\|from pytest\|@pytest\|def test_" .; then
    echo "✓ Detected pytest-based tests"
    TEST_FRAMEWORK="pytest"
else
    echo "⚠ No tests found, using pytest by default"
    TEST_FRAMEWORK="pytest"
fi

run_tests() {
    local framework=$1
    echo "==> Running tests with $framework..."
    if [ "$framework" = "pytest" ]; then
        /usr/bin/time -v python3 -m pytest -v . 2>&1 | tee output.log
    else
        /usr/bin/time -v python3 -m unittest discover -s . -p "*test*.py" 2>&1 | tee output.log
    fi
    return ${PIPESTATUS[0]}  # exit code del comando python
}

# Primo tentativo
run_tests "$TEST_FRAMEWORK"
EXIT_CODE=$?

# Se pytest ritorna 5 (no tests) o unittest 0 ma 0 tests (optional)
if [ "$EXIT_CODE" -ne 0 ]; then
    echo "⚠ Tests failed or none detected with $TEST_FRAMEWORK, trying the other framework..."
    if [ "$TEST_FRAMEWORK" = "pytest" ]; then
        run_tests "unittest"
    else
        run_tests "pytest"
    fi
fi

echo ""
echo "==> Test execution completed"
