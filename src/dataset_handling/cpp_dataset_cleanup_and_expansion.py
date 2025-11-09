#!/usr/bin/env python3
"""
C++ Dataset Cleanup and Expansion Pipeline
==========================================

This script orchestrates a 6-step pipeline to clean and expand the C++ dataset:

1. Identify unstable C++ base entries (< 100% pass rate)
2. Mark them for exclusion (without physical deletion)
3. Add new C++ entries from GitHub Exercism repositories
4. Generate LLM code for new entries
5. Execute tests on new entries
6. Analyze results and regenerate plots

Author: Research Project - Università di Pisa
Date: 2025-11-08
"""

import sys
import json
import logging
from pathlib import Path
from typing import Dict, List, Set, Tuple
from collections import defaultdict
from datetime import datetime

# Add parent directory to path
sys.path.append(str(Path(__file__).parent.parent))

from utility_dir import utility_paths, general_utils
from dataset_handling.github_ingestor import GitHubIngestor
from dataset_handling.clusterCreator import ClusterCreator

# Configure logging
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(levelname)s - %(message)s'
)
logger = logging.getLogger(__name__)


class CppDatasetCleanupAndExpansion:
    """
    Orchestrates the complete C++ dataset cleanup and expansion pipeline
    """

    def __init__(self,
                 execution_outputs_dir: Path = None,
                 clusters_dir: Path = None,
                 backup_dir: Path = None):
        """
        Initialize the pipeline

        Args:
            execution_outputs_dir: Directory containing execution results
            clusters_dir: Directory containing cluster files
            backup_dir: Directory for backups before modifications
        """
        self.execution_outputs_dir = execution_outputs_dir or utility_paths.OUTPUT_DIR_FILEPATH
        self.clusters_dir = clusters_dir or utility_paths.CLUSTERS_DIR_FILEPATH
        self.backup_dir = backup_dir or (utility_paths.SRC_DIR / "cluster_backups" / "backups" / datetime.now().strftime("%Y%m%d_%H%M%S"))

        # Create backup directory
        self.backup_dir.mkdir(parents=True, exist_ok=True)

        # Results containers
        self.unstable_entries = []
        self.stable_entries = []
        self.marked_clusters = set()

        logger.info(f"Initialized C++ Dataset Cleanup Pipeline")
        logger.info(f"Execution outputs: {self.execution_outputs_dir}")
        logger.info(f"Clusters directory: {self.clusters_dir}")
        logger.info(f"Backup directory: {self.backup_dir}")

    # ========================================================================
    # STEP 1: Identify Unstable C++ Base Entries
    # ========================================================================

    def step1_identify_unstable_entries(self) -> Dict:
        """
        Step 1: Identify C++ base entries with < 100% pass rate

        Returns:
            Dictionary with analysis results
        """
        logger.info("="*80)
        logger.info("STEP 1: Identifying unstable C++ base entries")
        logger.info("="*80)

        # Find all clusters with C++ entries
        cpp_clusters = []
        for exec_file in sorted(self.execution_outputs_dir.glob("*_results_1.json")):
            try:
                with open(exec_file, 'r') as f:
                    data = json.load(f)

                if 'results' in data and 'cpp' in data['results']:
                    cluster_name = exec_file.stem.replace('_results_1', '')
                    cpp_clusters.append(cluster_name)
            except Exception as e:
                logger.warning(f"Error reading {exec_file}: {e}")

        logger.info(f"Found {len(cpp_clusters)} clusters with C++ entries")

        # Analyze each cluster
        unstable_count = 0
        stable_count = 0

        for cluster in cpp_clusters:
            cpp_pass_status = defaultdict(list)

            # Check all 5 executions
            for exec_num in range(1, 6):
                filepath = self.execution_outputs_dir / f"{cluster}_results_{exec_num}.json"
                if not filepath.exists():
                    continue

                with open(filepath, 'r') as f:
                    data = json.load(f)

                if 'results' in data and 'cpp' in data['results']:
                    for entry in data['results']['cpp']:
                        entry_id = entry.get('id')
                        passed = entry.get('regressionTestPassed', False)
                        cpp_pass_status[entry_id].append(passed)

            # Classify entries
            for entry_id, status_list in cpp_pass_status.items():
                if len(status_list) == 5:
                    pass_rate = (sum(status_list) / len(status_list)) * 100

                    entry_info = {
                        'entry_id': entry_id,
                        'cluster': cluster,
                        'pass_pattern': status_list,
                        'pass_rate': pass_rate,
                        'stable': all(status_list)
                    }

                    if all(status_list):
                        self.stable_entries.append(entry_info)
                        stable_count += 1
                    else:
                        self.unstable_entries.append(entry_info)
                        unstable_count += 1
                        self.marked_clusters.add(cluster)

        # Generate report
        results = {
            'timestamp': datetime.now().isoformat(),
            'total_clusters': len(cpp_clusters),
            'clusters_with_unstable_entries': len(self.marked_clusters),
            'total_entries': stable_count + unstable_count,
            'stable_entries': stable_count,
            'unstable_entries': unstable_count,
            'stability_percentage': (stable_count / (stable_count + unstable_count) * 100) if (stable_count + unstable_count) > 0 else 0,
            'unstable_entries_list': self.unstable_entries,
            'stable_entries_list': self.stable_entries
        }

        # Save report
        report_path = self.backup_dir / "step1_unstable_entries_report.json"
        with open(report_path, 'w') as f:
            json.dump(results, f, indent=2)

        logger.info(f"✓ Analysis complete:")
        logger.info(f"  Total C++ entries: {stable_count + unstable_count}")
        logger.info(f"  Stable entries (100% pass): {stable_count} ({results['stability_percentage']:.1f}%)")
        logger.info(f"  Unstable entries (<100% pass): {unstable_count}")
        logger.info(f"  Clusters affected: {len(self.marked_clusters)}")
        logger.info(f"✓ Report saved: {report_path}")

        return results

    # ========================================================================
    # STEP 2: Mark Unstable Entries (Soft Delete)
    # ========================================================================

    def step2_mark_unstable_entries(self) -> Dict:
        """
        Step 2: Mark unstable entries by adding a flag to cluster files
        Does NOT physically delete files, only adds metadata

        Returns:
            Dictionary with marking results
        """
        logger.info("="*80)
        logger.info("STEP 2: Marking unstable entries in cluster files")
        logger.info("="*80)

        if not self.unstable_entries:
            logger.warning("No unstable entries found. Run step1 first.")
            return {}

        modified_clusters = set()
        entries_marked = 0

        # Backup clusters before modification
        logger.info("Creating backups of cluster files...")
        for cluster in self.marked_clusters:
            cluster_file = self.clusters_dir / f"cluster_{cluster}.json"
            if cluster_file.exists():
                backup_file = self.backup_dir / cluster_file.name
                import shutil
                shutil.copy2(cluster_file, backup_file)
                logger.debug(f"Backed up: {cluster_file.name}")

        # Mark entries in cluster files
        for entry_info in self.unstable_entries:
            cluster_name = entry_info['cluster']
            entry_id = entry_info['entry_id']

            cluster_file = self.clusters_dir / f"cluster_{cluster_name}.json"

            if not cluster_file.exists():
                logger.warning(f"Cluster file not found: {cluster_file}")
                continue

            # Load cluster data
            with open(cluster_file, 'r') as f:
                cluster_data = json.load(f)

            # Find and mark the entry
            if 'cpp' in cluster_data:
                for entry in cluster_data['cpp']:
                    if entry.get('id') == entry_id:
                        # Add instability metadata
                        entry['_unstable'] = True
                        entry['_instability_reason'] = f"Pass rate: {entry_info['pass_rate']:.1f}%"
                        entry['_pass_pattern'] = entry_info['pass_pattern']
                        entry['_marked_date'] = datetime.now().isoformat()
                        entry['_excluded_from_analysis'] = True

                        entries_marked += 1
                        modified_clusters.add(cluster_name)
                        logger.debug(f"Marked: {entry_id} in {cluster_name}")
                        break

            # Save modified cluster
            with open(cluster_file, 'w') as f:
                json.dump(cluster_data, f, indent=2)

        results = {
            'timestamp': datetime.now().isoformat(),
            'entries_marked': entries_marked,
            'clusters_modified': len(modified_clusters),
            'backup_directory': str(self.backup_dir),
            'modified_clusters_list': list(modified_clusters)
        }

        # Save report
        report_path = self.backup_dir / "step2_marking_report.json"
        with open(report_path, 'w') as f:
            json.dump(results, f, indent=2)

        logger.info(f"✓ Marking complete:")
        logger.info(f"  Entries marked: {entries_marked}")
        logger.info(f"  Clusters modified: {len(modified_clusters)}")
        logger.info(f"  Backups saved to: {self.backup_dir}")
        logger.info(f"✓ Report saved: {report_path}")

        return results

    # ========================================================================
    # STEP 3: Add New C++ Entries from GitHub
    # ========================================================================

    def step3_add_new_cpp_entries(self, target_count: int = 50) -> Dict:
        """
        Step 3: Use github_ingestor.py to add new C++ entries from GitHub

        Args:
            target_count: Target number of new entries to add

        Returns:
            Dictionary with ingestion results
        """
        logger.info("="*80)
        logger.info(f"STEP 3: Adding {target_count} new C++ entries from GitHub")
        logger.info("="*80)

        try:
            # Initialize GitHub Ingestor
            ingestor = GitHubIngestor(
                language='cpp',
                target_entries=target_count,
                output_dir=utility_paths.DATASET_DIR / "cpp"
            )

            logger.info("Starting GitHub ingestion...")
            results = ingestor.run_ingestion()

            logger.info(f"✓ Ingestion complete:")
            logger.info(f"  New entries added: {results.get('entries_added', 0)}")
            logger.info(f"  Repositories processed: {results.get('repos_processed', 0)}")

            return results

        except Exception as e:
            logger.error(f"Error during ingestion: {e}")
            return {'error': str(e)}

    # ========================================================================
    # Main Pipeline Execution
    # ========================================================================

    def run_pipeline(self,
                     run_step1: bool = True,
                     run_step2: bool = True,
                     run_step3: bool = False,
                     target_new_entries: int = 50):
        """
        Run the complete pipeline or selected steps

        Args:
            run_step1: Execute step 1 (identify unstable)
            run_step2: Execute step 2 (mark unstable)
            run_step3: Execute step 3 (add new entries)
            target_new_entries: Target count for new entries
        """
        logger.info("="*80)
        logger.info("C++ DATASET CLEANUP AND EXPANSION PIPELINE")
        logger.info("="*80)
        logger.info(f"Start time: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")

        results = {
            'pipeline_start': datetime.now().isoformat(),
            'steps_completed': []
        }

        # Step 1
        if run_step1:
            step1_results = self.step1_identify_unstable_entries()
            results['step1'] = step1_results
            results['steps_completed'].append('step1')

        # Step 2
        if run_step2:
            step2_results = self.step2_mark_unstable_entries()
            results['step2'] = step2_results
            results['steps_completed'].append('step2')

        # Step 3
        if run_step3:
            step3_results = self.step3_add_new_cpp_entries(target_new_entries)
            results['step3'] = step3_results
            results['steps_completed'].append('step3')

        results['pipeline_end'] = datetime.now().isoformat()

        # Save complete pipeline report
        pipeline_report = self.backup_dir / "pipeline_complete_report.json"
        with open(pipeline_report, 'w') as f:
            json.dump(results, f, indent=2)

        logger.info("="*80)
        logger.info("PIPELINE COMPLETE")
        logger.info("="*80)
        logger.info(f"Steps completed: {', '.join(results['steps_completed'])}")
        logger.info(f"Complete report: {pipeline_report}")
        logger.info(f"End time: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")

        return results


def main():
    """
    Main entry point with CLI interface
    """
    import argparse

    parser = argparse.ArgumentParser(
        description="C++ Dataset Cleanup and Expansion Pipeline",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Run only step 1 (analyze)
  python cpp_dataset_cleanup_and_expansion.py --step1

  # Run steps 1 and 2 (analyze + mark)
  python cpp_dataset_cleanup_and_expansion.py --step1 --step2

  # Run complete pipeline including GitHub ingestion
  python cpp_dataset_cleanup_and_expansion.py --all --target-entries 50
        """
    )

    parser.add_argument('--step1', action='store_true',
                       help='Run Step 1: Identify unstable entries')
    parser.add_argument('--step2', action='store_true',
                       help='Run Step 2: Mark unstable entries')
    parser.add_argument('--step3', action='store_true',
                       help='Run Step 3: Add new entries from GitHub')
    parser.add_argument('--all', action='store_true',
                       help='Run all steps (1, 2, 3)')
    parser.add_argument('--target-entries', type=int, default=50,
                       help='Target number of new entries to add (default: 50)')

    args = parser.parse_args()

    # Determine which steps to run
    run_step1 = args.step1 or args.all
    run_step2 = args.step2 or args.all
    run_step3 = args.step3 or args.all

    if not (run_step1 or run_step2 or run_step3):
        parser.print_help()
        sys.exit(1)

    # Create pipeline instance
    pipeline = CppDatasetCleanupAndExpansion()

    # Run pipeline
    results = pipeline.run_pipeline(
        run_step1=run_step1,
        run_step2=run_step2,
        run_step3=run_step3,
        target_new_entries=args.target_entries
    )

    # Exit with appropriate code
    if 'error' in results:
        sys.exit(1)
    else:
        sys.exit(0)


if __name__ == "__main__":
    main()
