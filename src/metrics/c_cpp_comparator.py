"""
C vs C++ Root Cause Analysis Script

This module performs comprehensive Root Cause Analysis (RCA) to investigate
why C++ LLM-generated code has systematically lower pass rates compared to C.

Modules:
A. PassRateComparator - Global statistics comparison
B. ClusterMatcher - Identifies common clusters for analysis
C. ErrorAnalyzer - Classifies and quantifies error types
D. CodeDiffGenerator - Generates side-by-side diffs
E. BuildConfigComparator - Compares build configurations
F. ReportGenerator - Creates comprehensive markdown report

Author: Generated for Thesis Analysis
Date: 2025
"""

import json
import os
import sys
from pathlib import Path
from typing import Dict, List
from collections import defaultdict, Counter
import difflib
import statistics

# Add parent directory to path for imports
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))

# Import unified_analyzer
try:
    from unified_analyzer.core.models import ExecutionEntry
    from unified_analyzer.analyzers.anomaly_detector import AnomalyDetector
    from unified_analyzer.analyzers.root_cause_analyzer import RootCauseAnalyzer
    from unified_analyzer.core.enums import AnomalyType
    from unified_analyzer.data.loader import DataLoader
    UNIFIED_ANALYZER_AVAILABLE = True
except ImportError:
    UNIFIED_ANALYZER_AVAILABLE = False
    print("Warning: unified_analyzer not available. Some features may be limited.")


class PassRateComparator:
    """
    Module A: Compares pass rates between C and C++ at various aggregation levels.

    CRITICAL: Only analyzes entries where base code has 100% pass rate.
    """

    def __init__(self, execution_output_dir: str = "../execution_outputs/"):
        self.execution_output_dir = Path(execution_output_dir)
        self.pass_rate_data = {
            'c': {'global': {}, 'by_model': {}, 'by_prompt': {}, 'by_cluster': {}},
            'cpp': {'global': {}, 'by_model': {}, 'by_prompt': {}, 'by_cluster': {}}
        }

    def calculate_pass_rate(self, executions: List[Dict], language: str,
                           entry_id: str, is_llm: bool = False,
                           llm_type: str = None) -> float:
        """Calculate pass rate for an entry across multiple executions."""
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
                    if 'LLM_results' not in entry:
                        continue

                    for llm_result in entry['LLM_results']:
                        if llm_result.get('LLM_type') == llm_type:
                            total_count += 1
                            if llm_result.get('regressionTestPassed', False):
                                passed_count += 1
                            break
                else:
                    total_count += 1
                    if entry.get('regressionTestPassed', False):
                        passed_count += 1

                break

        if total_count == 0:
            return None

        return (passed_count / total_count) * 100.0

    def analyze_languages(self, cluster_names: List[str],
                         clusters_dir: Path) -> Dict:
        """
        Analyze pass rates for C and C++ across all clusters.

        Returns comprehensive statistics for comparison.
        """
        print("Analyzing C vs C++ pass rates...")

        models = ['openAI', 'claude', 'gemini']
        prompt_versions = ['v1', 'v2', 'v3', 'v4']

        for lang in ['c', 'cpp']:
            all_pass_rates = []
            by_model_rates = defaultdict(list)
            by_prompt_rates = defaultdict(list)
            by_cluster_rates = {}

            for cluster_name in cluster_names:
                cluster_file = clusters_dir / f"cluster_{cluster_name}.json"
                if not cluster_file.exists():
                    cluster_file = clusters_dir / f"cluster_{cluster_name}.with_metrics.json"

                if not cluster_file.exists():
                    continue

                try:
                    with open(cluster_file, 'r') as f:
                        cluster_data = json.load(f)
                except:
                    continue

                if lang not in cluster_data:
                    continue

                cluster_pass_rates = []

                # Analyze LLM code for this cluster
                for prompt_version in prompt_versions:
                    llm_files = list(self.execution_output_dir.glob(
                        f"{cluster_name}_results_{prompt_version}_*.json"
                    ))

                    if not llm_files:
                        continue

                    llm_executions = []
                    for llm_file in llm_files:
                        try:
                            with open(llm_file, 'r') as f:
                                llm_executions.append(json.load(f))
                        except:
                            continue

                    if not llm_executions:
                        continue

                    # Calculate pass rates for each entry and model
                    for entry in cluster_data[lang]:
                        entry_id = entry.get('id')
                        if not entry_id:
                            continue

                        for model in models:
                            pass_rate = self.calculate_pass_rate(
                                llm_executions, lang, entry_id,
                                is_llm=True, llm_type=model
                            )

                            if pass_rate is not None:
                                all_pass_rates.append(pass_rate)
                                by_model_rates[model].append(pass_rate)
                                by_prompt_rates[prompt_version].append(pass_rate)
                                cluster_pass_rates.append(pass_rate)

                if cluster_pass_rates:
                    by_cluster_rates[cluster_name] = {
                        'mean': statistics.mean(cluster_pass_rates),
                        'median': statistics.median(cluster_pass_rates),
                        'count': len(cluster_pass_rates)
                    }

            # Calculate global statistics
            if all_pass_rates:
                self.pass_rate_data[lang]['global'] = {
                    'mean': statistics.mean(all_pass_rates),
                    'median': statistics.median(all_pass_rates),
                    'std': statistics.stdev(all_pass_rates) if len(all_pass_rates) > 1 else 0,
                    'min': min(all_pass_rates),
                    'max': max(all_pass_rates),
                    'count': len(all_pass_rates),
                    'zero_pass_rate_count': sum(1 for pr in all_pass_rates if pr == 0),
                    'full_pass_rate_count': sum(1 for pr in all_pass_rates if pr == 100)
                }

            # Calculate by model
            for model, rates in by_model_rates.items():
                if rates:
                    self.pass_rate_data[lang]['by_model'][model] = {
                        'mean': statistics.mean(rates),
                        'median': statistics.median(rates),
                        'count': len(rates)
                    }

            # Calculate by prompt
            for prompt, rates in by_prompt_rates.items():
                if rates:
                    self.pass_rate_data[lang]['by_prompt'][prompt] = {
                        'mean': statistics.mean(rates),
                        'median': statistics.median(rates),
                        'count': len(rates)
                    }

            self.pass_rate_data[lang]['by_cluster'] = by_cluster_rates

        return self.pass_rate_data

    def print_comparison(self):
        """Print a formatted comparison of C vs C++ pass rates."""
        print("\n" + "="*80)
        print("C vs C++ PASS RATE COMPARISON")
        print("="*80)

        # Global comparison
        print("\nGLOBAL STATISTICS:")
        print(f"{'Metric':<20} {'C':>15} {'C++':>15} {'Gap':>15}")
        print("-" * 70)

        c_global = self.pass_rate_data['c']['global']
        cpp_global = self.pass_rate_data['cpp']['global']

        if c_global and cpp_global:
            metrics = ['mean', 'median', 'std', 'min', 'max']
            for metric in metrics:
                c_val = c_global.get(metric, 0)
                cpp_val = cpp_global.get(metric, 0)
                gap = c_val - cpp_val
                print(f"{metric.capitalize():<20} {c_val:>14.2f}% {cpp_val:>14.2f}% {gap:>+14.2f}%")

            print(f"\n{'0% Pass Rate Count':<20} {c_global.get('zero_pass_rate_count', 0):>15} "
                  f"{cpp_global.get('zero_pass_rate_count', 0):>15}")
            print(f"{'100% Pass Rate Count':<20} {c_global.get('full_pass_rate_count', 0):>15} "
                  f"{cpp_global.get('full_pass_rate_count', 0):>15}")

        # By model comparison
        print("\n\nBY MODEL:")
        print(f"{'Model':<15} {'C Mean':>15} {'C++ Mean':>15} {'Gap':>15}")
        print("-" * 65)

        models = ['openAI', 'claude', 'gemini']
        for model in models:
            c_mean = self.pass_rate_data['c']['by_model'].get(model, {}).get('mean', 0)
            cpp_mean = self.pass_rate_data['cpp']['by_model'].get(model, {}).get('mean', 0)
            gap = c_mean - cpp_mean
            print(f"{model:<15} {c_mean:>14.2f}% {cpp_mean:>14.2f}% {gap:>+14.2f}%")

        print("\n" + "="*80)


class ClusterMatcher:
    """
    Module B: Identifies clusters that exist in both C and C++ with passing base code.
    """

    def __init__(self, clusters_dir: str = "../clusters/",
                 execution_output_dir: str = "../execution_outputs/"):
        self.clusters_dir = Path(clusters_dir)
        self.execution_output_dir = Path(execution_output_dir)

    def find_common_clusters(self) -> List[str]:
        """Find cluster names that have both C and C++ entries."""
        common_clusters = []

        for cluster_file in self.clusters_dir.glob("cluster_*.json"):
            try:
                with open(cluster_file, 'r') as f:
                    cluster_data = json.load(f)

                if 'c' in cluster_data and 'cpp' in cluster_data:
                    # Check that both have entries
                    if cluster_data['c'] and cluster_data['cpp']:
                        cluster_name = cluster_file.stem.replace('cluster_', '')
                        common_clusters.append(cluster_name)

            except Exception as e:
                print(f"Warning: Could not process {cluster_file}: {e}")
                continue

        return sorted(common_clusters)

    def filter_by_base_code_passing(self, cluster_names: List[str]) -> List[str]:
        """
        Filter clusters to only those where base code passes tests in BOTH C and C++.
        """
        passing_clusters = []

        for cluster_name in cluster_names:
            # Load cluster data
            cluster_file = self.clusters_dir / f"cluster_{cluster_name}.json"
            if not cluster_file.exists():
                cluster_file = self.clusters_dir / f"cluster_{cluster_name}.with_metrics.json"

            if not cluster_file.exists():
                continue

            try:
                with open(cluster_file, 'r') as f:
                    cluster_data = json.load(f)
            except:
                continue

            # Check base code pass rate for both languages
            both_pass = True

            for lang in ['c', 'cpp']:
                if lang not in cluster_data:
                    both_pass = False
                    break

                # Load base execution results
                base_files = list(self.execution_output_dir.glob(
                    f"{cluster_name}_results_[1-5].json"
                ))

                if not base_files:
                    both_pass = False
                    break

                base_executions = []
                for base_file in base_files:
                    try:
                        with open(base_file, 'r') as f:
                            base_executions.append(json.load(f))
                    except:
                        continue

                if not base_executions:
                    both_pass = False
                    break

                # Check if any entry in this language passes
                lang_has_passing = False

                for entry in cluster_data[lang]:
                    entry_id = entry.get('id')
                    if not entry_id:
                        continue

                    # Count passing executions
                    passed_count = 0
                    total_count = 0

                    for execution in base_executions:
                        if 'results' not in execution or lang not in execution['results']:
                            continue

                        for exec_entry in execution['results'][lang]:
                            if exec_entry.get('id') == entry_id:
                                total_count += 1
                                if exec_entry.get('regressionTestPassed', False):
                                    passed_count += 1
                                break

                    if total_count > 0 and passed_count == total_count:
                        lang_has_passing = True
                        break

                if not lang_has_passing:
                    both_pass = False
                    break

            if both_pass:
                passing_clusters.append(cluster_name)

        return passing_clusters

    def select_top_n_for_analysis(self, cluster_names: List[str],
                                  n: int = 5) -> List[str]:
        """
        Select top N clusters for detailed analysis.

        Selection criteria:
        - Most representative (diverse exercise types)
        - Highest failure rate in C++
        - Available LLM generated code
        """
        if len(cluster_names) <= n:
            return cluster_names

        # For simplicity, return first N
        # In production, could implement more sophisticated selection
        return cluster_names[:n]


class ErrorAnalyzer:
    """
    Module C: Analyzes and classifies errors using unified_analyzer.
    """

    def __init__(self, execution_output_dir: str = "../execution_outputs/"):
        self.execution_output_dir = Path(execution_output_dir)
        self.error_stats = {
            'c': {'total': 0, 'by_type': Counter(), 'by_root_cause': Counter()},
            'cpp': {'total': 0, 'by_type': Counter(), 'by_root_cause': Counter()}
        }

    def analyze_errors(self, cluster_names: List[str]) -> Dict:
        """
        Analyze errors for C and C++ clusters using unified_analyzer.
        """
        print("\nAnalyzing errors with unified_analyzer...")

        try:
            data_loader = DataLoader(base_dir=str(self.execution_output_dir.parent))
            anomaly_detector = AnomalyDetector()
            root_cause_analyzer = RootCauseAnalyzer()
        except:
            print("Warning: unified_analyzer not available. Using fallback error detection.")
            return self._fallback_error_analysis(cluster_names)

        for cluster_name in cluster_names:
            for lang in ['c', 'cpp']:
                try:
                    # Load execution results
                    base_results, llm_results = data_loader.load_execution_results(
                        cluster_name, language_filter=lang
                    )

                    # Analyze LLM results
                    for prompt_version, executions in llm_results.items():
                        for execution in executions:
                            # Convert to ExecutionEntry objects
                            entries = self._extract_entries(execution, lang, cluster_name)

                            for entry in entries:
                                # Detect anomalies
                                anomalies = anomaly_detector.detect_all(entry)

                                if anomalies:
                                    self.error_stats[lang]['total'] += 1

                                    for anomaly in anomalies:
                                        self.error_stats[lang]['by_type'][anomaly.anomaly_type] += 1

                                        # Perform root cause analysis
                                        if anomaly.anomaly_type in [
                                            AnomalyType.EXECUTION_FAILED,
                                            AnomalyType.INVALID_VALUE
                                        ]:
                                            rca_result = root_cause_analyzer.analyze(entry, anomaly)
                                            if rca_result and rca_result.root_cause:
                                                self.error_stats[lang]['by_root_cause'][
                                                    rca_result.root_cause
                                                ] += 1

                except Exception as e:
                    print(f"Warning: Could not analyze {cluster_name} ({lang}): {e}")
                    continue

        return self.error_stats

    def _extract_entries(self, execution: Dict, language: str,
                        cluster_name: str) -> List[ExecutionEntry]:
        """Extract ExecutionEntry objects from execution results."""
        entries = []

        if 'results' not in execution or language not in execution['results']:
            return entries

        for entry_data in execution['results'][language]:
            # Handle both base and LLM results
            if 'LLM_results' in entry_data:
                for llm_result in entry_data['LLM_results']:
                    entry = ExecutionEntry(
                        id=entry_data.get('id'),
                        cluster_name=cluster_name,
                        language=language,
                        filename=entry_data.get('filename'),
                        test_type='llm',
                        exec_number=1,  # Simplified
                        execution_time_ms=llm_result.get('execution_time_ms'),
                        cpu_usage=llm_result.get('CPU_usage'),
                        ram_usage=llm_result.get('RAM_usage'),
                        regression_test_passed=llm_result.get('regressionTestPassed'),
                        success=llm_result.get('success'),
                        error_message=llm_result.get('error_message'),
                        log_path=llm_result.get('log')
                    )
                    entries.append(entry)
            else:
                entry = ExecutionEntry(
                    id=entry_data.get('id'),
                    cluster_name=cluster_name,
                    language=language,
                    filename=entry_data.get('filename'),
                    test_type='base',
                    exec_number=1,
                    execution_time_ms=entry_data.get('execution_time_ms'),
                    cpu_usage=entry_data.get('CPU_usage'),
                    ram_usage=entry_data.get('RAM_usage'),
                    regression_test_passed=entry_data.get('regressionTestPassed'),
                    success=entry_data.get('success'),
                    error_message=entry_data.get('error_message'),
                    log_path=entry_data.get('log_path')
                )
                entries.append(entry)

        return entries

    def _fallback_error_analysis(self, cluster_names: List[str]) -> Dict:
        """Fallback error analysis when unified_analyzer is not available."""
        print("Using fallback error analysis...")

        for cluster_name in cluster_names:
            for lang in ['c', 'cpp']:
                # Load LLM execution results
                llm_files = list(self.execution_output_dir.glob(
                    f"{cluster_name}_results_v*_*.json"
                ))

                for llm_file in llm_files:
                    try:
                        with open(llm_file, 'r') as f:
                            execution = json.load(f)

                        if 'results' not in execution or lang not in execution['results']:
                            continue

                        for entry in execution['results'][lang]:
                            if 'LLM_results' not in entry:
                                continue

                            for llm_result in entry['LLM_results']:
                                if not llm_result.get('success', True):
                                    self.error_stats[lang]['total'] += 1

                                    # Simple classification based on available info
                                    if not llm_result.get('regressionTestPassed', False):
                                        self.error_stats[lang]['by_type']['TEST_FAILURE'] += 1
                                    elif llm_result.get('error_message'):
                                        if 'compilation' in llm_result['error_message'].lower():
                                            self.error_stats[lang]['by_root_cause']['COMPILATION_ERROR'] += 1
                                        elif 'timeout' in llm_result['error_message'].lower():
                                            self.error_stats[lang]['by_root_cause']['TIMEOUT'] += 1
                                        else:
                                            self.error_stats[lang]['by_root_cause']['RUNTIME_ERROR'] += 1

                    except Exception as e:
                        continue

        return self.error_stats

    def print_error_summary(self):
        """Print formatted error analysis summary."""
        print("\n" + "="*80)
        print("ERROR ANALYSIS SUMMARY")
        print("="*80)

        print("\nTOTAL ERRORS:")
        print(f"  C:   {self.error_stats['c']['total']}")
        print(f"  C++: {self.error_stats['cpp']['total']}")
        print(f"  Gap: {self.error_stats['cpp']['total'] - self.error_stats['c']['total']}")

        print("\nERROR TYPES (C):")
        for error_type, count in self.error_stats['c']['by_type'].most_common():
            print(f"  {error_type}: {count}")

        print("\nERROR TYPES (C++):")
        for error_type, count in self.error_stats['cpp']['by_type'].most_common():
            print(f"  {error_type}: {count}")

        print("\nROOT CAUSES (C):")
        for cause, count in self.error_stats['c']['by_root_cause'].most_common():
            print(f"  {cause}: {count}")

        print("\nROOT CAUSES (C++):")
        for cause, count in self.error_stats['cpp']['by_root_cause'].most_common():
            print(f"  {cause}: {count}")

        print("\n" + "="*80)


class CodeDiffGenerator:
    """
    Module D: Generates side-by-side code diffs for analysis.
    """

    def __init__(self, dataset_dir: str = "../dataset/"):
        self.dataset_dir = Path(dataset_dir)

    def generate_diff(self, file1_path: str, file2_path: str,
                     label1: str = "File 1", label2: str = "File 2") -> str:
        """Generate unified diff between two files."""
        try:
            with open(file1_path, 'r', encoding='utf-8', errors='ignore') as f1:
                file1_lines = f1.readlines()

            with open(file2_path, 'r', encoding='utf-8', errors='ignore') as f2:
                file2_lines = f2.readlines()

            diff = difflib.unified_diff(
                file1_lines, file2_lines,
                fromfile=label1, tofile=label2,
                lineterm=''
            )

            return '\n'.join(diff)

        except Exception as e:
            return f"Error generating diff: {e}"

    def generate_cluster_diffs(self, cluster_name: str,
                               cluster_data: Dict,
                               model: str = 'openAI',
                               prompt_version: str = 'v4') -> Dict[str, str]:
        """
        Generate diffs for a cluster comparing C vs C++ code.

        Returns dictionary with diff types as keys and diff text as values.
        """
        diffs = {}

        # Get first entry for each language (simplified)
        c_entry = cluster_data.get('c', [{}])[0] if 'c' in cluster_data else None
        cpp_entry = cluster_data.get('cpp', [{}])[0] if 'cpp' in cluster_data else None

        if not c_entry or not cpp_entry:
            return diffs

        # Diff 1: Base code C vs Base code C++
        c_base_path = c_entry.get('codeSnippetFilePath')
        cpp_base_path = cpp_entry.get('codeSnippetFilePath')

        if c_base_path and cpp_base_path:
            diffs['base_c_vs_base_cpp'] = self.generate_diff(
                c_base_path, cpp_base_path,
                label1="Base C", label2="Base C++"
            )

        # Diff 2: LLM code C vs LLM code C++ (same model/prompt)
        c_llm = None
        cpp_llm = None

        if 'LLMs' in c_entry:
            for llm in c_entry['LLMs']:
                if llm.get('type') == model and f"_{prompt_version}." in llm.get('filename', ''):
                    c_llm = llm
                    break

        if 'LLMs' in cpp_entry:
            for llm in cpp_entry['LLMs']:
                if llm.get('type') == model and f"_{prompt_version}." in llm.get('filename', ''):
                    cpp_llm = llm
                    break

        if c_llm and cpp_llm:
            c_llm_path = c_llm.get('path')
            cpp_llm_path = cpp_llm.get('path')

            if c_llm_path and cpp_llm_path:
                diffs['llm_c_vs_llm_cpp'] = self.generate_diff(
                    c_llm_path, cpp_llm_path,
                    label1=f"LLM C ({model} {prompt_version})",
                    label2=f"LLM C++ ({model} {prompt_version})"
                )

        # Diff 3: Base C vs LLM C
        if c_base_path and c_llm and c_llm.get('path'):
            diffs['base_c_vs_llm_c'] = self.generate_diff(
                c_base_path, c_llm['path'],
                label1="Base C", label2=f"LLM C ({model} {prompt_version})"
            )

        # Diff 4: Base C++ vs LLM C++
        if cpp_base_path and cpp_llm and cpp_llm.get('path'):
            diffs['base_cpp_vs_llm_cpp'] = self.generate_diff(
                cpp_base_path, cpp_llm['path'],
                label1="Base C++", label2=f"LLM C++ ({model} {prompt_version})"
            )

        return diffs


class BuildConfigComparator:
    """
    Module E: Compares build configurations between C and C++.
    """

    def __init__(self, docker_dir: str = "../docker/"):
        self.docker_dir = Path(docker_dir)

    def compare_dockerfiles(self) -> Dict:
        """Compare Dockerfile configurations for C and C++."""
        comparison = {
            'c_dockerfile': None,
            'cpp_dockerfile': None,
            'differences': []
        }

        c_dockerfile = self.docker_dir / "c" / "Dockerfile"
        cpp_dockerfile = self.docker_dir / "cpp" / "Dockerfile"

        if c_dockerfile.exists():
            with open(c_dockerfile, 'r') as f:
                comparison['c_dockerfile'] = f.read()

        if cpp_dockerfile.exists():
            with open(cpp_dockerfile, 'r') as f:
                comparison['cpp_dockerfile'] = f.read()

        # Identify key differences
        if comparison['c_dockerfile'] and comparison['cpp_dockerfile']:
            c_lines = comparison['c_dockerfile'].split('\n')
            cpp_lines = comparison['cpp_dockerfile'].split('\n')

            # Check for different base images
            c_base = next((line for line in c_lines if line.startswith('FROM')), '')
            cpp_base = next((line for line in cpp_lines if line.startswith('FROM')), '')

            if c_base != cpp_base:
                comparison['differences'].append({
                    'type': 'base_image',
                    'c': c_base,
                    'cpp': cpp_base
                })

            # Check for different compilers
            c_compiler = 'gcc' if 'gcc' in comparison['c_dockerfile'] else None
            cpp_compiler = 'g++' if 'g++' in comparison['cpp_dockerfile'] else None

            if c_compiler and cpp_compiler:
                comparison['differences'].append({
                    'type': 'compiler',
                    'c': c_compiler,
                    'cpp': cpp_compiler
                })

            # Check for C++ specific libraries (Boost, Catch2)
            if 'boost' in comparison['cpp_dockerfile'].lower():
                comparison['differences'].append({
                    'type': 'library',
                    'description': 'C++ uses Boost libraries, C does not'
                })

            if 'catch2' in comparison['cpp_dockerfile'].lower():
                comparison['differences'].append({
                    'type': 'test_framework',
                    'description': 'C++ uses Catch2 test framework'
                })

        return comparison

    def compare_makefiles(self) -> Dict:
        """Compare Makefile configurations."""
        comparison = {
            'c_makefile': None,
            'cpp_makefile': None,
            'differences': []
        }

        c_makefile = self.docker_dir / "c" / "Makefile.universal"
        cpp_makefile = self.docker_dir / "cpp" / "Makefile.universal"

        if c_makefile.exists():
            with open(c_makefile, 'r') as f:
                comparison['c_makefile'] = f.read()

        if cpp_makefile.exists():
            with open(cpp_makefile, 'r') as f:
                comparison['cpp_makefile'] = f.read()

        return comparison


class ReportGenerator:
    """
    Module F: Generates comprehensive markdown report.
    """

    def __init__(self, output_dir: str = "c_cpp_analysis"):
        self.output_dir = Path(output_dir)
        self.output_dir.mkdir(parents=True, exist_ok=True)

    def generate_report(self, pass_rate_data: Dict, error_stats: Dict,
                       selected_clusters: List[str], cluster_diffs: Dict,
                       build_config: Dict) -> str:
        """Generate comprehensive RCA report in markdown format."""

        report_path = self.output_dir / "RCA_report.md"

        with open(report_path, 'w', encoding='utf-8') as f:
            f.write("# Root Cause Analysis: C vs C++ Pass Rate Discrepancy\n\n")
            f.write("**Generated for Thesis - Section 5.3 (Threats to Validity)**\n\n")
            f.write("---\n\n")

            # Executive Summary
            f.write("## Executive Summary\n\n")
            c_mean = pass_rate_data['c']['global'].get('mean', 0)
            cpp_mean = pass_rate_data['cpp']['global'].get('mean', 0)
            gap = c_mean - cpp_mean

            f.write(f"- **C Mean Pass Rate**: {c_mean:.2f}%\n")
            f.write(f"- **C++ Mean Pass Rate**: {cpp_mean:.2f}%\n")
            f.write(f"- **Gap**: {gap:+.2f}% (C++ performs worse)\n\n")

            if cpp_mean < 20:
                f.write("⚠️ **CRITICAL FINDING**: C++ pass rate is critically low, "
                       "indicating systematic failures.\n\n")

            # Global Statistics
            f.write("## 1. Global Statistics\n\n")
            f.write("### Pass Rate Comparison\n\n")
            f.write("| Metric | C | C++ | Gap |\n")
            f.write("|--------|---|-----|-----|\n")

            metrics = ['mean', 'median', 'std', 'min', 'max']
            for metric in metrics:
                c_val = pass_rate_data['c']['global'].get(metric, 0)
                cpp_val = pass_rate_data['cpp']['global'].get(metric, 0)
                gap_val = c_val - cpp_val
                f.write(f"| {metric.capitalize()} | {c_val:.2f}% | {cpp_val:.2f}% | {gap_val:+.2f}% |\n")

            f.write("\n### Distribution Analysis\n\n")
            c_zero = pass_rate_data['c']['global'].get('zero_pass_rate_count', 0)
            cpp_zero = pass_rate_data['cpp']['global'].get('zero_pass_rate_count', 0)
            c_full = pass_rate_data['c']['global'].get('full_pass_rate_count', 0)
            cpp_full = pass_rate_data['cpp']['global'].get('full_pass_rate_count', 0)

            f.write(f"- **0% Pass Rate**: C = {c_zero}, C++ = {cpp_zero}\n")
            f.write(f"- **100% Pass Rate**: C = {c_full}, C++ = {cpp_full}\n\n")

            # By Model
            f.write("### By Model Breakdown\n\n")
            f.write("| Model | C Mean | C++ Mean | Gap |\n")
            f.write("|-------|--------|----------|-----|\n")

            for model in ['openAI', 'claude', 'gemini']:
                c_model = pass_rate_data['c']['by_model'].get(model, {}).get('mean', 0)
                cpp_model = pass_rate_data['cpp']['by_model'].get(model, {}).get('mean', 0)
                model_gap = c_model - cpp_model
                f.write(f"| {model} | {c_model:.2f}% | {cpp_model:.2f}% | {model_gap:+.2f}% |\n")

            # Error Analysis
            f.write("\n## 2. Error Classification\n\n")
            f.write("### Total Error Count\n\n")
            c_errors = error_stats['c']['total']
            cpp_errors = error_stats['cpp']['total']
            f.write(f"- **C Total Errors**: {c_errors}\n")
            f.write(f"- **C++ Total Errors**: {cpp_errors}\n")
            f.write(f"- **Difference**: {cpp_errors - c_errors} more errors in C++\n\n")

            f.write("### Root Cause Distribution\n\n")
            f.write("#### C Root Causes:\n\n")
            for cause, count in error_stats['c']['by_root_cause'].most_common():
                f.write(f"- **{cause}**: {count}\n")

            f.write("\n#### C++ Root Causes:\n\n")
            for cause, count in error_stats['cpp']['by_root_cause'].most_common():
                f.write(f"- **{cause}**: {count}\n")

            f.write("\n")

            # Build Configuration Analysis
            f.write("## 3. Build Configuration Differences\n\n")

            if build_config.get('differences'):
                f.write("### Key Differences:\n\n")
                for diff in build_config['differences']:
                    diff_type = diff.get('type')
                    if diff_type == 'base_image':
                        f.write(f"**Base Docker Image:**\n")
                        f.write(f"- C: `{diff['c']}`\n")
                        f.write(f"- C++: `{diff['cpp']}`\n\n")
                    elif diff_type == 'compiler':
                        f.write(f"**Compiler:**\n")
                        f.write(f"- C: `{diff['c']}`\n")
                        f.write(f"- C++: `{diff['cpp']}`\n\n")
                    elif diff_type in ['library', 'test_framework']:
                        f.write(f"- {diff['description']}\n\n")

            # Code Diff Analysis
            f.write("## 4. Code Analysis\n\n")
            f.write(f"### Analyzed Clusters (Top {len(selected_clusters)}):\n\n")
            for cluster_name in selected_clusters:
                f.write(f"- `{cluster_name}`\n")
            f.write("\n")

            if cluster_diffs:
                f.write("### Sample Code Differences\n\n")
                for cluster_name, diffs in cluster_diffs.items():
                    f.write(f"#### Cluster: `{cluster_name}`\n\n")

                    for diff_type, diff_content in diffs.items():
                        if diff_content and len(diff_content) > 0:
                            f.write(f"**{diff_type.replace('_', ' ').title()}:**\n\n")
                            f.write("```diff\n")
                            # Limit diff length
                            lines = diff_content.split('\n')[:100]
                            f.write('\n'.join(lines))
                            if len(diff_content.split('\n')) > 100:
                                f.write("\n... (truncated)")
                            f.write("\n```\n\n")

            # Hypothesis and Conclusions
            f.write("## 5. Hypotheses and Root Causes\n\n")

            if cpp_errors > c_errors * 2:
                f.write("### **Primary Hypothesis: Compilation Errors in C++ LLM Code**\n\n")
                f.write("The significantly higher error rate in C++ suggests that LLM-generated C++ code "
                       "encounters compilation issues that do not occur in C. Possible causes:\n\n")
                f.write("1. **Header File Mismanagement**\n")
                f.write("   - LLMs may incorrectly handle C++ header/implementation separation\n")
                f.write("   - Missing or incorrect `#include` directives\n")
                f.write("   - Header guards not properly maintained\n\n")

                f.write("2. **Function Signature Mismatches**\n")
                f.write("   - Declarations in `.h` files not matching definitions in `.cpp` files\n")
                f.write("   - Namespace issues not present in C\n\n")

                f.write("3. **Template and Complex Syntax**\n")
                f.write("   - C++ templates may be incorrectly modified by LLMs\n")
                f.write("   - Modern C++ features (C++11/14/17) may be misused\n\n")

                f.write("4. **Build System Complexity**\n")
                f.write("   - C++ build process (linking, multiple compilation units) more fragile\n")
                f.write("   - Test frameworks (Boost.Test, Catch2) have stricter requirements\n\n")

            f.write("## 6. Recommendations\n\n")
            f.write("1. **Manual Code Review**: Examine compilation logs for C++ failures\n")
            f.write("2. **Prompt Engineering**: Improve prompts with C++-specific constraints\n")
            f.write("3. **Build Validation**: Add pre-execution compilation checks\n")
            f.write("4. **Error Logging**: Enhanced error reporting for C++ builds\n")
            f.write("5. **Header Analysis**: Automated detection of header/implementation mismatches\n\n")

            # Footer
            f.write("---\n\n")
            f.write("*This report was generated automatically for thesis analysis.*\n")

        print(f"\n✓ Report generated: {report_path}")
        return str(report_path)


class CCppComparator:
    """
    Main orchestrator class that coordinates all modules.
    """

    def __init__(self, clusters_dir: str = "../clusters/",
                 execution_output_dir: str = "../execution_outputs/",
                 dataset_dir: str = "../dataset/",
                 docker_dir: str = "../docker/",
                 output_dir: str = "c_cpp_analysis"):

        self.clusters_dir = Path(clusters_dir)
        self.execution_output_dir = Path(execution_output_dir)
        self.dataset_dir = Path(dataset_dir)
        self.docker_dir = Path(docker_dir)
        self.output_dir = Path(output_dir)
        self.output_dir.mkdir(parents=True, exist_ok=True)

        # Initialize modules
        self.pass_rate_comparator = PassRateComparator(execution_output_dir)
        self.cluster_matcher = ClusterMatcher(clusters_dir, execution_output_dir)
        self.error_analyzer = ErrorAnalyzer(execution_output_dir)
        self.code_diff_generator = CodeDiffGenerator(dataset_dir)
        self.build_config_comparator = BuildConfigComparator(docker_dir)
        self.report_generator = ReportGenerator(output_dir)

    def run_full_analysis(self, top_n_clusters: int = 5) -> Dict:
        """
        Execute complete C vs C++ Root Cause Analysis.
        """
        print("="*80)
        print("C vs C++ ROOT CAUSE ANALYSIS")
        print("="*80)

        results = {}

        # Step 1: Find common clusters
        print("\n[Step 1] Finding common clusters...")
        common_clusters = self.cluster_matcher.find_common_clusters()
        print(f"Found {len(common_clusters)} clusters with both C and C++")

        # Step 2: Filter by passing base code
        print("\n[Step 2] Filtering for passing base code...")
        passing_clusters = self.cluster_matcher.filter_by_base_code_passing(common_clusters)
        print(f"Found {len(passing_clusters)} clusters where base code passes in both languages")

        # Step 3: Pass rate comparison
        print("\n[Step 3] Comparing pass rates...")
        pass_rate_data = self.pass_rate_comparator.analyze_languages(
            passing_clusters, self.clusters_dir
        )
        self.pass_rate_comparator.print_comparison()
        results['pass_rate_data'] = pass_rate_data

        # Save pass rate data
        with open(self.output_dir / "global_statistics.json", 'w') as f:
            json.dump(pass_rate_data, f, indent=2)
        print(f"✓ Saved: {self.output_dir / 'global_statistics.json'}")

        # Step 4: Error analysis
        print("\n[Step 4] Analyzing errors...")
        error_stats = self.error_analyzer.analyze_errors(passing_clusters)
        self.error_analyzer.print_error_summary()
        results['error_stats'] = error_stats

        # Save error classification
        with open(self.output_dir / "error_classification.json", 'w') as f:
            # Convert Counter objects to dicts for JSON serialization
            serializable_stats = {
                'c': {
                    'total': error_stats['c']['total'],
                    'by_type': dict(error_stats['c']['by_type']),
                    'by_root_cause': dict(error_stats['c']['by_root_cause'])
                },
                'cpp': {
                    'total': error_stats['cpp']['total'],
                    'by_type': dict(error_stats['cpp']['by_type']),
                    'by_root_cause': dict(error_stats['cpp']['by_root_cause'])
                }
            }
            json.dump(serializable_stats, f, indent=2)
        print(f"✓ Saved: {self.output_dir / 'error_classification.json'}")

        # Step 5: Select clusters for detailed analysis
        print(f"\n[Step 5] Selecting top {top_n_clusters} clusters for detailed analysis...")
        selected_clusters = self.cluster_matcher.select_top_n_for_analysis(
            passing_clusters, n=top_n_clusters
        )
        print(f"Selected: {', '.join(selected_clusters)}")
        results['selected_clusters'] = selected_clusters

        # Step 6: Generate code diffs
        print("\n[Step 6] Generating code diffs...")
        cluster_diffs = {}
        cluster_reports_dir = self.output_dir / "cluster_reports"
        cluster_reports_dir.mkdir(exist_ok=True)

        for cluster_name in selected_clusters:
            cluster_file = self.clusters_dir / f"cluster_{cluster_name}.json"
            if not cluster_file.exists():
                cluster_file = self.clusters_dir / f"cluster_{cluster_name}.with_metrics.json"

            if not cluster_file.exists():
                continue

            try:
                with open(cluster_file, 'r') as f:
                    cluster_data = json.load(f)

                diffs = self.code_diff_generator.generate_cluster_diffs(
                    cluster_name, cluster_data
                )
                cluster_diffs[cluster_name] = diffs

                # Save individual cluster report
                cluster_report_file = cluster_reports_dir / f"{cluster_name}_diffs.txt"
                with open(cluster_report_file, 'w', encoding='utf-8') as f:
                    f.write(f"Code Diffs for Cluster: {cluster_name}\n")
                    f.write("="*80 + "\n\n")

                    for diff_type, diff_content in diffs.items():
                        f.write(f"\n{diff_type.replace('_', ' ').upper()}\n")
                        f.write("-"*80 + "\n")
                        f.write(diff_content)
                        f.write("\n\n")

                print(f"  ✓ Generated diffs for {cluster_name}")

            except Exception as e:
                print(f"  Warning: Could not generate diffs for {cluster_name}: {e}")

        results['cluster_diffs'] = cluster_diffs

        # Step 7: Compare build configurations
        print("\n[Step 7] Comparing build configurations...")
        build_config = self.build_config_comparator.compare_dockerfiles()
        results['build_config'] = build_config
        print(f"  Found {len(build_config['differences'])} key differences")

        # Step 8: Generate comprehensive report
        print("\n[Step 8] Generating comprehensive report...")
        report_path = self.report_generator.generate_report(
            pass_rate_data, error_stats, selected_clusters,
            cluster_diffs, build_config
        )
        results['report_path'] = report_path

        print("\n" + "="*80)
        print("ROOT CAUSE ANALYSIS COMPLETE!")
        print("="*80)
        print(f"\nResults saved to: {self.output_dir}")
        print(f"Main report: {report_path}")
        print("\nFiles generated:")
        print(f"  - global_statistics.json")
        print(f"  - error_classification.json")
        print(f"  - RCA_report.md")
        print(f"  - cluster_reports/ (individual diffs)")
        print("="*80 + "\n")

        return results


def main():
    """Main execution function."""
    import argparse

    parser = argparse.ArgumentParser(
        description="C vs C++ Root Cause Analysis for Pass Rate Discrepancy"
    )
    parser.add_argument(
        '--top-n',
        type=int,
        default=5,
        help="Number of clusters to analyze in detail (default: 5)"
    )
    parser.add_argument(
        '--generate-diffs',
        action='store_true',
        default=True,
        help="Generate code diffs (default: True)"
    )
    parser.add_argument(
        '--full-report',
        action='store_true',
        default=True,
        help="Generate comprehensive markdown report (default: True)"
    )

    args = parser.parse_args()

    # Initialize comparator
    comparator = CCppComparator()

    # Run full analysis
    results = comparator.run_full_analysis(top_n_clusters=args.top_n)

    return results


if __name__ == "__main__":
    main()
