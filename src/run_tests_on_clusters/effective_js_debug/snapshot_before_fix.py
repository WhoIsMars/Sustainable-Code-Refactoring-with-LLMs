#!/usr/bin/env python3
"""
Create snapshot of JavaScript pass rates BEFORE applying fixes.
"""

import json
import sys
import os
from pathlib import Path
from collections import defaultdict
from datetime import datetime

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", ".."))
from utility_dir import utility_paths

OUTPUT_DIR = utility_paths.OUTPUT_DIR_FILEPATH

def analyze_current_state():
    """Analyze current JavaScript pass rates."""

    print("Creating snapshot of JavaScript test results BEFORE fixes...")
    print("=" * 80)

    js_entries = defaultdict(lambda: {"passes": 0, "total": 0, "runs": []})

    # Scan all result files
    for result_file in OUTPUT_DIR.glob("*_results_*.json"):
        try:
            with open(result_file, 'r') as f:
                data = json.load(f)

            results = data.get("results", {})
            if "javascript" not in results:
                continue

            # Analyze JavaScript entries
            for entry in results["javascript"]:
                entry_id = entry.get("id")
                passed = entry.get("regressionTestPassed", False)

                if entry_id:
                    js_entries[entry_id]["total"] += 1
                    if passed:
                        js_entries[entry_id]["passes"] += 1
                    js_entries[entry_id]["runs"].append({
                        "file": result_file.name,
                        "passed": passed,
                        "error": entry.get("error_message"),
                        "success": entry.get("success")
                    })

        except Exception as e:
            continue

    # Calculate pass rates
    entry_pass_rates = {}
    for entry_id, data in js_entries.items():
        if data["total"] > 0:
            pass_rate = (data["passes"] / data["total"]) * 100
            entry_pass_rates[entry_id] = {
                "pass_rate": pass_rate,
                "passes": data["passes"],
                "total": data["total"],
                "runs": data["runs"]
            }

    # Statistics
    total_entries = len(entry_pass_rates)
    entries_100 = sum(1 for r in entry_pass_rates.values() if r["pass_rate"] == 100.0)
    entries_0 = sum(1 for r in entry_pass_rates.values() if r["pass_rate"] == 0.0)
    entries_partial = total_entries - entries_100 - entries_0

    snapshot = {
        "timestamp": datetime.now().isoformat(),
        "summary": {
            "total_entries": total_entries,
            "entries_100_pass_rate": entries_100,
            "entries_0_pass_rate": entries_0,
            "entries_partial_pass_rate": entries_partial,
            "percentage_100": (entries_100 / total_entries * 100) if total_entries > 0 else 0,
            "percentage_0": (entries_0 / total_entries * 100) if total_entries > 0 else 0
        },
        "entry_details": entry_pass_rates
    }

    # Save snapshot
    snapshot_file = Path(__file__).parent / f"snapshot_before_fix_{datetime.now().strftime('%Y%m%d_%H%M%S')}.json"
    with open(snapshot_file, 'w') as f:
        json.dump(snapshot, f, indent=2)

    print(f"\n✓ Snapshot saved to: {snapshot_file.name}")
    print(f"\nCurrent JavaScript Status:")
    print(f"  Total entries: {total_entries}")
    print(f"  100% pass rate: {entries_100} ({entries_100/total_entries*100:.1f}%)")
    print(f"  0% pass rate: {entries_0} ({entries_0/total_entries*100:.1f}%)")
    print(f"  Partial pass rate: {entries_partial} ({entries_partial/total_entries*100:.1f}%)")
    print()

    # Show sample of 0% pass rate entries
    zero_pass_entries = [eid for eid, data in entry_pass_rates.items() if data["pass_rate"] == 0.0]
    print(f"Sample of entries with 0% pass rate (showing first 10):")
    for i, entry_id in enumerate(zero_pass_entries[:10], 1):
        print(f"  {i}. {entry_id}")

    return snapshot_file

if __name__ == "__main__":
    snapshot_file = analyze_current_state()
    print(f"\n✓ Snapshot complete! File: {snapshot_file}")
