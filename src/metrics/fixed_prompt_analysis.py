"""
Fixed Prompt Analysis - Generate plots with fixed prompt versions (v1 and v4)

This script generates comprehensive analysis plots fixing prompt versions to v1 and v4.
It creates:
1. Separate plots for v1 only
2. Separate plots for v4 only
3. Comparative plots v1 vs v4
4. Frequency distribution of improvements
5. Plots for appendix (v2 and v3)


Date: 2025-11-13
"""

import sys
import os
from pathlib import Path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))

import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
from collections import defaultdict
import logging
from typing import Dict, List, Tuple

from utility_dir import utility_paths
from utility_dir.general_utils import read_json, write_json, get_cluster_names

# Set style
sns.set_style("whitegrid")
plt.rcParams['figure.dpi'] = 300
plt.rcParams['font.size'] = 10


class FixedPromptAnalyzer:
    """
    Analyzer for generating plots with fixed prompt versions.

    Generates comprehensive analysis fixing prompt versions to isolate
    the effect of model and language on improvements.
    """

    def __init__(self, output_base_dir: Path = None):
        """
        Initialize the analyzer.

        Args:
            output_base_dir: Base directory for output plots
        """
        self.logger = logging.getLogger(__name__)

        if output_base_dir is None:
            self.output_base_dir = utility_paths.METRICS_DIR_FILEPATH / "fixed_prompt_plots"
        else:
            self.output_base_dir = Path(output_base_dir)

        # Create subdirectories
        self.v1_dir = self.output_base_dir / "v1_only"
        self.v4_dir = self.output_base_dir / "v4_only"
        self.comparison_dir = self.output_base_dir / "v1_vs_v4_comparison"
        self.appendix_dir = self.output_base_dir / "appendix_v2_v3"

        for dir_path in [self.v1_dir, self.v4_dir, self.comparison_dir, self.appendix_dir]:
            dir_path.mkdir(parents=True, exist_ok=True)

        self.metrics = ["CPU_usage", "RAM_usage", "execution_time_ms", "energy_joules", "pass_rate"]
        self.models = ["openAI", "gemini", "claude"]
        self.languages = ["c", "cpp", "go", "java", "python", "javascript", "typescript"]

        # Color schemes
        self.model_colors = {
            "openAI": "#3498db",   # Blue
            "gemini": "#e74c3c",   # Red
            "claude": "#9b59b6"    # Purple
        }

        self.language_colors = {
            "c": "#e74c3c",
            "cpp": "#e67e22",
            "go": "#3498db",
            "java": "#f39c12",
            "python": "#2ecc71",
            "javascript": "#f1c40f",
            "typescript": "#9b59b6"
        }

        self.logger.info(f"FixedPromptAnalyzer initialized. Output: {self.output_base_dir}")

    def load_improvement_data(self) -> Dict:
        """
        Load all improvement data from clusters.

        Returns:
            Dictionary with improvement data organized by prompt version, model, language
        """
        self.logger.info("Loading improvement data from clusters...")

        # Data structure: {prompt_version: {model: {language: {metric: [improvements]}}}}
        data = defaultdict(lambda: defaultdict(lambda: defaultdict(lambda: defaultdict(list))))

        # Load from energy improvements directory
        improvements_dir = utility_paths.METRICS_DIR_FILEPATH / "energy_improvements" / "clusters_improvements_data"

        if not improvements_dir.exists():
            self.logger.error(f"Improvements directory not found: {improvements_dir}")
            return {}

        json_files = list(improvements_dir.glob("improvements_cluster_*.json"))
        self.logger.info(f"Found {len(json_files)} cluster improvement files")

        for json_file in json_files:
            cluster_data = read_json(str(json_file))

            for entry_id, entry_data in cluster_data.items():
                if 'improvements_data' not in entry_data:
                    continue

                improvements = entry_data['improvements_data']
                base_language = entry_data.get('base_5_exec_data', {}).get('language', 'unknown')

                # Get base pass rate data for this entry
                base_5_exec = entry_data.get('base_5_exec_data', {})
                llm_5_exec = entry_data.get('LLM_5_exec_data', {})

                for model in self.models:
                    if model not in improvements:
                        continue

                    for prompt_key in ['prompt_v1', 'prompt_v2', 'prompt_v3', 'prompt_v4']:
                        if prompt_key not in improvements[model]:
                            continue

                        prompt_data = improvements[model][prompt_key]
                        language = self._normalize_language(prompt_data.get('language', base_language))

                        for metric in self.metrics:
                            # Skip pass_rate here - will be loaded from execution files
                            if metric == "pass_rate":
                                continue

                            if metric not in prompt_data:
                                continue

                            metric_data = prompt_data[metric]

                            # Only include valid improvements (not invalid, not outliers)
                            if metric_data['label'] != 'invalid' and not metric_data['is_outlier']:
                                improvement_pct = metric_data['improvement_percentage']
                                data[prompt_key][model][language][metric].append(improvement_pct)

        # Load pass_rate data from raw execution files
        self._load_pass_rate_data(data)

        self.logger.info(f"Loaded improvement data for {len(data)} prompt versions")
        return dict(data)

    def _normalize_language(self, language: str) -> str:
        """Normalize language name to lowercase"""
        lang_map = {
            'C': 'c', 'C++': 'cpp', 'Cpp': 'cpp', 'CPP': 'cpp',
            'Java': 'java', 'Python': 'python', 'JavaScript': 'javascript',
            'TypeScript': 'typescript', 'Go': 'go'
        }
        return lang_map.get(language, language.lower())

    def _load_pass_rate_data(self, data: Dict):
        """
        Load pass_rate data from raw execution output files.
        Calculates pass rate for each entry and stores improvement percentages.
        """
        execution_dir = utility_paths.OUTPUT_DIR_FILEPATH

        if not execution_dir.exists():
            self.logger.error(f"Execution outputs directory not found: {execution_dir}")
            return

        # Process each prompt version (v1-v4)
        for prompt_version in ['prompt_v1', 'prompt_v2', 'prompt_v3', 'prompt_v4']:
            version_num = prompt_version.replace('prompt_v', '')

            # Find all execution files for this version (5 runs per cluster)
            pattern = f"*_results_v{version_num}_*.json"
            execution_files = list(execution_dir.glob(pattern))

            if not execution_files:
                continue

            # Process each execution file
            for exec_file in execution_files:
                try:
                    exec_data = read_json(str(exec_file))

                    if 'results' not in exec_data:
                        continue

                    # Process each language in results
                    for language, entries in exec_data['results'].items():
                        norm_language = self._normalize_language(language)

                        for entry in entries:
                            if 'LLM_results' not in entry:
                                continue

                            # Process each LLM model result
                            for llm_result in entry['LLM_results']:
                                llm_type = llm_result.get('LLM_type')

                                # Map LLM_type to our model names
                                if llm_type == 'openAI':
                                    model = 'openAI'
                                elif llm_type == 'claude':
                                    model = 'claude'
                                elif llm_type == 'gemini':
                                    model = 'gemini'
                                else:
                                    continue

                                # Get pass_rate value (boolean -> percentage)
                                passed = llm_result.get('regressionTestPassed', False)
                                llm_pass_rate = 100.0 if passed else 0.0

                                # Base pass rate is always 100%
                                base_pass_rate = 100.0

                                # Calculate improvement percentage
                                improvement_pct = ((llm_pass_rate - base_pass_rate) / base_pass_rate) * 100.0

                                # Store in data structure
                                data[prompt_version][model][norm_language]['pass_rate'].append(improvement_pct)

                except Exception as e:
                    self.logger.warning(f"Error processing {exec_file.name}: {e}")
                    continue

        self.logger.info("Loaded pass_rate data from execution files")

    def generate_all_plots(self):
        """
        Generate all plots for fixed prompt analysis.

        This is the main orchestration method that generates:
        - Plots for v1 only
        - Plots for v4 only
        - Comparative plots v1 vs v4
        - Frequency distributions
        - Appendix plots for v2 and v3
        """
        self.logger.info("="*80)
        self.logger.info("Starting Fixed Prompt Analysis Plot Generation")
        self.logger.info("="*80)

        # Load data
        data = self.load_improvement_data()

        if not data:
            self.logger.error("No data loaded. Aborting.")
            return

        # Generate plots for each prompt version separately
        for prompt_version in ['prompt_v1', 'prompt_v4']:
            self.logger.info(f"\nGenerating plots for {prompt_version}...")
            output_dir = self.v1_dir if prompt_version == 'prompt_v1' else self.v4_dir
            self._generate_single_version_plots(data[prompt_version], prompt_version, output_dir)

        # Generate comparative plots v1 vs v4
        self.logger.info("\nGenerating comparative plots (v1 vs v4)...")
        self._generate_comparative_plots(data['prompt_v1'], data['prompt_v4'])

        # Generate frequency distribution plots
        self.logger.info("\nGenerating frequency distribution plots...")
        self._generate_frequency_distributions(data)

        # Generate box plots by model (prompt fixed)
        self.logger.info("\nGenerating box plots by model...")
        self._generate_model_boxplots(data)

        # Generate box plots by language (aggregated over models)
        self.logger.info("\nGenerating box plots by language...")
        self._generate_language_boxplots(data)

        # Generate appendix plots for v2 and v3
        self.logger.info("\nGenerating appendix plots (v2 and v3)...")
        for prompt_version in ['prompt_v2', 'prompt_v3']:
            if prompt_version in data:
                self._generate_single_version_plots(data[prompt_version], prompt_version, self.appendix_dir)

        self.logger.info("\n" + "="*80)
        self.logger.info("Fixed Prompt Analysis Complete!")
        self.logger.info(f"Output directory: {self.output_base_dir}")
        self.logger.info("="*80)

    def _generate_single_version_plots(self, version_data: Dict, prompt_version: str, output_dir: Path):
        """
        Generate all plots for a single prompt version.

        Creates box plots for each model showing improvements by language.
        """
        version_label = prompt_version.replace('prompt_', '').upper()

        for model in self.models:
            if model not in version_data:
                continue

            for metric in self.metrics:
                # Special handling for pass_rate
                if metric == "pass_rate":
                    self._generate_pass_rate_single(version_data, model, version_label, output_dir)
                    continue

                # Collect data by language for this model+metric
                plot_data = []
                labels = []

                for language in self.languages:
                    if language in version_data[model] and metric in version_data[model][language]:
                        improvements = version_data[model][language][metric]
                        if improvements:
                            plot_data.append(improvements)
                            labels.append(language.upper())

                if not plot_data:
                    continue

                # Create box plot
                fig, ax = plt.subplots(figsize=(12, 7))

                bp = ax.boxplot(plot_data, labels=labels, patch_artist=True,
                               showmeans=True, meanline=True,
                               meanprops=dict(linestyle='--', linewidth=1.5, color='darkred'),
                               flierprops=dict(marker='o', markerfacecolor='gray', markersize=3, alpha=0.3))

                # Color boxes by language
                for patch, label in zip(bp['boxes'], labels):
                    color = self.language_colors.get(label.lower(), '#95a5a6')
                    patch.set_facecolor(color)
                    patch.set_alpha(0.7)

                ax.axhline(y=0, color='black', linestyle='-', linewidth=2, alpha=0.8)
                ax.set_title(f'{model} - {metric.replace("_", " ").title()} Improvements by Language\n'
                           f'(Prompt {version_label})', fontsize=14, fontweight='bold')
                ax.set_xlabel('Programming Language', fontsize=12, fontweight='bold')
                ax.set_ylabel('Improvement %\n(+ = better)', fontsize=12, fontweight='bold')
                ax.grid(True, alpha=0.3)

                plt.tight_layout()
                filename = f"{model}_v{version_label.lower()}_improvements_by_language_{metric}.png"
                plt.savefig(output_dir / filename, dpi=300, bbox_inches='tight')
                plt.close()

                self.logger.info(f"  Saved: {filename}")

    def _generate_pass_rate_single(self, version_data: Dict, model: str, version_label: str, output_dir: Path):
        """
        Generate specialized pass rate bar plot for a single prompt version showing
        mean absolute pass rates from 100% baseline with degradation annotations.
        """
        BASELINE_PASS_RATE = 100.0

        # Collect mean pass rates by language
        labels = []
        mean_values = []
        colors_list = []

        for language in self.languages:
            if language in version_data[model] and 'pass_rate' in version_data[model][language]:
                improvements = version_data[model][language]['pass_rate']
                if improvements:
                    # Convert improvement percentages to absolute pass rates
                    absolute_pass_rates = [BASELINE_PASS_RATE + imp for imp in improvements]
                    mean_pass_rate = np.mean(absolute_pass_rates)

                    labels.append(language.upper())
                    mean_values.append(mean_pass_rate)
                    colors_list.append(self.language_colors.get(language.lower(), '#95a5a6'))

        if not mean_values:
            return

        # Create bar plot
        fig, ax = plt.subplots(figsize=(14, 7))

        x_pos = np.arange(len(labels))
        bars = ax.bar(x_pos, mean_values, width=0.7, alpha=0.8,
                     color=colors_list, edgecolor='black', linewidth=1.5)

        # Add baseline reference line at 100%
        ax.axhline(y=BASELINE_PASS_RATE, color='#2ecc71', linestyle='--',
                  linewidth=2.5, alpha=0.8, label='Base Code (100%)', zorder=1)

        # Calculate spacing for annotations
        max_val = max(mean_values) if mean_values else 100
        value_offset = max_val * 0.01
        degradation_offset = max_val * 0.08

        # Add value labels and degradation annotations
        for i, (bar, mean_val, label) in enumerate(zip(bars, mean_values, labels)):
            height = bar.get_height()

            # Value label above bar
            ax.text(bar.get_x() + bar.get_width()/2., height + value_offset,
                   f'{mean_val:.1f}%',
                   ha='center', va='bottom', fontsize=9, fontweight='bold')

            # Degradation percentage
            degradation_pct = mean_val - BASELINE_PASS_RATE

            if degradation_pct < 0:
                degradation_text = f"{degradation_pct:.1f}%"
                text_color = 'white'
                box_color = '#d32f2f'  # Red for degradation
                edge_color = '#b71c1c'
            else:
                degradation_text = f"+{degradation_pct:.1f}%"
                text_color = 'white'
                box_color = '#388e3c'  # Green for improvement
                edge_color = '#1b5e20'

            ax.text(bar.get_x() + bar.get_width()/2., height + degradation_offset,
                   degradation_text,
                   ha='center', va='bottom', fontsize=10, fontweight='bold',
                   color=text_color,
                   bbox=dict(boxstyle='round,pad=0.4', facecolor=box_color,
                            alpha=0.95, edgecolor=edge_color, linewidth=2))

        ax.set_title(f'{model} - Pass Rate by Language\n'
                   f'(Prompt {version_label} - Baseline: 100%)', fontsize=14, fontweight='bold')
        ax.set_xlabel('Programming Language', fontsize=12, fontweight='bold')
        ax.set_ylabel('Pass Rate %\n(100% = Base Code)', fontsize=12, fontweight='bold')
        ax.set_xticks(x_pos)
        ax.set_xticklabels(labels, fontsize=11)
        ax.set_ylim(bottom=0, top=max_val * 1.20)
        ax.grid(True, alpha=0.3, axis='y')
        ax.legend(fontsize=10, loc='lower right')

        plt.tight_layout()
        filename = f"{model}_v{version_label.lower()}_improvements_by_language_pass_rate.png"
        plt.savefig(output_dir / filename, dpi=300, bbox_inches='tight')
        plt.close()

        self.logger.info(f"  Saved: {filename}")

    def _generate_pass_rate_comparison(self, v1_data: Dict, v4_data: Dict, model: str):
        """
        Generate specialized pass rate comparison bar plots showing mean absolute pass rates
        from 100% baseline with degradation annotations.
        """
        BASELINE_PASS_RATE = 100.0

        fig, axes = plt.subplots(1, 2, figsize=(18, 7), sharey=True)

        all_mean_values = []  # Track all values for consistent y-axis

        for idx, (version_data, version_label, ax) in enumerate([
            (v1_data, 'V1', axes[0]),
            (v4_data, 'V4', axes[1])
        ]):
            labels = []
            mean_values = []
            colors_list = []

            for language in self.languages:
                if (language in version_data[model] and
                    'pass_rate' in version_data[model][language]):
                    improvements = version_data[model][language]['pass_rate']
                    if improvements:
                        # Convert improvement percentages to absolute pass rates
                        absolute_pass_rates = [BASELINE_PASS_RATE + imp for imp in improvements]
                        mean_pass_rate = np.mean(absolute_pass_rates)

                        labels.append(language.upper())
                        mean_values.append(mean_pass_rate)
                        colors_list.append(self.language_colors.get(language.lower(), '#95a5a6'))

            if not mean_values:
                continue

            all_mean_values.extend(mean_values)

            # Create bar plot
            x_pos = np.arange(len(labels))
            bars = ax.bar(x_pos, mean_values, width=0.7, alpha=0.8,
                         color=colors_list, edgecolor='black', linewidth=1.5)

            # Add baseline reference line at 100%
            ax.axhline(y=BASELINE_PASS_RATE, color='#2ecc71', linestyle='--',
                      linewidth=2.5, alpha=0.8, label='Base Code (100%)', zorder=1)

            # Calculate spacing for annotations
            max_val = max(mean_values) if mean_values else 100
            value_offset = max_val * 0.01
            degradation_offset = max_val * 0.08

            # Add value labels and degradation annotations
            for i, (bar, mean_val) in enumerate(zip(bars, mean_values)):
                height = bar.get_height()

                # Value label above bar
                ax.text(bar.get_x() + bar.get_width()/2., height + value_offset,
                       f'{mean_val:.1f}%',
                       ha='center', va='bottom', fontsize=8, fontweight='bold')

                # Degradation percentage
                degradation_pct = mean_val - BASELINE_PASS_RATE

                if degradation_pct < 0:
                    degradation_text = f"{degradation_pct:.1f}%"
                    text_color = 'white'
                    box_color = '#d32f2f'  # Red for degradation
                    edge_color = '#b71c1c'
                else:
                    degradation_text = f"+{degradation_pct:.1f}%"
                    text_color = 'white'
                    box_color = '#388e3c'  # Green for improvement
                    edge_color = '#1b5e20'

                ax.text(bar.get_x() + bar.get_width()/2., height + degradation_offset,
                       degradation_text,
                       ha='center', va='bottom', fontsize=9, fontweight='bold',
                       color=text_color,
                       bbox=dict(boxstyle='round,pad=0.4', facecolor=box_color,
                                alpha=0.95, edgecolor=edge_color, linewidth=2))

            ax.set_title(f'Prompt {version_label}', fontsize=13, fontweight='bold')
            ax.set_xlabel('Programming Language', fontsize=11, fontweight='bold')
            if idx == 0:
                ax.set_ylabel('Pass Rate %\n(100% = Base Code)', fontsize=11, fontweight='bold')
            ax.set_xticks(x_pos)
            ax.set_xticklabels(labels, fontsize=10)
            ax.grid(True, alpha=0.3, axis='y')
            if idx == 1:
                ax.legend(fontsize=10, loc='lower right')

        # Set consistent y-axis limits
        if all_mean_values:
            max_overall = max(all_mean_values)
            for ax in axes:
                ax.set_ylim(bottom=0, top=max_overall * 1.20)

        fig.suptitle(f'{model} - Pass Rate Comparison\n'
                   f'V1 vs V4 (Baseline: 100%)', fontsize=15, fontweight='bold')
        plt.tight_layout()

        filename = f"{model}_v1_vs_v4_pass_rate_comparison.png"
        plt.savefig(self.comparison_dir / filename, dpi=300, bbox_inches='tight')
        plt.close()

        self.logger.info(f"  Saved: {filename}")

    def _generate_comparative_plots(self, v1_data: Dict, v4_data: Dict):
        """
        Generate comparative plots showing v1 vs v4 side by side.
        """
        for model in self.models:
            if model not in v1_data or model not in v4_data:
                continue

            for metric in self.metrics:
                # Special handling for pass_rate - use absolute values from 100% baseline
                if metric == "pass_rate":
                    self._generate_pass_rate_comparison(v1_data, v4_data, model)
                    continue

                fig, axes = plt.subplots(1, 2, figsize=(16, 7), sharey=True)

                for idx, (version_data, version_label, ax) in enumerate([
                    (v1_data, 'V1', axes[0]),
                    (v4_data, 'V4', axes[1])
                ]):
                    plot_data = []
                    labels = []

                    for language in self.languages:
                        if (language in version_data[model] and
                            metric in version_data[model][language]):
                            improvements = version_data[model][language][metric]
                            if improvements:
                                plot_data.append(improvements)
                                labels.append(language.upper())

                    if not plot_data:
                        continue

                    bp = ax.boxplot(plot_data, labels=labels, patch_artist=True,
                                   showmeans=True, meanline=True,
                                   meanprops=dict(linestyle='--', linewidth=1.5, color='darkred'),
                                   flierprops=dict(marker='o', markerfacecolor='gray', markersize=3, alpha=0.3))

                    for patch, label in zip(bp['boxes'], labels):
                        color = self.language_colors.get(label.lower(), '#95a5a6')
                        patch.set_facecolor(color)
                        patch.set_alpha(0.7)

                    ax.axhline(y=0, color='black', linestyle='-', linewidth=2, alpha=0.8)
                    ax.set_title(f'Prompt {version_label}', fontsize=13, fontweight='bold')
                    ax.set_xlabel('Programming Language', fontsize=11, fontweight='bold')
                    if idx == 0:
                        ax.set_ylabel('Improvement %\n(+ = better)', fontsize=11, fontweight='bold')
                    ax.grid(True, alpha=0.3)

                fig.suptitle(f'{model} - {metric.replace("_", " ").title()} Improvements\n'
                           f'Comparison: Prompt V1 vs V4', fontsize=15, fontweight='bold')
                plt.tight_layout()

                filename = f"{model}_v1_vs_v4_{metric}_comparison.png"
                plt.savefig(self.comparison_dir / filename, dpi=300, bbox_inches='tight')
                plt.close()

                self.logger.info(f"  Saved: {filename}")

    def _generate_frequency_distributions(self, data: Dict):
        """Generate frequency distribution histograms for v1 and v4."""
        for prompt_version in ['prompt_v1', 'prompt_v4']:
            version_label = prompt_version.replace('prompt_', '').upper()

            if prompt_version not in data:
                continue

            for metric in self.metrics:
                # Collect all improvements for this metric (across all models and languages)
                all_improvements = []

                for model in self.models:
                    if model not in data[prompt_version]:
                        continue
                    for language in self.languages:
                        if (language in data[prompt_version][model] and
                            metric in data[prompt_version][model][language]):
                            all_improvements.extend(data[prompt_version][model][language][metric])

                if not all_improvements:
                    continue

                # Create histogram with KDE
                fig, ax = plt.subplots(figsize=(12, 7))

                ax.hist(all_improvements, bins=50, alpha=0.6, color='skyblue', edgecolor='black', density=False)
                ax.axvline(x=0, color='red', linestyle='--', linewidth=2, label='No change')
                ax.axvline(x=np.median(all_improvements), color='green', linestyle='-', linewidth=2,
                          label=f'Median: {np.median(all_improvements):.2f}%')
                ax.axvline(x=np.mean(all_improvements), color='orange', linestyle='-', linewidth=2,
                          label=f'Mean: {np.mean(all_improvements):.2f}%')

                ax.set_title(f'{metric.replace("_", " ").title()} Improvement Frequency Distribution\n'
                           f'(Prompt {version_label} - All models and languages)', fontsize=14, fontweight='bold')
                ax.set_xlabel('Improvement % (+ = better)', fontsize=12, fontweight='bold')
                ax.set_ylabel('Frequency (Number of entries)', fontsize=12, fontweight='bold')
                ax.legend(fontsize=11)
                ax.grid(True, alpha=0.3)

                plt.tight_layout()

                output_dir = self.v1_dir if prompt_version == 'prompt_v1' else self.v4_dir
                filename = f"improvement_frequency_distribution_{version_label.lower()}_{metric}.png"
                plt.savefig(output_dir / filename, dpi=300, bbox_inches='tight')
                plt.close()

                self.logger.info(f"  Saved: {filename}")

    def _generate_model_boxplots(self, data: Dict):
        """Generate box plots comparing models for fixed prompt versions."""
        for prompt_version in ['prompt_v1', 'prompt_v4']:
            version_label = prompt_version.replace('prompt_', '').upper()

            if prompt_version not in data:
                continue

            for metric in self.metrics:
                plot_data = []
                labels = []
                colors = []

                for model in self.models:
                    if model not in data[prompt_version]:
                        continue

                    # Aggregate across all languages
                    model_improvements = []
                    for language in self.languages:
                        if (language in data[prompt_version][model] and
                            metric in data[prompt_version][model][language]):
                            model_improvements.extend(data[prompt_version][model][language][metric])

                    if model_improvements:
                        plot_data.append(model_improvements)
                        labels.append(model)
                        colors.append(self.model_colors[model])

                if not plot_data:
                    continue

                fig, ax = plt.subplots(figsize=(10, 7))

                bp = ax.boxplot(plot_data, labels=labels, patch_artist=True,
                               showmeans=True, meanline=True,
                               meanprops=dict(linestyle='--', linewidth=1.5, color='darkred'),
                               flierprops=dict(marker='o', markerfacecolor='gray', markersize=3, alpha=0.3))

                for patch, color in zip(bp['boxes'], colors):
                    patch.set_facecolor(color)
                    patch.set_alpha(0.7)

                ax.axhline(y=0, color='black', linestyle='-', linewidth=2, alpha=0.8)
                ax.set_title(f'{metric.replace("_", " ").title()} Improvements by Model\n'
                           f'(Prompt {version_label} - Aggregated across all languages)',
                           fontsize=14, fontweight='bold')
                ax.set_xlabel('LLM Model', fontsize=12, fontweight='bold')
                ax.set_ylabel('Improvement %\n(+ = better)', fontsize=12, fontweight='bold')
                ax.grid(True, alpha=0.3)

                plt.tight_layout()

                output_dir = self.v1_dir if prompt_version == 'prompt_v1' else self.v4_dir
                filename = f"improvements_by_model_{version_label.lower()}_{metric}.png"
                plt.savefig(output_dir / filename, dpi=300, bbox_inches='tight')
                plt.close()

                self.logger.info(f"  Saved: {filename}")

    def _generate_language_boxplots(self, data: Dict):
        """Generate box plots comparing languages (aggregated over models) for fixed prompt versions."""
        for prompt_version in ['prompt_v1', 'prompt_v4']:
            version_label = prompt_version.replace('prompt_', '').upper()

            if prompt_version not in data:
                continue

            for metric in self.metrics:
                plot_data = []
                labels = []
                colors = []

                for language in self.languages:
                    # Aggregate across all models
                    lang_improvements = []
                    for model in self.models:
                        if model not in data[prompt_version]:
                            continue
                        if (language in data[prompt_version][model] and
                            metric in data[prompt_version][model][language]):
                            lang_improvements.extend(data[prompt_version][model][language][metric])

                    if lang_improvements:
                        plot_data.append(lang_improvements)
                        labels.append(language.upper())
                        colors.append(self.language_colors.get(language, '#95a5a6'))

                if not plot_data:
                    continue

                fig, ax = plt.subplots(figsize=(12, 7))

                bp = ax.boxplot(plot_data, labels=labels, patch_artist=True,
                               showmeans=True, meanline=True,
                               meanprops=dict(linestyle='--', linewidth=1.5, color='darkred'),
                               flierprops=dict(marker='o', markerfacecolor='gray', markersize=3, alpha=0.3))

                for patch, color in zip(bp['boxes'], colors):
                    patch.set_facecolor(color)
                    patch.set_alpha(0.7)

                ax.axhline(y=0, color='black', linestyle='-', linewidth=2, alpha=0.8)
                ax.set_title(f'{metric.replace("_", " ").title()} Improvements by Language\n'
                           f'(Prompt {version_label} - Aggregated across all models)',
                           fontsize=14, fontweight='bold')
                ax.set_xlabel('Programming Language', fontsize=12, fontweight='bold')
                ax.set_ylabel('Improvement %\n(+ = better)', fontsize=12, fontweight='bold')
                ax.grid(True, alpha=0.3)

                plt.tight_layout()

                output_dir = self.v1_dir if prompt_version == 'prompt_v1' else self.v4_dir
                filename = f"improvements_by_language_{version_label.lower()}_{metric}.png"
                plt.savefig(output_dir / filename, dpi=300, bbox_inches='tight')
                plt.close()

                self.logger.info(f"  Saved: {filename}")


def main():
    """Main entry point."""
    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s - %(name)s - %(levelname)s - %(message)s"
    )

    logger = logging.getLogger(__name__)
    logger.info("Starting Fixed Prompt Analysis")

    try:
        analyzer = FixedPromptAnalyzer()
        analyzer.generate_all_plots()
        logger.info("Analysis completed successfully!")
        return 0
    except Exception as e:
        logger.error(f"Analysis failed: {e}", exc_info=True)
        return 1


if __name__ == "__main__":
    import sys
    sys.exit(main())
