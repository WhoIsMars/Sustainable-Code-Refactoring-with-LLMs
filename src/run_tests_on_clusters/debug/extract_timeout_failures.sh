#!/bin/bash
# Extract timeout failures from log and create retry list

LOG_FILE="full_js_llm_all_rerun.log"
OUTPUT_FILE="timeout_failures.json"

echo "Extracting timeout failures from $LOG_FILE..."

# Use Python to parse log and create JSON
python3 << 'EOF'
import re
import json
from collections import defaultdict

log_file = "full_js_llm_all_rerun.log"
timeout_failures = defaultdict(list)

try:
    with open(log_file, 'r', encoding='utf-8', errors='ignore') as f:
        lines = f.readlines()

    current_cluster = None
    current_version = None

    for i, line in enumerate(lines):
        # Match: [HH:MM:SS] [N/103] vX - Processing: cluster_name
        match = re.search(r'\[(\d+)/\d+\]\s+(v\d+)\s+-\s+Processing:\s+(\w+)', line)
        if match:
            current_version = match.group(2)
            current_cluster = match.group(3)
            continue

        # Check for timeout on current or next line
        if '✗ Timeout' in line:
            if current_cluster and current_version:
                if current_version not in timeout_failures[current_cluster]:
                    timeout_failures[current_cluster].append(current_version)
            current_cluster = None
            current_version = None

    # Convert to sorted structure
    result = {
        'total_timeouts': sum(len(v) for v in timeout_failures.values()),
        'clusters_affected': len(timeout_failures),
        'failures': {cluster: sorted(versions) for cluster, versions in sorted(timeout_failures.items())}
    }

    with open('timeout_failures.json', 'w') as f:
        json.dump(result, f, indent=2)

    print(f"Found {result['total_timeouts']} timeout failures across {result['clusters_affected']} clusters")
    print("\nClusters with timeouts:")
    for cluster, versions in sorted(timeout_failures.items()):
        print(f"  - {cluster}: {', '.join(versions)}")

except FileNotFoundError:
    print(f"Error: {log_file} not found")
    result = {'total_timeouts': 0, 'clusters_affected': 0, 'failures': {}}
    with open('timeout_failures.json', 'w') as f:
        json.dump(result, f, indent=2)

EOF

echo ""
echo "✓ Timeout failures saved to $OUTPUT_FILE"
