#!/bin/bash
# Automatic completion script for JavaScript re-execution
# Waits for main LLM execution, then retries timeout failures

set -e

PID_FILE="js_llm_rerun.pid"
LOG_FILE="full_js_llm_all_rerun.log"

echo "================================================================================"
echo "AUTOMATIC JAVASCRIPT EXECUTION COMPLETION"
echo "================================================================================"
echo "Started: $(date '+%Y-%m-%d %H:%M:%S')"
echo ""

# Step 1: Wait for main LLM execution to complete
echo "Step 1: Waiting for main LLM execution to complete..."
echo "  PID file: $PID_FILE"
echo "  Log file: $LOG_FILE"
echo ""

while true; do
    if [ -f "$PID_FILE" ]; then
        PID=$(cat "$PID_FILE")
        if ps -p "$PID" > /dev/null 2>&1; then
            # Still running - show progress
            SUCCESS_COUNT=$(grep -c "✓ Success" "$LOG_FILE" 2>/dev/null || echo 0)
            TIMEOUT_COUNT=$(grep -c "✗ Timeout" "$LOG_FILE" 2>/dev/null || echo 0)
            echo -ne "\r[$(date '+%H:%M:%S')] LLM execution in progress... Success: $SUCCESS_COUNT | Timeouts: $TIMEOUT_COUNT"
            sleep 60
        else
            echo ""
            echo "✓ Main LLM execution completed (PID $PID no longer running)"
            break
        fi
    else
        echo "⚠️  PID file not found, checking log for completion..."
        if grep -q "ALL LLM EXECUTIONS COMPLETED\|EXECUTION COMPLETED" "$LOG_FILE" 2>/dev/null; then
            echo "✓ Found completion message in log"
            break
        fi
        sleep 60
    fi
done

echo ""
echo "Waiting 10 seconds for file writes to complete..."
sleep 10

# Step 2: Extract timeout failures
echo ""
echo "================================================================================"
echo "Step 2: Extracting timeout failures..."
echo "================================================================================"
./extract_timeout_failures.sh

# Check if there are timeouts
TIMEOUT_COUNT=$(python3 -c "import json; data=json.load(open('timeout_failures.json')); print(data['total_timeouts'])")

if [ "$TIMEOUT_COUNT" -eq 0 ]; then
    echo ""
    echo "✅ No timeout failures detected - JavaScript re-execution completed successfully!"
    echo "================================================================================"
    exit 0
fi

# Step 3: Retry timeout failures
echo ""
echo "================================================================================"
echo "Step 3: Re-executing timeout failures WITHOUT timeout limit..."
echo "================================================================================"
echo "Found $TIMEOUT_COUNT timeout failures to retry"
echo ""

# Run retry script with automatic yes
yes y | python3 -u retry_timeouts.py

# Step 4: Verify completion
echo ""
echo "================================================================================"
echo "Step 4: Final verification..."
echo "================================================================================"

# Re-extract to see if any still failed
./extract_timeout_failures.sh

REMAINING_TIMEOUTS=$(python3 -c "import json; data=json.load(open('timeout_failures.json')); print(data['total_timeouts'])")

if [ "$REMAINING_TIMEOUTS" -eq 0 ]; then
    echo ""
    echo "✅ ALL TIMEOUT FAILURES SUCCESSFULLY COMPLETED!"
    echo "✅ JavaScript re-execution is now complete with all clusters executed"
    echo "================================================================================"
    exit 0
else
    echo ""
    echo "⚠️  Warning: $REMAINING_TIMEOUTS timeout failures remain"
    echo "   Check retry_timeouts.log and errors/ directory for details"
    echo "================================================================================"
    exit 1
fi
