#!/bin/bash

# Force re-execution of JavaScript base tests - ONLY clusters with NON-EMPTY JavaScript entries
# This script uses a pre-validated list of 107 clusters with actual JavaScript code

echo "========================================================================"
echo "Forced JavaScript Base Test Re-Execution (FULLY CORRECTED)"
echo "========================================================================"
echo ""
echo "This will execute ONLY the 107 clusters with non-empty JavaScript arrays"
echo "Timestamp: $(date)"
echo ""

cd /Users/piccoletto/Desktop/Everything/pisa/tesi/Sustainable-Code-Refactoring-with-LLMs/src/run_tests_on_clusters/effective_js_debug

# Read valid cluster names from the pre-generated file
CLUSTER_NAMES=$(cat valid_js_clusters.txt | tr '\n' ' ')

NUM_CLUSTERS=$(cat valid_js_clusters.txt | wc -l | tr -d ' ')

echo "Found $NUM_CLUSTERS clusters with non-empty JavaScript entries"
echo ""
echo "Starting execution..."
echo "========================================================================"
echo ""

# Execute with proper flags
cd /Users/piccoletto/Desktop/Everything/pisa/tesi/Sustainable-Code-Refactoring-with-LLMs/src/run_tests_on_clusters

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
