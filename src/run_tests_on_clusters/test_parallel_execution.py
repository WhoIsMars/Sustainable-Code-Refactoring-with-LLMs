#!/usr/bin/env python3
"""
Test script for parallel execution
Creates a simple test to verify parallel processing works correctly
"""

import time
import subprocess
from pathlib import Path
import multiprocessing


def test_process(process_id, sleep_time):
    """Simulate a process that takes some time"""
    print(f"[Process {process_id}] Starting... (will run for {sleep_time}s)", flush=True)
    time.sleep(sleep_time)
    print(f"[Process {process_id}] Completed!", flush=True)
    return (process_id, True, f"Process {process_id} completed in {sleep_time}s")


def main():
    print("=" * 80)
    print("PARALLEL EXECUTION TEST")
    print("=" * 80)
    print()

    num_processes = 3
    test_args = [(0, 3), (1, 3), (2, 3)]  # 3 processes, each sleeping 3s

    print(f"Launching {num_processes} processes...")
    print(f"If running in parallel, total time should be ~3s")
    print(f"If running sequentially, total time would be ~9s")
    print()

    start_time = time.time()

    with multiprocessing.Pool(processes=num_processes) as pool:
        async_results = []
        for args in test_args:
            async_result = pool.apply_async(test_process, args)
            async_results.append(async_result)

        print("Waiting for all processes...")
        results = []
        for async_result in async_results:
            result = async_result.get()
            results.append(result)

    elapsed = time.time() - start_time

    print()
    print("=" * 80)
    print(f"Total time: {elapsed:.1f}s")
    if elapsed < 5:
        print("✅ SUCCESS: Processes ran in PARALLEL")
    else:
        print("❌ FAILURE: Processes ran SEQUENTIALLY")
    print("=" * 80)

    print("\nResults:")
    for process_id, success, message in results:
        status = "✅" if success else "❌"
        print(f"{status} {message}")


if __name__ == "__main__":
    main()
