#!/usr/bin/env python3
"""
Sync C++ LLM Metadata Script
=============================

This script ensures that all C++ entries in cluster JSON files have up-to-date
LLM metadata by:
1. Scanning the filesystem for actual LLM-generated files
2. Updating the 'LLMs' field in cluster JSON files
3. Calculating similarity scores using SimilarityCalculator

Usage:
    python sync_cpp_llm_metadata.py [--dry-run] [--verbose]

Author: Sustainable Code Refactoring Research Project
Date: 2025-11-12
"""

import argparse
import json
import logging
import re
import sys
from pathlib import Path
from typing import Dict, List, Tuple

# Add parent directory to path for imports
sys.path.insert(0, str(Path(__file__).parent.parent))

from utility_dir.utility_paths import (
    CLUSTERS_DIR_FILEPATH,
    DATASET_DIR
)
from utility_dir.general_utils import read_json, write_json

# Import similarity calculator
try:
    from metrics.similarity.similarity_calculator import SimilarityCalculator
    SIMILARITY_AVAILABLE = True
except ImportError:
    SIMILARITY_AVAILABLE = False
    print("⚠️  SimilarityCalculator not available - similarity scores will not be calculated")


class CppLLMMetadataSync:
    """Synchronizes LLM metadata for C++ entries in cluster files"""

    def __init__(self, dry_run: bool = False, verbose: bool = False):
        """
        Initialize the metadata synchronizer

        Args:
            dry_run: If True, only report changes without modifying files
            verbose: If True, enable verbose logging
        """
        self.dry_run = dry_run
        self.verbose = verbose
        self.logger = self._setup_logger()

        # Initialize similarity calculator if available
        self.similarity_calculator = None
        if SIMILARITY_AVAILABLE:
            try:
                self.similarity_calculator = SimilarityCalculator()
                self.logger.info("✅ SimilarityCalculator initialized")
            except Exception as e:
                self.logger.warning(f"⚠️  Failed to initialize SimilarityCalculator: {e}")

        # Statistics
        self.stats = {
            'clusters_scanned': 0,
            'entries_scanned': 0,
            'entries_with_llms': 0,
            'entries_updated': 0,
            'entries_with_missing_files': 0,
            'llm_files_found': 0,
            'clusters_modified': 0
        }

        # LLM directory mappings
        self.llm_mappings = {
            "openAI": "ChatGPT4",
            "claude": "ClaudeSonnet4",
            "gemini": "GeminiFlash"
        }

    def _setup_logger(self) -> logging.Logger:
        """Setup logging configuration"""
        logger = logging.getLogger('CppLLMMetadataSync')
        logger.setLevel(logging.DEBUG if self.verbose else logging.INFO)

        # Console handler
        console_handler = logging.StreamHandler()
        console_handler.setLevel(logging.DEBUG if self.verbose else logging.INFO)
        formatter = logging.Formatter(
            '%(asctime)s - %(levelname)s - %(message)s',
            datefmt='%Y-%m-%d %H:%M:%S'
        )
        console_handler.setFormatter(formatter)
        logger.addHandler(console_handler)

        return logger

    def _extract_prompt_version(self, filename: str) -> int:
        """
        Extract prompt version number from filename

        Args:
            filename: LLM file name (e.g., "ChatGPT4_exercise_v1.cpp")

        Returns:
            Prompt version number (1-4), or None if not found
        """
        # Pattern: ModelName_exercise_v{N}.cpp
        match = re.search(r'_v(\d+)\.cpp$', filename)
        if match:
            return int(match.group(1))
        return None

    def _scan_llm_files_for_entry(self, entry: Dict) -> List[Dict]:
        """
        Scan filesystem for LLM files associated with an entry

        Args:
            entry: Entry dictionary from cluster JSON

        Returns:
            List of LLM metadata dictionaries
        """
        llm_metadata = []

        code_snippet_path = entry.get("codeSnippetFilePath", "")
        if not code_snippet_path:
            self.logger.debug(f"  Entry {entry.get('id')} has no codeSnippetFilePath")
            return llm_metadata

        # Extract directory path (e.g., "cpp/hello-world")
        parts = str(code_snippet_path).split("/")
        if len(parts) < 2:
            self.logger.debug(f"  Invalid path structure: {code_snippet_path}")
            return llm_metadata

        dir_name = str(parts[0]) + "/" + str(parts[1])
        exercise_dir = DATASET_DIR / dir_name

        if not exercise_dir.exists():
            self.logger.debug(f"  Exercise directory not found: {exercise_dir}")
            return llm_metadata

        # Scan each LLM model directory
        for model_dir, file_prefix in self.llm_mappings.items():
            llm_dir_path = exercise_dir / model_dir
            if not llm_dir_path.exists():
                continue

            # Find all .cpp files in this directory
            for generated_file in llm_dir_path.glob("*.cpp"):
                if not generated_file.is_file():
                    continue

                prompt_version = self._extract_prompt_version(generated_file.name)
                if prompt_version is None:
                    self.logger.debug(f"  Could not extract version from: {generated_file.name}")
                    continue

                # Read file for statistics
                try:
                    with open(generated_file, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()

                    char_count = len(content)
                    word_count = len(content.split())
                    relative_path = str(generated_file.relative_to(DATASET_DIR))

                    # Build metadata block in correct format
                    llm_meta = {
                        "type": model_dir,
                        "path": relative_path,
                        "word_quantity": word_count,
                        "char_quantity": char_count,
                        "filename": generated_file.name,
                        "prompt_version": prompt_version,
                        "fuzzy_score": 0.0,  # Placeholder for similarity calculation
                        "cosine_similarity_score": 0.0,  # Placeholder
                        "similarity_index": 0.0  # Placeholder
                    }
                    llm_metadata.append(llm_meta)
                    self.stats['llm_files_found'] += 1

                except Exception as e:
                    self.logger.warning(f"  ⚠️  Error reading file {generated_file}: {e}")
                    continue

        # Sort for consistency (by type and prompt version)
        llm_metadata.sort(key=lambda x: (x["type"], x["prompt_version"]))

        return llm_metadata

    def _needs_update(self, entry: Dict, scanned_metadata: List[Dict]) -> bool:
        """
        Check if entry needs metadata update

        Args:
            entry: Entry dictionary
            scanned_metadata: Metadata from filesystem scan

        Returns:
            True if update is needed
        """
        current_llms = entry.get('LLMs', [])

        # Case 1: No current metadata but files exist
        if not current_llms and scanned_metadata:
            return True

        # Case 2: Current metadata exists but files are different
        if current_llms:
            # Check if counts match
            if len(current_llms) != len(scanned_metadata):
                return True

            # Check if metadata has old format (has 'llm_type' or 'generated_code_path')
            if current_llms and ('llm_type' in current_llms[0] or 'generated_code_path' in current_llms[0]):
                return True

            # Check if file paths match
            current_paths = {llm.get('path') for llm in current_llms}
            scanned_paths = {llm.get('path') for llm in scanned_metadata}
            if current_paths != scanned_paths:
                return True

        return False

    def sync_cluster(self, cluster_file: Path) -> Tuple[bool, int, int]:
        """
        Sync LLM metadata for a single cluster file

        Args:
            cluster_file: Path to cluster JSON file

        Returns:
            Tuple of (modified, total_entries, updated_entries)
        """
        cluster_name = cluster_file.stem.replace('cluster_', '')

        # Load cluster data
        try:
            cluster_data = read_json(cluster_file)
        except json.JSONDecodeError:
            self.logger.error(f"❌ Failed to decode JSON: {cluster_file}")
            return False, 0, 0

        # Check for C++ entries
        if 'cpp' not in cluster_data:
            return False, 0, 0

        cpp_entries = cluster_data['cpp']
        if not cpp_entries:
            return False, 0, 0

        self.logger.info(f"\n📁 Processing cluster: {cluster_name} ({len(cpp_entries)} C++ entries)")

        modified = False
        total_entries = len(cpp_entries)
        updated_entries = 0

        for entry in cpp_entries:
            entry_id = entry.get('id', 'unknown')
            self.stats['entries_scanned'] += 1

            # Scan filesystem for LLM files
            scanned_metadata = self._scan_llm_files_for_entry(entry)

            if scanned_metadata:
                self.stats['entries_with_llms'] += 1
                self.logger.debug(f"  ✓ {entry_id}: Found {len(scanned_metadata)} LLM files")
            else:
                self.logger.debug(f"  - {entry_id}: No LLM files found")

            # Check if update is needed
            if self._needs_update(entry, scanned_metadata):
                if scanned_metadata:
                    self.logger.info(f"  🔄 {entry_id}: Updating metadata ({len(scanned_metadata)} LLM files)")
                    entry['LLMs'] = scanned_metadata
                    modified = True
                    updated_entries += 1
                    self.stats['entries_updated'] += 1
                else:
                    # Files were in metadata but not found on disk
                    current_llms = entry.get('LLMs', [])
                    if current_llms:
                        self.logger.warning(f"  ⚠️  {entry_id}: Metadata exists but files missing on disk")
                        self.stats['entries_with_missing_files'] += 1
                        if not self.dry_run:
                            entry['LLMs'] = []  # Clear invalid metadata
                            modified = True
                            updated_entries += 1
                            self.stats['entries_updated'] += 1
            else:
                self.logger.debug(f"  ✓ {entry_id}: Metadata up-to-date")

        # Save cluster if modified
        if modified:
            self.stats['clusters_modified'] += 1

            if not self.dry_run:
                try:
                    write_json(cluster_file, cluster_data)
                    self.logger.info(f"  💾 Saved: {cluster_name}")

                    # Calculate similarity scores if available
                    if self.similarity_calculator:
                        self.logger.info(f"  🧠 Calculating similarity scores...")
                        try:
                            self.similarity_calculator.calculate_similarities_for_cluster(cluster_file.name)
                            self.logger.info(f"  ✓ Similarity scores updated")
                        except Exception as e:
                            self.logger.warning(f"  ⚠️  Similarity calculation failed: {e}")

                except Exception as e:
                    self.logger.error(f"  ❌ Failed to save {cluster_name}: {e}")
                    return False, total_entries, 0
            else:
                self.logger.info(f"  [DRY RUN] Would save {cluster_name}")

        return modified, total_entries, updated_entries

    def run(self) -> None:
        """Run the synchronization process"""
        self.logger.info("="*80)
        self.logger.info("C++ LLM METADATA SYNCHRONIZATION")
        self.logger.info("="*80)
        self.logger.info(f"Dry run: {self.dry_run}")
        self.logger.info(f"Clusters directory: {CLUSTERS_DIR_FILEPATH}")
        self.logger.info("")

        # Get all cluster files
        cluster_files = sorted(CLUSTERS_DIR_FILEPATH.glob("cluster_*.json"))

        if not cluster_files:
            self.logger.error("❌ No cluster files found")
            return

        self.logger.info(f"Found {len(cluster_files)} cluster files")
        self.logger.info("")

        # Process each cluster
        for cluster_file in cluster_files:
            self.stats['clusters_scanned'] += 1

            # Skip debug/test clusters
            if any(skip in cluster_file.name for skip in ["debug", "test", "bad_entries", "focused_", "with_metrics"]):
                continue

            modified, total, updated = self.sync_cluster(cluster_file)

        # Print summary
        self.logger.info("\n" + "="*80)
        self.logger.info("SYNCHRONIZATION SUMMARY")
        self.logger.info("="*80)
        self.logger.info(f"Clusters scanned: {self.stats['clusters_scanned']}")
        self.logger.info(f"Clusters modified: {self.stats['clusters_modified']}")
        self.logger.info(f"C++ entries scanned: {self.stats['entries_scanned']}")
        self.logger.info(f"Entries with LLM files: {self.stats['entries_with_llms']}")
        self.logger.info(f"Entries updated: {self.stats['entries_updated']}")
        self.logger.info(f"Entries with missing files: {self.stats['entries_with_missing_files']}")
        self.logger.info(f"Total LLM files found: {self.stats['llm_files_found']}")
        self.logger.info("")


def main():
    """Main entry point"""
    parser = argparse.ArgumentParser(
        description="Synchronize C++ LLM metadata in cluster JSON files",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Run synchronization
  python sync_cpp_llm_metadata.py

  # Dry run (report only)
  python sync_cpp_llm_metadata.py --dry-run

  # Verbose output
  python sync_cpp_llm_metadata.py --verbose
        """
    )

    parser.add_argument(
        '--dry-run',
        action='store_true',
        help='Report what would be done without modifying files'
    )

    parser.add_argument(
        '--verbose',
        action='store_true',
        help='Enable verbose logging'
    )

    args = parser.parse_args()

    # Create synchronizer and run
    syncer = CppLLMMetadataSync(dry_run=args.dry_run, verbose=args.verbose)
    syncer.run()


if __name__ == '__main__':
    main()
