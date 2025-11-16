#!/usr/bin/env python3
"""
Script to run ONLY JavaScript v4 tests for all clusters.
This will ADD results to existing files without overwriting other languages or versions.

This script:
1. Finds all clusters with JavaScript entries
2. Runs only JavaScript tests with prompt version v4
3. Preserves all existing results for other languages/versions
"""

import subprocess
import sys
import os
import json
from pathlib import Path

def get_clusters_with_javascript():
    """Find all cluster names that have JavaScript entries."""
    clusters_dir = Path(__file__).parent.parent / "clusters"
    js_clusters = []

    for cluster_file in clusters_dir.glob("cluster_*.json"):
        try:
            with open(cluster_file, 'r') as f:
                data = json.load(f)
                if 'javascript' in data and len(data['javascript']) > 0:
                    cluster_name = cluster_file.stem.replace("cluster_", "")
                    js_count = len(data['javascript'])
                    js_clusters.append((cluster_name, js_count))
        except Exception as e:
            print(f"Error reading {cluster_file}: {e}")

    return sorted(js_clusters, key=lambda x: x[0])


def check_existing_results(cluster_name):
    """Check if v4 results already exist for JavaScript in this cluster."""
    outputs_dir = Path(__file__).parent.parent / "execution_outputs"

    # Check first run file
    v4_file = outputs_dir / f"{cluster_name}_results_v4_1.json"
    if not v4_file.exists():
        return False, "No v4 file exists"

    try:
        with open(v4_file, 'r') as f:
            data = json.load(f)
            if 'results' in data and 'javascript' in data['results']:
                return True, f"{len(data['results']['javascript'])} JavaScript entries"
            else:
                return False, "No JavaScript entries in v4 file"
    except Exception as e:
        return False, f"Error reading: {e}"


def run_javascript_v4_for_cluster(cluster_name):
    """Run JavaScript v4 tests for a specific cluster."""
    script_path = Path(__file__).parent / "run_tests_on_cluster.py"

    cmd = [
        "python3",
        str(script_path),
        "--cluster-name", cluster_name,
        "--run-quantity", "5",
        "--llm-only",
        "--prompt-version", "4",
        "--languages", "javascript",
        "--selective-rerun"  # This ensures results are merged, not overwritten
    ]

    print(f"\nRunning: {' '.join(cmd)}")

    try:
        result = subprocess.run(
            cmd,
            capture_output=False,
            text=True,
            timeout=600  # 10 minute timeout per cluster
        )
        return result.returncode == 0
    except subprocess.TimeoutExpired:
        print(f"  TIMEOUT for cluster {cluster_name}")
        return False
    except Exception as e:
        print(f"  ERROR: {e}")
        return False


def main():
    print("=" * 70)
    print("JavaScript v4 Execution Script")
    print("=" * 70)
    print("This script will run ONLY JavaScript tests for prompt version v4.")
    print("It will ADD results to existing files without deleting other data.")
    print("=" * 70)

    # Get all clusters with JavaScript
    js_clusters = get_clusters_with_javascript()
    print(f"\nFound {len(js_clusters)} clusters with JavaScript entries")

    # Check which need execution
    to_execute = []
    already_done = []

    print("\nChecking existing results...")
    for cluster_name, js_count in js_clusters:
        exists, info = check_existing_results(cluster_name)
        if exists:
            already_done.append((cluster_name, js_count, info))
        else:
            to_execute.append((cluster_name, js_count, info))

    print(f"\nAlready have JavaScript v4 results: {len(already_done)} clusters")
    print(f"Need to execute JavaScript v4: {len(to_execute)} clusters")

    if not to_execute:
        print("\nAll clusters already have JavaScript v4 results!")
        return 0

    print("\n" + "=" * 70)
    print("Clusters to execute:")
    print("=" * 70)
    for cluster_name, js_count, info in to_execute[:20]:
        print(f"  {cluster_name}: {js_count} JS entries ({info})")
    if len(to_execute) > 20:
        print(f"  ... and {len(to_execute) - 20} more")

    # Ask for confirmation
    print(f"\nTotal JavaScript entries to execute: {sum(c[1] for c in to_execute)}")
    response = input("\nProceed with execution? (yes/no): ")
    if response.lower() != 'yes':
        print("Aborted.")
        return 1

    # Execute
    print("\n" + "=" * 70)
    print("Starting execution...")
    print("=" * 70)

    successful = 0
    failed = 0

    for i, (cluster_name, js_count, _) in enumerate(to_execute, 1):
        print(f"\n[{i}/{len(to_execute)}] Processing {cluster_name} ({js_count} JS entries)...")

        if run_javascript_v4_for_cluster(cluster_name):
            print(f"  SUCCESS: {cluster_name}")
            successful += 1
        else:
            print(f"  FAILED: {cluster_name}")
            failed += 1

    print("\n" + "=" * 70)
    print("EXECUTION COMPLETE")
    print("=" * 70)
    print(f"Successful: {successful}")
    print(f"Failed: {failed}")
    print(f"Total: {len(to_execute)}")

    return 0 if failed == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
