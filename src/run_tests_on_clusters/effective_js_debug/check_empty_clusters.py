#!/usr/bin/env python3
"""Check for clusters with empty JavaScript arrays"""

import json
import os
from pathlib import Path

clusters_dir = Path("/Users/piccoletto/Desktop/Everything/pisa/tesi/Sustainable-Code-Refactoring-with-LLMs/src/clusters")

empty_js_clusters = []
non_empty_js_clusters = []

for cluster_file in sorted(clusters_dir.glob("cluster_*.json")):
    try:
        with open(cluster_file) as f:
            data = json.load(f)

        # Check if has JavaScript key
        if "javascript" in data:
            js_entries = data["javascript"]
            cluster_name = cluster_file.stem.replace("cluster_", "")

            if isinstance(js_entries, list) and len(js_entries) == 0:
                empty_js_clusters.append(cluster_name)
            elif isinstance(js_entries, list) and len(js_entries) > 0:
                non_empty_js_clusters.append(cluster_name)

    except Exception as e:
        print(f"Error reading {cluster_file.name}: {e}")

print("=" * 80)
print(f"CLUSTER ANALYSIS")
print("=" * 80)
print(f"\nClusters with NON-EMPTY JavaScript arrays: {len(non_empty_js_clusters)}")
print(f"Clusters with EMPTY JavaScript arrays: {len(empty_js_clusters)}")
print()

if empty_js_clusters:
    print("Empty JavaScript clusters (first 20):")
    for name in empty_js_clusters[:20]:
        print(f"  - {name}")
    print()

print("=" * 80)
print("Writing valid cluster names to file...")
print("=" * 80)

# Write non-empty cluster names to file
output_file = Path("/Users/piccoletto/Desktop/Everything/pisa/tesi/Sustainable-Code-Refactoring-with-LLMs/src/run_tests_on_clusters/effective_js_debug/valid_js_clusters.txt")
with open(output_file, 'w') as f:
    for name in non_empty_js_clusters:
        f.write(f"{name}\n")

print(f"\nWritten {len(non_empty_js_clusters)} valid cluster names to: {output_file}")
print(f"These are the clusters that actually contain JavaScript entries.")
