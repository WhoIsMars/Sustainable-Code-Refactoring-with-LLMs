#important!
#create plots in ./execution_stats_plots

import sys
import os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
from utility_dir import utility_paths
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
from pathlib import Path
from typing import Dict, List
import logging

# Set style
sns.set_style("whitegrid")
sns.set_palette("husl")


class ExecMetricStatsVisualizator:
    """Visualizza le statistiche aggregate su tutto il dataset usando box plots, bar plots e scatter plots"""

    def __init__(self, output_dir: Path = None):
        self.logger = logging.getLogger(__name__)

        if output_dir is None:
            self.output_dir = utility_paths.METRICS_DIR_FILEPATH / "execution_stats_plots"
        else:
            self.output_dir = output_dir

        self.output_dir.mkdir(parents=True, exist_ok=True)

        self.metrics = ["CPU_usage", "RAM_usage", "execution_time_ms", "pass_rate", "energy_joules"]
        self.metric_labels = {
            "CPU_usage": "CPU Usage (%)",
            "RAM_usage": "RAM Usage (KB)",
            "execution_time_ms": "Execution Time (ms)",
            "pass_rate": "Pass Rate (%)",
            "energy_joules": "Energy Consumption (J)"
        }

        # Color schemes
        self.model_colors = {
            "base": "#2ecc71",
            "openai": "#3498db",
            "claude": "#9b59b6",
            "gemini": "#e74c3c"
        }

        # Blues gradient for prompt versions (v1=light, v4=dark)
        self.prompt_colors = {
            'v1': '#deebf7',  # Light blue
            'v2': '#9ecae1',  # Medium-light blue
            'v3': '#3182bd',  # Medium-dark blue
            'v4': '#08519c'   # Dark blue
        }

    def _remove_outliers_for_ylim(self, data: List, percentile: float = 95, force_include_zero: bool = True) -> tuple:
        """
        Calculate reasonable ylim by removing extreme outliers

        Args:
            data: List of data points or list of lists
            percentile: Upper percentile to use for max limit
            force_include_zero: If True, ensures 0 is always in the visible range

        Returns:
            Tuple of (min, max) for ylim
        """
        if not data:
            return (0, 1)

        flat_data = []
        for d in data:
            if isinstance(d, list):
                flat_data.extend(d)
            else:
                flat_data.append(d)

        if not flat_data:
            return (0, 1)

        q_low = np.percentile(flat_data, 1)
        q_high = np.percentile(flat_data, percentile)

        # Force include zero if requested (important for improvement plots)
        if force_include_zero:
            q_low = min(q_low, 0)
            q_high = max(q_high, 0)

        # Add some padding
        padding = (q_high - q_low) * 0.1
        return (q_low - padding, q_high + padding)

    def visualize_objective_1(self, data: Dict):
        """
        Obiettivo 1: Box plot per metrica in correlazione alla versione del prompt.
        Un grafico per ogni metrica, aggregato su tutto il dataset.
        """
        self.logger.info("Visualizing Objective 1: Metrics by Prompt Version")

        output_subdir = self.output_dir / "metrics_means_related_to_prompt_versions"
        output_subdir.mkdir(parents=True, exist_ok=True)

        base_data = data.get("base", {})
        prompt_versions_data = data.get("prompt_versions", {})

        # Create one plot per metric
        for metric in self.metrics:
            fig, ax = plt.subplots(figsize=(14, 7))

            plot_data = []
            labels = []
            colors = []

            # Add base code data
            if metric in base_data and base_data[metric]:
                plot_data.append(base_data[metric])
                labels.append("Base Code")
                colors.append(self.model_colors["base"])

            # Add prompt version data
            for version in sorted(prompt_versions_data.keys()):
                version_metrics = prompt_versions_data[version]
                if metric in version_metrics and version_metrics[metric]:
                    plot_data.append(version_metrics[metric])
                    labels.append(f"Prompt {version.upper()}")
                    # Use Blues gradient palette for prompt versions
                    colors.append(self.prompt_colors.get(version, "#3498db"))

            if not plot_data:
                self.logger.warning(f"No data for {metric} in Objective 1")
                plt.close(fig)
                continue

            # Set reasonable ylim to handle outliers
            if metric != "pass_rate":
                ylim = self._remove_outliers_for_ylim(plot_data, percentile=97)
                ax.set_ylim(ylim)

            # Create box plot
            bp = ax.boxplot(plot_data, labels=labels, patch_artist=True,
                           showmeans=True, meanline=True,
                           meanprops=dict(linestyle='--', linewidth=2, color='red'),
                           showfliers=True, flierprops=dict(marker='o', markerfacecolor='gray', markersize=4, alpha=0.3))

            # Color boxes
            for patch, color in zip(bp['boxes'], colors):
                patch.set_facecolor(color)
                patch.set_alpha(0.7)

            ax.set_ylabel(self.metric_labels[metric], fontsize=13, fontweight='bold')
            ax.set_xlabel('Prompt Version', fontsize=13, fontweight='bold')
            ax.set_title(f'{self.metric_labels[metric]} by Prompt Version\n(Aggregated across all clusters - Base code with 100% pass rate only)',
                       fontsize=14, fontweight='bold', pad=20)
            ax.grid(True, alpha=0.3, axis='y')

            # Add legend with Blues gradient
            from matplotlib.patches import Patch
            legend_elements = [
                Patch(facecolor=self.model_colors["base"], alpha=0.7, label='Base Code (100% pass rate)'),
                Patch(facecolor=self.prompt_colors['v1'], alpha=0.7, label='Prompt v1 (lightest)'),
                Patch(facecolor=self.prompt_colors['v2'], alpha=0.7, label='Prompt v2'),
                Patch(facecolor=self.prompt_colors['v3'], alpha=0.7, label='Prompt v3'),
                Patch(facecolor=self.prompt_colors['v4'], alpha=0.7, label='Prompt v4 (darkest)'),
                plt.Line2D([0], [0], color='red', linestyle='--', linewidth=2, label='Mean')
            ]
            ax.legend(handles=legend_elements, loc='upper right', fontsize=9, ncol=2)

            plt.xticks(rotation=45, ha='right')
            plt.tight_layout()

            # Save
            filename = f"prompt_versions_{metric}_boxplot.png"
            filepath = output_subdir / filename
            plt.savefig(filepath, dpi=300, bbox_inches='tight')
            plt.close(fig)

            self.logger.info(f"Saved: {filename}")

            # NUOVO: Bar plot con medie
            self._create_bar_plot_objective_1(plot_data, labels, metric, output_subdir)

    def _create_bar_plot_objective_1(self, plot_data: List, labels: List[str], metric: str, output_dir: Path):
        """Crea bar plot con medie per Obiettivo 1"""
        fig, ax = plt.subplots(figsize=(14, 7))

        means = [np.mean(d) for d in plot_data]
        stds = [np.std(d) for d in plot_data]
        colors_list = [self.model_colors["base"]] + ["#3498db"] * (len(labels) - 1)

        x_pos = np.arange(len(labels))
        bars = ax.bar(x_pos, means, yerr=stds, capsize=5, alpha=0.7, color=colors_list, edgecolor='black')

        ax.set_ylabel(self.metric_labels[metric], fontsize=13, fontweight='bold')
        ax.set_xlabel('Prompt Version', fontsize=13, fontweight='bold')
        ax.set_title(f'{self.metric_labels[metric]} - Mean Comparison\n(Base code with 100% pass rate only)',
                   fontsize=14, fontweight='bold', pad=20)
        ax.set_xticks(x_pos)
        ax.set_xticklabels(labels, rotation=45, ha='right')
        ax.grid(True, alpha=0.3, axis='y')

        # Add value labels on bars
        for i, (bar, mean, std) in enumerate(zip(bars, means, stds)):
            height = bar.get_height()
            ax.text(bar.get_x() + bar.get_width()/2., height + std,
                   f'{mean:.1f}',
                   ha='center', va='bottom', fontsize=9, fontweight='bold')

        # Legend
        from matplotlib.patches import Patch
        legend_elements = [
            Patch(facecolor=self.model_colors["base"], alpha=0.7, label='Base Code'),
            Patch(facecolor="#3498db", alpha=0.7, label='LLM Generated Code'),
        ]
        ax.legend(handles=legend_elements, loc='upper right', fontsize=10)

        plt.tight_layout()
        filename = f"prompt_versions_{metric}_barplot.png"
        plt.savefig(output_dir / filename, dpi=300, bbox_inches='tight')
        plt.close(fig)

    def visualize_objective_2(self, data: Dict):
        """
        Obiettivo 2: Box plot per metrica in correlazione ai linguaggi.
        Due set di grafici: uno per base code, uno per LLM code.
        Un grafico per ogni metrica.
        """
        self.logger.info("Visualizing Objective 2: Metrics by Language")

        output_subdir = self.output_dir / "metrics_means_related_to_languages"
        output_subdir.mkdir(parents=True, exist_ok=True)

        base_by_language = data.get("base_by_language", {})
        llm_by_language = data.get("llm_by_language", {})

        # BASE CODE PLOTS
        for metric in self.metrics:
            fig, ax = plt.subplots(figsize=(14, 7))

            plot_data = []
            labels = []

            for language in sorted(base_by_language.keys()):
                lang_metrics = base_by_language[language]
                if metric in lang_metrics and lang_metrics[metric]:
                    plot_data.append(lang_metrics[metric])
                    labels.append(language.upper())

            if not plot_data:
                self.logger.warning(f"No base data for {metric} in Objective 2")
                plt.close(fig)
                continue

            # Set reasonable ylim
            if metric != "pass_rate":
                ylim = self._remove_outliers_for_ylim(plot_data, percentile=97)
                ax.set_ylim(ylim)

            # Create box plot
            bp = ax.boxplot(plot_data, labels=labels, patch_artist=True,
                           showmeans=True, meanline=True,
                           meanprops=dict(linestyle='--', linewidth=2, color='red'),
                           showfliers=True, flierprops=dict(marker='o', markerfacecolor='gray', markersize=4, alpha=0.3))

            # Color boxes
            for patch in bp['boxes']:
                patch.set_facecolor(self.model_colors["base"])
                patch.set_alpha(0.7)

            ax.set_ylabel(self.metric_labels[metric], fontsize=13, fontweight='bold')
            ax.set_xlabel('Programming Language', fontsize=13, fontweight='bold')
            ax.set_title(f'{self.metric_labels[metric]} by Language - Base Code\n(Only entries with 100% pass rate)',
                       fontsize=14, fontweight='bold', pad=20)
            ax.grid(True, alpha=0.3, axis='y')

            # Legend
            from matplotlib.patches import Patch
            legend_elements = [
                Patch(facecolor=self.model_colors["base"], alpha=0.7, label='Base Code (100% pass rate)'),
                plt.Line2D([0], [0], color='red', linestyle='--', linewidth=2, label='Mean')
            ]
            ax.legend(handles=legend_elements, loc='upper right', fontsize=10)

            plt.xticks(rotation=45, ha='right')
            plt.tight_layout()

            # Save
            filename = f"languages_base_{metric}_boxplot.png"
            filepath = output_subdir / filename
            plt.savefig(filepath, dpi=300, bbox_inches='tight')
            plt.close(fig)

            self.logger.info(f"Saved: {filename}")

        # LLM CODE PLOTS
        for metric in self.metrics:
            fig, ax = plt.subplots(figsize=(14, 7))

            plot_data = []
            labels = []

            for language in sorted(llm_by_language.keys()):
                lang_metrics = llm_by_language[language]
                if metric in lang_metrics and lang_metrics[metric]:
                    plot_data.append(lang_metrics[metric])
                    labels.append(language.upper())

            if not plot_data:
                self.logger.warning(f"No LLM data for {metric} in Objective 2")
                plt.close(fig)
                continue

            # Set reasonable ylim
            if metric != "pass_rate":
                ylim = self._remove_outliers_for_ylim(plot_data, percentile=97)
                ax.set_ylim(ylim)

            # Create box plot
            bp = ax.boxplot(plot_data, labels=labels, patch_artist=True,
                           showmeans=True, meanline=True,
                           meanprops=dict(linestyle='--', linewidth=2, color='red'),
                           showfliers=True, flierprops=dict(marker='o', markerfacecolor='gray', markersize=4, alpha=0.3))

            # Color boxes
            for patch in bp['boxes']:
                patch.set_facecolor("#e74c3c")
                patch.set_alpha(0.7)

            ax.set_ylabel(self.metric_labels[metric], fontsize=13, fontweight='bold')
            ax.set_xlabel('Programming Language', fontsize=13, fontweight='bold')
            ax.set_title(f'{self.metric_labels[metric]} by Language - LLM Code\n(All LLM generated code)',
                       fontsize=14, fontweight='bold', pad=20)
            ax.grid(True, alpha=0.3, axis='y')

            # Legend
            from matplotlib.patches import Patch
            legend_elements = [
                Patch(facecolor="#e74c3c", alpha=0.7, label='LLM Generated Code'),
                plt.Line2D([0], [0], color='red', linestyle='--', linewidth=2, label='Mean')
            ]
            ax.legend(handles=legend_elements, loc='upper right', fontsize=10)

            plt.xticks(rotation=45, ha='right')
            plt.tight_layout()

            # Save
            filename = f"languages_llm_{metric}_boxplot.png"
            filepath = output_subdir / filename
            plt.savefig(filepath, dpi=300, bbox_inches='tight')
            plt.close(fig)

            self.logger.info(f"Saved: {filename}")

        # NUOVO: Scatter plot comparativo Base vs LLM per linguaggio
        self._create_scatter_comparison_languages(base_by_language, llm_by_language, output_subdir)

    def _create_scatter_comparison_languages(self, base_by_language: Dict, llm_by_language: Dict, output_dir: Path):
        """Crea violin/strip plots per confronto Base vs LLM per linguaggio con distribuzione dati"""
        for metric in self.metrics:
            fig, ax = plt.subplots(figsize=(16, 8))

            colors_map = {
                'c': '#e74c3c', 'cpp': '#3498db', 'go': '#2ecc71',
                'java': '#f39c12', 'python': '#9b59b6',
                'javascript': '#1abc9c', 'typescript': '#e67e22'
            }

            # Prepare data for grouped comparison
            plot_data = []
            labels = []
            colors_list = []
            positions = []
            current_pos = 0

            languages_sorted = sorted(base_by_language.keys())

            for i, language in enumerate(languages_sorted):
                if language in llm_by_language:
                    base_vals = base_by_language[language].get(metric, [])
                    llm_vals = llm_by_language[language].get(metric, [])

                    if base_vals and llm_vals:
                        # Add base data
                        plot_data.append(base_vals)
                        labels.append(f"{language.upper()}\nBase")
                        colors_list.append(self.model_colors["base"])
                        positions.append(current_pos)
                        current_pos += 1

                        # Add LLM data
                        plot_data.append(llm_vals)
                        labels.append(f"{language.upper()}\nLLM")
                        colors_list.append(colors_map.get(language.lower(), 'gray'))
                        positions.append(current_pos)
                        current_pos += 1.5  # Gap between language groups

            if not plot_data:
                plt.close(fig)
                return

            # Set reasonable ylim
            if metric != "pass_rate":
                ylim = self._remove_outliers_for_ylim(plot_data, percentile=97)
                ax.set_ylim(ylim)

            # Create violin plot with individual data points
            parts = ax.violinplot(plot_data, positions=positions, widths=0.7,
                                 showmeans=True, showmedians=True, showextrema=True)

            # Color violin plots
            for i, pc in enumerate(parts['bodies']):
                pc.set_facecolor(colors_list[i])
                pc.set_alpha(0.6)
                pc.set_edgecolor('black')
                pc.set_linewidth(1.2)

            # Style the violin plot elements
            for partname in ('cbars', 'cmins', 'cmaxes', 'cmedians', 'cmeans'):
                if partname in parts:
                    vp = parts[partname]
                    vp.set_edgecolor('black')
                    vp.set_linewidth(1.5)

            # Add individual data points as scatter
            for i, (data, pos) in enumerate(zip(plot_data, positions)):
                # Sample down if too many points
                if len(data) > 100:
                    sample_indices = np.random.choice(len(data), 100, replace=False)
                    sample_data = [data[j] for j in sample_indices]
                else:
                    sample_data = data

                # Add jitter to x-position
                x_jitter = np.random.normal(pos, 0.04, size=len(sample_data))
                ax.scatter(x_jitter, sample_data, alpha=0.3, s=10, color='black', zorder=3)

                # Add mean line marker
                mean_val = np.mean(data)
                ax.plot([pos - 0.3, pos + 0.3], [mean_val, mean_val],
                       color='red', linewidth=3, alpha=0.8, zorder=4)

            ax.set_xticks(positions)
            ax.set_xticklabels(labels, rotation=45, ha='right', fontsize=9)
            ax.set_ylabel(f'{self.metric_labels[metric]}', fontsize=13, fontweight='bold')
            ax.set_xlabel('Programming Language (Base vs LLM)', fontsize=13, fontweight='bold')

            title_text = f'{self.metric_labels[metric]} Distribution: Base vs LLM by Language\n'
            title_text += '(Violin shows distribution, red line = mean, dots = individual data points)'
            ax.set_title(title_text, fontsize=14, fontweight='bold', pad=20)

            ax.grid(True, alpha=0.3, axis='y')

            # Legend
            from matplotlib.patches import Patch
            legend_elements = [
                Patch(facecolor=self.model_colors["base"], alpha=0.6, edgecolor='black', label='Base Code'),
                Patch(facecolor='gray', alpha=0.6, edgecolor='black', label='LLM Code'),
                plt.Line2D([0], [0], color='red', linewidth=3, label='Mean'),
                plt.Line2D([0], [0], marker='o', color='w', markerfacecolor='black', markersize=5, alpha=0.3, label='Data points')
            ]
            ax.legend(handles=legend_elements, loc='upper right', fontsize=10)

            plt.tight_layout()
            filename = f"languages_distribution_{metric}_violin.png"
            plt.savefig(output_dir / filename, dpi=300, bbox_inches='tight')
            plt.close(fig)
            self.logger.info(f"Created distribution violin plot: {filename}")

    def visualize_objective_3(self, data: Dict):
        """
        Obiettivo 3: Box plot per metrica in correlazione a modelli + versione prompt.
        Include improvement percentages.
        Un grafico per ogni metrica.
        """
        self.logger.info("Visualizing Objective 3: Metrics by Model + Prompt Version")

        output_subdir = self.output_dir / "metrics_means_related_to_both_model_and_prompt_version"
        output_subdir.mkdir(parents=True, exist_ok=True)

        base_data = data.get("base", {})
        model_version_stats = data.get("model_version_stats", {})
        mean_improvements = data.get("mean_improvements", {})

        for metric in self.metrics:
            fig, ax = plt.subplots(figsize=(22, 8))

            plot_data = []
            labels = []
            colors = []
            improvements = []

            # Add base code
            if metric in base_data and base_data[metric]:
                plot_data.append(base_data[metric])
                labels.append("Base\nCode")
                colors.append(self.model_colors["base"])
                improvements.append(None)

            # Sort combinations by model then version
            sorted_combos = sorted(model_version_stats.keys(),
                                  key=lambda x: (x.split('_')[0], x.split('_')[1] if len(x.split('_')) > 1 else ""))

            for combo_key in sorted_combos:
                combo_metrics = model_version_stats[combo_key]
                if metric in combo_metrics and combo_metrics[metric]:
                    plot_data.append(combo_metrics[metric])

                    # Format label
                    parts = combo_key.split('_')
                    model = parts[0].capitalize()
                    version = parts[1].upper() if len(parts) > 1 else ""
                    labels.append(f"{model}\n{version}")

                    # Set color by model
                    model_lower = parts[0].lower()
                    if model_lower in self.model_colors:
                        colors.append(self.model_colors[model_lower])
                    else:
                        colors.append("#95a5a6")

                    # Get improvement
                    if combo_key in mean_improvements and metric in mean_improvements[combo_key]:
                        improvements.append(mean_improvements[combo_key][metric])
                    else:
                        improvements.append(None)

            if not plot_data:
                self.logger.warning(f"No data for {metric} in Objective 3")
                plt.close(fig)
                continue

            # Set reasonable ylim
            if metric != "pass_rate":
                ylim = self._remove_outliers_for_ylim(plot_data, percentile=97)
                ax.set_ylim(ylim)

            # Create box plot
            bp = ax.boxplot(plot_data, labels=labels, patch_artist=True,
                           showmeans=True, meanline=True,
                           meanprops=dict(linestyle='--', linewidth=2, color='red'),
                           showfliers=True, flierprops=dict(marker='o', markerfacecolor='gray', markersize=3, alpha=0.2))

            # Color boxes
            for patch, color in zip(bp['boxes'], colors):
                patch.set_facecolor(color)
                patch.set_alpha(0.7)

            # Add improvement percentages as text
            for i, (label, improvement) in enumerate(zip(labels, improvements), 1):
                if improvement is not None:
                    # NEW SEMANTIC: Positive = improvement for ALL metrics (formula inverted in calculator)
                    is_good = improvement >= 0

                    text_color = 'green' if is_good else 'red'
                    # Always show the sign for clarity
                    sign = '+' if improvement >= 0 else ''

                    # Position text above box
                    y_max = np.percentile(plot_data[i-1], 75) if plot_data[i-1] else 0
                    ax.text(i, y_max * 1.01, f'{sign}{improvement:.1f}%',
                           ha='center', va='bottom', fontsize=8,
                           color=text_color, fontweight='bold',
                           bbox=dict(boxstyle='round,pad=0.3', facecolor='white', alpha=0.8, edgecolor=text_color))

            ax.set_ylabel(self.metric_labels[metric], fontsize=13, fontweight='bold')
            ax.set_xlabel('Model + Prompt Version', fontsize=13, fontweight='bold')
            ax.set_title(f'{self.metric_labels[metric]} by Model and Prompt Version\n(+ = improvement, - = degradation. Base code: 100% pass rate only)',
                       fontsize=14, fontweight='bold', pad=20)
            ax.grid(True, alpha=0.3, axis='y')

            # Legend
            from matplotlib.patches import Patch
            legend_elements = [
                Patch(facecolor=self.model_colors["base"], alpha=0.7, label='Base Code'),
                Patch(facecolor=self.model_colors["openai"], alpha=0.7, label='OpenAI'),
                Patch(facecolor=self.model_colors["claude"], alpha=0.7, label='Claude'),
                Patch(facecolor=self.model_colors["gemini"], alpha=0.7, label='Gemini'),
                plt.Line2D([0], [0], color='red', linestyle='--', linewidth=2, label='Mean')
            ]
            ax.legend(handles=legend_elements, loc='upper right', fontsize=9, ncol=2)

            plt.xticks(rotation=45, ha='right', fontsize=10)
            plt.tight_layout()

            # Save
            filename = f"model_prompt_version_{metric}_boxplot.png"
            filepath = output_subdir / filename
            plt.savefig(filepath, dpi=300, bbox_inches='tight')
            plt.close(fig)

            self.logger.info(f"Saved: {filename}")

        # NUOVO: Bar plot con mean comparisons e improvements
        self._create_improvements_barplot(base_data, model_version_stats, mean_improvements, output_subdir)

    def _create_improvements_barplot(self, base_data: Dict, combinations_data: Dict, mean_improvements: Dict, output_dir: Path):
        """Crea bar plot con medie assolute (base + LLM combinations) e annotazioni improvements"""
        for metric in self.metrics:
            fig, ax = plt.subplots(figsize=(20, 8))

            # Calcola media base
            base_mean = None
            if metric in base_data and base_data[metric]:
                base_mean = np.mean(base_data[metric])

            if base_mean is None:
                self.logger.warning(f"No base data for metric {metric}, skipping improvement barplot")
                plt.close(fig)
                continue

            # Prepara dati
            sorted_combos = sorted(combinations_data.keys(),
                                  key=lambda x: (x.split('_')[0], x.split('_')[1] if len(x.split('_')) > 1 else ""))

            labels = ["Base Code"]
            values = [base_mean]
            colors_list = ['#2ecc71']  # Green for base
            improvements_text = [None]  # No improvement for base

            for combo_key in sorted_combos:
                if metric in combinations_data[combo_key] and combinations_data[combo_key][metric]:
                    llm_mean = np.mean(combinations_data[combo_key][metric])
                    improvement = mean_improvements.get(combo_key, {}).get(metric)

                    parts = combo_key.split('_')
                    model = parts[0].capitalize()
                    version = parts[1].upper() if len(parts) > 1 else ""
                    labels.append(f"{model}\n{version}")
                    values.append(llm_mean)
                    improvements_text.append(improvement)

                    # ENHANCED FOR FIG 4.3: Color with gradient based on prompt version
                    # For pass_rate, use gradient colors showing prompt version progression
                    if metric == "pass_rate":
                        # Extract version number (v1, v2, v3, v4)
                        version_key = parts[1] if len(parts) > 1 else "v1"

                        # Model-specific gradient palettes
                        model_gradients = {
                            'openai': {
                                'v1': '#e3f2fd',  # Very light blue
                                'v2': '#90caf9',  # Light blue
                                'v3': '#42a5f5',  # Medium blue
                                'v4': '#1976d2'   # Dark blue
                            },
                            'gemini': {
                                'v1': '#ffebee',  # Very light red
                                'v2': '#ef9a9a',  # Light red
                                'v3': '#ef5350',  # Medium red
                                'v4': '#c62828'   # Dark red
                            },
                            'claude': {
                                'v1': '#f3e5f5',  # Very light purple
                                'v2': '#ba68c8',  # Light purple
                                'v3': '#9c27b0',  # Medium purple
                                'v4': '#6a1b9a'   # Dark purple
                            }
                        }

                        model_key = parts[0].lower()
                        if model_key in model_gradients and version_key in model_gradients[model_key]:
                            colors_list.append(model_gradients[model_key][version_key])
                        else:
                            colors_list.append('#95a5a6')
                    else:
                        # Original color logic for other metrics
                        # Color based on improvement
                        # NEW SEMANTIC: Positive = improvement for ALL metrics (formula inverted in calculator)
                        if improvement is not None:
                            is_good = improvement >= 0

                            # Use model colors but adjust alpha based on good/bad
                            if 'openai' in combo_key:
                                base_color = '#3498db'
                            elif 'claude' in combo_key:
                                base_color = '#9b59b6'
                            elif 'gemini' in combo_key:
                                base_color = '#e74c3c'
                            else:
                                base_color = '#95a5a6'

                            colors_list.append(base_color)
                        else:
                            colors_list.append('#95a5a6')

            if len(values) <= 1:
                plt.close(fig)
                return

            x_pos = np.arange(len(labels))
            # ENHANCED FOR FIG 4.3: Increase bar width for pass_rate for better readability
            bar_width = 0.85 if metric == "pass_rate" else 0.8
            bars = ax.bar(x_pos, values, width=bar_width, alpha=0.8, color=colors_list, edgecolor='black', linewidth=1.5)

            # Reference line at base mean
            ax.axhline(y=base_mean, color='#2ecc71', linestyle='--', linewidth=2, alpha=0.7, label=f'Base Mean: {base_mean:.2f}')

            ax.set_ylabel(f'{self.metric_labels[metric]}', fontsize=14, fontweight='bold')
            ax.set_xlabel('Base Code + Model + Prompt Version', fontsize=14, fontweight='bold')

            if metric == "pass_rate":
                title_text = f'{self.metric_labels[metric]} - Mean Comparison\n(+ = improvement for all metrics, - = degradation)'
            else:
                title_text = f'{self.metric_labels[metric]} - Mean Comparison\n(+ = improvement for all metrics, - = degradation)'

            ax.set_title(title_text, fontsize=15, fontweight='bold', pad=20)

            ax.set_xticks(x_pos)
            ax.set_xticklabels(labels, rotation=45, ha='right', fontsize=10)
            ax.grid(True, alpha=0.3, axis='y')

            # Calculate dynamic spacing for text annotations
            _y_range = max(values) - min(values) if values else 1
            max_val = max(values) if values else 1

            # ENHANCED FOR PASS_RATE: Larger annotations for better visibility
            if metric == "pass_rate":
                value_offset = max_val * 0.005  # 0.5% for value text
                improvement_offset = max_val * 0.08  # 8% for improvement text (INCREASED)
                value_fontsize = 8  # Slightly larger
                improvement_fontsize = 9  # MUCH larger for degradation visibility
                improvement_padding = 0.25  # More padding
                improvement_linewidth = 2.0  # Thicker border
            else:
                value_offset = max_val * 0.01
                improvement_offset = max_val * 0.06
                value_fontsize = 7
                improvement_fontsize = 6.5
                improvement_padding = 0.15
                improvement_linewidth = 1.2

            # Adjust plot limits to accommodate text
            current_ylim = ax.get_ylim()
            headroom = 1.20 if metric == "pass_rate" else 1.15  # More space for pass_rate
            ax.set_ylim(current_ylim[0], max_val * headroom)

            # Add value labels and improvement percentages
            for i, (bar, val, improvement) in enumerate(zip(bars, values, improvements_text)):
                height = bar.get_height()

                # Value label - positioned just above the bar
                ax.text(bar.get_x() + bar.get_width()/2., height + value_offset,
                       f'{val:.1f}',
                       ha='center', va='bottom',
                       fontsize=value_fontsize, fontweight='bold')

                # Improvement percentage (only for LLM combinations)
                if improvement is not None:
                    # NEW SEMANTIC: Positive = improvement for ALL metrics (formula inverted in calculator)
                    is_good = improvement >= 0

                    color = 'green' if is_good else 'red'
                    sign = '+' if improvement >= 0 else ''

                    # ENHANCED FOR PASS_RATE: Much more visible degradation annotations
                    # Place improvement text above the value label with more spacing
                    ax.text(bar.get_x() + bar.get_width()/2., height + improvement_offset,
                           f'{sign}{improvement:.1f}%',
                           ha='center', va='bottom',
                           fontsize=improvement_fontsize, fontweight='bold', color=color,
                           bbox=dict(boxstyle='round,pad=' + str(improvement_padding),
                                   facecolor='white', edgecolor=color, alpha=0.95,
                                   linewidth=improvement_linewidth))

            # ENHANCED FOR FIG 4.3: Add legend with gradient explanation for pass_rate
            if metric == "pass_rate":
                from matplotlib.patches import Patch
                legend_elements = [
                    Patch(facecolor='#2ecc71', alpha=0.8, label='Base Code (100% pass rate)'),
                    Patch(facecolor='#e3f2fd', alpha=0.8, label='OpenAI - v1 (lightest)'),
                    Patch(facecolor='#1976d2', alpha=0.8, label='OpenAI - v4 (darkest)'),
                    Patch(facecolor='#ffebee', alpha=0.8, label='Gemini - v1 (lightest)'),
                    Patch(facecolor='#c62828', alpha=0.8, label='Gemini - v4 (darkest)'),
                    Patch(facecolor='#f3e5f5', alpha=0.8, label='Claude - v1 (lightest)'),
                    Patch(facecolor='#6a1b9a', alpha=0.8, label='Claude - v4 (darkest)'),
                ]
                ax.legend(handles=legend_elements, loc='upper right', fontsize=9, ncol=2,
                         title="Color Gradient: lighter → darker = v1 → v4", title_fontsize=10)
            else:
                ax.legend(loc='upper left', fontsize=11)

            plt.tight_layout()
            filename = f"mean_comparison_{metric}_barplot.png"
            plt.savefig(output_dir / filename, dpi=300, bbox_inches='tight')
            plt.close(fig)
            self.logger.info(f"Created mean comparison bar plot: {filename}")

    def visualize_objective_4(self, data: Dict):
        """
        Obiettivo 4: Box plot per metrica in correlazione a linguaggio + modello.
        Un grafico per ogni metrica.
        """
        self.logger.info("Visualizing Objective 4: Metrics by Language + Model")

        output_subdir = self.output_dir / "metrics_means_related_to_language_and_model"
        output_subdir.mkdir(parents=True, exist_ok=True)

        language_model_stats = data.get("language_model_stats", {})

        for metric in self.metrics:
            fig, ax = plt.subplots(figsize=(22, 8))

            plot_data = []
            labels = []
            colors = []

            # Sort combinations by language then model
            sorted_combos = sorted(language_model_stats.keys(),
                                  key=lambda x: (x.split('_')[0], x.split('_')[1] if len(x.split('_')) > 1 else ""))

            for combo_key in sorted_combos:
                combo_metrics = language_model_stats[combo_key]
                if metric in combo_metrics and combo_metrics[metric]:
                    plot_data.append(combo_metrics[metric])

                    # Format label
                    parts = combo_key.split('_')
                    language = parts[0].upper() if parts else ""
                    model = parts[1].capitalize() if len(parts) > 1 else ""
                    labels.append(f"{language}\n{model}")

                    # Set color by model
                    model_lower = parts[1].lower() if len(parts) > 1 else ""
                    if model_lower in self.model_colors:
                        colors.append(self.model_colors[model_lower])
                    else:
                        colors.append("#95a5a6")

            if not plot_data:
                self.logger.warning(f"No data for {metric} in Objective 4")
                plt.close(fig)
                continue

            # Set reasonable ylim
            if metric != "pass_rate":
                ylim = self._remove_outliers_for_ylim(plot_data, percentile=97)
                ax.set_ylim(ylim)

            # Create box plot
            bp = ax.boxplot(plot_data, labels=labels, patch_artist=True,
                           showmeans=True, meanline=True,
                           meanprops=dict(linestyle='--', linewidth=2, color='red'),
                           showfliers=True, flierprops=dict(marker='o', markerfacecolor='gray', markersize=3, alpha=0.2))

            # Color boxes
            for patch, color in zip(bp['boxes'], colors):
                patch.set_facecolor(color)
                patch.set_alpha(0.7)

            ax.set_ylabel(self.metric_labels[metric], fontsize=13, fontweight='bold')
            ax.set_xlabel('Language + Model', fontsize=13, fontweight='bold')
            ax.set_title(f'{self.metric_labels[metric]} by Language and Model (LLM Code)\n(All LLM generated code)',
                       fontsize=14, fontweight='bold', pad=20)
            ax.grid(True, alpha=0.3, axis='y')

            # Legend
            from matplotlib.patches import Patch
            legend_elements = [
                Patch(facecolor=self.model_colors["openai"], alpha=0.7, label='OpenAI'),
                Patch(facecolor=self.model_colors["claude"], alpha=0.7, label='Claude'),
                Patch(facecolor=self.model_colors["gemini"], alpha=0.7, label='Gemini'),
                plt.Line2D([0], [0], color='red', linestyle='--', linewidth=2, label='Mean')
            ]
            ax.legend(handles=legend_elements, loc='upper right', fontsize=9, ncol=2)

            plt.xticks(rotation=90, ha='right', fontsize=9)
            plt.tight_layout()

            # Save
            filename = f"language_model_{metric}_boxplot.png"
            filepath = output_subdir / filename
            plt.savefig(filepath, dpi=300, bbox_inches='tight')
            plt.close(fig)

            self.logger.info(f"Saved: {filename}")

    def plot_energy_pass_rate_tradeoff(self, all_data: Dict):
        """
        Scatter plot: Energy Improvement (X) vs Pass Rate (Y)
        Aggregato per model+prompt (media su 7 linguaggi)
        """
        import pandas as pd

        self.logger.info("Creating Energy vs Pass Rate trade-off scatter plot")

        # Verifica che i dati di objective_3 esistano
        if "objective_3" not in all_data or "mean_improvements" not in all_data["objective_3"]:
            self.logger.warning("No objective_3 data found for energy-pass_rate plot")
            return

        # Prepara i dati
        plot_data = []
        mean_improvements = all_data["objective_3"]["mean_improvements"]
        model_version_stats = all_data["objective_3"]["model_version_stats"]

        for model_prompt_key, improvements in mean_improvements.items():
            if '_' in model_prompt_key:  # es. "openai_v1"
                parts = model_prompt_key.split('_')
                model = parts[0]
                prompt_version = '_'.join(parts[1:])  # Gestisce casi come "v1" o versioni più complesse

                # Estrai improvement energetico e pass rate
                energy_improvement = improvements.get('energy_joules', None)

                # Calcola pass rate medio per questa combinazione model+prompt
                if model_prompt_key in model_version_stats:
                    pass_rates = model_version_stats[model_prompt_key].get('pass_rate', [])
                    if pass_rates:
                        mean_pass_rate = np.mean(pass_rates)
                    else:
                        mean_pass_rate = None
                else:
                    mean_pass_rate = None

                if energy_improvement is not None and mean_pass_rate is not None:
                    plot_data.append({
                        'model': model,
                        'prompt_version': prompt_version,
                        'energy_improvement': energy_improvement,
                        'pass_rate': mean_pass_rate
                    })

        if not plot_data:
            self.logger.warning("No valid data points for energy-pass_rate plot")
            return

        df = pd.DataFrame(plot_data)

        # Crea scatter plot
        fig, ax = plt.subplots(figsize=(12, 8))

        # Mappa i marker per le versioni prompt
        markers = {'v1': 'o', 'v2': 's', 'v3': '^', 'v4': 'D'}

        # Plotta per ogni modello
        for model in df['model'].unique():
            model_data = df[df['model'] == model]
            for version in model_data['prompt_version'].unique():
                version_data = model_data[model_data['prompt_version'] == version]
                ax.scatter(
                    version_data['energy_improvement'],
                    version_data['pass_rate'],
                    c=self.model_colors.get(model, '#000000'),
                    marker=markers.get(version, 'o'),
                    s=200,
                    alpha=0.7,
                    edgecolors='black',
                    linewidth=1.5,
                    label=f'{model.capitalize()} {version}'
                )

        # Linee di riferimento
        ax.axvline(0, color='gray', linestyle='--', alpha=0.5, linewidth=2, label='No energy change')
        ax.axhline(100, color='green', linestyle='--', alpha=0.5, linewidth=2, label='100% pass rate')

        # ENHANCED FOR FIG 4.6: Add trend line (diagonal showing average behavior)
        # Calculate linear regression or LOWESS trend
        try:
            from scipy import stats
            # Extract x and y data
            x_data = df['energy_improvement'].values
            y_data = df['pass_rate'].values

            # Linear regression
            slope, intercept, r_value, p_value, std_err = stats.linregress(x_data, y_data)

            # Create trend line
            x_trend = np.linspace(x_data.min(), x_data.max(), 100)
            y_trend = slope * x_trend + intercept

            # Plot trend line
            ax.plot(x_trend, y_trend, 'r--', linewidth=2.5, alpha=0.7,
                   label=f'Average Trend (R²={r_value**2:.3f})')

            self.logger.info(f"Trend line added: slope={slope:.4f}, R²={r_value**2:.3f}")
        except ImportError:
            # Fallback: simple mean line if scipy not available
            mean_energy = df['energy_improvement'].mean()
            mean_pass_rate = df['pass_rate'].mean()
            ax.plot([x_data.min(), x_data.max()],
                   [mean_pass_rate, mean_pass_rate],
                   'r--', linewidth=2.5, alpha=0.7,
                   label=f'Average Pass Rate ({mean_pass_rate:.1f}%)')
            self.logger.warning("scipy not available, using simple mean line")
        except Exception as e:
            self.logger.warning(f"Could not add trend line: {e}")

        # Etichette e titolo
        ax.set_xlabel('Energy Improvement (%)\n(+ = reduction, - = increase)', fontsize=14, fontweight='bold')
        ax.set_ylabel('Pass Rate (%)', fontsize=14, fontweight='bold')
        ax.set_title(
            'Trade-off: Energy Improvement vs Test Pass Rate\n'
            '(Aggregated by Model + Prompt Version across all languages)',
            fontsize=16,
            fontweight='bold',
            pad=20
        )

        # Legenda
        ax.legend(bbox_to_anchor=(1.05, 1), loc='upper left', fontsize=10, frameon=True, shadow=True)

        # Griglia
        ax.grid(True, alpha=0.3, linestyle=':', linewidth=0.8)

        # Tight layout
        plt.tight_layout()

        # Salva
        output_dir = self.output_dir / "tradeoff_analysis"
        output_dir.mkdir(parents=True, exist_ok=True)
        filepath = output_dir / "energy_vs_pass_rate_tradeoff.png"
        plt.savefig(filepath, dpi=300, bbox_inches='tight')
        plt.close(fig)

        self.logger.info(f"Saved: energy_vs_pass_rate_tradeoff.png")

    def visualize_all_objectives(self, all_data: Dict):
        """Visualizza tutte le statistiche aggregate per tutti gli obiettivi."""
        self.logger.info("Starting visualization of all objectives")

        # Objective 1
        if "objective_1" in all_data:
            self.visualize_objective_1(all_data["objective_1"])

        # Objective 2
        if "objective_2" in all_data:
            self.visualize_objective_2(all_data["objective_2"])

        # Objective 3
        if "objective_3" in all_data:
            self.visualize_objective_3(all_data["objective_3"])

        # Objective 4
        if "objective_4" in all_data:
            self.visualize_objective_4(all_data["objective_4"])

        # Trade-off analysis: Energy vs Pass Rate
        self.plot_energy_pass_rate_tradeoff(all_data)

        self.logger.info("Completed visualization of all objectives")

    def create_summary_report(self, all_data: Dict):
        """Crea un report riassuntivo in formato markdown."""
        self.logger.info("Creating summary report")

        report_lines = ["# Execution Metrics Analysis Report\n\n"]

        # Add timestamp
        from datetime import datetime
        report_lines.append(f"**Generated:** {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n\n")

        report_lines.append("## Overview\n\n")
        report_lines.append("This report summarizes execution metrics aggregated across all clusters.\n\n")
        report_lines.append("**IMPORTANT**: Base code entries are filtered to include ONLY those with 100% pass rate across all 5 executions.\n\n")

        # Objective summaries
        for i in range(1, 5):
            obj_key = f"objective_{i}"
            if obj_key in all_data:
                report_lines.append(f"### Objective {i}\n\n")

                if i == 1:
                    report_lines.append("**Metrics by Prompt Version**\n\n")
                    data = all_data[obj_key]
                    if "base" in data:
                        base_count = len(data["base"].get("pass_rate", []))
                        report_lines.append(f"- Base code entries (100% pass rate): {base_count}\n")
                    if "prompt_versions" in data:
                        report_lines.append(f"- Prompt versions analyzed: {', '.join(data['prompt_versions'].keys())}\n")

                elif i == 2:
                    report_lines.append("**Metrics by Programming Language**\n\n")
                    data = all_data[obj_key]
                    if "base_by_language" in data:
                        languages = list(data["base_by_language"].keys())
                        report_lines.append(f"- Languages (base code): {', '.join(languages)}\n")
                    if "llm_by_language" in data:
                        languages = list(data["llm_by_language"].keys())
                        report_lines.append(f"- Languages (LLM code): {', '.join(languages)}\n")

                elif i == 3:
                    report_lines.append("**Metrics by Model + Prompt Version**\n\n")
                    data = all_data[obj_key]
                    if "model_version_stats" in data:
                        combos = list(data["model_version_stats"].keys())
                        report_lines.append(f"- Model combinations analyzed: {len(combos)}\n")
                    if "mean_improvements" in data:
                        report_lines.append("- Improvement percentages calculated\n")
                        report_lines.append("- **Improvement interpretation**:\n")
                        report_lines.append("  - For ALL metrics: **Positive (+) is GOOD** (improvement), **Negative (-) is BAD** (degradation)\n")
                        report_lines.append("  - Formula inverted in calculator: CPU/RAM/Time improvements show as positive percentages\n")

                elif i == 4:
                    report_lines.append("**Metrics by Language + Model**\n\n")
                    data = all_data[obj_key]
                    if "language_model_stats" in data:
                        combos = list(data["language_model_stats"].keys())
                        report_lines.append(f"- Language-model combinations analyzed: {len(combos)}\n")

                report_lines.append("\n")

        report_lines.append("## Visualization Files\n\n")
        report_lines.append("All plots are saved in subdirectories within `execution_stats_plots/`:\n\n")
        report_lines.append("### Box Plots (show distribution and variance)\n")
        report_lines.append("- `metrics_means_related_to_prompt_versions/`\n")
        report_lines.append("- `metrics_means_related_to_languages/`\n")
        report_lines.append("- `metrics_means_related_to_both_model_and_prompt_version/`\n")
        report_lines.append("- `metrics_means_related_to_language_and_model/`\n\n")

        report_lines.append("### Bar Plots (show mean comparisons)\n")
        report_lines.append("- Available in same directories with `_barplot.png` suffix\n\n")

        report_lines.append("### Scatter Plots (show base vs LLM comparison)\n")
        report_lines.append("- Available in language metrics directory\n\n")

        report_lines.append("## Metrics\n\n")
        report_lines.append("The following metrics are analyzed:\n\n")
        report_lines.append("- **CPU Usage (%)**: CPU utilization during execution\n")
        report_lines.append("- **RAM Usage (KB)**: Memory consumption\n")
        report_lines.append("- **Execution Time (ms)**: Time taken to execute tests\n")
        report_lines.append("- **Pass Rate (%)**: Percentage of tests passed\n")
        report_lines.append("- **Energy Consumption (J)**: Total energy in Joules (calculated from CPU, RAM, time with TDP/PUE factors)\n\n")

        report_lines.append("## Data Filtering\n\n")
        report_lines.append("**Base Code**: Only entries with 100% pass rate (across all 5 executions) are included.\n\n")
        report_lines.append("This ensures we compare LLM-generated code against known-good baseline implementations.\n\n")

        report_lines.append("## Notes\n\n")
        report_lines.append("- All plots use box plots to show data distribution and variance\n")
        report_lines.append("- Red dashed line indicates mean value\n")
        report_lines.append("- Outliers are shown but axis limits are adjusted for clarity\n")
        report_lines.append("- For improvement percentages (Objective 3):\n")
        report_lines.append("  - **Positive (+) values are GOOD** for ALL metrics (improvement)\n")
        report_lines.append("  - **Negative (-) values are BAD** for ALL metrics (degradation)\n")
        report_lines.append("  - Green text = improvement, Red text = degradation\n")
        report_lines.append("  - Formula inverted in calculator: reductions in CPU/RAM/Time show as positive %\n")

        # Save report
        report_path = self.output_dir / "summary_report.md"
        with open(report_path, 'w') as f:
            f.writelines(report_lines)

        self.logger.info(f"Summary report saved to {report_path}")


if __name__ == "__main__":
    # Example usage
    visualizator = ExecMetricStatsVisualizator()
    print(f"Output directory: {visualizator.output_dir}")
