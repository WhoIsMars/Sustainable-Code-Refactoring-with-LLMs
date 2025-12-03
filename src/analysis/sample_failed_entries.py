"""
Sample Failed Entries Script

This script analyzes execution outputs to identify entries with pass rate < 100%
and samples 15 random entries per language (C, Java, Python, JavaScript) for
root cause analysis.


Date: 2025-11-18
"""

import json
import random
from pathlib import Path
from collections import defaultdict
from typing import Dict, List, Set, Tuple
import sys


class FailedEntrySampler:
    """Samples failed entries from execution outputs for root cause analysis."""

    def __init__(self, execution_outputs_dir: str = "../execution_outputs/"):
        """
        Initialize the sampler.

        Args:
            execution_outputs_dir: Path to execution outputs directory
        """
        self.execution_outputs_dir = Path(execution_outputs_dir)
        self.target_languages = ['c', 'java', 'python', 'javascript']
        self.sample_size = 15

        # Storage for failed entries by language
        self.failed_entries = defaultdict(list)  # language -> [(entry_id, pass_rate, cluster, details)]

    def load_base_execution_results(self) -> Dict[str, List]:
        """
        Load all base code execution results (not LLM).

        Returns:
            Dictionary mapping cluster name to list of 5 execution results
        """
        print("Loading base execution results...")

        cluster_executions = defaultdict(list)

        # Find all base execution files (pattern: {cluster}_results_{1-5}.json)
        base_files = []
        for file in self.execution_outputs_dir.glob("*_results_*.json"):
            # Skip LLM files (contain _v1_, _v2_, etc.)
            if "_v1_" in file.name or "_v2_" in file.name or "_v3_" in file.name or "_v4_" in file.name:
                continue
            # Skip backup files
            if "backup" in file.name or "selective" in file.name:
                continue
            base_files.append(file)

        print(f"Found {len(base_files)} base execution files")

        # Load each file
        for file in base_files:
            try:
                with open(file, 'r') as f:
                    data = json.load(f)

                # Extract cluster name from filename
                # Format: {cluster}_results_{num}.json
                filename = file.stem
                parts = filename.rsplit('_results_', 1)
                if len(parts) == 2:
                    cluster_name = parts[0]
                    exec_num = parts[1]
                    cluster_executions[cluster_name].append({
                        'execution_number': exec_num,
                        'data': data,
                        'file': file
                    })
            except Exception as e:
                print(f"Warning: Could not load {file}: {e}")
                continue

        print(f"Loaded results for {len(cluster_executions)} clusters")
        return cluster_executions

    def calculate_pass_rate_for_entry(self, cluster_name: str, entry_id: str,
                                     executions: List[Dict]) -> Tuple[float, int, int, Dict]:
        """
        Calculate pass rate for a specific entry across its executions.

        Args:
            cluster_name: Cluster name
            entry_id: Entry ID
            executions: List of execution results

        Returns:
            Tuple of (pass_rate, passed_count, total_count, details)
        """
        passed_count = 0
        total_count = 0
        error_messages = []
        log_paths = []

        for execution in executions:
            data = execution['data']
            if 'results' not in data:
                continue

            # Check all languages
            for language, entries in data['results'].items():
                for entry in entries:
                    if entry.get('id') == entry_id:
                        total_count += 1

                        # Check if test passed
                        if entry.get('regressionTestPassed', False):
                            passed_count += 1
                        else:
                            # Record error details
                            error_msg = entry.get('error_message')
                            if error_msg:
                                error_messages.append(error_msg)

                            log_path = entry.get('log_path') or entry.get('base_log')
                            if log_path:
                                log_paths.append(log_path)

        if total_count == 0:
            return 0.0, 0, 0, {}

        pass_rate = (passed_count / total_count) * 100.0

        details = {
            'cluster': cluster_name,
            'entry_id': entry_id,
            'passed': passed_count,
            'total': total_count,
            'pass_rate': pass_rate,
            'error_messages': error_messages,
            'log_paths': log_paths
        }

        return pass_rate, passed_count, total_count, details

    def analyze_all_entries(self):
        """Main analysis function: identify all entries with pass rate < 100%."""
        print("\n" + "="*80)
        print("ANALYZING ENTRIES FOR PASS RATE < 100%")
        print("="*80)
        print(f"Target languages: {', '.join(self.target_languages)}")
        print(f"Sample size per language: {self.sample_size}")
        print()

        # Load all executions
        cluster_executions = self.load_base_execution_results()

        # Track all unique entry IDs per language
        entries_by_language = defaultdict(set)

        # First pass: collect all entry IDs
        print("Collecting all entry IDs...")
        for cluster_name, executions in cluster_executions.items():
            for execution in executions:
                data = execution['data']
                if 'results' not in data:
                    continue

                for language, entries in data['results'].items():
                    if language in self.target_languages:
                        for entry in entries:
                            entry_id = entry.get('id')
                            if entry_id:
                                entries_by_language[language].add((entry_id, cluster_name))

        print(f"Found total entries per language:")
        for lang in self.target_languages:
            print(f"  {lang.upper()}: {len(entries_by_language[lang])} unique entries")
        print()

        # Second pass: calculate pass rates
        print("Calculating pass rates...")
        processed = 0

        for language in self.target_languages:
            print(f"\nProcessing {language.upper()}...")

            for entry_id, cluster_name in entries_by_language[language]:
                # Get executions for this cluster
                executions = cluster_executions.get(cluster_name, [])
                if not executions:
                    continue

                # Calculate pass rate
                pass_rate, passed, total, details = self.calculate_pass_rate_for_entry(
                    cluster_name, entry_id, executions
                )

                # Only include if pass rate < 100%
                if total > 0 and pass_rate < 100.0:
                    self.failed_entries[language].append(details)

                processed += 1
                if processed % 100 == 0:
                    print(f"  Processed {processed} entries...", end='\r')

        print(f"\n\nFailed entries found per language:")
        for lang in self.target_languages:
            count = len(self.failed_entries[lang])
            print(f"  {lang.upper()}: {count} entries with pass rate < 100%")

    def sample_failed_entries(self) -> Dict[str, List]:
        """
        Sample N random failed entries per language.

        Returns:
            Dictionary mapping language to sampled entries
        """
        print("\n" + "="*80)
        print("SAMPLING FAILED ENTRIES FOR ROOT CAUSE ANALYSIS")
        print("="*80)

        sampled = {}

        for language in self.target_languages:
            failed = self.failed_entries[language]

            if len(failed) == 0:
                print(f"\n{language.upper()}: No failed entries found! ✅")
                sampled[language] = []
                continue

            # Sample min(sample_size, len(failed)) entries
            sample_count = min(self.sample_size, len(failed))
            sample = random.sample(failed, sample_count)

            sampled[language] = sample

            print(f"\n{language.upper()}:")
            print(f"  Total failed: {len(failed)}")
            print(f"  Sampled: {sample_count}")

            # Show pass rate distribution
            pass_rates = [e['pass_rate'] for e in sample]
            avg_pass_rate = sum(pass_rates) / len(pass_rates) if pass_rates else 0
            print(f"  Average pass rate: {avg_pass_rate:.1f}%")
            print(f"  Pass rate range: {min(pass_rates):.0f}% - {max(pass_rates):.0f}%")

        return sampled

    def save_samples(self, sampled: Dict[str, List], output_dir: str = "samples"):
        """
        Save sampled entries to JSON files.

        Args:
            sampled: Dictionary of sampled entries per language
            output_dir: Output directory for samples
        """
        output_path = Path(output_dir)
        output_path.mkdir(parents=True, exist_ok=True)

        print("\n" + "="*80)
        print("SAVING SAMPLES")
        print("="*80)

        for language, entries in sampled.items():
            output_file = output_path / f"failed_entries_{language}.json"

            # Prepare data for saving
            save_data = {
                'language': language,
                'sample_size': len(entries),
                'total_failed': len(self.failed_entries[language]),
                'sample_date': '2025-11-18',
                'entries': entries
            }

            with open(output_file, 'w') as f:
                json.dump(save_data, f, indent=2)

            print(f"  {language.upper()}: Saved to {output_file}")

            # Also create a simple text file with entry IDs for easy processing
            txt_file = output_path / f"failed_entry_ids_{language}.txt"
            with open(txt_file, 'w') as f:
                for entry in entries:
                    f.write(f"{entry['entry_id']}\n")

            print(f"  {language.upper()}: Entry IDs saved to {txt_file}")

        # Save summary statistics
        summary_file = output_path / "sampling_summary.json"
        summary = {
            'sample_date': '2025-11-18',
            'target_languages': self.target_languages,
            'sample_size_per_language': self.sample_size,
            'results': {}
        }

        for language in self.target_languages:
            summary['results'][language] = {
                'total_failed': len(self.failed_entries[language]),
                'sampled': len(sampled.get(language, [])),
                'sampling_rate': (len(sampled.get(language, [])) / len(self.failed_entries[language]) * 100)
                                 if self.failed_entries[language] else 0
            }

        with open(summary_file, 'w') as f:
            json.dump(summary, f, indent=2)

        print(f"\n  Summary saved to {summary_file}")
        print("\n✅ All samples saved successfully!")


def main():
    """Main execution function."""
    # Set random seed for reproducibility
    random.seed(42)

    # Initialize sampler
    sampler = FailedEntrySampler()

    # Analyze all entries
    sampler.analyze_all_entries()

    # Sample failed entries
    sampled = sampler.sample_failed_entries()

    # Save samples
    sampler.save_samples(sampled)

    print("\n" + "="*80)
    print("SAMPLING COMPLETE")
    print("="*80)
    print("\nNext step: Run analyze_failure_logs.py to classify errors")
    print()


if __name__ == "__main__":
    main()
