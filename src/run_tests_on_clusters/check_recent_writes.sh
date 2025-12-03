#!/bin/bash
#
# Check for recently modified result files
# This helps verify if execution is actually writing results
#

OUTPUT_DIR="../execution_outputs"

echo "================================================================================"
echo "CHECKING FOR RECENTLY MODIFIED RESULT FILES"
echo "================================================================================"
echo ""

echo "Files modified in the last 5 minutes:"
find "$OUTPUT_DIR" -name "*_results_*.json" -mmin -5 -exec ls -lh {} \; | tail -20

echo ""
echo "Files modified in the last 1 minute:"
find "$OUTPUT_DIR" -name "*_results_*.json" -mmin -1 -exec ls -lh {} \; | tail -10

echo ""
echo "Total result files:"
find "$OUTPUT_DIR" -name "*_results_*.json" | wc -l

echo ""
echo "================================================================================"
