#!/bin/bash
cd "$(dirname "$0")"

echo "=========================================="
echo "JAVASCRIPT BASE EXECUTION - ALL CLUSTERS"
echo "=========================================="

CLUSTERS=$(cat effective_js_debug/valid_js_clusters.txt)
TOTAL=$(wc -l < effective_js_debug/valid_js_clusters.txt | tr -d ' ')
COUNT=0

for cluster in $CLUSTERS; do
  COUNT=$((COUNT + 1))
  echo ""
  echo "[$COUNT/$TOTAL] Processing cluster: $cluster"
  
  python3 run_tests_on_cluster.py \
    --cluster-name "$cluster" \
    --base-only \
    --languages javascript \
    --selective-rerun \
    --overwrite-results \
    --run-quantity 5
  
  if [ $? -ne 0 ]; then
    echo "WARNING: Cluster $cluster failed"
  fi
done

echo ""
echo "BASE EXECUTION COMPLETE"
