"""
Regenerate All CPP LLM Entries Script

This script regenerates LLM execution data for ALL CPP entries with 100% base pass rate.
This ensures complete coverage of CPP data for all prompt versions and models.

Expected execution:
- 141 CPP base entries (with 100% pass rate)
- 12 LLM codes per entry (3 models × 4 prompt versions)
- 5 executions per LLM code
- Total: 141 × 12 × 5 = 8,460 executions

Estimated time: ~5 hours (upper bound with 2s per execution including container overhead)

Author: Claude Code
Date: 2025-11-20
"""

import json
import subprocess
import time
from pathlib import Path
from collections import defaultdict
from typing import Dict, List, Tuple


class CPPLLMRegenerator:
    """Regenerates all LLM execution data for CPP entries with 100% base pass rate."""

    def __init__(
        self,
        execution_outputs_dir: str = "../execution_outputs/",
        clusters_dir: str = "../clusters/",
    ):
        """
        Initialize the regenerator.

        Args:
            execution_outputs_dir: Path to execution outputs directory
            clusters_dir: Path to clusters directory
        """
        self.execution_outputs_dir = Path(execution_outputs_dir)
        self.clusters_dir = Path(clusters_dir)

        self.target_language = "cpp"

        # Storage: [(cluster_name, entry_id)]
        self.cpp_entries_to_regenerate = []

        self.stats = {
            "total_base_entries": 0,
            "entries_with_100_pass": 0,
            "unique_clusters": 0,
        }

    def identify_cpp_entries_with_100_pass_rate(self):
        """
        Identify all CPP entries with 100% base pass rate (5/5 executions passed).
        """
        print("\n" + "=" * 80)
        print("IDENTIFYING CPP ENTRIES WITH 100% BASE PASS RATE")
        print("=" * 80)
        print(f"Target language: {self.target_language}")
        print()

        # Track pass rates for all CPP entries
        # entry_key (cluster::entry_id) -> {'total': int, 'passed': int}
        entry_pass_rates = defaultdict(lambda: {'total': 0, 'passed': 0})
        entry_to_cluster = {}  # entry_key -> cluster_name

        # Scan all base execution files (results_1.json through results_5.json)
        base_files = []
        for file in self.execution_outputs_dir.glob("*_results_[1-5].json"):
            # Skip backup files
            if "backup" in file.name or "selective" in file.name:
                continue
            base_files.append(file)

        print(f"Found {len(base_files)} base execution files")

        for file in base_files:
            try:
                with open(file, "r") as f:
                    data = json.load(f)

                # Extract cluster name
                filename = file.stem
                # Pattern: cluster_name_results_X.json
                cluster_name = filename.rsplit("_results_", 1)[0]

                # Process CPP results
                if "results" in data and self.target_language in data["results"]:
                    for entry in data["results"][self.target_language]:
                        entry_id = entry.get("id")
                        if not entry_id:
                            continue

                        entry_key = f"{cluster_name}::{entry_id}"
                        entry_to_cluster[entry_key] = cluster_name

                        # Track execution
                        entry_pass_rates[entry_key]['total'] += 1
                        if entry.get("regressionTestPassed", False):
                            entry_pass_rates[entry_key]['passed'] += 1

            except Exception as e:
                print(f"Warning: Could not load {file}: {e}")
                continue

        # Identify entries with exactly 5 executions and 100% pass rate
        self.stats["total_base_entries"] = len(entry_pass_rates)

        for entry_key, rates in entry_pass_rates.items():
            if rates['total'] == 5 and rates['passed'] == 5:
                cluster_name = entry_to_cluster[entry_key]
                entry_id = entry_key.split("::", 1)[1]

                self.cpp_entries_to_regenerate.append((cluster_name, entry_id))
                self.stats["entries_with_100_pass"] += 1

        # Count unique clusters
        unique_clusters = set(cluster for cluster, _ in self.cpp_entries_to_regenerate)
        self.stats["unique_clusters"] = len(unique_clusters)

        print(f"Total CPP base entries found: {self.stats['total_base_entries']}")
        print(f"Entries with 100% base pass rate (5/5): {self.stats['entries_with_100_pass']}")
        print(f"Unique clusters affected: {self.stats['unique_clusters']}")
        print()

        # Print cluster distribution
        cluster_counts = defaultdict(int)
        for cluster, _ in self.cpp_entries_to_regenerate:
            cluster_counts[cluster] += 1

        print("Entries per cluster:")
        for cluster, count in sorted(cluster_counts.items(), key=lambda x: x[1], reverse=True)[:10]:
            print(f"  {cluster}: {count} entries")
        if len(cluster_counts) > 10:
            print(f"  ... and {len(cluster_counts) - 10} more clusters")
        print()

    def identify_incomplete_entries(self):
        """
        Identify entries that are missing LLM execution data.

        Returns:
            set: Set of (cluster_name, entry_id) tuples for incomplete entries
        """
        print("\n" + "=" * 80)
        print("IDENTIFYING INCOMPLETE ENTRIES")
        print("=" * 80)

        # Count how many entries have LLM data for each prompt version
        entries_with_llm = defaultdict(set)  # prompt_version -> set of (cluster, entry_id)

        for prompt_version in [1, 2, 3, 4]:
            llm_files = list(self.execution_outputs_dir.glob(f"*_results_v{prompt_version}_*.json"))

            for file in llm_files:
                try:
                    with open(file, "r") as f:
                        data = json.load(f)

                    cluster_name = file.stem.split(f"_results_v{prompt_version}_")[0]

                    if "results" in data and self.target_language in data["results"]:
                        for entry in data["results"][self.target_language]:
                            entry_id = entry.get("id")
                            if entry_id and "LLM_results" in entry:
                                entries_with_llm[prompt_version].add((cluster_name, entry_id))
                except:
                    continue

        # Identify incomplete entries
        target_entries = set(self.cpp_entries_to_regenerate)
        incomplete_entries = set()

        for entry in target_entries:
            versions_present = sum(1 for pv in [1, 2, 3, 4] if entry in entries_with_llm[pv])
            if versions_present < 4:
                incomplete_entries.add(entry)

        complete_count = len(target_entries) - len(incomplete_entries)

        print(f"Total target entries: {len(target_entries)}")
        print(f"Complete entries (all 4 versions): {complete_count}")
        print(f"Incomplete entries: {len(incomplete_entries)}")
        print()

        # Show breakdown by completion level
        if incomplete_entries:
            by_completion = defaultdict(list)
            for entry in incomplete_entries:
                versions_present = sum(1 for pv in [1, 2, 3, 4] if entry in entries_with_llm[pv])
                by_completion[versions_present].append(entry)

            print("Incomplete entries breakdown:")
            for version_count in sorted(by_completion.keys()):
                count = len(by_completion[version_count])
                print(f"  {version_count}/4 versions present: {count} entries")

        return incomplete_entries

    def regenerate_llm_entries(
        self, max_workers: int = 4, dry_run: bool = False, limit: int = None, only_incomplete: bool = False
    ):
        """
        Regenerate LLM execution data for all CPP entries with 100% base pass rate.

        Uses prompt_version = -1 to execute ALL prompt versions (v1, v2, v3, v4).

        Args:
            max_workers: Number of parallel workers (default: 4)
            dry_run: If True, only print what would be done without executing
            limit: If specified, only process first N entries (for testing)
            only_incomplete: If True, only process entries with incomplete data (default: False)
        """
        print("=" * 80)
        if only_incomplete:
            print("REGENERATING INCOMPLETE CPP LLM ENTRIES ONLY")
        elif limit:
            print(f"REGENERATING CPP LLM ENTRIES (LIMITED TO {limit})")
        else:
            print("REGENERATING ALL CPP LLM ENTRIES")
        print("=" * 80)
        print(f"Total entries available: {len(self.cpp_entries_to_regenerate)}")

        # Filter by incomplete entries if requested
        if only_incomplete:
            incomplete_entries = self.identify_incomplete_entries()
            entries_to_process = [e for e in self.cpp_entries_to_regenerate if e in incomplete_entries]
            print(f"\n🎯 Filtering to incomplete entries only: {len(entries_to_process)}/{len(self.cpp_entries_to_regenerate)}")
        else:
            entries_to_process = self.cpp_entries_to_regenerate

        # Apply limit if specified
        if limit:
            print(f"Processing limit: {limit} entries")
            entries_to_process = entries_to_process[:limit]

        print(f"Parallel workers: {max_workers}")
        print(f"Dry run: {dry_run}")
        print()

        if not entries_to_process:
            print("✅ No entries to regenerate! All entries are already complete.")
            return

        # Calculate expected executions
        total_entries = len(entries_to_process)
        executions_per_entry = 3 * 4 * 5  # 3 models × 4 prompt versions × 5 runs
        total_executions = total_entries * executions_per_entry

        print("Expected execution volume:")
        print(f"  Entries: {total_entries}")
        print(f"  LLM codes per entry: 12 (3 models × 4 prompt versions)")
        print(f"  Runs per LLM code: 5")
        print(f"  Total executions: {total_executions:,}")
        print(f"  Estimated time (upper bound @ 2s/exec): {total_executions * 2 / 3600:.1f} hours")
        print()

        # Prepare lists for --entry-ids and --entry-clusters
        entry_ids = [entry_id for _, entry_id in entries_to_process]
        cluster_names = [cluster_name for cluster_name, _ in entries_to_process]

        if dry_run:
            print("=" * 80)
            print("DRY RUN - Would execute:")
            print("=" * 80)
            print("  python3 ../run_tests_on_clusters/run_tests_on_cluster.py")
            print("          --llm-only")
            print("          --run-quantity 5")
            print("          --prompt-version -1  # ALL prompt versions")
            print(f"          --languages {self.target_language}")
            print(f"          --max-workers {max_workers}")
            print(f"          --entry-ids {' '.join(entry_ids[:5])}{'...' if len(entry_ids) > 5 else ''}")
            print(f"          --entry-clusters {' '.join(cluster_names[:5])}{'...' if len(cluster_names) > 5 else ''}")
            print()
            print(f"Total entries: {len(entry_ids)}")
            print(f"Total clusters: {len(set(cluster_names))}")
            return

        # Build command using --entry-ids and --entry-clusters
        # Use prompt_version = -1 to execute ALL prompt versions
        cmd = (
            [
                "python3",
                "../run_tests_on_clusters/run_tests_on_cluster.py",
                "--llm-only",
                "--run-quantity",
                "5",
                "--prompt-version",
                "-1",  # Execute ALL prompt versions (v1, v2, v3, v4)
                "--languages",
                self.target_language,
                "--entry-ids",
            ]
            + entry_ids
            + ["--entry-clusters"]
            + cluster_names
            + ["--max-workers", str(max_workers)]
        )

        print("=" * 80)
        print("STARTING EXECUTION")
        print("=" * 80)
        print(f"Processing {len(entry_ids)} entries across {len(set(cluster_names))} clusters...")
        print("This may take several hours. Progress will be shown by run_tests_on_cluster.py")
        print()

        start_time = time.time()

        try:
            # Execute with no timeout (this will take hours)
            result = subprocess.run(
                cmd,
                capture_output=False,
                text=True,
                cwd=Path(__file__).parent,
            )

            elapsed = time.time() - start_time

            if result.returncode != 0:
                print("\n" + "=" * 80)
                print(f"⚠️  WARNING: Execution failed with exit code {result.returncode}")
                print("=" * 80)
                print(f"Elapsed time: {elapsed / 3600:.2f} hours")
            else:
                print("\n" + "=" * 80)
                print("✅ EXECUTION COMPLETED SUCCESSFULLY")
                print("=" * 80)
                print(f"Total time: {elapsed / 60:.1f} minutes ({elapsed / 3600:.2f} hours)")
                print(f"Average time per entry: {elapsed / len(entry_ids):.1f} seconds")
                print(f"Average time per execution: {elapsed / total_executions:.2f} seconds")

        except subprocess.TimeoutExpired:
            print("\n" + "=" * 80)
            print("❌ TIMEOUT: Execution took too long")
            print("=" * 80)
        except KeyboardInterrupt:
            print("\n" + "=" * 80)
            print("⚠️  INTERRUPTED: Execution stopped by user")
            print("=" * 80)
            elapsed = time.time() - start_time
            print(f"Elapsed time before interruption: {elapsed / 60:.1f} minutes")
        except Exception as e:
            print("\n" + "=" * 80)
            print(f"❌ ERROR: {e}")
            print("=" * 80)

    def verify_regeneration(self):
        """
        Verify that LLM data was successfully regenerated by checking execution output files.
        """
        print("\n" + "=" * 80)
        print("VERIFYING REGENERATION RESULTS")
        print("=" * 80)

        # Count how many entries now have LLM data for each prompt version
        entries_with_llm = defaultdict(set)  # prompt_version -> set of (cluster, entry_id)

        for prompt_version in [1, 2, 3, 4]:
            llm_files = list(self.execution_outputs_dir.glob(f"*_results_v{prompt_version}_*.json"))

            for file in llm_files:
                try:
                    with open(file, "r") as f:
                        data = json.load(f)

                    cluster_name = file.stem.split(f"_results_v{prompt_version}_")[0]

                    if "results" in data and self.target_language in data["results"]:
                        for entry in data["results"][self.target_language]:
                            entry_id = entry.get("id")
                            if entry_id and "LLM_results" in entry:
                                entries_with_llm[prompt_version].add((cluster_name, entry_id))
                except:
                    continue

        # Create set of target entries for comparison
        target_entries = set(self.cpp_entries_to_regenerate)

        print("CPP entries with LLM data by prompt version:")
        for pv in sorted(entries_with_llm.keys()):
            # Count only target entries (not orphaned old entries)
            matched = entries_with_llm[pv] & target_entries
            count = len(matched)
            expected = len(target_entries)
            coverage = (count / expected * 100) if expected > 0 else 0
            total_found = len(entries_with_llm[pv])
            orphaned = total_found - count
            print(f"  Prompt v{pv}: {count}/{expected} target entries ({coverage:.1f}% coverage)")
            if orphaned > 0:
                print(f"             + {orphaned} orphaned entries (old data)")

        # Check which target entries have data for all versions
        entries_by_version_count = defaultdict(int)

        for entry in target_entries:
            versions_present = sum(1 for pv in [1, 2, 3, 4] if entry in entries_with_llm[pv])
            entries_by_version_count[versions_present] += 1

        print(f"\nTarget entries by version coverage:")
        for version_count in sorted(entries_by_version_count.keys(), reverse=True):
            count = entries_by_version_count[version_count]
            print(f"  {version_count}/4 prompt versions: {count} entries")

        # Identify entries missing from any version
        complete_entries = set()
        incomplete_entries = defaultdict(list)  # entry -> list of missing versions

        for entry in target_entries:
            missing_versions = [pv for pv in [1, 2, 3, 4] if entry not in entries_with_llm[pv]]
            if not missing_versions:
                complete_entries.add(entry)
            else:
                incomplete_entries[entry] = missing_versions

        print(f"\nComplete entries (all 4 versions present): {len(complete_entries)}/{len(target_entries)}")

        if incomplete_entries:
            print(f"Incomplete entries: {len(incomplete_entries)}")
            print("\nFirst 10 incomplete entries:")
            for i, (entry, missing_vs) in enumerate(list(incomplete_entries.items())[:10]):
                cluster, entry_id = entry
                missing_str = ",".join(f"v{v}" for v in missing_vs)
                print(f"  {cluster}/{entry_id} - missing: {missing_str}")
            if len(incomplete_entries) > 10:
                print(f"  ... and {len(incomplete_entries) - 10} more")


def main():
    """Main execution function."""
    import argparse

    parser = argparse.ArgumentParser(
        description="Regenerate LLM execution data for all CPP entries with 100% base pass rate"
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Only print what would be done without executing",
    )
    parser.add_argument(
        "--max-workers",
        type=int,
        default=4,
        help="Number of parallel workers (default: 4)",
    )
    parser.add_argument(
        "--verify-only",
        action="store_true",
        help="Only verify existing results without regenerating",
    )
    parser.add_argument(
        "--limit",
        type=int,
        default=None,
        help="Limit processing to first N entries (for testing, default: None = all)",
    )
    parser.add_argument(
        "--only-incomplete",
        action="store_true",
        help="Only process entries with incomplete execution data (missing any of 4 prompt versions)",
    )

    args = parser.parse_args()

    regenerator = CPPLLMRegenerator()

    # Step 1: Identify CPP entries with 100% base pass rate
    regenerator.identify_cpp_entries_with_100_pass_rate()

    if args.verify_only:
        print("\n--verify-only specified, skipping regeneration")
    else:
        # Step 2: Regenerate LLM entries
        regenerator.regenerate_llm_entries(
            max_workers=args.max_workers,
            dry_run=args.dry_run,
            limit=args.limit,
            only_incomplete=args.only_incomplete,
        )

    # Step 3: Verify results
    if not args.dry_run:
        regenerator.verify_regeneration()
    else:
        print("\n[DRY RUN] Verification skipped")

    print("\n" + "=" * 80)
    print("SCRIPT COMPLETED")
    print("=" * 80)


if __name__ == "__main__":
    main()
