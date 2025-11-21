"""
Dataset Statistics Module
Generates statistics and visualizations for the thesis dataset.
"""

import logging
from pathlib import Path
from typing import Dict, List
from collections import Counter

import sys
sys.path.append(str(Path(__file__).parent.parent))

from utility_dir.general_utils import read_json, get_cluster_names, CodeEntry
from utility_dir.utility_paths import CLUSTERS_DIR_FILEPATH, OUTPUT_DIR_FILEPATH

logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s'
)
logger = logging.getLogger(__name__)


class DatasetStatisticsCollector:
    """Collects statistics from the dataset clusters."""
    
    def __init__(self, clusters_dir: Path, execution_outputs_dir: Path = None):
        self.clusters_dir = clusters_dir
        self.execution_outputs_dir = execution_outputs_dir or OUTPUT_DIR_FILEPATH
        self.cluster_names = get_cluster_names(clusters_dir)
        self.statistics = {
            'total_clusters': 0,
            'total_entries': 0,
            'entries_by_language': Counter(),
            'entries_by_cluster': {},
            'clusters_by_language': Counter()
        }
        self.passing_entries = set()  # Set of entry IDs with 100% pass rate
    
    def collect_statistics(self) -> Dict:
        """
        Collects all statistics from cluster files.
        
        Returns:
            Dict containing all collected statistics
        """
        logger.info(f"Starting statistics collection for {len(self.cluster_names)} clusters")
        
        for cluster_name in self.cluster_names:
            cluster_file = self.clusters_dir / f"cluster_{cluster_name}.json"
            
            if not cluster_file.exists():
                logger.warning(f"Cluster file not found: {cluster_file}")
                continue
            
            try:
                cluster_data = read_json(cluster_file)
                self._process_cluster(cluster_name, cluster_data)
            except Exception as e:
                logger.error(f"Error processing cluster {cluster_name}: {e}")
                continue
        
        self.statistics['total_clusters'] = len(self.cluster_names)
        
        logger.info(f"Statistics collection completed: {self.statistics['total_entries']} total entries")
        return self.statistics
    
    def _normalize_language(self, language: str) -> str:
        """Normalize language names to handle case variations."""
        lang_map = {
            'java': 'Java',
            'javascript': 'JavaScript',
            'typescript': 'TypeScript',
            'python': 'Python',
            'c': 'C',
            'cpp': 'C++',
            'c++': 'C++',
            'go': 'Go'
        }
        return lang_map.get(language.lower(), language)
    
    def _process_cluster(self, cluster_name: str, cluster_data: Dict):
        """Process a single cluster and update statistics."""
        entries_count = 0
        languages_in_cluster = set()
        
        # Process each language section in the cluster
        for language_key, entries in cluster_data.items():
            if not isinstance(entries, list):
                continue
            
            for entry_data in entries:
                try:
                    entry = CodeEntry.from_dict(entry_data)
                    normalized_lang = self._normalize_language(entry.language)
                    self.statistics['entries_by_language'][normalized_lang] += 1
                    languages_in_cluster.add(normalized_lang)
                    entries_count += 1
                except Exception as e:
                    logger.debug(f"Error processing entry in {cluster_name}: {e}")
                    continue
        
        self.statistics['total_entries'] += entries_count
        self.statistics['entries_by_cluster'][cluster_name] = entries_count
        
        # Track which languages appear in this cluster
        for lang in languages_in_cluster:
            self.statistics['clusters_by_language'][lang] += 1
        
        logger.debug(f"Processed cluster '{cluster_name}': {entries_count} entries, "
                    f"languages: {languages_in_cluster}")
    
    def _load_passing_entries(self):
        """
        Load all entries that have 100% pass rate (pass all 5 base test runs).
        Populates self.passing_entries with entry IDs that pass all tests.
        """
        logger.info("Loading test results to identify entries with 100% pass rate...")

        # Dictionary to track pass count per entry
        # Format: {entry_id: {'total_runs': int, 'passed_runs': int}}
        entry_test_results = {}

        for cluster_name in self.cluster_names:
            # Load all 5 result files for this cluster
            for run_num in range(1, 6):  # runs 1 through 5
                result_file = self.execution_outputs_dir / f"{cluster_name}_results_{run_num}.json"

                if not result_file.exists():
                    logger.debug(f"Result file not found: {result_file}")
                    continue

                try:
                    result_data = read_json(result_file)

                    # Process results by language
                    if 'results' not in result_data:
                        continue

                    for language, entries in result_data['results'].items():
                        if not isinstance(entries, list):
                            continue

                        for entry in entries:
                            entry_id = entry.get('id')
                            regression_passed = entry.get('regressionTestPassed', False)

                            if not entry_id:
                                continue

                            # Initialize tracking for this entry
                            if entry_id not in entry_test_results:
                                entry_test_results[entry_id] = {
                                    'total_runs': 0,
                                    'passed_runs': 0
                                }

                            entry_test_results[entry_id]['total_runs'] += 1
                            if regression_passed:
                                entry_test_results[entry_id]['passed_runs'] += 1

                except Exception as e:
                    logger.warning(f"Error loading result file {result_file}: {e}")
                    continue

        # Identify entries with 100% pass rate (passed all available runs)
        for entry_id, results in entry_test_results.items():
            if results['total_runs'] > 0 and results['passed_runs'] == results['total_runs']:
                self.passing_entries.add(entry_id)

        logger.info(f"Found {len(self.passing_entries)} entries with 100% pass rate out of {len(entry_test_results)} total entries tested")

    def collect_statistics_100pass(self) -> Dict:
        """
        Collects statistics only for entries with 100% pass rate in base code.

        Returns:
            Dict containing statistics filtered for passing entries only
        """
        logger.info("Collecting statistics for entries with 100% pass rate...")

        # First, load the passing entries
        self._load_passing_entries()

        # Create filtered statistics structure
        filtered_stats = {
            'total_clusters': 0,
            'total_entries': 0,
            'entries_by_language': Counter(),
            'entries_by_cluster': {},
            'clusters_by_language': Counter(),
            'filter_applied': '100% pass rate'
        }

        clusters_with_passing_entries = set()

        # Process each cluster
        for cluster_name in self.cluster_names:
            cluster_file = self.clusters_dir / f"cluster_{cluster_name}.json"

            if not cluster_file.exists():
                logger.warning(f"Cluster file not found: {cluster_file}")
                continue

            try:
                cluster_data = read_json(cluster_file)
                entries_count = 0
                languages_in_cluster = set()

                # Process each language section in the cluster
                for language_key, entries in cluster_data.items():
                    if not isinstance(entries, list):
                        continue

                    for entry_data in entries:
                        try:
                            entry = CodeEntry.from_dict(entry_data)

                            # FILTER: Only count if this entry has 100% pass rate
                            if entry.id not in self.passing_entries:
                                continue

                            normalized_lang = self._normalize_language(entry.language)
                            filtered_stats['entries_by_language'][normalized_lang] += 1
                            languages_in_cluster.add(normalized_lang)
                            entries_count += 1

                        except Exception as e:
                            logger.debug(f"Error processing entry in {cluster_name}: {e}")
                            continue

                if entries_count > 0:
                    filtered_stats['total_entries'] += entries_count
                    filtered_stats['entries_by_cluster'][cluster_name] = entries_count
                    clusters_with_passing_entries.add(cluster_name)

                    # Track which languages appear in this cluster
                    for lang in languages_in_cluster:
                        filtered_stats['clusters_by_language'][lang] += 1

            except Exception as e:
                logger.error(f"Error processing cluster {cluster_name}: {e}")
                continue

        filtered_stats['total_clusters'] = len(clusters_with_passing_entries)

        logger.info(f"Statistics collection completed for 100% pass entries: {filtered_stats['total_entries']} entries in {filtered_stats['total_clusters']} clusters")
        return filtered_stats

    def get_summary(self) -> str:
        """Returns a formatted summary of the statistics."""
        summary_lines = [
            "\n" + "="*60,
            "DATASET STATISTICS SUMMARY",
            "="*60,
            f"\nTotal Clusters: {self.statistics['total_clusters']}",
            f"Total Entries: {self.statistics['total_entries']}",
            "\nEntries by Language:",
        ]

        # Sort languages by entry count (descending)
        sorted_languages = sorted(
            self.statistics['entries_by_language'].items(),
            key=lambda x: x[1],
            reverse=True
        )

        for language, count in sorted_languages:
            percentage = (count / self.statistics['total_entries'] * 100) if self.statistics['total_entries'] > 0 else 0
            summary_lines.append(f"  - {language}: {count} entries ({percentage:.1f}%)")

        summary_lines.append("="*60 + "\n")

        return "\n".join(summary_lines)


class DatasetStatisticsVisualizer:
    """Creates visualizations for dataset statistics."""
    
    def __init__(self, statistics: Dict, output_dir: Path):
        self.statistics = statistics
        self.output_dir = output_dir
        self.output_dir.mkdir(parents=True, exist_ok=True)
    
    def create_language_pie_chart(self) -> Path:
        """
        Creates a publication-quality pie chart showing the distribution of entries by language.
        Follows scientific publication standards (IEEE, ACM style).
        
        Returns:
            Path to the saved chart file
        """
        import matplotlib.pyplot as plt
        import matplotlib as mpl
        
        # Set publication-quality style
        mpl.rcParams['font.family'] = 'serif'
        mpl.rcParams['font.serif'] = ['Times New Roman', 'DejaVu Serif']
        mpl.rcParams['font.size'] = 11
        mpl.rcParams['axes.linewidth'] = 1.2
        
        # Prepare data
        languages = list(self.statistics['entries_by_language'].keys())
        counts = list(self.statistics['entries_by_language'].values())
        total_entries = self.statistics['total_entries']
        
        # Sort by count (descending)
        sorted_data = sorted(zip(languages, counts), key=lambda x: x[1], reverse=True)
        languages, counts = zip(*sorted_data) if sorted_data else ([], [])
        
        # Calculate percentages
        percentages = [(count / total_entries * 100) if total_entries > 0 else 0 
                      for count in counts]
        
        # Create figure with scientific publication size (single column: 3.5", double: 7.16")
        fig, ax = plt.subplots(figsize=(7.16, 5), dpi=300)
        
        # Define professional color palette (colorblind-friendly)
        # Based on ColorBrewer qualitative palette
        colors = [
            '#1f77b4',  # Blue
            '#ff7f0e',  # Orange
            '#2ca02c',  # Green
            '#d62728',  # Red
            '#9467bd',  # Purple
            '#8c564b',  # Brown
            '#e377c2',  # Pink
            '#7f7f7f',  # Gray
        ]
        
        # Create pie chart with clean styling
        wedges, texts, autotexts = ax.pie(
            counts,
            labels=languages,
            autopct=lambda pct: f'{pct:.1f}%' if pct > 3 else '',
            startangle=90,
            colors=colors[:len(languages)],
            textprops={'fontsize': 10, 'weight': 'normal'},
            pctdistance=0.82,
            wedgeprops={'linewidth': 0.8, 'edgecolor': 'white'}
        )
        
        # Style the labels (language names)
        for text in texts:
            text.set_fontsize(10)
            text.set_weight('normal')
        
        # Style the percentage texts
        for autotext in autotexts:
            autotext.set_color('white')
            autotext.set_fontsize(9)
            autotext.set_weight('bold')
        
        # Add title in scientific style
        plt.title(
            'Distribution of Code Entries by Programming Language',
            fontsize=12,
            weight='bold',
            pad=15,
            family='serif'
        )
        
        # Create clean table for detailed statistics
        table_data = []
        table_data.append(['Language', 'Entries', 'Percentage'])
        table_data.append(['─'*12, '─'*8, '─'*12])
        
        for lang, count, pct in zip(languages, counts, percentages):
            table_data.append([lang, f'{count:,}', f'{pct:.1f}%'])
        
        table_data.append(['─'*12, '─'*8, '─'*12])
        table_data.append(['Total', f'{total_entries:,}', '100.0%'])
        table_data.append(['', '', ''])
        table_data.append([f'Clusters: {self.statistics["total_clusters"]}', '', ''])
        
        # Create formatted table
        from matplotlib.table import Table
        
        # Position table to the right of the pie chart
        table_ax = fig.add_axes([0.72, 0.15, 0.25, 0.7])
        table_ax.axis('off')
        
        # Add text-based table (cleaner for publications)
        table_text = []
        col_widths = [12, 8, 10]
        
        for row in table_data:
            if len(row) == 3:
                formatted_row = f"{row[0]:<{col_widths[0]}} {row[1]:>{col_widths[1]}} {row[2]:>{col_widths[2]}}"
                table_text.append(formatted_row)
        
        table_ax.text(
            0.05, 0.95,
            '\n'.join(table_text),
            transform=table_ax.transAxes,
            fontsize=9,
            verticalalignment='top',
            family='monospace',
            bbox=dict(boxstyle='round,pad=0.8', 
                     facecolor='#f8f8f8', 
                     edgecolor='#cccccc',
                     linewidth=1)
        )
        
        # Equal aspect ratio ensures that pie is drawn as a circle
        ax.axis('equal')
        
        # Adjust layout to prevent label cutoff
        plt.subplots_adjust(left=0.05, right=0.70, top=0.92, bottom=0.05)
        
        # Save figure in multiple formats for publication
        base_path = self.output_dir / 'dataset_language_distribution'
        
        # PNG for general use (high DPI)
        png_path = base_path.with_suffix('.png')
        plt.savefig(png_path, dpi=300, bbox_inches='tight', 
                   facecolor='white', edgecolor='none')
        
        # PDF for LaTeX publications (vector format)
        pdf_path = base_path.with_suffix('.pdf')
        plt.savefig(pdf_path, format='pdf', bbox_inches='tight',
                   facecolor='white', edgecolor='none')
        
        # SVG for web and further editing (vector format)
        svg_path = base_path.with_suffix('.svg')
        plt.savefig(svg_path, format='svg', bbox_inches='tight',
                   facecolor='white', edgecolor='none')
        
        plt.close()
        
        logger.info(f"Charts saved to: {base_path}.[png|pdf|svg]")
        return png_path
    
    def create_language_pie_chart_100pass(self) -> Path:
        """
        Creates a publication-quality pie chart showing the distribution of entries by language
        for entries with 100% pass rate only.
        Identical styling to create_language_pie_chart but with filtered data.

        Returns:
            Path to the saved chart file
        """
        import matplotlib.pyplot as plt
        import matplotlib as mpl

        # Set publication-quality style
        mpl.rcParams['font.family'] = 'serif'
        mpl.rcParams['font.serif'] = ['Times New Roman', 'DejaVu Serif']
        mpl.rcParams['font.size'] = 11
        mpl.rcParams['axes.linewidth'] = 1.2

        # Prepare data
        languages = list(self.statistics['entries_by_language'].keys())
        counts = list(self.statistics['entries_by_language'].values())
        total_entries = self.statistics['total_entries']

        # Sort by count (descending)
        sorted_data = sorted(zip(languages, counts), key=lambda x: x[1], reverse=True)
        languages, counts = zip(*sorted_data) if sorted_data else ([], [])

        # Calculate percentages
        percentages = [(count / total_entries * 100) if total_entries > 0 else 0
                      for count in counts]

        # Create figure with larger size to prevent label cutoff
        fig, ax = plt.subplots(figsize=(9, 6.5), dpi=300)

        # Define professional color palette (colorblind-friendly)
        # Based on ColorBrewer qualitative palette
        colors = [
            '#1f77b4',  # Blue
            '#ff7f0e',  # Orange
            '#2ca02c',  # Green
            '#d62728',  # Red
            '#9467bd',  # Purple
            '#8c564b',  # Brown
            '#e377c2',  # Pink
            '#7f7f7f',  # Gray
        ]

        # Create pie chart with clean styling
        # Rotated startangle to position JavaScript label away from the table
        wedges, texts, autotexts = ax.pie(
            counts,
            labels=languages,
            autopct=lambda pct: f'{pct:.1f}%' if pct > 3 else '',
            startangle=135,  # Adjusted to move C/C++ labels away from title
            colors=colors[:len(languages)],
            textprops={'fontsize': 10, 'weight': 'normal'},
            pctdistance=0.82,
            labeldistance=1.12,  # Reduced to bring labels closer to pie
            wedgeprops={'linewidth': 0.8, 'edgecolor': 'white'}
        )

        # Style the labels (language names)
        for text in texts:
            text.set_fontsize(10)
            text.set_weight('normal')

        # Style the percentage texts
        for autotext in autotexts:
            autotext.set_color('white')
            autotext.set_fontsize(9)
            autotext.set_weight('bold')

        # Add title in scientific style with filter info (increased padding)
        plt.title(
            'Distribution of Code Entries by Programming Language\n(Entries with 100% Pass Rate Only)',
            fontsize=12,
            weight='bold',
            pad=25,  # Increased from 15 to avoid overlap with C/C++ labels
            family='serif'
        )

        # Create clean table for detailed statistics
        table_data = []
        table_data.append(['Language', 'Entries', 'Percentage'])
        table_data.append(['─'*12, '─'*8, '─'*12])

        for lang, count, pct in zip(languages, counts, percentages):
            table_data.append([lang, f'{count:,}', f'{pct:.1f}%'])

        table_data.append(['─'*12, '─'*8, '─'*12])
        table_data.append(['Total', f'{total_entries:,}', '100.0%'])
        table_data.append(['', '', ''])
        table_data.append([f'Clusters: {self.statistics["total_clusters"]}', '', ''])
        table_data.append(['Filter: 100% pass', '', ''])

        # Create formatted table
        from matplotlib.table import Table

        # Position table further to the right to avoid overlap
        table_ax = fig.add_axes([0.76, 0.15, 0.22, 0.7])
        table_ax.axis('off')

        # Add text-based table (cleaner for publications)
        table_text = []
        col_widths = [12, 8, 10]

        for row in table_data:
            if len(row) == 3:
                formatted_row = f"{row[0]:<{col_widths[0]}} {row[1]:>{col_widths[1]}} {row[2]:>{col_widths[2]}}"
                table_text.append(formatted_row)

        table_ax.text(
            0.05, 0.95,
            '\n'.join(table_text),
            transform=table_ax.transAxes,
            fontsize=9,
            verticalalignment='top',
            family='monospace',
            bbox=dict(boxstyle='round,pad=0.8',
                     facecolor='#f8f8f8',
                     edgecolor='#cccccc',
                     linewidth=1)
        )

        # Equal aspect ratio ensures that pie is drawn as a circle
        ax.axis('equal')

        # Adjust layout to give more space for pie labels on the right
        plt.subplots_adjust(left=0.0, right=0.74, top=0.92, bottom=0.05)

        # Save figure in multiple formats for publication
        base_path = self.output_dir / 'dataset_language_distribution_100pass'

        # PNG for general use (high DPI)
        png_path = base_path.with_suffix('.png')
        plt.savefig(png_path, dpi=300, bbox_inches='tight',
                   facecolor='white', edgecolor='none')

        # PDF for LaTeX publications (vector format)
        pdf_path = base_path.with_suffix('.pdf')
        plt.savefig(pdf_path, format='pdf', bbox_inches='tight',
                   facecolor='white', edgecolor='none')

        # SVG for web and further editing (vector format)
        svg_path = base_path.with_suffix('.svg')
        plt.savefig(svg_path, format='svg', bbox_inches='tight',
                   facecolor='white', edgecolor='none')

        plt.close()

        logger.info(f"100% pass rate charts saved to: {base_path}.[png|pdf|svg]")
        return png_path

    def create_all_visualizations(self) -> List[Path]:
        """
        Creates all visualization charts.

        Returns:
            List of paths to saved chart files
        """
        logger.info("Creating visualizations...")

        charts = []

        # Create pie chart
        try:
            pie_chart_path = self.create_language_pie_chart()
            charts.append(pie_chart_path)
        except Exception as e:
            logger.error(f"Error creating pie chart: {e}")

        logger.info(f"Created {len(charts)} visualization(s)")
        return charts


def main():
    """Main execution function."""
    logger.info("Starting Dataset Statistics Module")

    # Create output directory for stats
    stats_output_dir = Path(__file__).parent / 'reports'
    stats_output_dir.mkdir(exist_ok=True)

    # Collect statistics for ALL entries
    collector = DatasetStatisticsCollector(CLUSTERS_DIR_FILEPATH)
    statistics = collector.collect_statistics()

    # Print summary
    print(collector.get_summary())

    # Create visualizations for all entries
    visualizer = DatasetStatisticsVisualizer(statistics, stats_output_dir)
    _chart_paths = visualizer.create_all_visualizations()

    # Save statistics to JSON
    from utility_dir.general_utils import write_json
    stats_json_path = stats_output_dir / 'dataset_statistics.json'
    write_json(stats_json_path, statistics)
    logger.info(f"Statistics saved to: {stats_json_path}")

    # ========== NEW: Generate statistics and charts for 100% pass rate entries ==========
    logger.info("\n" + "="*60)
    logger.info("Generating statistics for entries with 100% pass rate...")
    logger.info("="*60)

    # Collect statistics for 100% pass entries
    statistics_100pass = collector.collect_statistics_100pass()

    # Print summary for 100% pass entries
    print("\n" + "="*60)
    print("DATASET STATISTICS SUMMARY (100% Pass Rate Only)")
    print("="*60)
    print(f"\nTotal Clusters: {statistics_100pass['total_clusters']}")
    print(f"Total Entries: {statistics_100pass['total_entries']}")
    print("\nEntries by Language:")

    sorted_languages_100pass = sorted(
        statistics_100pass['entries_by_language'].items(),
        key=lambda x: x[1],
        reverse=True
    )

    for language, count in sorted_languages_100pass:
        percentage = (count / statistics_100pass['total_entries'] * 100) if statistics_100pass['total_entries'] > 0 else 0
        print(f"  - {language}: {count} entries ({percentage:.1f}%)")

    print("="*60 + "\n")

    # Create visualization for 100% pass entries
    visualizer_100pass = DatasetStatisticsVisualizer(statistics_100pass, stats_output_dir)
    try:
        chart_100pass_path = visualizer_100pass.create_language_pie_chart_100pass()
        logger.info(f"Created 100% pass rate chart: {chart_100pass_path}")
    except Exception as e:
        logger.error(f"Error creating 100% pass rate chart: {e}")

    # Save 100% pass statistics to JSON
    stats_100pass_json_path = stats_output_dir / 'dataset_statistics_100pass.json'
    write_json(stats_100pass_json_path, statistics_100pass)
    logger.info(f"100% pass rate statistics saved to: {stats_100pass_json_path}")

    logger.info("\nDataset Statistics Module completed successfully")


if __name__ == "__main__":
    main()