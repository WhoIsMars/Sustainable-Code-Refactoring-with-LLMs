#!/bin/bash

# Force re-execution of ALL JavaScript base tests with the fixed Docker containers
# This script properly uses the --overwrite-results flag to force re-execution

echo "========================================================================"
echo "Forced JavaScript Base Test Re-Execution"
echo "========================================================================"
echo ""
echo "This will force re-execute ALL JavaScript base tests (5 runs each)"
echo "to apply the infrastructure fixes:"
echo "  1. Jest configuration updated for *_testSuite.js pattern"
echo "  2. Dependencies added: chai, big-integer"
echo ""
echo "Timestamp: $(date)"
echo ""

# Get list of all cluster names WITHOUT the "cluster_" prefix (script will add it)
CLUSTER_NAMES=$(ls ../../../src/clusters/cluster_*.json 2>/dev/null | xargs -n1 basename | sed 's/\.json$//' | sed 's/^cluster_//' | tr '\n' ' ')

NUM_CLUSTERS=$(echo "$CLUSTER_NAMES" | wc -w | tr -d ' ')

echo "Found $NUM_CLUSTERS cluster files"
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
