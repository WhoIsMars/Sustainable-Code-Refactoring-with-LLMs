#!/bin/bash

# Force re-execution of JavaScript base tests - ONLY clusters with JavaScript entries
# This script properly filters clusters that contain JavaScript before execution

echo "========================================================================"
echo "Forced JavaScript Base Test Re-Execution (FIXED)"
echo "========================================================================"
echo ""
echo "This will force re-execute ONLY JavaScript base tests (5 runs each)"
echo "for clusters that actually contain JavaScript entries."
echo ""
echo "Infrastructure fixes applied:"
echo "  1. Jest configuration updated for *_testSuite.js pattern"
echo "  2. Dependencies added: chai, big-integer"
echo ""
echo "Timestamp: $(date)"
echo ""

# Get ONLY cluster names that contain JavaScript entries
cd /Users/piccoletto/Desktop/Everything/pisa/tesi/Sustainable-Code-Refactoring-with-LLMs

CLUSTER_NAMES=$(grep -l '"javascript"' src/clusters/cluster_*.json | xargs -n1 basename | sed 's/\.json$//' | sed 's/^cluster_//' | tr '\n' ' ')

NUM_CLUSTERS=$(echo "$CLUSTER_NAMES" | wc -w | tr -d ' ')

echo "Found $NUM_CLUSTERS clusters with JavaScript entries"
echo ""
echo "Starting execution..."
echo "========================================================================"
echo ""

# Execute with proper flags
cd src/run_tests_on_clusters

python3 run_tests_on_cluster.py \
  --base-only \
  --languages javascript \
  --run-quantity 5 \
  --overwrite-results \
  --container-prefix persistent \
  --cluster-names $CLUSTER_NAMES

EXIT_CODE=$?

echo ""
echo "========================================================================"
echo "Execution completed with exit code: $EXIT_CODE"
echo "Timestamp: $(date)"
echo "========================================================================"

exit $EXIT_CODE
