#!/usr/bin/env python3
"""
Re-execute JavaScript base tests for entries that were fixed by infrastructure changes.
"""

import json
import os
import subprocess
import sys
from pathlib import Path
from collections import defaultdict

# Add parent directory to path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", ".."))
from utility_dir import utility_paths

LOGS_DIR = utility_paths.SRC_DIR / "logs"
CLUSTERS_DIR = utility_paths.CLUSTERS_DIR_FILEPATH
OUTPUT_DIR = utility_paths.OUTPUT_DIR_FILEPATH

def find_affected_entries():
    """
    Find JavaScript entries that should be re-executed based on diagnostic analysis.
    Returns dict: {cluster_name: [entry_ids]}
    """
    print("Analyzing diagnostic files to find affected entries...")

    # Categories we want to re-execute
    retryable_categories = [
        "JEST_NO_TESTS_FOUND",  # Fixed by jest.config update
        "MODULE_NOT_FOUND",      # Potentially fixed by chai/big-integer dependencies
    ]

    affected_entries = defaultdict(set)

    # Scan all JavaScript diagnostic files
    for diag_file in LOGS_DIR.glob("*javascript*diagnostic.json"):
        try:
            with open(diag_file, 'r') as f:
                data = json.load(f)

            entry_id = data.get("entry_id")
            error_category = data.get("error_category", "")
            stdout = data.get("docker_stdout_full", "")

            # Categorize error
            should_retry = False

            if "No tests found" in stdout:
                should_retry = True
                category = "JEST_NO_TESTS_FOUND"
            elif data.get("docker_exit_code") == 1:
                # Check if it's a module not found error we might have fixed
                if "Cannot find module" in stdout or "MODULE_NOT_FOUND" in stdout:
                    if "chai" in stdout or "big-integer" in stdout:
                        should_retry = True
                        category = "MODULE_NOT_FOUND"

            if should_retry and entry_id:
                # Extract cluster name from entry_id
                # Format: javascript_<cluster>_<source>
                parts = entry_id.split('_')
                if len(parts) >= 2:
                    # Remove language prefix
                    cluster_name = '_'.join(parts[1:]).split('_exercism')[0]
                    cluster_name = cluster_name.replace('-', '_')
                    affected_entries[cluster_name].add(entry_id)

        except Exception as e:
            continue

    return affected_entries

def get_cluster_names():
    """Get all cluster names that have JavaScript entries."""
    cluster_names = []
    for cluster_file in CLUSTERS_DIR.glob("cluster_*.json"):
        try:
            with open(cluster_file, 'r') as f:
                data = json.load(f)

            # Check if cluster has JavaScript entries
            if "javascript" in data:
                cluster_name = cluster_file.stem  # This is already "cluster_<name>"
                cluster_names.append(cluster_name)

        except Exception as e:
            continue

    return sorted(cluster_names)

def count_javascript_entries_in_cluster(cluster_name):
    """Count how many JavaScript entries are in a cluster."""
    cluster_file = CLUSTERS_DIR / f"{cluster_name}.json"

    if not cluster_file.exists():
        return 0

    try:
        with open(cluster_file, 'r') as f:
            data = json.load(f)

        return len(data.get("javascript", []))
    except:
        return 0

def main():
    print("=" * 80)
    print("JavaScript Test Re-Execution Script")
    print("=" * 80)
    print()
    print("This script will re-execute JavaScript base tests for entries that")
    print("were affected by the infrastructure fixes:")
    print("  1. Jest configuration update (*_testSuite.js pattern)")
    print("  2. New dependencies (chai, big-integer)")
    print()

    # Find affected entries
    affected_by_cluster = find_affected_entries()

    print(f"\nFound {sum(len(v) for v in affected_by_cluster.values())} unique affected entry IDs")
    print(f"Across {len(affected_by_cluster)} clusters")
    print()

    # Show top 10 clusters by affected entries
    sorted_clusters = sorted(affected_by_cluster.items(), key=lambda x: len(x[1]), reverse=True)
    print("Top 10 clusters with most affected entries:")
    for i, (cluster, entries) in enumerate(sorted_clusters[:10], 1):
        total_js = count_javascript_entries_in_cluster(f"cluster_{cluster}")
        print(f"  {i:2d}. {cluster:30s}: {len(entries):3d} affected entries (total JS entries: {total_js})")

    print()
    print("=" * 80)
    print("Execution Options:")
    print("=" * 80)
    print("1. Re-execute ALL JavaScript base tests (recommended for comprehensive fix)")
    print("2. Re-execute only clusters with affected entries")
    print("3. Re-execute specific clusters (manual selection)")
    print("4. Exit without executing")
    print()

    choice = input("Select option (1-4): ").strip()

    if choice == "1":
        # Re-execute ALL JavaScript base tests
        print("\nOption 1: Re-executing ALL JavaScript base tests")
        print("This will re-run base tests for ALL JavaScript entries to ensure comprehensive fixing.")

        confirm = input("\nThis may take a while. Proceed? (yes/no): ").strip().lower()
        if confirm not in ["yes", "y"]:
            print("Aborted.")
            return

        # Get all clusters with JavaScript
        all_clusters = get_cluster_names()
        print(f"\nFound {len(all_clusters)} clusters with JavaScript entries")

        # Build command - use absolute path
        run_tests_script = Path(__file__).parent.parent / "run_tests_on_cluster.py"
        cmd = [
            "python3",
            str(run_tests_script),
            "--base-only",
            "--languages", "javascript",
            "--run-quantity", "5",
            "--container-prefix", "persistent",
            "--cluster-names"
        ] + all_clusters

        print(f"\nExecuting command:")
        print(" ".join(cmd))
        print()

        # Execute
        result = subprocess.run(cmd)
        sys.exit(result.returncode)

    elif choice == "2":
        # Re-execute only affected clusters
        print("\nOption 2: Re-executing only clusters with affected entries")

        affected_cluster_names = [f"cluster_{c}" for c in affected_by_cluster.keys()]
        print(f"\nWill re-execute {len(affected_cluster_names)} clusters")

        confirm = input("\nProceed? (yes/no): ").strip().lower()
        if confirm not in ["yes", "y"]:
            print("Aborted.")
            return

        # Build command - use absolute path
        run_tests_script = Path(__file__).parent.parent / "run_tests_on_cluster.py"
        cmd = [
            "python3",
            str(run_tests_script),
            "--base-only",
            "--languages", "javascript",
            "--run-quantity", "5",
            "--container-prefix", "persistent",
            "--cluster-names"
        ] + affected_cluster_names

        print(f"\nExecuting command:")
        print(" ".join(cmd))
        print()

        # Execute
        result = subprocess.run(cmd)
        sys.exit(result.returncode)

    elif choice == "3":
        # Manual cluster selection
        print("\nOption 3: Manual cluster selection")
        print("\nEnter cluster names separated by spaces (e.g., grade_school bob hello_world):")
        clusters_input = input("> ").strip()

        if not clusters_input:
            print("No clusters specified. Aborted.")
            return

        cluster_names = [f"cluster_{c}" if not c.startswith("cluster_") else c
                        for c in clusters_input.split()]

        print(f"\nWill execute {len(cluster_names)} clusters: {', '.join(cluster_names)}")

        confirm = input("\nProceed? (yes/no): ").strip().lower()
        if confirm not in ["yes", "y"]:
            print("Aborted.")
            return

        # Build command - use absolute path
        run_tests_script = Path(__file__).parent.parent / "run_tests_on_cluster.py"
        cmd = [
            "python3",
            str(run_tests_script),
            "--base-only",
            "--languages", "javascript",
            "--run-quantity", "5",
            "--container-prefix", "persistent",
            "--cluster-names"
        ] + cluster_names

        print(f"\nExecuting command:")
        print(" ".join(cmd))
        print()

        # Execute
        result = subprocess.run(cmd)
        sys.exit(result.returncode)

    else:
        print("\nExiting without execution.")
        return

if __name__ == "__main__":
    main()
