#!/usr/bin/env python3
"""
Optimized JavaScript LLM execution for v3 and v4.

Features:
- Parallel execution of v3 and v4 in separate processes
- Single container per process (reduced Docker overhead)
- Real-time progress logging
- Timeout handling for stuck tests
- Resume capability

Usage:
    python3 parallel_js_v3_v4_executor.py --version 3
    python3 parallel_js_v3_v4_executor.py --version 4
    python3 parallel_js_v3_v4_executor.py --both  # Parallel v3 and v4
"""

import json
import subprocess
import sys
import argparse
import multiprocessing as mp
from datetime import datetime
from pathlib import Path
import time
import signal


def get_js_clusters():
    """Get list of JavaScript clusters."""
    clusters = []
    skip_patterns = ['debug', 'test', 'bad_entries', 'focused_', 'with_metrics']

    clusters_dir = Path(__file__).parent.parent / 'clusters'

    for f in sorted(clusters_dir.glob('cluster_*.json')):
        if any(skip in f.name for skip in skip_patterns):
            continue

        try:
            with open(f) as fp:
                data = json.load(fp)
                if 'javascript' in data and len(data['javascript']) > 0:
                    cluster_name = f.stem.replace('cluster_', '')
                    if not any(skip in cluster_name for skip in skip_patterns):
                        clusters.append(cluster_name)
        except Exception:
            continue

    return clusters


def get_missing_clusters(prompt_version):
    """Get clusters that still need execution for given version."""
    outputs_dir = Path(__file__).parent.parent / "execution_outputs"
    clusters_dir = Path(__file__).parent.parent / "clusters"

    js_clusters = get_js_clusters()
    missing = []

    for cluster_name in js_clusters:
        # Check if all LLM variants are present
        cluster_file = clusters_dir / f"cluster_{cluster_name}.json"
        result_file = outputs_dir / f"{cluster_name}_results_v{prompt_version}_1.json"

        expected_combos = set()
        found_combos = set()

        # Get expected combinations
        try:
            with open(cluster_file) as f:
                data = json.load(f)
                for entry in data.get('javascript', []):
                    for llm_info in entry.get('LLMs', []):
                        if f"_v{prompt_version}" in llm_info.get('filename', ''):
                            llm_type = llm_info.get('type', 'unknown')
                            expected_combos.add((entry['id'], llm_type))
        except Exception:
            pass

        # Get found combinations
        if result_file.exists():
            try:
                with open(result_file) as f:
                    data = json.load(f)
                    if 'results' in data and 'javascript' in data['results']:
                        for entry in data['results']['javascript']:
                            if entry.get('LLM_results'):
                                llm_type = entry['LLM_results'][0].get('LLM_type', 'unknown')
                                found_combos.add((entry['id'], llm_type))
            except Exception:
                pass

        # If missing any combinations, add to list
        if expected_combos - found_combos:
            missing_count = len(expected_combos - found_combos)
            missing.append((cluster_name, missing_count))

    return missing


def execute_cluster(cluster_name, prompt_version, timeout=600):
    """Execute a single cluster with timeout and logging."""
    cmd = [
        'python3', 'run_tests_on_cluster.py',
        '--languages', 'javascript',
        '--run-quantity', '5',
        '--selective-rerun',
        '--cluster-name', cluster_name,
        '--llm-only',
        '--prompt-version', str(prompt_version)
    ]

    timestamp = datetime.now().strftime('%H:%M:%S')
    print(f"[{timestamp}] [v{prompt_version}] Starting {cluster_name}...")
    sys.stdout.flush()

    start_time = time.time()

    try:
        result = subprocess.run(
            cmd,
            capture_output=False,  # Show output in real-time
            text=True,
            timeout=timeout,
            cwd=Path(__file__).parent
        )

        elapsed = time.time() - start_time
        status = "✓ SUCCESS" if result.returncode == 0 else f"✗ FAILED (code {result.returncode})"
        print(f"[{timestamp}] [v{prompt_version}] {cluster_name}: {status} ({elapsed:.1f}s)")
        sys.stdout.flush()

        return result.returncode == 0

    except subprocess.TimeoutExpired:
        elapsed = time.time() - start_time
        print(f"[{timestamp}] [v{prompt_version}] {cluster_name}: ✗ TIMEOUT after {elapsed:.1f}s")
        sys.stdout.flush()
        return False

    except Exception as e:
        print(f"[{timestamp}] [v{prompt_version}] {cluster_name}: ✗ ERROR: {e}")
        sys.stdout.flush()
        return False


def run_version(prompt_version, resume=True):
    """Run all clusters for a specific version."""
    print("=" * 80)
    print(f"JAVASCRIPT LLM EXECUTION - PROMPT VERSION {prompt_version}")
    print("=" * 80)
    print(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print(f"PID: {mp.current_process().pid}")
    print()

    # Get clusters to process
    if resume:
        clusters = get_missing_clusters(prompt_version)
        print(f"Resume mode: Found {len(clusters)} clusters with missing combinations")
    else:
        all_clusters = get_js_clusters()
        clusters = [(c, 0) for c in all_clusters]
        print(f"Full mode: Processing all {len(clusters)} JavaScript clusters")

    if not clusters:
        print(f"✓ All clusters already complete for v{prompt_version}!")
        return 0

    print(f"\nClusters to process:")
    for i, (cluster_name, missing_count) in enumerate(clusters[:10], 1):
        print(f"  {i}. {cluster_name} ({missing_count} missing)")
    if len(clusters) > 10:
        print(f"  ... and {len(clusters) - 10} more")
    print()

    # Execute clusters
    success_count = 0
    failed_count = 0
    failed_clusters = []

    for i, (cluster_name, _) in enumerate(clusters, 1):
        print(f"\n--- [{i}/{len(clusters)}] Processing {cluster_name} ---")

        if execute_cluster(cluster_name, prompt_version):
            success_count += 1
        else:
            failed_count += 1
            failed_clusters.append(cluster_name)

    # Summary
    print()
    print("=" * 80)
    print(f"EXECUTION COMPLETE - v{prompt_version}")
    print("=" * 80)
    print(f"Total: {len(clusters)}")
    print(f"Success: {success_count}")
    print(f"Failed: {failed_count}")

    if failed_clusters:
        print(f"\nFailed clusters:")
        for c in failed_clusters[:20]:
            print(f"  - {c}")
        if len(failed_clusters) > 20:
            print(f"  ... and {len(failed_clusters) - 20} more")

    print(f"\nCompleted: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print("=" * 80)

    return 0 if failed_count == 0 else 1


def run_parallel(versions):
    """Run multiple versions in parallel processes."""
    print("=" * 80)
    print("PARALLEL JAVASCRIPT LLM EXECUTION")
    print("=" * 80)
    print(f"Versions: {versions}")
    print(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print()

    processes = []

    for version in versions:
        p = mp.Process(target=run_version, args=(version,))
        p.start()
        processes.append((version, p))
        print(f"Started process for v{version} (PID: {p.pid})")

    print("\nWaiting for all processes to complete...")
    print("Monitor progress with: tail -f *.log")
    print()

    # Wait for all processes
    results = []
    for version, p in processes:
        p.join()
        results.append((version, p.exitcode))
        print(f"v{version} completed with exit code {p.exitcode}")

    print()
    print("=" * 80)
    print("ALL PARALLEL EXECUTIONS COMPLETE")
    print("=" * 80)
    for version, exitcode in results:
        status = "✓ SUCCESS" if exitcode == 0 else f"✗ FAILED (code {exitcode})"
        print(f"  v{version}: {status}")

    return 0 if all(code == 0 for _, code in results) else 1


def main():
    parser = argparse.ArgumentParser(description="Optimized JavaScript LLM execution")
    parser.add_argument('--version', type=int, choices=[3, 4], help='Prompt version to run')
    parser.add_argument('--both', action='store_true', help='Run v3 and v4 in parallel')
    parser.add_argument('--no-resume', action='store_true', help='Re-run all clusters (not just missing)')
    parser.add_argument('--analyze', action='store_true', help='Only analyze what needs to be done')

    args = parser.parse_args()

    if args.analyze:
        print("=" * 80)
        print("ANALYSIS OF MISSING CLUSTERS")
        print("=" * 80)
        for version in [3, 4]:
            missing = get_missing_clusters(version)
            total_missing_combos = sum(count for _, count in missing)
            print(f"\nv{version}:")
            print(f"  Clusters with missing combinations: {len(missing)}")
            print(f"  Total missing (entry_id, llm_type) combinations: {total_missing_combos}")
            if missing:
                print(f"  First 10:")
                for name, count in missing[:10]:
                    print(f"    {name}: {count} missing")
        return 0

    if args.both:
        return run_parallel([3, 4])
    elif args.version:
        return run_version(args.version, resume=not args.no_resume)
    else:
        parser.print_help()
        return 1


if __name__ == '__main__':
    sys.exit(main())
