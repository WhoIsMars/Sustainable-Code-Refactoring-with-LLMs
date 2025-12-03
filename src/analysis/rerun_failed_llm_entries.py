"""
Re-run Failed LLM Entries Script

After fixing base code infrastructure, this script re-executes LLM entries
that failed regression tests to align LLM pass rates with base code improvements.

Focuses on Python LLM entries that failed regression tests.


Date: 2025-11-18
"""

import json
import subprocess
import time
from pathlib import Path
from collections import defaultdict



class FailedLLMRerunner:
    """Re-executes failed LLM entries after base code infrastructure fixes."""

    def __init__(
        self,
        execution_outputs_dir: str = "../execution_outputs/",
        clusters_dir: str = "../clusters/",
    ):
        """
        Initialize the rerunner.

        Args:
            execution_outputs_dir: Path to execution outputs directory
            clusters_dir: Path to clusters directory
        """
        self.execution_outputs_dir = Path(execution_outputs_dir)
        self.clusters_dir = Path(clusters_dir)

        self.target_languages = ["cpp"]#["javascript"]

        # Storage: language -> prompt_version -> [(cluster_name, llm_entry_id)]
        self.failed_llm_by_language = defaultdict(lambda: defaultdict(list))

        self.stats = {
            "before": defaultdict(
                lambda: defaultdict(int)
            ),  # language -> prompt_version -> count
            "after": defaultdict(lambda: defaultdict(int)),
            "recovered": defaultdict(lambda: defaultdict(int)),
        }

    def identify_failed_llm_entries(self):
        """
        Identify all LLM entries with pass rate < 100% and group by language and prompt version.
        """
        print("\n" + "=" * 80)
        print("IDENTIFYING FAILED LLM ENTRIES TO RE-RUN")
        print("=" * 80)
        print(f"Target languages: {', '.join(self.target_languages)}")
        print()

        # Load all LLM execution results
        llm_files = []
        for file in self.execution_outputs_dir.glob("*_results_v*_*.json"):
            # Skip backup files
            if "backup" in file.name or "selective" in file.name:
                continue
            llm_files.append(file)

        print(f"Found {len(llm_files)} LLM execution files")

        # Track entries by cluster, language, and prompt version
        # cluster -> language -> prompt_version -> [execution_data]
        cluster_executions = defaultdict(lambda: defaultdict(lambda: defaultdict(list)))

        for file in llm_files:
            try:
                with open(file, "r") as f:
                    data = json.load(f)

                # Extract cluster name and prompt version
                filename = file.stem
                # Pattern: cluster_name_results_vX_Y.json
                parts = filename.split("_results_v")
                if len(parts) != 2:
                    continue

                cluster_name = parts[0]
                version_run = parts[1]  # e.g., "1_2" for v1 run 2

                prompt_version = int(version_run.split("_")[0])

                # Store by language and prompt version
                if "results" in data:
                    for language, entries in data["results"].items():
                        if language in self.target_languages:
                            cluster_executions[cluster_name][language][
                                prompt_version
                            ].extend(entries)

            except Exception as e:
                print(f"Warning: Could not load {file}: {e}")
                continue

        print(f"Processed {len(cluster_executions)} unique clusters")
        print()

        # Identify LLM entries with failed regression tests
        failed_count = defaultdict(
            lambda: defaultdict(int)
        )  # language -> prompt_version -> count
        total_count = defaultdict(lambda: defaultdict(int))

        for cluster_name, languages_data in cluster_executions.items():
            for language, prompt_versions in languages_data.items():
                for prompt_version, entries in prompt_versions.items():
                    # Count unique LLM entries
                    unique_ids = set(e.get("id") for e in entries if e.get("id"))

                    for llm_entry_id in unique_ids:
                        total_count[language][prompt_version] += 1

                        # Check pass rate across all executions
                        entry_executions = [
                            e for e in entries if e.get("id") == llm_entry_id
                        ]

                        # FIX: regressionTestPassed is inside LLM_results[0], not at entry level

                        passed = sum(
                            1
                            for e in entry_executions
                            if (res := e.get("LLM_results"))
                            and res[0].get("regressionTestPassed", False)
                        )
                        total = len(entry_executions)

                        if total > 0:
                            pass_rate = (passed / total) * 100.0

                            if (
                                pass_rate < 100.0
                                and llm_entry_id
                                != "javascript_acronym_exercism-javascript-ffflorian_ffflorian"
                                and llm_entry_id
                                != "javascript_acronym_exercism-javascript-ffflorian"
                                and llm_entry_id 
                                != "javascript_acronym_exercism-javascript-ThomasZumsteg_ThomasZumsteg"
                                and llm_entry_id 
                                != "javascript_alphametics_exercism-javascript-ThomasZumsteg_ThomasZumsteg (javascript)"
                                and "alphametics" not in llm_entry_id
                                and "amusement" not in llm_entry_id
                                and "atbash" not in llm_entry_id                                
                                
                            ):
                                # Add to language+prompt_version grouped list
                                self.failed_llm_by_language[language][
                                    prompt_version
                                ].append((cluster_name, llm_entry_id))
                                failed_count[language][prompt_version] += 1
                            else:
                                # Track valid entries (before re-run)
                                self.stats["before"][language][prompt_version] += 1

        print("Failed LLM entries per language and prompt version (before re-run):")
        for lang in self.target_languages:
            print(f"\n{lang.upper()}:")
            for pv in sorted(failed_count[lang].keys()):
                failed = failed_count[lang][pv]
                total = total_count[lang][pv]
                valid = self.stats["before"][lang][pv]
                print(f"  Prompt v{pv}: {failed}/{total} failed ({valid} valid)")

        # Calculate total
        total_failed = sum(sum(pv_dict.values()) for pv_dict in failed_count.values())
        print(f"\nTotal failed LLM entries to re-run: {total_failed}")
        print()

    def rerun_llm_entries(
        self, max_workers: int = 4, dry_run: bool = False, limit_per_version: int = None
    ):
        """
        Re-execute all failed LLM entries using entry-specific execution grouped by language and prompt version.

        Args:
            max_workers: Number of parallel workers (default: 4)
            dry_run: If True, only print what would be done without executing
            limit_per_version: Maximum number of entries to process per prompt version (None = all)
        """
        print("=" * 80)
        if limit_per_version:
            print(
                f"RE-RUNNING FAILED LLM ENTRIES (LIMIT: {limit_per_version} per version)"
            )
        else:
            print("RE-RUNNING ALL FAILED LLM ENTRIES")
        print("=" * 80)
        print(f"Parallel workers: {max_workers}")
        print(f"Dry run: {dry_run}")
        print()

        start_time = time.time()
        failed_executions = []

        for language in self.target_languages:
            prompt_versions = self.failed_llm_by_language[language]

            if not prompt_versions:
                print(f"\n[{language.upper()}] No failed LLM entries to re-run")
                continue

            for prompt_version, entries_list in sorted(prompt_versions.items()):
                if not entries_list:
                    continue

                # Apply limit if specified
                if limit_per_version:
                    entries_list = entries_list[:limit_per_version]

                total_entries = len(entries_list)
                print(f"\n{'=' * 80}")
                print(
                    f"[{language.upper()} - Prompt v{prompt_version}] Processing {total_entries} failed entries"
                )
                print(f"{'=' * 80}")

                # Prepare lists for --entry-ids and --entry-clusters
                entry_ids = [entry_id for _, entry_id in entries_list]

                cluster_names = [cluster_name for cluster_name, _ in entries_list]

                if dry_run:
                    print("  [DRY RUN] Would execute:")
                    print("    python3 run_tests_on_cluster.py")
                    print("            --llm-only --run-quantity 5")
                    print(f"            --prompt-version {prompt_version}")
                    print(f"            --languages {language}")
                    print(f"            --max-workers {max_workers}")
                    print(
                        f"            --entry-ids {' '.join(entry_ids[:5])}{'...' if len(entry_ids) > 5 else ''}"
                    )
                    print(
                        f"            --entry-clusters {' '.join(cluster_names[:5])}{'...' if len(cluster_names) > 5 else ''}"
                    )
                    continue

                # Build command using --entry-ids and --entry-clusters
                cmd = (
                    [
                        "python3",
                        "../run_tests_on_clusters/run_tests_on_cluster.py",
                        "--llm-only",
                        "--run-quantity",
                        "5",
                        "--prompt-version",
                        str(prompt_version),
                        "--languages",
                        language,
                        "--entry-ids",
                    ]
                    + entry_ids
                    + ["--entry-clusters"]
                    + cluster_names
                    + ["--max-workers", str(max_workers)]
                )

                try:
                    print(
                        f"  Executing {total_entries} entries across {len(set(cluster_names))} clusters..."
                    )
                    exec_start = time.time()

                    # Execute with timeout (max 30 minutes per version batch)
                    result = subprocess.run(
                        cmd,
                        capture_output=False,
                        text=True,
                        timeout=1800,
                        cwd=Path(__file__).parent,
                    )

                    exec_elapsed = time.time() - exec_start

                    if result.returncode != 0:
                        print(
                            f"  ⚠️  WARNING: Execution failed with exit code {result.returncode}"
                        )
                        failed_executions.append(f"{language}_v{prompt_version}")
                        print(f"  Error output (last 50 lines):")
                        error_lines = result.stderr.split("\n")[-50:]
                        for line in error_lines:
                            print(f"    {line}")
                    else:
                        print(
                            f"  ✅ Completed successfully in {exec_elapsed:.1f}s ({exec_elapsed / 60:.1f} min)"
                        )

                except subprocess.TimeoutExpired:
                    print(f"  ❌ TIMEOUT: Execution took > 30 minutes, skipping")
                    failed_executions.append(f"{language}_v{prompt_version}")
                except Exception as e:
                    print(f"  ❌ ERROR: {e}")
                    failed_executions.append(f"{language}_v{prompt_version}")

        elapsed_total = time.time() - start_time
        print("\n" + "=" * 80)
        print("RE-RUN COMPLETED")
        print("=" * 80)
        print(
            f"Total time: {elapsed_total / 60:.1f} minutes ({elapsed_total / 3600:.1f} hours)"
        )
        print(f"Failed executions: {len(failed_executions)}")

        if failed_executions:
            print("\nFailed language+version executions:")
            for combo in failed_executions:
                print(f"  - {combo}")

    def analyze_recovery(self):
        """
        Analyze how many LLM entries were recovered after re-run.
        """
        print("\n" + "=" * 80)
        print("ANALYZING LLM RECOVERY RESULTS")
        print("=" * 80)

        # Re-scan execution outputs to count valid LLM entries
        llm_files = []
        for file in self.execution_outputs_dir.glob("*_results_v*_*.json"):
            if "backup" in file.name or "selective" in file.name:
                continue
            llm_files.append(file)

        cluster_executions = defaultdict(lambda: defaultdict(lambda: defaultdict(list)))

        for file in llm_files:
            try:
                with open(file, "r") as f:
                    data = json.load(f)

                filename = file.stem
                parts = filename.split("_results_v")
                if len(parts) != 2:
                    continue

                cluster_name = parts[0]
                version_run = parts[1]
                prompt_version = int(version_run.split("_")[0])

                if "results" in data:
                    for language, entries in data["results"].items():
                        if language in self.target_languages:
                            cluster_executions[cluster_name][language][
                                prompt_version
                            ].extend(entries)
            except Exception:
                continue

        # Count valid entries after re-run
        for cluster_name, languages_data in cluster_executions.items():
            for language, prompt_versions in languages_data.items():
                for prompt_version, entries in prompt_versions.items():
                    unique_ids = set(e.get("id") for e in entries if e.get("id"))

                    for llm_entry_id in unique_ids:
                        entry_executions = [
                            e for e in entries if e.get("id") == llm_entry_id
                        ]

                        # FIX: regressionTestPassed is inside LLM_results[0], not at entry level
                        passed = sum(
                            1
                            for e in entry_executions
                            if (res := e.get("LLM_results"))
                            and res[0].get("regressionTestPassed", False)
                        )
                        total = len(entry_executions)

                        if total > 0:
                            pass_rate = (passed / total) * 100.0

                            if pass_rate == 100.0:
                                self.stats["after"][language][prompt_version] += 1

        # Calculate recovery
        for lang in self.target_languages:
            for pv in set(
                list(self.stats["before"][lang].keys())
                + list(self.stats["after"][lang].keys())
            ):
                before = self.stats["before"][lang][pv]
                after = self.stats["after"][lang][pv]
                recovered = after - before
                self.stats["recovered"][lang][pv] = recovered

        # Print results
        print("\nRECOVERY STATISTICS:")
        print(
            f"{'Language':<12} | {'Prompt':<8} | {'Before':<8} | {'After':<8} | {'Recovered':<10} | {'Gain %':<8}"
        )
        print("-" * 80)

        for lang in self.target_languages:
            prompt_versions = sorted(
                set(
                    list(self.stats["before"][lang].keys())
                    + list(self.stats["after"][lang].keys())
                )
            )

            for pv in prompt_versions:
                before = self.stats["before"][lang][pv]
                after = self.stats["after"][lang][pv]
                recovered = self.stats["recovered"][lang][pv]
                gain_pct = (recovered / before * 100) if before > 0 else 0

                print(
                    f"{lang.upper():<12} | v{pv:<7} | {before:<8} | {after:<8} | +{recovered:<9} | +{gain_pct:>6.1f}%"
                )

        print("-" * 80)

        # Overall totals per language
        for lang in self.target_languages:
            total_before = sum(self.stats["before"][lang].values())
            total_after = sum(self.stats["after"][lang].values())
            total_recovered = sum(self.stats["recovered"][lang].values())
            total_gain = (
                (total_recovered / total_before * 100) if total_before > 0 else 0
            )

            print(
                f"{lang.upper()} TOTAL  | ALL      | {total_before:<8} | {total_after:<8} | +{total_recovered:<9} | +{total_gain:>6.1f}%"
            )

        print()

        # Save recovery report
        report_file = Path("reports/llm_recovery_report.json")
        report_file.parent.mkdir(parents=True, exist_ok=True)

        recovery_data = {
            "timestamp": time.strftime("%Y-%m-%d %H:%M:%S"),
            "target_languages": self.target_languages,
            "statistics": {
                lang: {
                    "before": dict(self.stats["before"][lang]),
                    "after": dict(self.stats["after"][lang]),
                    "recovered": dict(self.stats["recovered"][lang]),
                }
                for lang in self.target_languages
            },
            "total_failed_entries_rerun": sum(
                len(pv_entries)
                for lang_dict in self.failed_llm_by_language.values()
                for pv_entries in lang_dict.values()
            ),
        }

        with open(report_file, "w") as f:
            json.dump(recovery_data, f, indent=2)

        print(f"LLM recovery report saved to: {report_file}")


def main():
    """Main execution function."""
    import argparse

    parser = argparse.ArgumentParser(
        description="Re-run failed LLM entries after base code fixes"
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
        "--analyze-only",
        action="store_true",
        help="Only analyze results without re-running",
    )
    parser.add_argument(
        "--limit-per-version",
        type=int,
        default=None,
        help="Limit processing to first N entries per prompt version (default: None = all)",
    )

    args = parser.parse_args()

    rerunner = FailedLLMRerunner()

    # Step 1: Identify failed LLM entries
    rerunner.identify_failed_llm_entries()

    if args.analyze_only:
        print("\n--analyze-only specified, skipping re-run")
    else:
        # Step 2: Re-run LLM entries
        rerunner.rerun_llm_entries(
            max_workers=args.max_workers,
            dry_run=args.dry_run,
            limit_per_version=args.limit_per_version,
        )

    # Step 3: Analyze recovery
    if not args.dry_run:
        rerunner.analyze_recovery()
    else:
        print("\n[DRY RUN] Recovery analysis skipped")

    print("\n" + "=" * 80)
    print("SCRIPT COMPLETED")
    print("=" * 80)


if __name__ == "__main__":
    main()
