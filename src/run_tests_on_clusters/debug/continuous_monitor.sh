#!/bin/bash
# Continuous monitoring script for JavaScript execution

LOG_FILE="javascript_rerun_20251114_195934.log"
REPORT_INTERVAL=600  # Report every 10 minutes

echo "Continuous JavaScript Execution Monitor"
echo "========================================"
echo "Log file: $LOG_FILE"
echo "Reporting every $((REPORT_INTERVAL/60)) minutes"
echo ""

last_count=0

while true; do
    if [ ! -f "$LOG_FILE" ]; then
        echo "Waiting for log file..."
        sleep 10
        continue
    fi

    # Count completed clusters
    success=$(grep -c "✓ Success" full_js_base_rerun.log 2>/dev/null || echo 0)
    failed=$(grep -c "✗ Failed" full_js_base_rerun.log 2>/dev/null || echo 0)
    total=$((success + failed))

    # Only report if progress changed
    if [ $total -ne $last_count ]; then
        clear
        echo "JavaScript Base Code Execution - Live Monitor"
        echo "=============================================="
        echo "$(date '+%Y-%m-%d %H:%M:%S')"
        echo ""
        echo "Progress: $total / 103 clusters ($((total * 100 / 103))%)"
        echo "  ✓ Success: $success"
        echo "  ✗ Failed: $failed"

        if [ $total -gt 0 ]; then
            success_rate=$((success * 100 / total))
            echo "  Success rate: ${success_rate}%"
        fi

        echo ""
        echo "Last 5 clusters:"
        grep "Processing cluster" full_js_base_rerun.log | tail -5 | sed 's/.*Processing cluster: /  - /' | sed 's/\x1b\[[0-9;]*m//g'

        echo ""

        # Check for completion
        if grep -q "Execution Complete\|Done!" full_js_base_rerun.log 2>/dev/null; then
            echo "✅ BASE CODE EXECUTION COMPLETED!"
            break
        fi

        # Estimate time remaining
        if [ $total -gt 5 ]; then
            # Calculate rate (clusters per minute)
            start_time=$(stat -f %B "$LOG_FILE" 2>/dev/null || stat -c %Y "$LOG_FILE")
            current_time=$(date +%s)
            elapsed=$((current_time - start_time))
            rate=$(echo "scale=2; $total / ($elapsed / 60)" | bc)
            remaining=$((103 - total))
            eta_minutes=$(echo "scale=0; $remaining / $rate" | bc)
            echo "Estimated time remaining: ${eta_minutes} minutes"
        fi

        last_count=$total
    fi

    sleep $REPORT_INTERVAL
done

echo ""
echo "Monitoring complete. Generating final report..."
