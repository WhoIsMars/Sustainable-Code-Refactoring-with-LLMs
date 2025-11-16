#!/bin/bash
# Quick status check for parallel execution

echo "=========================================="
echo "JavaScript Parallel Execution Status"
echo "=========================================="
echo "Time: $(date '+%H:%M:%S')"
echo ""

# Count active workers
WORKERS=$(ps aux | grep 'run_tests_on_cluster.py' | grep -v grep | wc -l | tr -d ' ')
echo "Active workers: $WORKERS/6"
echo ""

# Count v3/v4 result files from TODAY
RECENT=$(find ../execution_outputs -name '*_results_v3_*.json' -o -name '*_results_v4_*.json' 2>/dev/null | xargs ls -l 2>/dev/null | grep "Nov 15" | wc -l | tr -d ' ')
echo "V3/V4 files created today: $RECENT"
echo ""

# Show most recent 5 completions
echo "Latest completions:"
ls -lt ../execution_outputs/*_results_v*.json 2>/dev/null | head -5 | awk '{print "  " $9 " at " $6 " " $7 " " $8}' | sed 's|.*/||'
echo ""

# Count errors
ERRORS=$(ls errors/parallel_*.log 2>/dev/null | wc -l | tr -d ' ')
echo "Errors: $ERRORS"
echo ""

# Calculate rough progress
TOTAL=220
echo "Estimated progress: $RECENT/$TOTAL ($(( RECENT * 100 / TOTAL ))%)"
echo "=========================================="
