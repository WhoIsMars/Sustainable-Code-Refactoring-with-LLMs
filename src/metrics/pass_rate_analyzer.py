"""
Pass Rate Analyzer for Thesis Section 4.1

This module calculates pass rate statistics for:
- Base code (always 100% by design)
- LLM-generated code (per model, per prompt version, per language)

Author: Generated for Thesis Analysis
Date: 2025
"""

import json
from pathlib import Path
from typing import Dict, List
from collections import defaultdict
import statistics


class PassRateAnalyzer:
    """
    Analyzes pass rates across all execution results.

    Pass Rate = (number of passed executions / total executions) * 100
    Each entry is executed 5 times, so pass_rate can be: 0%, 20%, 40%, 60%, 80%, or 100%
    """

    def __init__(self, clusters_dir: str = "../clusters/",
                 execution_output_dir: str = "../execution_outputs/"):
        """
        Initialize the analyzer.

        Args:
            clusters_dir: Path to clusters directory
            execution_output_dir: Path to execution output directory
        """
        self.clusters_dir = Path(clusters_dir)
        self.execution_output_dir = Path(execution_output_dir)

        # Storage for results
        self.pass_rate_data = {
            'global': {},
            'by_language': {},
            'by_model': {},
            'by_prompt_version': {},
            'by_language_model': {},
            'by_language_prompt': {},
            'by_model_prompt': {},
            'by_language_model_prompt': {}
        }

        # Languages and models
        self.languages = ['c', 'cpp', 'go', 'java', 'python', 'javascript', 'typescript']
        self.models = ['openAI', 'claude', 'gemini']
        self.prompt_versions = ['v1', 'v2', 'v3', 'v4']

    def get_cluster_names(self) -> List[str]:
        """Get all cluster names from execution output directory."""
        cluster_names = set()

        if not self.execution_output_dir.exists():
            print(f"Warning: Execution output directory not found: {self.execution_output_dir}")
            return []

        for file in self.execution_output_dir.glob("*_results_*.json"):
            # Extract cluster name from filename
            # Format: {cluster}_results_{num}.json or {cluster}_results_v{version}_{num}.json
            filename = file.stem
            parts = filename.split('_results_')
            if len(parts) >= 2:
                cluster_name = parts[0]
                cluster_names.add(cluster_name)

        return sorted(list(cluster_names))

    def load_execution_results(self, cluster_name: str, test_type: str = "base",
                              prompt_version: str = None) -> List[Dict]:
        """
        Load execution results for a specific cluster and test type.

        Args:
            cluster_name: Name of the cluster
            test_type: "base" or "llm"
            prompt_version: Version for LLM tests (v1-v4), required if test_type="llm"

        Returns:
            List of result dictionaries from all 5 executions
        """
        results = []

        for exec_num in range(1, 6):  # 5 executions
            if test_type == "base":
                filename = f"{cluster_name}_results_{exec_num}.json"
            else:
                if not prompt_version:
                    raise ValueError("prompt_version required for LLM test type")
                filename = f"{cluster_name}_results_{prompt_version}_{exec_num}.json"

            filepath = self.execution_output_dir / filename

            if filepath.exists():
                try:
                    with open(filepath, 'r') as f:
                        data = json.load(f)
                        results.append(data)
                except Exception as e:
                    print(f"Warning: Could not load {filepath}: {e}")

        return results

    def calculate_pass_rate_for_entry(self, executions: List[Dict],
                                     language: str, entry_id: str,
                                     is_llm: bool = False,
                                     llm_type: str = None) -> float:
        """
        Calculate pass rate for a specific entry across 5 executions.

        Args:
            executions: List of 5 execution result dictionaries
            language: Programming language
            entry_id: Entry ID to find
            is_llm: Whether this is LLM code
            llm_type: LLM type if is_llm=True

        Returns:
            Pass rate as percentage (0-100)
        """
        passed_count = 0
        total_count = 0

        for execution in executions:
            if 'results' not in execution:
                continue

            if language not in execution['results']:
                continue

            for entry in execution['results'][language]:
                if entry.get('id') != entry_id:
                    continue

                if is_llm:
                    # For LLM code, check LLM_results
                    if 'LLM_results' not in entry:
                        continue

                    for llm_result in entry['LLM_results']:
                        if llm_result.get('LLM_type') == llm_type:
                            total_count += 1
                            if llm_result.get('regressionTestPassed', False):
                                passed_count += 1
                            break  # Found the LLM result we're looking for
                else:
                    # For base code
                    total_count += 1
                    if entry.get('regressionTestPassed', False):
                        passed_count += 1

                break  # Found the entry

        if total_count == 0:
            return None  # No data available

        return (passed_count / total_count) * 100.0

    def analyze_cluster(self, cluster_name: str) -> Dict:
        """
        Analyze pass rates for a single cluster.

        CRITICAL FILTER: Only includes base code entries with 100% pass rate.
        This ensures we only compare LLM code against known-good baseline.

        Returns:
            Dictionary with pass rate data for this cluster
        """
        cluster_results = {
            'cluster_name': cluster_name,
            'base': {},
            'llm': {},
            'valid_entries': {}  # Track which entries have 100% base pass rate
        }

        # Load cluster metadata to get entry IDs
        cluster_file = self.clusters_dir / f"cluster_{cluster_name}.json"
        if not cluster_file.exists():
            cluster_file = self.clusters_dir / f"cluster_{cluster_name}.with_metrics.json"

        if not cluster_file.exists():
            print(f"Warning: Cluster file not found for {cluster_name}")
            return cluster_results

        try:
            with open(cluster_file, 'r') as f:
                cluster_data = json.load(f)
        except Exception as e:
            print(f"Warning: Could not load cluster {cluster_name}: {e}")
            return cluster_results

        # PHASE 1: Analyze base code and identify entries with 100% pass rate
        base_executions = self.load_execution_results(cluster_name, test_type="base")
        valid_entries_by_language = defaultdict(set)  # language -> set of valid entry_ids

        if base_executions:
            for language in self.languages:
                if language not in cluster_data:
                    continue

                for entry in cluster_data[language]:
                    entry_id = entry.get('id')
                    if not entry_id:
                        continue

                    pass_rate = self.calculate_pass_rate_for_entry(
                        base_executions, language, entry_id, is_llm=False
                    )

                    # CRITICAL FILTER: Only include if pass_rate is exactly 100%
                    if pass_rate is not None and pass_rate == 100.0:
                        if language not in cluster_results['base']:
                            cluster_results['base'][language] = {}
                        cluster_results['base'][language][entry_id] = pass_rate
                        valid_entries_by_language[language].add(entry_id)

        # PHASE 2: Analyze LLM code ONLY for entries with 100% base pass rate
        for prompt_version in self.prompt_versions:
            llm_executions = self.load_execution_results(
                cluster_name, test_type="llm", prompt_version=prompt_version
            )

            if not llm_executions:
                continue

            for language in self.languages:
                if language not in cluster_data:
                    continue

                # Skip if no valid base entries for this language
                if language not in valid_entries_by_language:
                    continue

                for entry in cluster_data[language]:
                    entry_id = entry.get('id')
                    if not entry_id:
                        continue

                    # CRITICAL FILTER: Only analyze if base code passed at 100%
                    if entry_id not in valid_entries_by_language[language]:
                        continue

                    # Check each model
                    for model in self.models:
                        pass_rate = self.calculate_pass_rate_for_entry(
                            llm_executions, language, entry_id,
                            is_llm=True, llm_type=model
                        )

                        if pass_rate is not None:
                            key = f"{language}_{model}_{prompt_version}"
                            if key not in cluster_results['llm']:
                                cluster_results['llm'][key] = {}
                            cluster_results['llm'][key][entry_id] = pass_rate

        return cluster_results

    def aggregate_across_clusters(self) -> Dict:
        """
        Main analysis function: aggregates pass rates across all clusters.

        CRITICAL: Only analyzes entries where base code has 100% pass rate.

        Returns:
            Dictionary with aggregated statistics at multiple levels
        """
        print("Starting pass rate analysis across all clusters...")
        print("CRITICAL FILTER: Only analyzing entries with 100% base code pass rate")

        cluster_names = self.get_cluster_names()
        print(f"Found {len(cluster_names)} clusters")

        # Storage for all pass rates (for aggregation)
        all_pass_rates = {
            'base': defaultdict(list),  # language -> [pass_rates]
            'llm_by_language': defaultdict(list),  # language -> [pass_rates]
            'llm_by_model': defaultdict(list),  # model -> [pass_rates]
            'llm_by_prompt': defaultdict(list),  # prompt_version -> [pass_rates]
            'llm_by_language_model': defaultdict(list),  # (language, model) -> [pass_rates]
            'llm_by_language_prompt': defaultdict(list),  # (language, prompt) -> [pass_rates]
            'llm_by_model_prompt': defaultdict(list),  # (model, prompt) -> [pass_rates]
            'llm_by_language_model_prompt': defaultdict(list)  # (language, model, prompt) -> [pass_rates]
        }

        # Track filtering statistics
        total_base_entries = 0
        filtered_base_entries = 0

        # Process each cluster
        for i, cluster_name in enumerate(cluster_names, 1):
            print(f"Processing cluster {i}/{len(cluster_names)}: {cluster_name}")

            cluster_results = self.analyze_cluster(cluster_name)

            # Count entries for filtering statistics
            for language, entries in cluster_results['base'].items():
                filtered_base_entries += len(entries)  # These passed the filter (100%)

            # Aggregate base code pass rates
            for language, entries in cluster_results['base'].items():
                for entry_id, pass_rate in entries.items():
                    all_pass_rates['base'][language].append(pass_rate)

            # Aggregate LLM pass rates
            for key, entries in cluster_results['llm'].items():
                # Parse key: language_model_promptVersion
                parts = key.rsplit('_', 2)
                if len(parts) != 3:
                    continue

                language, model, prompt_version = parts

                for entry_id, pass_rate in entries.items():
                    # Store in different aggregation levels
                    all_pass_rates['llm_by_language'][language].append(pass_rate)
                    all_pass_rates['llm_by_model'][model].append(pass_rate)
                    all_pass_rates['llm_by_prompt'][prompt_version].append(pass_rate)
                    all_pass_rates['llm_by_language_model'][(language, model)].append(pass_rate)
                    all_pass_rates['llm_by_language_prompt'][(language, prompt_version)].append(pass_rate)
                    all_pass_rates['llm_by_model_prompt'][(model, prompt_version)].append(pass_rate)
                    all_pass_rates['llm_by_language_model_prompt'][(language, model, prompt_version)].append(pass_rate)

        # Calculate statistics for each aggregation level
        print("\nCalculating statistics...")
        print(f"✓ Included {filtered_base_entries} base code entries with 100% pass rate")
        print(f"  (These are the ONLY entries analyzed for LLM comparison)")

        # Global statistics
        self.pass_rate_data['global'] = self._calculate_statistics(all_pass_rates)

        # By language
        for language in self.languages:
            base_rates = all_pass_rates['base'].get(language, [])
            llm_rates = all_pass_rates['llm_by_language'].get(language, [])

            self.pass_rate_data['by_language'][language] = {
                'base': self._compute_stats(base_rates),
                'llm_aggregated': self._compute_stats(llm_rates),
                'degradation_percent': self._calculate_degradation(base_rates, llm_rates)
            }

        # By model
        for model in self.models:
            llm_rates = all_pass_rates['llm_by_model'].get(model, [])
            self.pass_rate_data['by_model'][model] = self._compute_stats(llm_rates)

        # By prompt version
        for prompt_version in self.prompt_versions:
            llm_rates = all_pass_rates['llm_by_prompt'].get(prompt_version, [])
            self.pass_rate_data['by_prompt_version'][prompt_version] = self._compute_stats(llm_rates)

        # By language + model
        for language in self.languages:
            if language not in self.pass_rate_data['by_language_model']:
                self.pass_rate_data['by_language_model'][language] = {}

            for model in self.models:
                llm_rates = all_pass_rates['llm_by_language_model'].get((language, model), [])
                self.pass_rate_data['by_language_model'][language][model] = self._compute_stats(llm_rates)

        # By language + prompt version
        for language in self.languages:
            if language not in self.pass_rate_data['by_language_prompt']:
                self.pass_rate_data['by_language_prompt'][language] = {}

            for prompt_version in self.prompt_versions:
                base_rates = all_pass_rates['base'].get(language, [])
                llm_rates = all_pass_rates['llm_by_language_prompt'].get((language, prompt_version), [])

                self.pass_rate_data['by_language_prompt'][language][prompt_version] = {
                    'base': self._compute_stats(base_rates),
                    'llm': {},
                    'degradation_percent': self._calculate_degradation(base_rates, llm_rates)
                }

                # Also store per model for this language+prompt combination
                for model in self.models:
                    model_rates = all_pass_rates['llm_by_language_model_prompt'].get(
                        (language, model, prompt_version), []
                    )
                    self.pass_rate_data['by_language_prompt'][language][prompt_version]['llm'][model] = \
                        self._compute_stats(model_rates)

        # By model + prompt version
        for model in self.models:
            if model not in self.pass_rate_data['by_model_prompt']:
                self.pass_rate_data['by_model_prompt'][model] = {}

            for prompt_version in self.prompt_versions:
                llm_rates = all_pass_rates['llm_by_model_prompt'].get((model, prompt_version), [])
                self.pass_rate_data['by_model_prompt'][model][prompt_version] = self._compute_stats(llm_rates)

        print("✓ Pass rate analysis complete!")
        return self.pass_rate_data

    def _calculate_statistics(self, all_pass_rates: Dict) -> Dict:
        """Calculate comprehensive statistics from raw pass rate data."""
        stats = {}

        # Base code statistics
        all_base_rates = []
        for rates in all_pass_rates['base'].values():
            all_base_rates.extend(rates)
        stats['base'] = self._compute_stats(all_base_rates)

        # LLM aggregated statistics
        all_llm_rates = []
        for rates in all_pass_rates['llm_by_language'].values():
            all_llm_rates.extend(rates)
        stats['llm_aggregated'] = self._compute_stats(all_llm_rates)

        # Overall degradation
        stats['overall_degradation_percent'] = self._calculate_degradation(
            all_base_rates, all_llm_rates
        )

        return stats

    def _compute_stats(self, values: List[float]) -> Dict:
        """Compute statistical measures for a list of pass rates."""
        if not values:
            return {
                'mean': None,
                'median': None,
                'std': None,
                'min': None,
                'max': None,
                'count': 0
            }

        return {
            'mean': statistics.mean(values),
            'median': statistics.median(values),
            'std': statistics.stdev(values) if len(values) > 1 else 0.0,
            'min': min(values),
            'max': max(values),
            'count': len(values)
        }

    def _calculate_degradation(self, base_rates: List[float],
                               llm_rates: List[float]) -> float:
        """
        Calculate degradation percentage.

        Degradation = ((LLM_mean - Base_mean) / Base_mean) * 100
        Negative values indicate degradation, positive values indicate improvement
        """
        if not base_rates or not llm_rates:
            return None

        base_mean = statistics.mean(base_rates)
        llm_mean = statistics.mean(llm_rates)

        if base_mean == 0:
            return None

        return ((llm_mean - base_mean) / base_mean) * 100.0

    def save_results(self, output_dir: str = "execution_stats"):
        """Save aggregated pass rate data to JSON file."""
        output_path = Path(output_dir)
        output_path.mkdir(parents=True, exist_ok=True)

        output_file = output_path / "pass_rate_aggregated.json"

        with open(output_file, 'w') as f:
            json.dump(self.pass_rate_data, f, indent=2)

        print(f"✓ Results saved to {output_file}")
        return output_file

    def print_summary(self):
        """Print a summary of the pass rate analysis."""
        print("\n" + "="*80)
        print("PASS RATE ANALYSIS SUMMARY")
        print("="*80)

        # Global statistics
        if 'global' in self.pass_rate_data and self.pass_rate_data['global']:
            global_stats = self.pass_rate_data['global']
            print("\nGLOBAL STATISTICS:")
            base_mean = global_stats.get('base', {}).get('mean')
            llm_mean = global_stats.get('llm_aggregated', {}).get('mean')
            degradation = global_stats.get('overall_degradation_percent')

            if base_mean is not None:
                print(f"  Base Code Mean Pass Rate: {base_mean:.2f}%")
            else:
                print(f"  Base Code Mean Pass Rate: No data")

            if llm_mean is not None:
                print(f"  LLM Aggregated Mean Pass Rate: {llm_mean:.2f}%")
            else:
                print(f"  LLM Aggregated Mean Pass Rate: No data")

            if degradation is not None:
                print(f"  Overall Degradation: {degradation:.2f}%")
            else:
                print(f"  Overall Degradation: No data")

        # By language
        if 'by_language' in self.pass_rate_data:
            print("\nPASS RATE BY LANGUAGE:")
            has_data = False
            for language, stats in self.pass_rate_data['by_language'].items():
                base_mean = stats.get('base', {}).get('mean')
                llm_mean = stats.get('llm_aggregated', {}).get('mean')
                degradation = stats.get('degradation_percent')

                if base_mean is not None and llm_mean is not None:
                    has_data = True
                    print(f"  {language.upper()}:")
                    print(f"    Base: {base_mean:.2f}%")
                    print(f"    LLM:  {llm_mean:.2f}%")
                    if degradation is not None:
                        print(f"    Degradation: {degradation:.2f}%")

            if not has_data:
                print("  No data available")

        # By model
        if 'by_model' in self.pass_rate_data:
            print("\nPASS RATE BY MODEL:")
            has_data = False
            for model, stats in self.pass_rate_data['by_model'].items():
                mean = stats.get('mean')
                if mean is not None:
                    has_data = True
                    print(f"  {model}: {mean:.2f}%")
            if not has_data:
                print("  No data available")

        # By prompt version
        if 'by_prompt_version' in self.pass_rate_data:
            print("\nPASS RATE BY PROMPT VERSION:")
            has_data = False
            for version, stats in self.pass_rate_data['by_prompt_version'].items():
                mean = stats.get('mean')
                if mean is not None:
                    has_data = True
                    print(f"  {version}: {mean:.2f}%")
            if not has_data:
                print("  No data available")

        print("\n" + "="*80)


def main():
    """Main execution function."""
    # Initialize analyzer
    analyzer = PassRateAnalyzer()

    # Run analysis
    results = analyzer.aggregate_across_clusters()

    # Save results
    analyzer.save_results()

    # Print summary
    analyzer.print_summary()


if __name__ == "__main__":
    main()
