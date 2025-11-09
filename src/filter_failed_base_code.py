"""
Script to filter C++ entries from clusters where base code fails unit tests.

This script:
1. Scans execution_outputs files for base code executions (test_type="base")
2. Identifies C++ entries where regressionTestPassed=false
3. Removes these entries from their respective cluster files
4. Does NOT delete the original dataset files
5. Generates a report of filtered entries

Usage:
    python filter_failed_base_code.py [--dry-run] [--language cpp]
"""

import json
import logging
from pathlib import Path
from typing import Dict, List, Set
from collections import defaultdict
import sys
import argparse

# Add parent directory to path for imports
sys.path.insert(0, str(Path(__file__).parent))

from utility_dir.general_utils import read_json, write_json
from utility_dir.utility_paths import CLUSTERS_DIR_FILEPATH, OUTPUT_DIR_FILEPATH

logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(levelname)s - %(message)s'
)
logger = logging.getLogger(__name__)


class BaseCodeFailureFilter:
    """Filters entries from clusters where base code fails unit tests."""

    def __init__(self, execution_outputs_dir: Path, clusters_dir: Path, target_language: str = "cpp"):
        self.execution_outputs_dir = execution_outputs_dir
        self.clusters_dir = clusters_dir
        self.target_language = target_language
        self.failed_entries = defaultdict(set)  # cluster_name -> set of entry_ids
        self.stats = {
            'total_executions_analyzed': 0,
            'base_executions_found': 0,
            'failed_entries_found': 0,
            'clusters_affected': 0,
            'entries_removed': 0
        }

    def analyze_execution_outputs(self) -> Dict[str, Set[str]]:
        """
        Scans execution output files to find entries where base code failed tests.

        Returns:
            Dict mapping cluster_name to set of failed entry_ids
        """
        logger.info(f"Scanning execution outputs in: {self.execution_outputs_dir}")

        execution_files = list(self.execution_outputs_dir.glob("*_results_*.json"))
        logger.info(f"Found {len(execution_files)} execution output files")

        for exec_file in execution_files:
            # Only process base code executions (files without _v1, _v2, etc.)
            if "_v1_" in exec_file.name or "_v2_" in exec_file.name or \
               "_v3_" in exec_file.name or "_v4_" in exec_file.name:
                continue

            self.stats['total_executions_analyzed'] += 1

            try:
                data = read_json(exec_file)

                # Verify it's a base code execution
                metadata = data.get('execution_metadata', {})
                test_type = metadata.get('test_type', '')

                if test_type != 'base':
                    continue

                self.stats['base_executions_found'] += 1

                # Extract cluster name from metadata or filename
                cluster_name = metadata.get('cluster', '')
                if not cluster_name:
                    # Try to extract from filename: {cluster}_results_{num}.json
                    cluster_name = exec_file.stem.replace('_results_' + exec_file.stem.split('_')[-1], '')

                cluster_name = cluster_name.replace('cluster_', '')

                # Analyze results
                results = data.get('results', {})

                # Check target language results
                if self.target_language in results:
                    for entry in results[self.target_language]:
                        entry_id = entry.get('id')
                        regression_passed = entry.get('regressionTestPassed', False)

                        # If base code failed regression test, mark for removal
                        if not regression_passed and entry_id:
                            self.failed_entries[cluster_name].add(entry_id)
                            self.stats['failed_entries_found'] += 1
                            logger.debug(f"Found failed entry: {entry_id} in cluster {cluster_name}")

            except Exception as e:
                logger.error(f"Error processing {exec_file.name}: {e}")
                continue

        self.stats['clusters_affected'] = len(self.failed_entries)

        logger.info(f"Analysis complete. Found {self.stats['failed_entries_found']} "
                   f"failed entries across {self.stats['clusters_affected']} clusters")

        return dict(self.failed_entries)

    def filter_clusters(self, dry_run: bool = False) -> Dict[str, int]:
        """
        Removes failed entries from cluster files.

        Args:
            dry_run: If True, only simulates the operation without modifying files

        Returns:
            Dict mapping cluster_name to number of entries removed
        """
        removed_per_cluster = {}

        logger.info(f"Starting cluster filtering (dry_run={dry_run})")

        for cluster_name, failed_ids in self.failed_entries.items():
            cluster_file = self.clusters_dir / f"cluster_{cluster_name}.json"

            if not cluster_file.exists():
                logger.warning(f"Cluster file not found: {cluster_file}")
                continue

            try:
                # Read cluster data
                cluster_data = read_json(cluster_file)

                # Filter entries from target language
                if self.target_language not in cluster_data:
                    logger.debug(f"Language {self.target_language} not found in cluster {cluster_name}")
                    continue

                original_entries = cluster_data[self.target_language]
                original_count = len(original_entries)

                # Filter out failed entries
                filtered_entries = [
                    entry for entry in original_entries
                    if entry.get('id') not in failed_ids
                ]

                entries_removed = original_count - len(filtered_entries)
                removed_per_cluster[cluster_name] = entries_removed
                self.stats['entries_removed'] += entries_removed

                if entries_removed > 0:
                    logger.info(f"Cluster '{cluster_name}': removing {entries_removed} "
                               f"failed entries ({len(filtered_entries)} remaining)")

                    if not dry_run:
                        # Update cluster data
                        cluster_data[self.target_language] = filtered_entries

                        # Write back to file
                        write_json(cluster_file, cluster_data)
                        logger.debug(f"Updated cluster file: {cluster_file}")

            except Exception as e:
                logger.error(f"Error filtering cluster {cluster_name}: {e}")
                continue

        return removed_per_cluster

    def generate_report(self, removed_per_cluster: Dict[str, int], output_file: Path):
        """
        Generates a detailed report of the filtering operation.

        Args:
            removed_per_cluster: Dict mapping cluster_name to entries removed
            output_file: Path to save the report
        """
        report = {
            'summary': {
                'language': self.target_language,
                'total_executions_analyzed': self.stats['total_executions_analyzed'],
                'base_executions_found': self.stats['base_executions_found'],
                'failed_entries_found': self.stats['failed_entries_found'],
                'clusters_affected': self.stats['clusters_affected'],
                'total_entries_removed': self.stats['entries_removed']
            },
            'clusters_modified': {},
            'failed_entries_by_cluster': {}
        }

        # Add details per cluster
        for cluster_name, failed_ids in self.failed_entries.items():
            report['failed_entries_by_cluster'][cluster_name] = {
                'failed_entry_ids': sorted(list(failed_ids)),
                'count': len(failed_ids),
                'removed': removed_per_cluster.get(cluster_name, 0)
            }

        # Sort clusters by number of removed entries
        report['clusters_modified'] = dict(
            sorted(removed_per_cluster.items(), key=lambda x: x[1], reverse=True)
        )

        # Write report
        write_json(output_file, report)
        logger.info(f"Report saved to: {output_file}")

        # Also create a human-readable markdown report
        md_file = output_file.with_suffix('.md')
        self._generate_markdown_report(report, md_file)

    def _generate_markdown_report(self, report: Dict, output_file: Path):
        """Generates a markdown version of the report."""
        lines = [
            f"# Base Code Failure Filter Report",
            f"",
            f"## Summary",
            f"",
            f"- **Language:** {report['summary']['language'].upper()}",
            f"- **Total Executions Analyzed:** {report['summary']['total_executions_analyzed']}",
            f"- **Base Executions Found:** {report['summary']['base_executions_found']}",
            f"- **Failed Entries Found:** {report['summary']['failed_entries_found']}",
            f"- **Clusters Affected:** {report['summary']['clusters_affected']}",
            f"- **Total Entries Removed:** {report['summary']['total_entries_removed']}",
            f"",
            f"## Clusters Modified",
            f"",
            f"| Cluster Name | Entries Removed |",
            f"|--------------|-----------------|"
        ]

        for cluster_name, count in report['clusters_modified'].items():
            lines.append(f"| {cluster_name} | {count} |")

        lines.extend([
            f"",
            f"## Detailed Failed Entries",
            f""
        ])

        for cluster_name, details in sorted(report['failed_entries_by_cluster'].items()):
            lines.extend([
                f"### Cluster: {cluster_name}",
                f"",
                f"- **Failed Entries:** {details['count']}",
                f"- **Removed:** {details['removed']}",
                f"",
                f"**Entry IDs:**",
                f""
            ])

            for entry_id in details['failed_entry_ids']:
                lines.append(f"- `{entry_id}`")

            lines.append("")

        output_file.write_text('\n'.join(lines))
        logger.info(f"Markdown report saved to: {output_file}")

    def print_stats(self):
        """Prints filtering statistics."""
        print("\n" + "=" * 70)
        print("BASE CODE FAILURE FILTER STATISTICS")
        print("=" * 70)
        print(f"Language:                     {self.target_language.upper()}")
        print(f"Total Executions Analyzed:    {self.stats['total_executions_analyzed']}")
        print(f"Base Executions Found:        {self.stats['base_executions_found']}")
        print(f"Failed Entries Found:         {self.stats['failed_entries_found']}")
        print(f"Clusters Affected:            {self.stats['clusters_affected']}")
        print(f"Total Entries Removed:        {self.stats['entries_removed']}")
        print("=" * 70 + "\n")


def main():
    """Main execution function."""
    parser = argparse.ArgumentParser(
        description="Filter entries from clusters where base code fails unit tests"
    )
    parser.add_argument(
        '--dry-run',
        action='store_true',
        help='Simulate the operation without modifying files'
    )
    parser.add_argument(
        '--language',
        type=str,
        default='cpp',
        help='Programming language to filter (default: cpp)'
    )
    parser.add_argument(
        '--output-report',
        type=str,
        default=None,
        help='Path for output report (default: src/metrics/base_code_filter_report.json)'
    )

    args = parser.parse_args()

    logger.info("Starting Base Code Failure Filter")
    logger.info(f"Target Language: {args.language.upper()}")
    logger.info(f"Dry Run: {args.dry_run}")

    # Initialize filter
    filter_tool = BaseCodeFailureFilter(
        execution_outputs_dir=OUTPUT_DIR_FILEPATH,
        clusters_dir=CLUSTERS_DIR_FILEPATH,
        target_language=args.language
    )

    # Step 1: Analyze execution outputs
    logger.info("\nStep 1: Analyzing execution outputs...")
    failed_entries = filter_tool.analyze_execution_outputs()

    if not failed_entries:
        logger.info(f"No failed {args.language.upper()} base code entries found. Nothing to filter.")
        return

    # Step 2: Filter clusters
    logger.info(f"\nStep 2: Filtering clusters...")
    removed_per_cluster = filter_tool.filter_clusters(dry_run=args.dry_run)

    # Step 3: Generate report
    if args.output_report:
        report_path = Path(args.output_report)
    else:
        report_path = Path(__file__).parent / 'metrics' / 'base_code_filter_report.json'

    report_path.parent.mkdir(parents=True, exist_ok=True)

    logger.info(f"\nStep 3: Generating report...")
    filter_tool.generate_report(removed_per_cluster, report_path)

    # Print statistics
    filter_tool.print_stats()

    if args.dry_run:
        logger.info("DRY RUN completed. No files were modified.")
        logger.info("Run without --dry-run to apply changes.")
    else:
        logger.info("Filtering completed successfully!")
        logger.info(f"Removed {filter_tool.stats['entries_removed']} entries from clusters.")
        logger.info("Original dataset files remain unchanged.")


if __name__ == "__main__":
    main()