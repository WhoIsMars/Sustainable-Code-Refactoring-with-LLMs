#!/usr/bin/env python3
"""
C++ Dataset Integrity and Completion Script
============================================

This script validates and completes the C++ dataset through four sequential phases:
0. Test Completion: Completes missing test executions for entries with partial results (1-4/5)
1. Validation and Pruning: Removes invalid base entries that don't pass tests
   (checks existing execution results instead of re-running tests)
2. LLM Regeneration: Regenerates missing Gemini variants for valid entries
   (checks if LLM files already exist before regenerating)
3. Test Execution: Runs missing test executions for LLM entries
   (checks if all 5 test results already exist before re-executing)

Author: Sustainable Code Refactoring Research Project
Date: 2025-11-12
"""

import argparse
import logging
import sys
from pathlib import Path
from typing import List, Tuple
from datetime import datetime

# Add parent directory to path for imports
sys.path.insert(0, str(Path(__file__).parent.parent))

from utility_dir.utility_paths import (
    CLUSTERS_DIR_FILEPATH,
    OUTPUT_DIR_FILEPATH,
    SRC_DIR
)
from utility_dir.general_utils import read_json, write_json

# Import test execution logic
try:
    from run_tests_on_clusters.run_tests_on_cluster import ClusterRunner
    TEST_RUNNER_AVAILABLE = True
except ImportError:
    TEST_RUNNER_AVAILABLE = False
    print("WARNING: Test runner not available")

# Check if LLM API modules are available
try:
    from LLMs_generator_engine.api import gemini_api_gestor, claude_api_gestor, openai_api_gestor
    LLM_GENERATOR_AVAILABLE = True
except ImportError:
    LLM_GENERATOR_AVAILABLE = False
    print("WARNING: LLM API modules not available")


class CppDatasetValidator:
    """
    Validates and completes C++ dataset entries through validation,
    LLM regeneration, and test execution phases.
    """

    def __init__(self, dry_run: bool = False):
        """
        Initialize validator

        Args:
            dry_run: If True, only report what would be done without modifying files
        """
        self.dry_run = dry_run
        self.logger = self._setup_logger()

        # Statistics
        self.stats = {
            'phase0': {
                'entries_checked': 0,
                'entries_with_partial_results': 0,
                'tests_completed': 0,
                'entries_became_valid': 0,
                'execution_errors': 0
            },
            'phase1': {
                'entries_checked': 0,
                'entries_removed': 0,
                'entries_no_results': 0,
                'clusters_modified': 0,
                'removed_ids': [],
                'no_results_ids': []
            },
            'phase2': {
                'entries_checked': 0,
                'llm_files_already_exist': 0,
                'gemini_variants_generated': 0,
                'clusters_modified': 0,
                'generation_errors': 0
            },
            'phase3': {
                'entries_checked': 0,
                'entries_already_complete': 0,
                'tests_executed': 0,
                'execution_errors': 0
            }
        }

    def _setup_logger(self) -> logging.Logger:
        """Setup logging configuration"""
        logger = logging.getLogger('CppDatasetValidator')
        logger.setLevel(logging.INFO)

        # Console handler
        console_handler = logging.StreamHandler()
        console_handler.setLevel(logging.INFO)
        formatter = logging.Formatter(
            '%(asctime)s - %(name)s - %(levelname)s - %(message)s',
            datefmt='%Y-%m-%d %H:%M:%S'
        )
        console_handler.setFormatter(formatter)
        logger.addHandler(console_handler)

        # File handler
        logs_dir = SRC_DIR / "logs"
        logs_dir.mkdir(exist_ok=True)
        log_file = logs_dir / f"cpp_validation_{datetime.now().strftime('%Y%m%d_%H%M%S')}.log"
        file_handler = logging.FileHandler(log_file)
        file_handler.setLevel(logging.DEBUG)
        file_handler.setFormatter(formatter)
        logger.addHandler(file_handler)

        logger.info(f"Log file: {log_file}")
        return logger

    def _get_cpp_clusters(self) -> List[Path]:
        """Get all cluster files"""
        cluster_files = sorted(CLUSTERS_DIR_FILEPATH.glob("cluster_*.json"))
        self.logger.info(f"Found {len(cluster_files)} cluster files")
        return cluster_files

    def _check_existing_test_results(
        self,
        entry_id: str,
        cluster_name: str,
        num_executions: int = 5
    ) -> Tuple[bool, int, bool]:
        """
        Check existing test results without re-running tests

        Reads AGGREGATED format result files: {"results": {"cpp": [...]}}

        Args:
            entry_id: Entry ID to validate
            cluster_name: Cluster name
            num_executions: Expected number of test runs (default: 5)

        Returns:
            Tuple of (is_valid, passed_count, has_results)
            - is_valid: True if 100% pass rate
            - passed_count: Number of successful test runs
            - has_results: True if ANY results were found (even if incomplete)
        """
        try:
            passed_count = 0
            total_found = 0

            # Check execution_outputs for existing results
            for run_num in range(1, num_executions + 1):
                result_file = OUTPUT_DIR_FILEPATH / f"{cluster_name}_results_{run_num}.json"

                if not result_file.exists():
                    continue

                result_data = read_json(result_file)
                if not result_data or 'results' not in result_data:
                    # Skip invalid or corrupted files
                    continue

                # AGGREGATED format: {"results": {"cpp": [...]}}
                found_entry = False

                for lang_results in result_data['results'].values():
                    for entry_result in lang_results:
                        if entry_result.get('id') == entry_id:
                            found_entry = True
                            total_found += 1
                            if entry_result.get('regressionTestPassed'):
                                passed_count += 1
                            break
                    if found_entry:
                        break

            # Entry is valid only if:
            # 1. All expected results exist (total_found == num_executions)
            # 2. All results passed (passed_count == num_executions)
            has_results = total_found > 0
            is_valid = (total_found == num_executions) and (passed_count == num_executions)

            if has_results:
                self.logger.debug(
                    f"  {entry_id}: {passed_count}/{total_found} tests passed "
                    f"(expected {num_executions}) - {'VALID' if is_valid else 'INVALID'}"
                )
            else:
                self.logger.debug(f"  {entry_id}: No existing results found")

            return is_valid, passed_count, has_results

        except Exception as e:
            self.logger.error(f"  Error checking results for {entry_id}: {e}")
            return False, 0, False

    def phase0_complete_partial_tests(self) -> None:
        """
        Phase 0: Complete missing test executions for entries with partial results

        For each C++ base entry with 1-4/5 test results:
        1. Identify which test executions are missing
        2. Run the missing tests to complete the 5 required executions
        3. Check if the entry becomes valid (5/5 passed)

        This phase runs BEFORE validation to maximize the number of valid entries.
        """
        self.logger.info("="*80)
        self.logger.info("PHASE 0: COMPLETING PARTIAL TEST RESULTS")
        self.logger.info("="*80)
        self.logger.info("ℹ️  Running missing tests for entries with partial results (1-4/5)")

        if not TEST_RUNNER_AVAILABLE:
            self.logger.error("Test runner not available - skipping Phase 0")
            return

        cluster_files = self._get_cpp_clusters()

        for cluster_file in cluster_files:
            cluster_name = cluster_file.stem.replace('cluster_', '')
            self.logger.info(f"\n📁 Processing cluster: {cluster_name}")

            # Load cluster data
            cluster_data = read_json(cluster_file)
            if not cluster_data:
                self.logger.warning(f"  ⚠️  Failed to load {cluster_file}")
                continue

            # Check for C++ entries
            cpp_entries = cluster_data.get('cpp', [])
            if not cpp_entries:
                self.logger.debug(f"  No C++ entries in {cluster_name}")
                continue

            self.logger.info(f"  Found {len(cpp_entries)} C++ entries")

            # Check each entry for partial results
            for entry in cpp_entries:
                entry_id = entry.get('id')
                if not entry_id:
                    continue

                self.stats['phase0']['entries_checked'] += 1

                # Check existing test results
                is_valid, passed_count, has_results = self._check_existing_test_results(
                    entry_id, cluster_name, num_executions=5
                )

                # Skip if already valid or has no results at all
                if is_valid:
                    self.logger.debug(f"  ✓ {entry_id}: Already valid (5/5)")
                    continue

                if not has_results:
                    self.logger.debug(f"  - {entry_id}: No results (will be handled in Phase 1)")
                    continue

                # Entry has partial results (1-4/5)
                self.stats['phase0']['entries_with_partial_results'] += 1

                # Determine which test runs are missing
                missing_runs = []
                for run_num in range(1, 6):
                    result_file = OUTPUT_DIR_FILEPATH / f"{cluster_name}_results_{run_num}.json"

                    if not result_file.exists():
                        missing_runs.append(run_num)
                        continue

                    # Check if entry exists in this result file
                    result_data = read_json(result_file)
                    if not result_data or 'results' not in result_data:
                        missing_runs.append(run_num)
                        continue

                    found = False
                    for lang_results in result_data['results'].values():
                        for entry_result in lang_results:
                            if entry_result.get('id') == entry_id:
                                found = True
                                break
                        if found:
                            break

                    if not found:
                        missing_runs.append(run_num)

                if missing_runs:
                    self.logger.info(
                        f"  🔄 {entry_id}: Partial results ({passed_count}/5 passed, "
                        f"missing runs: {missing_runs})"
                    )

                    if not self.dry_run:
                        try:
                            # Run missing test executions
                            self.logger.info(f"    Running {len(missing_runs)} missing test executions...")

                            runner = ClusterRunner()

                            for run_num in missing_runs:
                                self.logger.info(f"      Running base test execution {run_num}/5...")

                                # Run base tests for this entry
                                _, _ = runner.run_cluster_tests(
                                    cluster_path=cluster_file,
                                    base_only=True,
                                    llm_only=False,
                                    run_number=run_num,
                                    cluster_name=cluster_name,
                                    selected_languages=['cpp'],
                                    entry_ids_filter=[entry_id]  # Only run this specific entry
                                )

                                self.stats['phase0']['tests_completed'] += 1

                            # Re-check if entry is now valid
                            is_now_valid, new_passed, _ = self._check_existing_test_results(
                                entry_id, cluster_name, num_executions=5
                            )

                            if is_now_valid:
                                self.stats['phase0']['entries_became_valid'] += 1
                                self.logger.info(
                                    f"    ✓ Entry is now VALID (5/5 tests passed)"
                                )
                            else:
                                self.logger.info(
                                    f"    ✗ Entry still INVALID ({new_passed}/5 tests passed)"
                                )

                        except Exception as e:
                            self.stats['phase0']['execution_errors'] += 1
                            self.logger.error(f"    ✗ Error executing tests: {e}")
                    else:
                        self.logger.info(
                            f"    [DRY RUN] Would execute {len(missing_runs)} test runs"
                        )

        # Phase 0 summary
        self.logger.info("\n" + "="*80)
        self.logger.info("PHASE 0 SUMMARY")
        self.logger.info("="*80)
        self.logger.info(f"Entries checked: {self.stats['phase0']['entries_checked']}")
        self.logger.info(
            f"Entries with partial results: {self.stats['phase0']['entries_with_partial_results']}"
        )
        self.logger.info(f"Tests completed: {self.stats['phase0']['tests_completed']}")
        self.logger.info(
            f"Entries became valid: {self.stats['phase0']['entries_became_valid']}"
        )
        self.logger.info(f"Execution errors: {self.stats['phase0']['execution_errors']}")

    def phase1_validate_and_prune(self) -> None:
        """
        Phase 1: Validate base C++ entries and remove invalid ones

        For each C++ base entry:
        1. Check existing test results (5 executions)
        2. If pass rate < 100% or no results, mark as invalid
        3. Remove invalid entries from cluster JSON
        4. Log removed entries and entries without results
        """
        self.logger.info("="*80)
        self.logger.info("PHASE 1: VALIDATION AND PRUNING")
        self.logger.info("="*80)
        self.logger.info("ℹ️  Checking existing test results (no re-execution)")

        cluster_files = self._get_cpp_clusters()

        for cluster_file in cluster_files:
            cluster_name = cluster_file.stem.replace('cluster_', '')
            self.logger.info(f"\n📁 Processing cluster: {cluster_name}")

            # Load cluster data
            cluster_data = read_json(cluster_file)
            if not cluster_data:
                self.logger.warning(f"  ⚠️  Failed to load {cluster_file}")
                continue

            # Check for C++ entries
            cpp_entries = cluster_data.get('cpp', [])
            if not cpp_entries:
                self.logger.debug(f"  No C++ entries in {cluster_name}")
                continue

            self.logger.info(f"  Found {len(cpp_entries)} C++ entries")

            # Validate each entry
            invalid_entries = []
            valid_entries = []

            for entry in cpp_entries:
                entry_id = entry.get('id')
                if not entry_id:
                    continue

                self.stats['phase1']['entries_checked'] += 1

                # Check existing test results
                is_valid, passed_count, has_results = self._check_existing_test_results(
                    entry_id, cluster_name, num_executions=5
                )

                if is_valid:
                    valid_entries.append(entry)
                    self.logger.debug(f"  ✓ Valid: {entry_id} (5/5 tests passed)")
                else:
                    invalid_entries.append(entry)

                    if not has_results:
                        self.stats['phase1']['entries_no_results'] += 1
                        self.stats['phase1']['no_results_ids'].append(entry_id)
                        self.logger.warning(
                            f"  ✗ Invalid: {entry_id} "
                            "(no test results found)"
                        )
                    else:
                        self.logger.warning(
                            f"  ✗ Invalid: {entry_id} "
                            f"(passed {passed_count}/5 tests)"
                        )

                    self.stats['phase1']['removed_ids'].append(entry_id)

            # Update cluster if needed
            if invalid_entries:
                self.stats['phase1']['entries_removed'] += len(invalid_entries)
                self.stats['phase1']['clusters_modified'] += 1

                self.logger.info(
                    f"  🗑️  Removing {len(invalid_entries)} invalid entries"
                )

                if not self.dry_run:
                    # Update cluster with only valid entries
                    cluster_data['cpp'] = valid_entries
                    write_json(cluster_file, cluster_data)
                    self.logger.info(f"  💾 Updated {cluster_file.name}")
                else:
                    self.logger.info(f"  [DRY RUN] Would remove entries from {cluster_file.name}")

        # Phase 1 summary
        self.logger.info("\n" + "="*80)
        self.logger.info("PHASE 1 SUMMARY")
        self.logger.info("="*80)
        self.logger.info(f"Entries checked: {self.stats['phase1']['entries_checked']}")
        self.logger.info(f"Entries removed: {self.stats['phase1']['entries_removed']}")
        self.logger.info(
            f"  - With no results: {self.stats['phase1']['entries_no_results']}"
        )
        self.logger.info(
            f"  - With failed tests: "
            f"{self.stats['phase1']['entries_removed'] - self.stats['phase1']['entries_no_results']}"
        )
        self.logger.info(f"Clusters modified: {self.stats['phase1']['clusters_modified']}")

        if self.stats['phase1']['no_results_ids']:
            self.logger.info("\nEntries without test results:")
            for entry_id in self.stats['phase1']['no_results_ids']:
                self.logger.info(f"  - {entry_id}")

        if self.stats['phase1']['removed_ids']:
            failed_ids = [
                eid for eid in self.stats['phase1']['removed_ids']
                if eid not in self.stats['phase1']['no_results_ids']
            ]
            if failed_ids:
                self.logger.info("\nEntries with failed tests:")
                for entry_id in failed_ids:
                    self.logger.info(f"  - {entry_id}")

    def phase2_regenerate_gemini(self) -> None:
        """
        Phase 2: Regenerate missing Gemini variants

        For each valid C++ base entry:
        1. Check if all 4 Gemini variants (v1-v4) exist (check both metadata AND actual files)
        2. If missing or file doesn't exist, generate them using llm_generator.py
        3. Update cluster JSON with new LLM metadata

        Only regenerates variants that are truly missing to avoid unnecessary API calls.
        """
        self.logger.info("\n" + "="*80)
        self.logger.info("PHASE 2: GEMINI VARIANT REGENERATION")
        self.logger.info("="*80)

        if not LLM_GENERATOR_AVAILABLE:
            self.logger.error("LLM generator not available - skipping Phase 2")
            return

        cluster_files = self._get_cpp_clusters()

        for cluster_file in cluster_files:
            cluster_name = cluster_file.stem.replace('cluster_', '')
            self.logger.info(f"\n📁 Processing cluster: {cluster_name}")

            # Load cluster data
            cluster_data = read_json(cluster_file)
            if not cluster_data:
                continue

            cpp_entries = cluster_data.get('cpp', [])
            if not cpp_entries:
                continue

            self.logger.info(f"  Found {len(cpp_entries)} C++ entries")

            cluster_modified = False

            for entry in cpp_entries:
                entry_id = entry.get('id')
                if not entry_id:
                    continue

                self.stats['phase2']['entries_checked'] += 1

                # Check for missing Gemini variants (v1-v4)
                # Check BOTH metadata AND actual file existence
                # NOTE: Cluster JSONs use 'LLMs' field, not 'llm_variants'
                existing_gemini_versions = set()

                # Scan LLM metadata for this entry
                llm_list = entry.get('LLMs', [])

                for llm_entry in llm_list:
                    llm_type = llm_entry.get('type', '')
                    if llm_type == 'gemini':
                        prompt_version = llm_entry.get('prompt_version')
                        llm_path = llm_entry.get('path', '')

                        # Check if file actually exists
                        if prompt_version and llm_path:
                            # Path is relative to DATASET_DIR
                            from utility_dir.utility_paths import DATASET_DIR
                            code_file = DATASET_DIR / llm_path

                            if code_file.exists():
                                # Convert prompt_version (int) to 'vN' format
                                version_str = f"v{prompt_version}"
                                existing_gemini_versions.add(version_str)
                            else:
                                self.logger.warning(
                                    f"  ⚠️  {entry_id}: Metadata has v{prompt_version} "
                                    f"but file doesn't exist: {llm_path}"
                                )

                # Determine missing versions
                required_versions = {'v1', 'v2', 'v3', 'v4'}
                missing_versions = required_versions - existing_gemini_versions

                if not missing_versions:
                    self.stats['phase2']['llm_files_already_exist'] += 1
                    self.logger.debug(f"  ✓ {entry_id}: All Gemini variants present")
                    continue

                self.logger.info(
                    f"  🔄 {entry_id}: Missing Gemini versions: {sorted(missing_versions)}"
                )

                # Generate missing variants using API gestors directly
                if not self.dry_run:
                    try:
                        # Import utility paths (API gestors already imported at top)
                        from utility_dir.utility_paths import PROMPTS_DIR_FILEPATH, DATASET_DIR

                        # Initialize API gestors
                        gemini_api_g = gemini_api_gestor.GeminiAIApiGestor()
                        claude_api_g = claude_api_gestor.ClaudeApiGestor()
                        openai_api_g = openai_api_gestor.OpenAIApiGestor()

                        # Map prompt versions to file paths and numbers
                        prompt_files = {
                            'v1': (PROMPTS_DIR_FILEPATH / "promptV1.txt", 1),
                            'v2': (PROMPTS_DIR_FILEPATH / "promptV2.txt", 2),
                            'v3': (PROMPTS_DIR_FILEPATH / "promptV3.txt", 3),
                            'v4': (PROMPTS_DIR_FILEPATH / "promptV4.txt", 4),
                        }

                        # Get base code file path
                        code_snippet_path = entry.get("codeSnippetFilePath", "")
                        if not code_snippet_path:
                            self.logger.error(f"    ✗ No codeSnippetFilePath for {entry_id}")
                            continue

                        parts = str(code_snippet_path).split("/")
                        dir_name = str(parts[0]) + "/" + str(parts[1])
                        exercise_dir = DATASET_DIR / dir_name
                        filename = entry.get("filename", "")

                        code_file_path = DATASET_DIR / code_snippet_path
                        if entry.get('language') in ['c', 'cpp']:
                            code_file_path = code_file_path / filename

                        # Generate for each missing version
                        for version in sorted(missing_versions):
                            prompt_path, prompt_num = prompt_files[version]
                            self.logger.info(f"    Generating {version} for all 3 models (Gemini, Claude, OpenAI)...")

                            # Generate with all 3 models
                            models_to_generate = [
                                ("Gemini", gemini_api_g),
                                ("Claude", claude_api_g),
                                ("OpenAI", openai_api_g)
                            ]

                            for model_name, generator in models_to_generate:
                                success = generator.generate_and_save_LLM_code_by_files(
                                    prompt_path,
                                    code_file_path,
                                    exercise_dir,
                                    prompt_num,
                                    filename
                                )

                                if success:
                                    self.stats['phase2']['gemini_variants_generated'] += 1
                                    self.logger.info(f"      ✓ {model_name} {version} generated/exists")
                                else:
                                    self.stats['phase2']['generation_errors'] += 1
                                    self.logger.error(f"      ✗ {model_name} {version} failed")

                    except Exception as e:
                        self.stats['phase2']['generation_errors'] += 1
                        self.logger.error(f"    Error generating LLM variants: {e}")
                else:
                    self.logger.info(
                        f"    [DRY RUN] Would generate: {sorted(missing_versions)}"
                    )

            # Save cluster if modified
            if cluster_modified:
                self.stats['phase2']['clusters_modified'] += 1
                write_json(cluster_file, cluster_data)
                self.logger.info(f"  💾 Updated {cluster_file.name}")

        # Phase 2 summary
        self.logger.info("\n" + "="*80)
        self.logger.info("PHASE 2 SUMMARY")
        self.logger.info("="*80)
        self.logger.info(f"Entries checked: {self.stats['phase2']['entries_checked']}")
        self.logger.info(
            f"Entries with all LLM files present: {self.stats['phase2']['llm_files_already_exist']}"
        )
        self.logger.info(
            f"Gemini variants generated: {self.stats['phase2']['gemini_variants_generated']}"
        )
        self.logger.info(f"Clusters modified: {self.stats['phase2']['clusters_modified']}")
        self.logger.info(f"Generation errors: {self.stats['phase2']['generation_errors']}")

    def phase3_execute_missing_tests(self) -> None:
        """
        Phase 3: Execute missing LLM test runs

        For each C++ LLM entry:
        1. Check if all 5 execution results exist in execution_outputs/
        2. If any are missing, run ONLY the missing tests
        3. Skip entries that already have all 5/5 results to avoid re-execution

        Only executes tests that are truly missing to save time and resources.
        """
        self.logger.info("\n" + "="*80)
        self.logger.info("PHASE 3: MISSING TEST EXECUTION")
        self.logger.info("="*80)

        if not TEST_RUNNER_AVAILABLE:
            self.logger.error("Test runner not available - skipping Phase 3")
            return

        cluster_files = self._get_cpp_clusters()

        for cluster_file in cluster_files:
            cluster_name = cluster_file.stem.replace('cluster_', '')
            self.logger.info(f"\n📁 Processing cluster: {cluster_name}")

            # Load cluster data
            cluster_data = read_json(cluster_file)
            if not cluster_data:
                continue

            cpp_entries = cluster_data.get('cpp', [])
            if not cpp_entries:
                continue

            for entry in cpp_entries:
                entry_id = entry.get('id')
                if not entry_id:
                    continue

                self.stats['phase3']['entries_checked'] += 1

                # Check LLM variants - use 'LLMs' field from cluster JSON
                llm_list = entry.get('LLMs', [])

                if not llm_list:
                    self.logger.debug(f"  - {entry_id}: No LLM metadata found")
                    continue

                for llm_entry in llm_list:
                    llm_type = llm_entry.get('type', '')
                    prompt_version = llm_entry.get('prompt_version')

                    if not prompt_version:
                        continue

                    # Check for missing execution results (5 runs per version)
                    version_num = str(prompt_version)
                    missing_runs = []
                    existing_runs = []

                    for run_num in range(1, 6):  # 5 runs
                        result_file = OUTPUT_DIR_FILEPATH / (
                            f"{cluster_name}_results_v{version_num}_{run_num}.json"
                        )

                        if not result_file.exists():
                            missing_runs.append(run_num)
                            continue

                        # Check if this specific entry exists in results
                        results_data = read_json(result_file)
                        if not results_data:
                            missing_runs.append(run_num)
                            continue

                        # Check if entry_id is in results (AGGREGATED format)
                        found = False
                        for lang_results in results_data.get('results', {}).values():
                            for result_entry in lang_results:
                                if result_entry.get('id') == entry_id:
                                    found = True
                                    existing_runs.append(run_num)
                                    break
                            if found:
                                break

                        if not found:
                            missing_runs.append(run_num)

                    # Skip if all 5 results already exist
                    if not missing_runs:
                        self.stats['phase3']['entries_already_complete'] += 1
                        self.logger.debug(
                            f"  ✓ {entry_id} ({llm_type} v{prompt_version}): "
                            f"All 5 test results present"
                        )
                        continue

                    if missing_runs:
                        self.logger.info(
                            f"  🔄 {entry_id} ({llm_type} v{prompt_version}): "
                            f"Missing runs: {missing_runs}"
                        )

                        if not self.dry_run:
                            try:
                                # Run missing test executions
                                runner = ClusterRunner()

                                for run_num in missing_runs:
                                    self.logger.info(f"      Running test execution {run_num}/5...")

                                    # Run tests for this LLM variant
                                    base_results, llm_results = runner.run_cluster_tests(
                                        cluster_path=cluster_file,
                                        base_only=False,
                                        llm_only=True,
                                        prompt_version=int(version_num),
                                        run_number=run_num,
                                        cluster_name=cluster_name,
                                        selected_languages=['cpp'],
                                        entry_ids_filter=[entry_id]  # Only run this specific entry
                                    )

                                    self.stats['phase3']['tests_executed'] += 1

                                self.logger.info(f"      ✓ Executed {len(missing_runs)} test runs")

                            except Exception as e:
                                self.stats['phase3']['execution_errors'] += 1
                                self.logger.error(f"      ✗ Error executing tests: {e}")
                        else:
                            self.logger.info(
                                f"      [DRY RUN] Would execute {len(missing_runs)} test runs"
                            )

        # Phase 3 summary
        self.logger.info("\n" + "="*80)
        self.logger.info("PHASE 3 SUMMARY")
        self.logger.info("="*80)
        self.logger.info(f"Entries checked: {self.stats['phase3']['entries_checked']}")
        self.logger.info(
            f"Entries already complete (5/5 results): {self.stats['phase3']['entries_already_complete']}"
        )
        self.logger.info(f"Tests executed: {self.stats['phase3']['tests_executed']}")
        self.logger.info(f"Execution errors: {self.stats['phase3']['execution_errors']}")

    def run(self, phases: List[int]) -> None:
        """
        Run specified validation phases

        Args:
            phases: List of phase numbers to run (0, 1, 2, 3)
        """
        self.logger.info("="*80)
        self.logger.info("C++ DATASET VALIDATION AND COMPLETION")
        self.logger.info("="*80)
        self.logger.info(f"Dry run: {self.dry_run}")
        self.logger.info(f"Phases to run: {phases}")
        self.logger.info("")

        start_time = datetime.now()

        if 0 in phases:
            self.phase0_complete_partial_tests()

        if 1 in phases:
            self.phase1_validate_and_prune()

        if 2 in phases:
            self.phase2_regenerate_gemini()

        if 3 in phases:
            self.phase3_execute_missing_tests()

        # Final summary
        elapsed = datetime.now() - start_time
        self.logger.info("\n" + "="*80)
        self.logger.info("FINAL SUMMARY")
        self.logger.info("="*80)
        self.logger.info(f"Total execution time: {elapsed}")
        self.logger.info("\nPhase 0 (Test Completion):")
        self.logger.info(f"  - Entries checked: {self.stats['phase0']['entries_checked']}")
        self.logger.info(
            f"  - Entries with partial results: {self.stats['phase0']['entries_with_partial_results']}"
        )
        self.logger.info(f"  - Tests completed: {self.stats['phase0']['tests_completed']}")
        self.logger.info(
            f"  - Entries became valid: {self.stats['phase0']['entries_became_valid']}"
        )
        self.logger.info("\nPhase 1 (Validation & Pruning):")
        self.logger.info(f"  - Entries checked: {self.stats['phase1']['entries_checked']}")
        self.logger.info(f"  - Entries removed: {self.stats['phase1']['entries_removed']}")
        self.logger.info(
            f"    • No test results: {self.stats['phase1']['entries_no_results']}"
        )
        self.logger.info(
            f"    • Failed tests: "
            f"{self.stats['phase1']['entries_removed'] - self.stats['phase1']['entries_no_results']}"
        )
        self.logger.info(f"  - Clusters modified: {self.stats['phase1']['clusters_modified']}")
        self.logger.info("\nPhase 2 (Gemini Regeneration):")
        self.logger.info(f"  - Entries checked: {self.stats['phase2']['entries_checked']}")
        self.logger.info(
            f"  - Entries already complete: {self.stats['phase2']['llm_files_already_exist']}"
        )
        self.logger.info(
            f"  - Variants generated: {self.stats['phase2']['gemini_variants_generated']}"
        )
        self.logger.info(f"  - Clusters modified: {self.stats['phase2']['clusters_modified']}")
        self.logger.info("\nPhase 3 (Test Execution):")
        self.logger.info(f"  - Entries checked: {self.stats['phase3']['entries_checked']}")
        self.logger.info(
            f"  - Entries already complete: {self.stats['phase3']['entries_already_complete']}"
        )
        self.logger.info(f"  - Tests executed: {self.stats['phase3']['tests_executed']}")


def main():
    """Main entry point"""
    parser = argparse.ArgumentParser(
        description="Validate and complete C++ dataset entries",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Run all phases (including test completion for partial results)
  python validate_and_complete_cpp.py --steps all

  # Run only test completion for entries with partial results (Phase 0)
  python validate_and_complete_cpp.py --steps 0

  # Run only validation and pruning (Phase 1)
  python validate_and_complete_cpp.py --steps 1

  # Run test completion + validation (Phases 0 and 1)
  python validate_and_complete_cpp.py --steps 0 1

  # Run Gemini regeneration and test execution (Phases 2 and 3)
  python validate_and_complete_cpp.py --steps 2 3

  # Dry run (report only, no modifications)
  python validate_and_complete_cpp.py --steps all --dry-run
        """
    )

    parser.add_argument(
        '--steps',
        nargs='+',
        choices=['0', '1', '2', '3', 'all'],
        required=True,
        help='Phases to execute: 0 (test completion), 1 (validation), 2 (LLM regen), 3 (test exec), or "all"'
    )

    parser.add_argument(
        '--dry-run',
        action='store_true',
        help='Report what would be done without modifying files'
    )

    args = parser.parse_args()

    # Parse phases
    if 'all' in args.steps:
        phases = [0, 1, 2, 3]
    else:
        phases = sorted([int(p) for p in args.steps])

    # Create validator and run
    validator = CppDatasetValidator(dry_run=args.dry_run)
    validator.run(phases)


if __name__ == '__main__':
    main()
