"""
Pass Rate Visualizator for Thesis Section 4.1

Generates:
- 4.1.A: 2 overview graphs (aggregated + by model) for pass rate per language
- 4.1.B: 28 drill-down graphs (7 languages × 4 prompt versions)

Author: Generated for Thesis Analysis
Date: 2025
"""

import json
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
from pathlib import Path
from typing import Dict, List


class PassRateVisualizator:
    """
    Generates visualizations for pass rate analysis.
    """

    def __init__(self, stats_file: str = "execution_stats/pass_rate_aggregated.json",
                 output_dir: str = "execution_stats_plots"):
        """
        Initialize visualizator.

        Args:
            stats_file: Path to aggregated pass rate statistics JSON
            output_dir: Directory for output plots
        """
        self.stats_file = Path(stats_file)
        self.output_dir = Path(output_dir)
        self.output_dir.mkdir(parents=True, exist_ok=True)

        # Load data
        self.data = self._load_data()

        # Configuration
        self.languages = ['c', 'cpp', 'go', 'java', 'python', 'javascript', 'typescript']
        self.language_display_names = {
            'c': 'C',
            'cpp': 'C++',
            'go': 'Go',
            'java': 'Java',
            'python': 'Python',
            'javascript': 'JavaScript',
            'typescript': 'TypeScript'
        }
        self.models = ['openAI', 'claude', 'gemini']
        self.model_colors = {
            'openAI': '#3498db',  # Blue
            'claude': '#9b59b6',  # Purple
            'gemini': '#e74c3c'   # Red
        }
        self.prompt_versions = ['v1', 'v2', 'v3', 'v4']

        # Plot styling
        self.dpi = 300
        self.figsize_overview = (14, 8)
        self.figsize_drilldown = (10, 6)

        # Set style
        sns.set_style("whitegrid")
        plt.rcParams['font.size'] = 10
        plt.rcParams['axes.titlesize'] = 14
        plt.rcParams['axes.labelsize'] = 13
        plt.rcParams['xtick.labelsize'] = 10
        plt.rcParams['ytick.labelsize'] = 10

    def _load_data(self) -> Dict:
        """Load pass rate statistics from JSON file."""
        if not self.stats_file.exists():
            raise FileNotFoundError(f"Statistics file not found: {self.stats_file}")

        with open(self.stats_file, 'r') as f:
            return json.load(f)

    def generate_all_visualizations(self):
        """Generate all pass rate visualizations."""
        print("Generating pass rate visualizations...")

        # 4.1.A: Overview graphs
        print("\n[4.1.A] Generating overview graphs...")
        self.generate_4_1_A_aggregated()
        self.generate_4_1_A_by_model()

        # 4.1.B: Drill-down graphs
        print("\n[4.1.B] Generating drill-down graphs (28 total)...")
        self.generate_4_1_B_drilldown()

        print("\n✓ All visualizations generated successfully!")

    def generate_4_1_A_aggregated(self):
        """
        Generate 4.1.A - Aggregated overview graph.

        Bar chart showing Base Code (100%) vs. LLM Aggregated for each language.
        Includes degradation % annotations.
        """
        print("  - Generating aggregated overview...")

        # Prepare data
        languages_to_plot = []
        base_rates = []
        llm_rates = []
        degradations = []
        base_counts = []

        # Get filtering statistics for entry counts
        valid_entries_by_lang = self.data.get('filtering_statistics', {}).get('valid_entries_by_language', {})

        for lang in self.languages:
            if lang in self.data.get('by_language', {}):
                lang_data = self.data['by_language'][lang]

                base_mean = lang_data.get('base', {}).get('mean')
                llm_mean = lang_data.get('llm_aggregated', {}).get('mean')
                degradation = lang_data.get('degradation_percent')
                base_count = valid_entries_by_lang.get(lang, 0)

                if base_mean is not None and llm_mean is not None:
                    languages_to_plot.append(self.language_display_names[lang])
                    base_rates.append(base_mean)
                    llm_rates.append(llm_mean)
                    degradations.append(degradation if degradation is not None else 0)
                    base_counts.append(base_count)

        if not languages_to_plot:
            print("    Warning: No data available for aggregated overview")
            return

        # Create plot
        fig, ax = plt.subplots(figsize=self.figsize_overview, dpi=self.dpi)

        x = np.arange(len(languages_to_plot))
        width = 0.35

        # Plot bars
        bars1 = ax.bar(x - width/2, base_rates, width, label='Base Code',
                      color='#27ae60', alpha=0.8, edgecolor='black', linewidth=0.5)
        bars2 = ax.bar(x + width/2, llm_rates, width, label='LLM Aggregated',
                      color='#3498db', alpha=0.8, edgecolor='black', linewidth=0.5)

        # Add value labels on bars
        for bar in bars1:
            height = bar.get_height()
            ax.text(bar.get_x() + bar.get_width()/2., height,
                   f'{height:.1f}%',
                   ha='center', va='bottom', fontsize=9, fontweight='bold')

        for bar, deg in zip(bars2, degradations):
            height = bar.get_height()
            ax.text(bar.get_x() + bar.get_width()/2., height,
                   f'{height:.1f}%',
                   ha='center', va='bottom', fontsize=9, fontweight='bold')

            # Add degradation annotation
            color = '#c0392b' if deg < 0 else '#27ae60'
            ax.text(bar.get_x() + bar.get_width()/2., height + 5,
                   f'({deg:+.1f}%)',
                   ha='center', va='bottom', fontsize=8, color=color,
                   fontweight='bold', style='italic')

        # Customize plot
        ax.set_xlabel('Programming Language', fontweight='bold')
        ax.set_ylabel('Pass Rate (%)', fontweight='bold')
        ax.set_title('4.1.A - Pass Rate by Language (Aggregated LLM)',
                    fontweight='bold', pad=20)
        ax.set_xticks(x)

        # Add entry counts to x-axis labels
        labels_with_counts = [f'{lang}\n(n={count})' for lang, count in zip(languages_to_plot, base_counts)]
        ax.set_xticklabels(labels_with_counts, rotation=0)

        ax.set_ylim(0, 110)
        ax.legend(loc='upper right', framealpha=0.9)
        ax.grid(axis='y', alpha=0.3)

        # Add horizontal line at 100%
        ax.axhline(y=100, color='gray', linestyle='--', linewidth=1, alpha=0.5)

        plt.tight_layout()

        # Save
        output_file = self.output_dir / "language_pass_rate_aggregated.png"
        plt.savefig(output_file, dpi=self.dpi, bbox_inches='tight')
        plt.close()

        print(f"    ✓ Saved: {output_file}")

    def generate_4_1_A_by_model(self):
        """
        Generate 4.1.A - By model overview graph.

        Grouped bar chart showing Base Code + OpenAI + Claude + Gemini for each language.
        """
        print("  - Generating by-model overview...")

        # Prepare data
        languages_to_plot = []
        data_by_model = {model: [] for model in self.models}
        base_rates = []

        for lang in self.languages:
            if lang in self.data.get('by_language_model', {}):
                lang_data = self.data['by_language_model'][lang]

                # Check if we have data for all models
                has_all_data = True
                model_means = {}

                for model in self.models:
                    if model in lang_data:
                        mean = lang_data[model].get('mean')
                        if mean is not None:
                            model_means[model] = mean
                        else:
                            has_all_data = False
                    else:
                        has_all_data = False

                if has_all_data:
                    # Get base rate
                    base_mean = self.data['by_language'][lang]['base'].get('mean', 100.0)

                    languages_to_plot.append(self.language_display_names[lang])
                    base_rates.append(base_mean)

                    for model in self.models:
                        data_by_model[model].append(model_means[model])

        if not languages_to_plot:
            print("    Warning: No data available for by-model overview")
            return

        # Create plot
        fig, ax = plt.subplots(figsize=self.figsize_overview, dpi=self.dpi)

        x = np.arange(len(languages_to_plot))
        width = 0.2

        # Plot bars
        bars_base = ax.bar(x - 1.5*width, base_rates, width, label='Base Code',
                          color='#27ae60', alpha=0.8, edgecolor='black', linewidth=0.5)
        bars_openai = ax.bar(x - 0.5*width, data_by_model['openAI'], width, label='OpenAI',
                            color=self.model_colors['openAI'], alpha=0.8,
                            edgecolor='black', linewidth=0.5)
        bars_claude = ax.bar(x + 0.5*width, data_by_model['claude'], width, label='Claude',
                            color=self.model_colors['claude'], alpha=0.8,
                            edgecolor='black', linewidth=0.5)
        bars_gemini = ax.bar(x + 1.5*width, data_by_model['gemini'], width, label='Gemini',
                            color=self.model_colors['gemini'], alpha=0.8,
                            edgecolor='black', linewidth=0.5)

        # Add value labels (only for LLM bars to avoid clutter)
        for bars in [bars_openai, bars_claude, bars_gemini]:
            for bar in bars:
                height = bar.get_height()
                if height > 0:  # Only label non-zero bars
                    ax.text(bar.get_x() + bar.get_width()/2., height,
                           f'{height:.0f}',
                           ha='center', va='bottom', fontsize=7)

        # Customize plot
        ax.set_xlabel('Programming Language', fontweight='bold')
        ax.set_ylabel('Pass Rate (%)', fontweight='bold')
        ax.set_title('4.1.A - Pass Rate by Language and Model',
                    fontweight='bold', pad=20)
        ax.set_xticks(x)
        ax.set_xticklabels(languages_to_plot, rotation=0)
        ax.set_ylim(0, 110)
        ax.legend(loc='upper right', framealpha=0.9, ncol=2)
        ax.grid(axis='y', alpha=0.3)

        # Add horizontal line at 100%
        ax.axhline(y=100, color='gray', linestyle='--', linewidth=1, alpha=0.5)

        plt.tight_layout()

        # Save
        output_file = self.output_dir / "language_pass_rate_by_model.png"
        plt.savefig(output_file, dpi=self.dpi, bbox_inches='tight')
        plt.close()

        print(f"    ✓ Saved: {output_file}")

    def generate_4_1_B_drilldown(self):
        """
        Generate 4.1.B - Drill-down graphs.

        28 individual graphs (7 languages × 4 prompt versions).
        Each graph shows: Base Code (100%) + 3 model bars for that specific (language, prompt).
        """
        # Create directory structure
        base_dir = self.output_dir / "language_pass_rate"
        base_dir.mkdir(parents=True, exist_ok=True)

        total_graphs = 0

        for prompt_version in self.prompt_versions:
            # Create subdirectory for this prompt version
            prompt_dir = base_dir / prompt_version
            prompt_dir.mkdir(parents=True, exist_ok=True)

            print(f"  - Generating drill-down for {prompt_version}...")

            for lang in self.languages:
                # Check if data exists
                if lang not in self.data.get('by_language_prompt', {}):
                    continue

                if prompt_version not in self.data['by_language_prompt'][lang]:
                    continue

                prompt_data = self.data['by_language_prompt'][lang][prompt_version]

                # Get base rate
                base_mean = prompt_data.get('base', {}).get('mean', 100.0)

                # Get LLM rates for each model
                model_rates = {}
                for model in self.models:
                    if model in prompt_data.get('llm', {}):
                        mean = prompt_data['llm'][model].get('mean')
                        if mean is not None:
                            model_rates[model] = mean

                if not model_rates:
                    continue  # Skip if no LLM data

                # Create plot
                fig, ax = plt.subplots(figsize=self.figsize_drilldown, dpi=self.dpi)

                # Prepare data
                labels = ['Base Code'] + [self._get_model_display_name(m) for m in self.models]
                values = [base_mean] + [model_rates.get(m, 0) for m in self.models]
                colors = ['#27ae60'] + [self.model_colors[m] for m in self.models]

                # Plot bars
                x = np.arange(len(labels))
                bars = ax.bar(x, values, color=colors, alpha=0.8,
                             edgecolor='black', linewidth=0.5)

                # Add value labels
                for bar in bars:
                    height = bar.get_height()
                    ax.text(bar.get_x() + bar.get_width()/2., height,
                           f'{height:.1f}%',
                           ha='center', va='bottom', fontsize=10, fontweight='bold')

                # Calculate and add degradation for each model
                for i, model in enumerate(self.models, start=1):
                    if model in model_rates:
                        degradation = ((model_rates[model] - base_mean) / base_mean) * 100
                        color = '#c0392b' if degradation < 0 else '#27ae60'
                        ax.text(bars[i].get_x() + bars[i].get_width()/2., bars[i].get_height() + 3,
                               f'({degradation:+.1f}%)',
                               ha='center', va='bottom', fontsize=8, color=color,
                               fontweight='bold', style='italic')

                # Customize plot
                lang_display = self.language_display_names[lang]
                ax.set_xlabel('Code Type', fontweight='bold')
                ax.set_ylabel('Pass Rate (%)', fontweight='bold')
                ax.set_title(f'Pass Rate: {lang_display} - Prompt {prompt_version.upper()}',
                            fontweight='bold', pad=15)
                ax.set_xticks(x)
                ax.set_xticklabels(labels, rotation=0)
                ax.set_ylim(0, 110)
                ax.grid(axis='y', alpha=0.3)

                # Add horizontal line at 100%
                ax.axhline(y=100, color='gray', linestyle='--', linewidth=1, alpha=0.5)

                plt.tight_layout()

                # Save
                output_file = prompt_dir / f"{lang}.png"
                plt.savefig(output_file, dpi=self.dpi, bbox_inches='tight')
                plt.close()

                total_graphs += 1

            print(f"    ✓ Generated {len(self.languages)} graphs for {prompt_version}")

        print(f"  ✓ Total drill-down graphs generated: {total_graphs}")

    def _get_model_display_name(self, model: str) -> str:
        """Get display name for model."""
        display_names = {
            'openAI': 'OpenAI',
            'claude': 'Claude',
            'gemini': 'Gemini'
        }
        return display_names.get(model, model)

    def generate_summary_report(self):
        """Generate a markdown summary report for pass rate analysis."""
        print("\nGenerating summary report...")

        report_file = self.output_dir / "pass_rate_summary_report.md"

        with open(report_file, 'w') as f:
            f.write("# Pass Rate Analysis Summary Report\n\n")
            f.write("This report summarizes the pass rate analysis for Thesis Section 4.1.\n\n")

            # Global statistics
            if 'global' in self.data:
                global_stats = self.data['global']
                f.write("## Global Statistics\n\n")
                base_mean = global_stats.get('base', {}).get('mean')
                llm_mean = global_stats.get('llm_aggregated', {}).get('mean')
                degradation = global_stats.get('overall_degradation_percent')

                if base_mean is not None:
                    f.write(f"- **Base Code Mean Pass Rate**: {base_mean:.2f}%\n")
                else:
                    f.write(f"- **Base Code Mean Pass Rate**: No data\n")

                if llm_mean is not None:
                    f.write(f"- **LLM Aggregated Mean Pass Rate**: {llm_mean:.2f}%\n")
                else:
                    f.write(f"- **LLM Aggregated Mean Pass Rate**: No data\n")

                if degradation is not None:
                    f.write(f"- **Overall Degradation**: {degradation:.2f}%\n\n")
                else:
                    f.write(f"- **Overall Degradation**: No data\n\n")

            # By language
            if 'by_language' in self.data:
                f.write("## Pass Rate by Language\n\n")
                f.write("| Language | Base Code | LLM Aggregated | Degradation |\n")
                f.write("|----------|-----------|----------------|-------------|\n")

                for lang in self.languages:
                    if lang in self.data['by_language']:
                        lang_data = self.data['by_language'][lang]
                        base_mean = lang_data['base'].get('mean', 0)
                        llm_mean = lang_data['llm_aggregated'].get('mean', 0)
                        degradation = lang_data.get('degradation_percent', 0)

                        f.write(f"| {self.language_display_names[lang]} | "
                               f"{base_mean:.2f}% | "
                               f"{llm_mean:.2f}% | "
                               f"{degradation:+.2f}% |\n")

                f.write("\n")

            # By model
            if 'by_model' in self.data:
                f.write("## Pass Rate by Model\n\n")
                f.write("| Model | Mean Pass Rate |\n")
                f.write("|-------|----------------|\n")

                for model in self.models:
                    if model in self.data['by_model']:
                        mean = self.data['by_model'][model].get('mean', 0)
                        f.write(f"| {self._get_model_display_name(model)} | {mean:.2f}% |\n")

                f.write("\n")

            # By prompt version
            if 'by_prompt_version' in self.data:
                f.write("## Pass Rate by Prompt Version\n\n")
                f.write("| Prompt Version | Mean Pass Rate |\n")
                f.write("|----------------|----------------|\n")

                for version in self.prompt_versions:
                    if version in self.data['by_prompt_version']:
                        mean = self.data['by_prompt_version'][version].get('mean', 0)
                        f.write(f"| {version.upper()} | {mean:.2f}% |\n")

                f.write("\n")

            # Visualization index
            f.write("## Generated Visualizations\n\n")
            f.write("### 4.1.A - Overview Graphs\n\n")
            f.write("1. `language_pass_rate_aggregated.png` - Pass rate by language (LLM aggregated)\n")
            f.write("2. `language_pass_rate_by_model.png` - Pass rate by language and model\n\n")

            f.write("### 4.1.B - Drill-down Graphs\n\n")
            f.write("28 individual graphs organized by prompt version:\n\n")

            for version in self.prompt_versions:
                f.write(f"- `language_pass_rate/{version}/` - 7 language-specific graphs for {version.upper()}\n")

            f.write("\n")

        print(f"✓ Summary report saved: {report_file}")


def main():
    """Main execution function."""
    # Initialize visualizator
    visualizator = PassRateVisualizator()

    # Generate all visualizations
    visualizator.generate_all_visualizations()

    # Generate summary report
    visualizator.generate_summary_report()


if __name__ == "__main__":
    main()
