#!/usr/bin/env python3
"""
Test script for github_ingestor with test validation

This script tests the new validation workflow:
1. Download entry
2. Validate with 5 test executions
3. Save to cluster only if tests pass
"""

import sys
from pathlib import Path

# Add parent directory to path
sys.path.insert(0, str(Path(__file__).parent.parent))

from dataset_handling.github_ingestor import GitHubIngestor
from utility_dir.utility_paths import DATASET_DIR, CLUSTERS_DIR_FILEPATH
from utility_dir.general_utils import load_github_token
import logging

# Setup logging
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s'
)
logger = logging.getLogger(__name__)


def test_ingestion_with_validation():
    """Test the ingestion process with validation enabled"""

    logger.info("="*80)
    logger.info("TESTING GITHUB INGESTOR WITH TEST VALIDATION")
    logger.info("="*80)

    # Load GitHub token
    token = load_github_token()
    if not token:
        logger.warning("No GitHub token found - API rate limits will be strict")
        response = input("Continue without token? (y/n): ")
        if response.lower() != 'y':
            logger.info("Test cancelled")
            return

    # Initialize ingestor
    ingestor = GitHubIngestor(
        dataset_dir=DATASET_DIR,
        clusters_dir=CLUSTERS_DIR_FILEPATH,
        github_token=token
    )

    # Test with minimal parameters
    logger.info("\nTest parameters:")
    logger.info("  - Language: C")
    logger.info("  - Max repos: 2")
    logger.info("  - Max entries: 3")
    logger.info("  - Test executions per entry: 5")
    logger.info("  - Parallelization: 3 workers")
    logger.info("")

    # Run ingestion
    try:
        count = ingestor.ingest_entries(
            language='c',
            max_repos=2,
            max_entries_per_lang=3
        )

        logger.info("\n" + "="*80)
        logger.info("TEST COMPLETED SUCCESSFULLY")
        logger.info("="*80)
        logger.info(f"Total entries ingested: {count}")
        logger.info("="*80)

    except Exception as e:
        logger.error(f"\n❌ TEST FAILED: {e}")
        import traceback
        traceback.print_exc()


if __name__ == "__main__":
    test_ingestion_with_validation()
