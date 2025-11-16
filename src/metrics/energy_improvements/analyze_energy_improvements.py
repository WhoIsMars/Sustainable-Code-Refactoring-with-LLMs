#!/usr/bin/env python3
"""
Energy Improvements Analysis Script
====================================

This script analyzes energy improvement data from LLM-generated code optimizations.

Main Analyses:
1. Improvements per language (CPU, RAM, execution time)
2. Improvements per model (openAI, gemini, claude)
3. Improvements per prompt version (v1, v2, v3, v4)
4. Improvements per model + prompt version combination
5. Invalid improvements analysis (by model, language, prompt)
6. Outliers analysis (by model, language, prompt)
7. Success rate analysis (valid executions percentage)

Data Processing:
- Valid improvements: label='reduction' or 'degradation', is_outlier=False, label!='invalid'
- Invalid improvements: label='invalid'
- Outliers: is_outlier=True
- Positive improvement % = reduction (better) - NUOVA SEMANTICA INVERTITA
- Negative improvement % = degradation (worse)

Output:
- Statistics JSON files in current directory
- PNG charts in current directory
- Console summary statistics
"""

import json
import os
from pathlib import Path
from typing import Dict, List, Tuple
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from collections import defaultdict
from dataclasses import dataclass, asdict
import pandas as pd

# Set style for professional charts
sns.set_style("whitegrid")
plt.rcParams['figure.figsize'] = (12, 8)
plt.rcParams['font.size'] = 10
plt.rcParams['axes.titlesize'] = 14
plt.rcParams['axes.labelsize'] = 12

@dataclass
class ImprovementStats:
    """Statistics for a set of improvements"""
    count: int
    mean: float
    median: float
    std: float
    min: float
    max: float
    q25: float
    q75: float

    @staticmethod
    def from_values(values: List[float]) -> 'ImprovementStats':
        """Create stats from a list of values"""
        if not values:
            return ImprovementStats(0, 0, 0, 0, 0, 0, 0, 0)
        arr = np.array(values)
        return ImprovementStats(
            count=len(values),
            mean=float(np.mean(arr)),
            median=float(np.median(arr)),
            std=float(np.std(arr)),
            min=float(np.min(arr)),
            max=float(np.max(arr)),
            q25=float(np.percentile(arr, 25)),
            q75=float(np.percentile(arr, 75))
        )


class EnergyImprovementsAnalyzer:
    """Analyzer for energy improvements data"""

    def __init__(self, data_dir: str):
        self.data_dir = Path(data_dir)
        self.output_dir = Path(__file__).parent
        self.metrics = ['CPU_usage', 'RAM_usage', 'execution_time_ms', 'energy_joules']
        self.models = ['openAI', 'gemini', 'claude']
        self.prompts = ['prompt_v1', 'prompt_v2', 'prompt_v3', 'prompt_v4']

        # Language normalization mapping
        self.language_normalization = {
            'java': 'java',
            'Java': 'java',
            'python': 'python',
            'Python': 'python',
            'javascript': 'javascript',
            'JavaScript': 'javascript',
            'typescript': 'typescript',
            'TypeScript': 'typescript',
            'go': 'go',
            'Go': 'go',
            'c': 'c',
            'C': 'c',
            'cpp': 'cpp',
            'Cpp': 'cpp',
            'CPP': 'cpp',
            'C++': 'cpp',
        }

        # Display names for plots (capitalized, proper formatting)
        self.language_display_names = {
            'java': 'Java',
            'python': 'Python',
            'javascript': 'JavaScript',
            'typescript': 'TypeScript',
            'go': 'Go',
            'c': 'C',
            'cpp': 'C++',
        }

        # Data containers
        self.all_data = []
        self.valid_improvements = defaultdict(list)
        self.invalid_improvements = defaultdict(list)
        self.outliers = defaultdict(list)

    def normalize_language(self, language: str) -> str:
        """Normalize language name to consistent lowercase format"""
        if not language or language == 'unknown':
            return language
        return self.language_normalization.get(language, language.lower())

    def get_display_language(self, language: str) -> str:
        """Get properly formatted display name for a language"""
        normalized = self.normalize_language(language)
        return self.language_display_names.get(normalized, normalized.capitalize())

    def load_all_data(self):
        """Load all improvement data from JSON files"""
        print("Loading data from JSON files...")

        json_files = list(self.data_dir.glob("improvements_cluster_*.json"))
        print(f"Found {len(json_files)} cluster files")

        for json_file in json_files:
            with open(json_file, 'r') as f:
                data = json.load(f)

            # Each file can have multiple entries
            for entry_id, entry_data in data.items():
                if 'improvements_data' not in entry_data:
                    continue

                improvements = entry_data['improvements_data']
                base_language = entry_data.get('base_5_exec_data', {}).get('language', 'unknown')

                for model in self.models:
                    if model not in improvements:
                        continue

                    for prompt in self.prompts:
                        if prompt not in improvements[model]:
                            continue

                        prompt_data = improvements[model][prompt]
                        language = prompt_data.get('language', base_language)
                        # Normalize language name for consistency
                        language = self.normalize_language(language)

                        for metric in self.metrics:
                            if metric not in prompt_data:
                                continue

                            metric_data = prompt_data[metric]

                            record = {
                                'entry_id': entry_id,
                                'cluster_file': json_file.stem,
                                'model': model,
                                'prompt': prompt,
                                'language': language,
                                'metric': metric,
                                'improvement_percentage': metric_data['improvement_percentage'],
                                'label': metric_data['label'],
                                'is_outlier': metric_data['is_outlier'],
                                'base_value': metric_data['base_value'],
                                'llm_value': metric_data['llm_value'],
                                'successfully_exec': prompt_data.get('LLM_successfully_exec_quantity', 0)
                            }

                            self.all_data.append(record)

                            # Categorize the record
                            key = (model, prompt, language, metric)

                            if metric_data['label'] == 'invalid':
                                self.invalid_improvements[key].append(record)
                            elif metric_data['is_outlier']:
                                self.outliers[key].append(record)
                            else:
                                # Valid improvement (reduction or degradation)
                                self.valid_improvements[key].append(record)

        print(f"Loaded {len(self.all_data)} total records")
        print(f"Valid improvements: {sum(len(v) for v in self.valid_improvements.values())}")
        print(f"Invalid improvements: {sum(len(v) for v in self.invalid_improvements.values())}")
        print(f"Outliers: {sum(len(v) for v in self.outliers.values())}")

    def analyze_by_language(self) -> Dict:
        """Analyze improvements grouped by programming language"""
        print("\n=== Analyzing by Language ===")

        results = {}

        for metric in self.metrics:
            results[metric] = {}

            # Collect data by language
            lang_data = defaultdict(list)

            for key, records in self.valid_improvements.items():
                model, prompt, language, rec_metric = key
                if rec_metric != metric or not language or language == 'unknown':
                    continue

                for record in records:
                    lang_data[language].append(record['improvement_percentage'])

            # Calculate statistics
            for language, values in lang_data.items():
                stats = ImprovementStats.from_values(values)
                results[metric][language] = asdict(stats)
                print(f"{metric} - {language}: {stats.count} samples, mean={stats.mean:.2f}%")

        # Save results
        output_file = self.output_dir / 'stats_by_language.json'
        with open(output_file, 'w') as f:
            json.dump(results, f, indent=2)
        print(f"\nSaved statistics to {output_file}")

        return results

    def analyze_by_model(self) -> Dict:
        """Analyze improvements grouped by model"""
        print("\n=== Analyzing by Model ===")

        results = {}

        for metric in self.metrics:
            results[metric] = {}

            # Collect data by model
            model_data = defaultdict(list)

            for key, records in self.valid_improvements.items():
                model, prompt, language, rec_metric = key
                if rec_metric != metric:
                    continue

                for record in records:
                    model_data[model].append(record['improvement_percentage'])

            # Calculate statistics
            for model, values in model_data.items():
                stats = ImprovementStats.from_values(values)
                results[metric][model] = asdict(stats)
                print(f"{metric} - {model}: {stats.count} samples, mean={stats.mean:.2f}%")

        # Save results
        output_file = self.output_dir / 'stats_by_model.json'
        with open(output_file, 'w') as f:
            json.dump(results, f, indent=2)
        print(f"\nSaved statistics to {output_file}")

        return results

    def analyze_by_prompt(self) -> Dict:
        """Analyze improvements grouped by prompt version"""
        print("\n=== Analyzing by Prompt Version ===")

        results = {}

        for metric in self.metrics:
            results[metric] = {}

            # Collect data by prompt
            prompt_data = defaultdict(list)

            for key, records in self.valid_improvements.items():
                model, prompt, language, rec_metric = key
                if rec_metric != metric:
                    continue

                for record in records:
                    prompt_data[prompt].append(record['improvement_percentage'])

            # Calculate statistics
            for prompt, values in prompt_data.items():
                stats = ImprovementStats.from_values(values)
                results[metric][prompt] = asdict(stats)
                print(f"{metric} - {prompt}: {stats.count} samples, mean={stats.mean:.2f}%")

        # Save results
        output_file = self.output_dir / 'stats_by_prompt.json'
        with open(output_file, 'w') as f:
            json.dump(results, f, indent=2)
        print(f"\nSaved statistics to {output_file}")

        return results

    def analyze_by_model_and_prompt(self) -> Dict:
        """Analyze improvements grouped by model + prompt version"""
        print("\n=== Analyzing by Model + Prompt Version ===")

        results = {}

        for metric in self.metrics:
            results[metric] = {}

            # Collect data by model+prompt
            combo_data = defaultdict(list)

            for key, records in self.valid_improvements.items():
                model, prompt, language, rec_metric = key
                if rec_metric != metric:
                    continue

                combo_key = f"{model}_{prompt}"
                for record in records:
                    combo_data[combo_key].append(record['improvement_percentage'])

            # Calculate statistics
            for combo, values in combo_data.items():
                stats = ImprovementStats.from_values(values)
                results[metric][combo] = asdict(stats)
                print(f"{metric} - {combo}: {stats.count} samples, mean={stats.mean:.2f}%")

        # Save results
        output_file = self.output_dir / 'stats_by_model_and_prompt.json'
        with open(output_file, 'w') as f:
            json.dump(results, f, indent=2)
        print(f"\nSaved statistics to {output_file}")

        return results

    def analyze_invalid_improvements(self) -> Dict:
        """Analyze invalid improvements by model, language, and prompt"""
        print("\n=== Analyzing Invalid Improvements ===")

        results = {
            'by_model': defaultdict(int),
            'by_language': defaultdict(int),
            'by_prompt': defaultdict(int),
            'by_model_prompt': defaultdict(int),
            'total': sum(len(v) for v in self.invalid_improvements.values())
        }

        for key, records in self.invalid_improvements.items():
            model, prompt, language, metric = key
            count = len(records)

            results['by_model'][model] += count
            results['by_language'][language] += count
            results['by_prompt'][prompt] += count
            results['by_model_prompt'][f"{model}_{prompt}"] += count

        print(f"Total invalid improvements: {results['total']}")
        print(f"\nBy model: {dict(results['by_model'])}")
        print(f"By language: {dict(results['by_language'])}")
        print(f"By prompt: {dict(results['by_prompt'])}")

        # Convert defaultdicts to regular dicts for JSON serialization
        results['by_model'] = dict(results['by_model'])
        results['by_language'] = dict(results['by_language'])
        results['by_prompt'] = dict(results['by_prompt'])
        results['by_model_prompt'] = dict(results['by_model_prompt'])

        # Save results
        output_file = self.output_dir / 'stats_invalid_improvements.json'
        with open(output_file, 'w') as f:
            json.dump(results, f, indent=2)
        print(f"\nSaved statistics to {output_file}")

        return results

    def analyze_outliers(self) -> Dict:
        """Analyze outliers by model, language, and prompt"""
        print("\n=== Analyzing Outliers ===")

        results = {
            'by_model': defaultdict(int),
            'by_language': defaultdict(int),
            'by_prompt': defaultdict(int),
            'by_model_prompt': defaultdict(int),
            'total': sum(len(v) for v in self.outliers.values())
        }

        for key, records in self.outliers.items():
            model, prompt, language, metric = key
            count = len(records)

            results['by_model'][model] += count
            results['by_language'][language] += count
            results['by_prompt'][prompt] += count
            results['by_model_prompt'][f"{model}_{prompt}"] += count

        print(f"Total outliers: {results['total']}")
        print(f"\nBy model: {dict(results['by_model'])}")
        print(f"By language: {dict(results['by_language'])}")
        print(f"By prompt: {dict(results['by_prompt'])}")

        # Convert defaultdicts to regular dicts
        results['by_model'] = dict(results['by_model'])
        results['by_language'] = dict(results['by_language'])
        results['by_prompt'] = dict(results['by_prompt'])
        results['by_model_prompt'] = dict(results['by_model_prompt'])

        # Save results
        output_file = self.output_dir / 'stats_outliers.json'
        with open(output_file, 'w') as f:
            json.dump(results, f, indent=2)
        print(f"\nSaved statistics to {output_file}")

        return results

    def analyze_success_rate(self) -> Dict:
        """Analyze success rate (valid executions) by model and prompt"""
        print("\n=== Analyzing Success Rate ===")

        # Count total attempts vs valid executions
        total_attempts = defaultdict(int)
        valid_executions = defaultdict(int)

        for record in self.all_data:
            key = (record['model'], record['prompt'])
            total_attempts[key] += 1

            if record['label'] != 'invalid':
                valid_executions[key] += 1

        results = {}
        for key in total_attempts:
            model, prompt = key
            total = total_attempts[key]
            valid = valid_executions[key]
            rate = (valid / total * 100) if total > 0 else 0

            combo_name = f"{model}_{prompt}"
            results[combo_name] = {
                'total_attempts': total,
                'valid_executions': valid,
                'success_rate_percentage': rate
            }
            print(f"{combo_name}: {valid}/{total} = {rate:.2f}%")

        # Save results
        output_file = self.output_dir / 'stats_success_rate.json'
        with open(output_file, 'w') as f:
            json.dump(results, f, indent=2)
        print(f"\nSaved statistics to {output_file}")

        return results

    def create_visualizations(self):
        """Create all visualization charts"""
        print("\n=== Creating Visualizations ===")

        self._plot_improvements_by_language()
        self._plot_improvements_by_model()
        self._plot_improvements_by_prompt()
        self._plot_improvements_by_model_prompt()
        self._plot_improvements_by_model_prompt_boxplots()
        self._plot_invalid_and_outliers()
        self._plot_success_rate()
        self._plot_distribution_by_metric()

        print("All visualizations created successfully")

    def _plot_improvements_by_language(self):
        """Create box plots for improvements by language with distinct colors"""
        fig, axes = plt.subplots(2, 2, figsize=(18, 12))
        axes = axes.flatten()

        # Define distinct colors for each language
        language_colors = {
            'C': '#e74c3c',         # Red
            'C++': '#e67e22',       # Orange
            'Go': '#3498db',        # Blue
            'Java': '#f39c12',      # Yellow-orange
            'Python': '#2ecc71',    # Green
            'JavaScript': '#f1c40f', # Yellow
            'TypeScript': '#9b59b6'  # Purple
        }

        # Fixed language order (consistent across all subplots)
        lang_order_fixed = ['JavaScript', 'C', 'Python', 'C++', 'TypeScript', 'Go', 'Java']

        # First pass: collect all data to find global y-axis limits
        all_data_by_metric = {}
        for idx, metric in enumerate(self.metrics):
            data_for_plot = []
            for key, records in self.valid_improvements.items():
                model, prompt, language, rec_metric = key
                if rec_metric != metric or not language or language == 'unknown':
                    continue
                display_lang = self.get_display_language(language)
                for record in records:
                    data_for_plot.append({
                        'Language': display_lang,
                        'Improvement %': record['improvement_percentage']
                    })
            all_data_by_metric[metric] = data_for_plot

        # Find global min and max across all metrics for consistent scales
        all_values = []
        for data in all_data_by_metric.values():
            if data:
                df_temp = pd.DataFrame(data)
                all_values.extend(df_temp['Improvement %'].values)

        if all_values:
            global_min = min(all_values)
            global_max = max(all_values)
            # Add padding
            y_range = global_max - global_min
            y_min = global_min - 0.1 * y_range
            y_max = global_max + 0.1 * y_range

        # Second pass: create plots with consistent order and scales
        for idx, metric in enumerate(self.metrics):
            ax = axes[idx]
            data_for_plot = all_data_by_metric[metric]

            if data_for_plot:
                df = pd.DataFrame(data_for_plot)

                # Filter to only include languages that have data
                lang_order = [lang for lang in lang_order_fixed if lang in df['Language'].unique()]

                # Create box plot with custom colors
                bp = ax.boxplot(
                    [df[df['Language'] == lang]['Improvement %'].values for lang in lang_order],
                    labels=lang_order,
                    patch_artist=True,
                    showmeans=True,
                    meanline=True,
                    meanprops=dict(linestyle='--', linewidth=1.5, color='darkred'),
                    flierprops=dict(marker='o', markerfacecolor='gray', markersize=3, alpha=0.3)
                )

                # Apply colors
                for patch, lang in zip(bp['boxes'], lang_order):
                    color = language_colors.get(lang, '#95a5a6')
                    patch.set_facecolor(color)
                    patch.set_alpha(0.7)

                # Set consistent y-axis limits so 0 is at the same height
                ax.set_ylim(y_min, y_max)

                ax.axhline(y=0, color='black', linestyle='-', linewidth=2, alpha=0.8)
                ax.set_title(f'{metric.replace("_", " ").title()}', fontsize=14, fontweight='bold')
                ax.set_xlabel('Programming Language', fontsize=12)
                ax.set_ylabel('Improvement %\n(+ = better)', fontsize=12)
                ax.tick_params(axis='x', rotation=45)
                ax.grid(True, alpha=0.3)

        plt.tight_layout()
        output_file = self.output_dir / 'fig_improvements_by_language.png'
        plt.savefig(output_file, dpi=300, bbox_inches='tight')
        plt.close()
        print(f"Saved {output_file}")

    def _plot_improvements_by_model(self):
        """Create box plots for improvements by model"""
        fig, axes = plt.subplots(2, 2, figsize=(15, 10))
        axes = axes.flatten()

        for idx, metric in enumerate(self.metrics):
            ax = axes[idx]

            # Collect data
            data_for_plot = []

            for key, records in self.valid_improvements.items():
                model, prompt, language, rec_metric = key
                if rec_metric != metric:
                    continue

                for record in records:
                    data_for_plot.append({
                        'Model': model,
                        'Improvement %': record['improvement_percentage']
                    })

            if data_for_plot:
                df = pd.DataFrame(data_for_plot)

                # Define model-specific base colors
                model_colors = {
                    'openAI': '#1976d2',   # Dark blue
                    'gemini': '#2e7d32',   # Dark green
                    'claude': '#6a1b9a'    # Dark purple
                }

                # Order models
                model_order = ['openAI', 'gemini', 'claude']

                # Create box plot with custom colors
                bp = ax.boxplot(
                    [df[df['Model'] == model]['Improvement %'].values for model in model_order],
                    labels=model_order,
                    patch_artist=True,
                    showmeans=True,
                    meanline=True,
                    meanprops=dict(linestyle='--', linewidth=1.5, color='darkred'),
                    flierprops=dict(marker='o', markerfacecolor='gray', markersize=3, alpha=0.3)
                )

                # Apply colors to each model's box
                for patch, model in zip(bp['boxes'], model_order):
                    color = model_colors.get(model, '#95a5a6')
                    patch.set_facecolor(color)
                    patch.set_alpha(0.7)

                ax.axhline(y=0, color='red', linestyle='--', linewidth=1, alpha=0.7)
                ax.set_title(f'{metric.replace("_", " ").title()}')
                ax.set_xlabel('LLM Model')
                ax.set_ylabel('Improvement %\n(+ = better)')
                ax.grid(True, alpha=0.3)

        plt.tight_layout()
        output_file = self.output_dir / 'fig_improvements_by_model.png'
        plt.savefig(output_file, dpi=300, bbox_inches='tight')
        plt.close()
        print(f"Saved {output_file}")

    def _plot_improvements_by_prompt(self):
        """Create box plots for improvements by prompt version"""
        fig, axes = plt.subplots(2, 2, figsize=(15, 10))
        axes = axes.flatten()

        # ENHANCED FOR FIG 4.7: Collect all data first to calculate global y-limits for CPU and RAM
        metric_data = {metric: [] for metric in self.metrics}

        for metric in self.metrics:
            for key, records in self.valid_improvements.items():
                model, prompt, language, rec_metric = key
                if rec_metric != metric:
                    continue

                for record in records:
                    metric_data[metric].append(record['improvement_percentage'])

        # Calculate synchronized y-limits for CPU_usage and RAM_usage to ensure 0 is at same height
        cpu_data = metric_data.get('CPU_usage', [])
        ram_data = metric_data.get('RAM_usage', [])

        if cpu_data and ram_data:
            # Combine CPU and RAM data to find global range
            combined_data = cpu_data + ram_data
            y_min_combined = np.percentile(combined_data, 1)
            y_max_combined = np.percentile(combined_data, 99)

            # Force include 0
            y_min_combined = min(y_min_combined, 0)
            y_max_combined = max(y_max_combined, 0)

            # Add padding
            padding = (y_max_combined - y_min_combined) * 0.1
            global_ylim_cpu_ram = (y_min_combined - padding, y_max_combined + padding)
        else:
            global_ylim_cpu_ram = (-50, 50)

        for idx, metric in enumerate(self.metrics):
            ax = axes[idx]

            # Collect data
            data_for_plot = []

            for key, records in self.valid_improvements.items():
                model, prompt, language, rec_metric = key
                if rec_metric != metric:
                    continue

                for record in records:
                    data_for_plot.append({
                        'Prompt': prompt,
                        'Improvement %': record['improvement_percentage']
                    })

            if data_for_plot:
                df = pd.DataFrame(data_for_plot)

                # Order prompts
                prompt_order = ['prompt_v1', 'prompt_v2', 'prompt_v3', 'prompt_v4']

                # Define Blues gradient for prompt versions (light to dark)
                prompt_colors = {
                    'prompt_v1': '#e3f2fd',  # Lightest blue
                    'prompt_v2': '#90caf9',  # Light blue
                    'prompt_v3': '#42a5f5',  # Medium blue
                    'prompt_v4': '#1976d2'   # Dark blue
                }

                # Create box plot with custom colors
                bp = ax.boxplot(
                    [df[df['Prompt'] == prompt]['Improvement %'].values for prompt in prompt_order],
                    labels=['v1', 'v2', 'v3', 'v4'],
                    patch_artist=True,
                    showmeans=True,
                    meanline=True,
                    meanprops=dict(linestyle='--', linewidth=1.5, color='darkred'),
                    flierprops=dict(marker='o', markerfacecolor='gray', markersize=3, alpha=0.3)
                )

                # Apply gradient colors to each prompt version's box
                for patch, prompt in zip(bp['boxes'], prompt_order):
                    color = prompt_colors.get(prompt, '#95a5a6')
                    patch.set_facecolor(color)
                    patch.set_alpha(0.7)

                # ENHANCED FOR FIG 4.7: Apply synchronized y-limits for CPU and RAM
                if metric in ['CPU_usage', 'RAM_usage']:
                    ax.set_ylim(global_ylim_cpu_ram)

                # Make the y=0 line more prominent
                ax.axhline(y=0, color='black', linestyle='-', linewidth=2, alpha=0.8, zorder=10)
                ax.set_title(f'{metric.replace("_", " ").title()}', fontweight='bold')
                ax.set_xlabel('Prompt Version', fontweight='bold')
                ax.set_ylabel('Improvement %\n(+ = better)', fontweight='bold')
                ax.grid(True, alpha=0.3)

        plt.tight_layout()
        output_file = self.output_dir / 'fig_improvements_by_prompt.png'
        plt.savefig(output_file, dpi=300, bbox_inches='tight')
        plt.close()
        print(f"Saved {output_file}")

    def _plot_improvements_by_model_prompt(self):
        """Create heatmap for improvements by model + prompt version"""
        fig, axes = plt.subplots(2, 2, figsize=(18, 12))
        axes = axes.flatten()

        for idx, metric in enumerate(self.metrics):
            ax = axes[idx]

            # Collect data
            combo_data = defaultdict(list)

            for key, records in self.valid_improvements.items():
                model, prompt, language, rec_metric = key
                if rec_metric != metric:
                    continue

                for record in records:
                    combo_data[(model, prompt)].append(record['improvement_percentage'])

            # Create matrix for heatmap
            models_list = ['openAI', 'gemini', 'claude']
            prompts_list = ['prompt_v1', 'prompt_v2', 'prompt_v3', 'prompt_v4']

            matrix = np.zeros((len(models_list), len(prompts_list)))

            for i, model in enumerate(models_list):
                for j, prompt in enumerate(prompts_list):
                    key = (model, prompt)
                    if key in combo_data:
                        matrix[i, j] = np.mean(combo_data[key])
                    else:
                        matrix[i, j] = np.nan

            # Create heatmap
            # NEW SEMANTIC: positive=green (good), negative=red (bad) → use RdYlGn (NOT _r)
            sns.heatmap(matrix, annot=True, fmt='.2f', cmap='RdYlGn',
                       xticklabels=[p.replace('prompt_', '') for p in prompts_list],  # FIX: vv1→v1
                       yticklabels=models_list, ax=ax, center=0,
                       cbar_kws={'label': 'Mean Improvement %\n(+ = better)'})
            ax.set_title(f'{metric.replace("_", " ").title()}')
            ax.set_xlabel('Prompt Version')
            ax.set_ylabel('LLM Model')

        plt.tight_layout()
        output_file = self.output_dir / 'fig_heatmap_model_prompt.png'
        plt.savefig(output_file, dpi=300, bbox_inches='tight')
        plt.close()
        print(f"Saved {output_file}")

    def _plot_improvements_by_model_prompt_boxplots(self):
        """
        Create box plots for all model + prompt combinations (4 subplots, one per metric)

        Features:
        - Blues gradient for prompt versions BUT different shades per model
        - Consistent y-axis scale (0 at same height across all subplots)
        - Clear model separations
        """
        fig, axes = plt.subplots(2, 2, figsize=(20, 12))
        axes = axes.flatten()

        # Define Blues gradient for each MODEL (different base colors)
        # OpenAI: Light Blues, Gemini: Medium Blues/Greens, Claude: Dark Blues/Purples
        model_gradients = {
            'openAI': {
                'v1': '#e3f2fd',  # Very light blue
                'v2': '#90caf9',  # Light blue
                'v3': '#42a5f5',  # Medium blue
                'v4': '#1976d2'   # Blue
            },
            'gemini': {
                'v1': '#e8f5e9',  # Very light green
                'v2': '#81c784',  # Light green
                'v3': '#4caf50',  # Green
                'v4': '#2e7d32'   # Dark green
            },
            'claude': {
                'v1': '#f3e5f5',  # Very light purple
                'v2': '#ba68c8',  # Light purple
                'v3': '#9c27b0',  # Purple
                'v4': '#6a1b9a'   # Dark purple
            }
        }

        # First pass: collect all data to determine global y-axis limits
        all_improvements = []
        metric_data = {metric: [] for metric in self.metrics}

        for key, records in self.valid_improvements.items():
            model, prompt, language, rec_metric = key
            if rec_metric in self.metrics:
                for record in records:
                    all_improvements.append(record['improvement_percentage'])
                    metric_data[rec_metric].append(record['improvement_percentage'])

        # Calculate global y-limits to ensure 0 is at the same height
        if all_improvements:
            import numpy as np
            y_min = np.percentile(all_improvements, 1)
            y_max = np.percentile(all_improvements, 99)

            # Force include 0
            y_min = min(y_min, 0)
            y_max = max(y_max, 0)

            # Add padding
            padding = (y_max - y_min) * 0.1
            global_ylim = (y_min - padding, y_max + padding)
        else:
            global_ylim = (-50, 50)

        for idx, metric in enumerate(self.metrics):
            ax = axes[idx]

            # Collect data for all model+prompt combinations
            data_for_plot = []

            for key, records in self.valid_improvements.items():
                model, prompt, language, rec_metric = key
                if rec_metric != metric:
                    continue

                # Create combination label like "openAI_v1", "claude_v2", etc.
                prompt_short = prompt.replace('prompt_', '')
                combo_label = f"{model}_{prompt_short}"

                for record in records:
                    data_for_plot.append({
                        'Model_Prompt': combo_label,
                        'Model': model,
                        'Prompt': prompt_short,
                        'Improvement %': record['improvement_percentage']
                    })

            if data_for_plot:
                df = pd.DataFrame(data_for_plot)

                # Create ordered list of combinations: openAI_v1-v4, gemini_v1-v4, claude_v1-v4
                combo_order = []
                for model in ['openAI', 'gemini', 'claude']:
                    for v in ['v1', 'v2', 'v3', 'v4']:
                        combo_order.append(f"{model}_{v}")

                # Filter to only existing combinations
                existing_combos = [c for c in combo_order if c in df['Model_Prompt'].unique()]

                # Create color palette with model-specific gradients
                palette = []
                for combo in existing_combos:
                    model_name = combo.split('_')[0]  # Extract openAI, gemini, claude
                    prompt_version = combo.split('_')[1]  # Extract v1, v2, v3, v4
                    color = model_gradients.get(model_name, {}).get(prompt_version, '#3498db')
                    palette.append(color)

                # Create box plot with custom palette
                bp = ax.boxplot(
                    [df[df['Model_Prompt'] == combo]['Improvement %'].values for combo in existing_combos],
                    labels=existing_combos,
                    patch_artist=True,
                    showmeans=True,
                    meanline=True,
                    meanprops=dict(linestyle='--', linewidth=1.5, color='darkred'),
                    flierprops=dict(marker='o', markerfacecolor='gray', markersize=3, alpha=0.3)
                )

                # Apply Blues gradient colors
                for patch, color in zip(bp['boxes'], palette):
                    patch.set_facecolor(color)
                    patch.set_alpha(0.8)

                # Add horizontal line at y=0
                ax.axhline(y=0, color='black', linestyle='-', linewidth=2, alpha=0.8, zorder=10)

                # Apply global y-limits
                ax.set_ylim(global_ylim)

                # Styling
                ax.set_title(f'{metric.replace("_", " ").title()}', fontsize=14, fontweight='bold')
                ax.set_xlabel('Model + Prompt Version', fontsize=12)
                ax.set_ylabel('Improvement %\n(+ = better)', fontsize=12)  # UPDATED SEMANTIC

                # Rotate x-axis labels
                ax.tick_params(axis='x', rotation=45)

                # Add vertical lines to separate models
                ax.axvline(x=4.5, color='gray', linestyle=':', linewidth=1.5, alpha=0.7)
                ax.axvline(x=8.5, color='gray', linestyle=':', linewidth=1.5, alpha=0.7)

                # Add model labels at the top
                y_pos = global_ylim[1] * 0.95
                ax.text(2.5, y_pos, 'OpenAI',
                       ha='center', fontsize=11, fontweight='bold', color='darkblue',
                       bbox=dict(boxstyle='round,pad=0.3', facecolor='white', alpha=0.7))
                ax.text(6.5, y_pos, 'Gemini',
                       ha='center', fontsize=11, fontweight='bold', color='darkgreen',
                       bbox=dict(boxstyle='round,pad=0.3', facecolor='white', alpha=0.7))
                ax.text(10.5, y_pos, 'Claude',
                       ha='center', fontsize=11, fontweight='bold', color='darkred',
                       bbox=dict(boxstyle='round,pad=0.3', facecolor='white', alpha=0.7))

                ax.grid(True, alpha=0.3, axis='y')

        plt.tight_layout()
        output_file = self.output_dir / 'fig_model_prompt_combinations_boxplots.png'
        plt.savefig(output_file, dpi=300, bbox_inches='tight')
        plt.close()
        print(f"Saved {output_file}")

    def _plot_invalid_and_outliers(self):
        """Create bar plots for invalid improvements and outliers"""
        fig, axes = plt.subplots(2, 2, figsize=(15, 12))

        # Invalid by model
        invalid_by_model = defaultdict(int)
        for key, records in self.invalid_improvements.items():
            model, prompt, language, metric = key
            invalid_by_model[model] += len(records)

        ax = axes[0, 0]
        models = list(invalid_by_model.keys())
        counts = list(invalid_by_model.values())
        ax.bar(models, counts, color='coral')
        ax.set_title('Invalid Improvements by Model')
        ax.set_xlabel('Model')
        ax.set_ylabel('Count')
        ax.grid(True, alpha=0.3)

        # Invalid by prompt
        invalid_by_prompt = defaultdict(int)
        for key, records in self.invalid_improvements.items():
            model, prompt, language, metric = key
            invalid_by_prompt[prompt] += len(records)

        ax = axes[0, 1]
        prompts = sorted(invalid_by_prompt.keys())
        counts = [invalid_by_prompt[p] for p in prompts]
        ax.bar([p.replace('prompt_', 'v') for p in prompts], counts, color='coral')
        ax.set_title('Invalid Improvements by Prompt Version')
        ax.set_xlabel('Prompt Version')
        ax.set_ylabel('Count')
        ax.grid(True, alpha=0.3)

        # Outliers by model
        outliers_by_model = defaultdict(int)
        for key, records in self.outliers.items():
            model, prompt, language, metric = key
            outliers_by_model[model] += len(records)

        ax = axes[1, 0]
        models = list(outliers_by_model.keys())
        counts = list(outliers_by_model.values())
        ax.bar(models, counts, color='steelblue')
        ax.set_title('Outliers by Model')
        ax.set_xlabel('Model')
        ax.set_ylabel('Count')
        ax.grid(True, alpha=0.3)

        # Outliers by prompt
        outliers_by_prompt = defaultdict(int)
        for key, records in self.outliers.items():
            model, prompt, language, metric = key
            outliers_by_prompt[prompt] += len(records)

        ax = axes[1, 1]
        prompts = sorted(outliers_by_prompt.keys())
        counts = [outliers_by_prompt[p] for p in prompts]
        ax.bar([p.replace('prompt_', 'v') for p in prompts], counts, color='steelblue')
        ax.set_title('Outliers by Prompt Version')
        ax.set_xlabel('Prompt Version')
        ax.set_ylabel('Count')
        ax.grid(True, alpha=0.3)

        plt.tight_layout()
        output_file = self.output_dir / 'fig_invalid_and_outliers.png'
        plt.savefig(output_file, dpi=300, bbox_inches='tight')
        plt.close()
        print(f"Saved {output_file}")

    def _plot_success_rate(self):
        """Create bar plot for success rates"""
        # Count total attempts vs valid executions
        total_attempts = defaultdict(int)
        valid_executions = defaultdict(int)

        for record in self.all_data:
            key = (record['model'], record['prompt'])
            total_attempts[key] += 1

            if record['label'] != 'invalid':
                valid_executions[key] += 1

        # Prepare data
        data_for_plot = []
        for key in total_attempts:
            model, prompt = key
            total = total_attempts[key]
            valid = valid_executions[key]
            rate = (valid / total * 100) if total > 0 else 0

            data_for_plot.append({
                'Model': model,
                'Prompt': prompt.replace('prompt_', 'v'),
                'Success Rate %': rate
            })

        df = pd.DataFrame(data_for_plot)

        # Create grouped bar plot
        fig, ax = plt.subplots(figsize=(12, 6))

        # Pivot for grouped bars
        pivot_df = df.pivot(index='Prompt', columns='Model', values='Success Rate %')
        pivot_df.plot(kind='bar', ax=ax, width=0.8)

        ax.set_title('Success Rate by Model and Prompt Version')
        ax.set_xlabel('Prompt Version')
        ax.set_ylabel('Success Rate (%)')
        ax.set_ylim([0, 105])
        ax.legend(title='Model')
        ax.grid(True, alpha=0.3)
        plt.xticks(rotation=0)

        plt.tight_layout()
        output_file = self.output_dir / 'fig_success_rate.png'
        plt.savefig(output_file, dpi=300, bbox_inches='tight')
        plt.close()
        print(f"Saved {output_file}")

    def _plot_distribution_by_metric(self):
        """Create distribution plots for each metric"""
        fig, axes = plt.subplots(2, 2, figsize=(18, 10))
        axes = axes.flatten()

        for idx, metric in enumerate(self.metrics):
            ax = axes[idx]

            # Collect all valid improvements for this metric
            values = []
            for key, records in self.valid_improvements.items():
                model, prompt, language, rec_metric = key
                if rec_metric != metric:
                    continue

                for record in records:
                    values.append(record['improvement_percentage'])

            if values:
                # Create histogram with KDE
                ax.hist(values, bins=50, alpha=0.6, color='skyblue', edgecolor='black')
                ax.axvline(x=0, color='red', linestyle='--', linewidth=2, label='No change')
                ax.axvline(x=np.median(values), color='green', linestyle='-', linewidth=2, label=f'Median: {np.median(values):.2f}%')

                ax.set_title(f'{metric.replace("_", " ").title()} Distribution')
                ax.set_xlabel('Improvement % (+ = better)')
                ax.set_ylabel('Frequency')
                ax.legend()
                ax.grid(True, alpha=0.3)

        plt.tight_layout()
        output_file = self.output_dir / 'fig_improvement_distributions.png'
        plt.savefig(output_file, dpi=300, bbox_inches='tight')
        plt.close()
        print(f"Saved {output_file}")

    def run_full_analysis(self):
        """Run complete analysis pipeline"""
        print("="*80)
        print("ENERGY IMPROVEMENTS ANALYSIS")
        print("="*80)

        # Load data
        self.load_all_data()

        # Run all analyses
        self.analyze_by_language()
        self.analyze_by_model()
        self.analyze_by_prompt()
        self.analyze_by_model_and_prompt()
        self.analyze_invalid_improvements()
        self.analyze_outliers()
        self.analyze_success_rate()

        # Create visualizations
        self.create_visualizations()

        print("\n" + "="*80)
        print("ANALYSIS COMPLETE")
        print("="*80)
        print(f"\nOutput directory: {self.output_dir}")
        print("\nGenerated files:")
        print("  Statistics JSON files:")
        print("    - stats_by_language.json")
        print("    - stats_by_model.json")
        print("    - stats_by_prompt.json")
        print("    - stats_by_model_and_prompt.json")
        print("    - stats_invalid_improvements.json")
        print("    - stats_outliers.json")
        print("    - stats_success_rate.json")
        print("\n  Visualization PNG files:")
        print("    - fig_improvements_by_language.png")
        print("    - fig_improvements_by_model.png")
        print("    - fig_improvements_by_prompt.png")
        print("    - fig_heatmap_model_prompt.png")
        print("    - fig_model_prompt_combinations_boxplots.png")
        print("    - fig_invalid_and_outliers.png")
        print("    - fig_success_rate.png")
        print("    - fig_improvement_distributions.png")


def main():
    """Main entry point"""
    # Data directory
    data_dir = Path(__file__).parent / 'clusters_improvements_data'

    if not data_dir.exists():
        print(f"ERROR: Data directory not found: {data_dir}")
        return

    # Create analyzer and run
    analyzer = EnergyImprovementsAnalyzer(data_dir)
    analyzer.run_full_analysis()


if __name__ == '__main__':
    main()
