"""
Re-run Failed Entries Script

After applying Docker/run.sh fixes, this script re-executes all entries
that previously had pass rate < 100% to attempt recovery.

Uses entry-level granularity with automatic result merging.

Target languages: C, Python, JavaScript (Java excluded - mostly base code bugs)

Date: 2025-11-18
"""

import json
import subprocess
import time
from pathlib import Path
from collections import defaultdict
import sys 
import os 

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
from utility_dir import  general_utils



class FailedEntriesRerunner:
    """Re-executes failed entries after infrastructure fixes."""

    def __init__(self,
                 execution_outputs_dir: str = "../execution_outputs/",
                 clusters_dir: str = "../clusters/"):
        """
        Initialize the rerunner.

        Args:
            execution_outputs_dir: Path to execution outputs directory
            clusters_dir: Path to clusters directory
        """
        self.execution_outputs_dir = Path(execution_outputs_dir)
        self.clusters_dir = Path(clusters_dir)

        self.target_languages = ["java"] #'javascript'

        # Storage: language -> list of (cluster_name, entry_id) tuples
        self.failed_entries_by_language = defaultdict(list)

        self.stats = {
            'before': defaultdict(int),  # language -> count valid entries
            'after': defaultdict(int),   # language -> count valid entries
            'recovered': defaultdict(int)  # language -> count recovered
        }

    def identify_failed_entries(self):
        """
        Identify all entries with pass rate < 100% and group by language.
        """
        print("\n" + "="*80)
        print("IDENTIFYING FAILED ENTRIES TO RE-RUN")
        print("="*80)
        print(f"Target languages: {', '.join(self.target_languages)}")
        print()

        # Load all base execution results
        base_files = []
        for file in self.execution_outputs_dir.glob("*_results_*.json"):
            # Skip LLM files
            if "_v1_" in file.name or "_v2_" in file.name or "_v3_" in file.name or "_v4_" in file.name:
                continue
            if "backup" in file.name or "selective" in file.name:
                continue
            base_files.append(file)

        print(f"Found {len(base_files)} base execution files")

        # Track entries by cluster and language
        cluster_executions = defaultdict(lambda: defaultdict(list))  # cluster -> language -> [execution_data]

        for file in base_files:
            try:
                with open(file, 'r') as f:
                    data = json.load(f)

                # Extract cluster name
                filename = file.stem
                parts = filename.rsplit('_results_', 1)
                if len(parts) != 2:
                    continue
                cluster_name = parts[0]

                if "_full" in cluster_name : 
                    continue

                if any(skip in cluster_name for skip in general_utils.SKIP_PATTERNS):
                    continue

                # Store by language
                if 'results' in data:
                    for language, entries in data['results'].items():
                        if language in self.target_languages:
                            cluster_executions[cluster_name][language].extend(entries)
            except Exception as e:
                print(f"Warning: Could not load {file}: {e}")
                continue

        print(f"Processed {len(cluster_executions)} unique clusters")
        print()

        # Identify entries with pass rate < 100%
        failed_entries_count = defaultdict(int)
        total_entries_count = defaultdict(int)

        for cluster_name, languages_data in cluster_executions.items():
            for language, entries in languages_data.items():
                # Count unique entries
                unique_ids = set(e.get('id') for e in entries if e.get('id'))

                for entry_id in unique_ids:
                    total_entries_count[language] += 1

                    # Check pass rate across all executions
                    entry_executions = [e for e in entries if e.get('id') == entry_id]
                    passed = sum(1 for e in entry_executions if e.get('regressionTestPassed', False))
                    total = len(entry_executions)

                    if total > 0:
                        pass_rate = (passed / total) * 100.0

                        if pass_rate < 100.0:
                            # Add to language-grouped list
                            self.failed_entries_by_language[language].append((cluster_name, entry_id))
                            failed_entries_count[language] += 1
                        else:
                            # Track valid entries (before re-run)
                            self.stats['before'][language] += 1

        print("Failed entries per language (before re-run):")
        for lang in self.target_languages:
            failed = failed_entries_count[lang]
            total = total_entries_count[lang]
            valid = self.stats['before'][lang]
            print(f"  {lang.upper():<12}: {failed}/{total} failed ({valid} valid)")

        # Calculate total
        total_failed = sum(failed_entries_count.values())
        print(f"\nTotal failed entries to re-run: {total_failed}")
        print()

    def rerun_entries(self, max_workers: int = 4, dry_run: bool = False, limit_per_lang: int = None):
        """
        Re-execute all failed entries using entry-specific execution grouped by language.

        Args:
            max_workers: Number of parallel workers (default: 4)
            dry_run: If True, only print what would be done without executing
            limit_per_lang: Maximum number of entries to process per language (None = all)
        """
        print("="*80)
        if limit_per_lang:
            print(f"RE-RUNNING FAILED ENTRIES (LIMIT: {limit_per_lang} per language)")
        else:
            print("RE-RUNNING ALL FAILED ENTRIES")
        print("="*80)
        print(f"Parallel workers: {max_workers}")
        print(f"Dry run: {dry_run}")
        print()

        start_time = time.time()
        failed_executions = []

        for language in self.target_languages:
            entries_list = self.failed_entries_by_language[language]

            if not entries_list:
                print(f"\n[{language.upper()}] No failed entries to re-run")
                continue

            # Apply limit if specified
            if limit_per_lang:
                entries_list = entries_list[:limit_per_lang]

            total_entries = len(entries_list)
            print(f"\n{'='*80}")
            print(f"[{language.upper()}] Processing {total_entries} failed entries")
            print(f"{'='*80}")

            # Prepare lists for --entry-ids and --entry-clusters
            entry_ids = [entry_id for _, entry_id in entries_list]
            cluster_names = [cluster_name for cluster_name, _ in entries_list]

            if dry_run:
                print("  [DRY RUN] Would execute:")
                print("    python3 run_tests_on_cluster.py")
                print("            --base-only --run-quantity 5")
                print(f"            --languages {language}")
                print(f"            --max-workers {max_workers}")
                print(f"            --entry-ids {' '.join(entry_ids[:5])}{'...' if len(entry_ids) > 5 else ''}")
                print(f"            --entry-clusters {' '.join(cluster_names[:5])}{'...' if len(cluster_names) > 5 else ''}")
                continue

            # Build command using --entry-ids and --entry-clusters
            cmd = [
                'python3',
                '../run_tests_on_clusters/run_tests_on_cluster.py',
                '--base-only',
                '--run-quantity', '5',
                '--languages', language,
                '--entry-ids'
            ] + entry_ids + [
                '--entry-clusters'
            ] + cluster_names + [
                '--max-workers', str(max_workers)
            ]

            try:
                print(f"  Executing {total_entries} entries across {len(set(cluster_names))} clusters...")
                exec_start = time.time()

                # Execute with timeout (max 30 minutes for entire language batch)
                result = subprocess.run(
                    cmd,
                    capture_output=False,
                    text=True,                    
                    cwd=Path(__file__).parent
                )

                exec_elapsed = time.time() - exec_start

                if result.returncode != 0:
                    print(f"  ⚠️  WARNING: Execution failed with exit code {result.returncode}")
                    failed_executions.append(language)
                    print("  Error output (last 50 lines):")
                    error_lines = result.stderr.split('\n')[-50:]
                    for line in error_lines:
                        print(f"    {line}")
                else:
                    print(f"  ✅ Completed successfully in {exec_elapsed:.1f}s ({exec_elapsed/60:.1f} min)")

            except subprocess.TimeoutExpired:
                print("  ❌ TIMEOUT: Execution took > 30 minutes, skipping")
                failed_executions.append(language)
            except Exception as e:
                print(f"  ❌ ERROR: {e}")
                failed_executions.append(language)

        elapsed_total = time.time() - start_time
        print("\n" + "="*80)
        print("RE-RUN COMPLETED")
        print("="*80)
        print(f"Total time: {elapsed_total/60:.1f} minutes ({elapsed_total/3600:.1f} hours)")
        print(f"Languages processed: {len(self.target_languages)}")
        print(f"Failed executions: {len(failed_executions)}")

        if failed_executions:
            print("\nFailed language executions:")
            for lang in failed_executions:
                print(f"  - {lang}")

    def analyze_recovery(self):
        """
        Analyze how many entries were recovered after re-run.
        """
        print("\n" + "="*80)
        print("ANALYZING RECOVERY RESULTS")
        print("="*80)

        # Re-scan execution outputs to count valid entries
        base_files = []
        for file in self.execution_outputs_dir.glob("*_results_*.json"):
            if "_v1_" in file.name or "_v2_" in file.name or "_v3_" in file.name or "_v4_" in file.name:
                continue
            if "backup" in file.name or "selective" in file.name:
                continue
            base_files.append(file)

        cluster_executions = defaultdict(lambda: defaultdict(list))

        for file in base_files:
            try:
                with open(file, 'r') as f:
                    data = json.load(f)

                filename = file.stem
                parts = filename.rsplit('_results_', 1)
                if len(parts) != 2:
                    continue
                cluster_name = parts[0]

                if 'results' in data:
                    for language, entries in data['results'].items():
                        if language in self.target_languages:
                            cluster_executions[cluster_name][language].extend(entries)
            except Exception:
                continue

        # Count valid entries after re-run
        for cluster_name, languages_data in cluster_executions.items():
            for language, entries in languages_data.items():
                unique_ids = set(e.get('id') for e in entries if e.get('id'))

                for entry_id in unique_ids:
                    entry_executions = [e for e in entries if e.get('id') == entry_id]
                    passed = sum(1 for e in entry_executions if e.get('regressionTestPassed', False))
                    total = len(entry_executions)

                    if total > 0:
                        pass_rate = (passed / total) * 100.0

                        if pass_rate == 100.0:
                            self.stats['after'][language] += 1

        # Calculate recovery
        for lang in self.target_languages:
            before = self.stats['before'][lang]
            after = self.stats['after'][lang]
            recovered = after - before
            self.stats['recovered'][lang] = recovered

        # Print results
        print("\nRECOVERY STATISTICS:")
        print(f"{'Language':<12} | {'Before':<8} | {'After':<8} | {'Recovered':<10} | {'Gain %':<8}")
        print("-" * 60)

        for lang in self.target_languages:
            before = self.stats['before'][lang]
            after = self.stats['after'][lang]
            recovered = self.stats['recovered'][lang]
            gain_pct = (recovered / before * 100) if before > 0 else 0

            print(f"{lang.upper():<12} | {before:<8} | {after:<8} | +{recovered:<9} | +{gain_pct:>6.1f}%")

        print("-" * 60)
        total_before = sum(self.stats['before'].values())
        total_after = sum(self.stats['after'].values())
        total_recovered = sum(self.stats['recovered'].values())
        total_gain = (total_recovered / total_before * 100) if total_before > 0 else 0

        print(f"{'TOTAL':<12} | {total_before:<8} | {total_after:<8} | +{total_recovered:<9} | +{total_gain:>6.1f}%")
        print()

        # Save recovery report
        report_file = Path("reports/recovery_report.json")
        report_file.parent.mkdir(parents=True, exist_ok=True)

        recovery_data = {
            'timestamp': time.strftime("%Y-%m-%d %H:%M:%S"),
            'target_languages': self.target_languages,
            'statistics': {
                'before': dict(self.stats['before']),
                'after': dict(self.stats['after']),
                'recovered': dict(self.stats['recovered'])
            },
            'total_failed_entries_rerun': sum(len(entries) for entries in self.failed_entries_by_language.values())
        }

        with open(report_file, 'w') as f:
            json.dump(recovery_data, f, indent=2)

        print(f"Recovery report saved to: {report_file}")


def main():
    """Main execution function."""
    import argparse

    parser = argparse.ArgumentParser(description='Re-run failed entries after Docker fixes')
    parser.add_argument('--dry-run', action='store_true',
                       help='Only print what would be done without executing')
    parser.add_argument('--max-workers', type=int, default=4,
                       help='Number of parallel workers (default: 4)')
    parser.add_argument('--analyze-only', action='store_true',
                       help='Only analyze results without re-running')
    parser.add_argument('--limit-per-lang', type=int, default=None,
                       help='Limit processing to first N entries per language (default: None = all)')

    args = parser.parse_args()

    rerunner = FailedEntriesRerunner()

    # Step 1: Identify failed entries
    rerunner.identify_failed_entries()

    if args.analyze_only:
        print("\n--analyze-only specified, skipping re-run")
    else:
        # Step 2: Re-run entries
        rerunner.rerun_entries(
            max_workers=args.max_workers,
            dry_run=args.dry_run,
            limit_per_lang=args.limit_per_lang
        )

    # Step 3: Analyze recovery
    if not args.dry_run:
        rerunner.analyze_recovery()
    else:
        print("\n[DRY RUN] Recovery analysis skipped")

    print("\n" + "="*80)
    print("SCRIPT COMPLETED")
    print("="*80)


if __name__ == "__main__":
    main()
