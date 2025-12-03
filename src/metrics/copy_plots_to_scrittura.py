"""
Copy Fixed Prompt Analysis Plots to Scrittura Directory

This script copies plots from src/metrics/fixed_prompt_plots/ to scrittura/plots/fixed_prompt_analysis/
maintaining the same directory structure.


Date: 2025-11-13
"""

import sys
import os
from pathlib import Path
import shutil
import logging

# Add parent directory to path for imports
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))

from utility_dir import utility_paths


class PlotCopier:
    """
    Copies fixed prompt analysis plots to scrittura directory.
    """

    def __init__(self):
        """Initialize the plot copier."""
        self.logger = logging.getLogger(__name__)

        # Source directory (where plots are generated)
        self.source_dir = utility_paths.METRICS_DIR_FILEPATH / "fixed_prompt_plots"

        # Destination directory (scrittura) - use relative path from SRC_DIR
        # SRC_DIR is Sustainable-Code-Refactoring-with-LLMs/src
        # We need to go up to tesi/ then into scrittura/
        project_root = utility_paths.SRC_DIR.parent  # Sustainable-Code-Refactoring-with-LLMs/
        tesi_dir = project_root.parent  # tesi/
        self.dest_dir = tesi_dir / "scrittura" / "plots" / "fixed_prompt_analysis"

        self.logger.info(f"Source directory: {self.source_dir}")
        self.logger.info(f"Destination directory: {self.dest_dir}")

    def copy_all_plots(self, force: bool = True) -> int:
        """
        Copy all plots from source to destination, maintaining directory structure.

        Args:
            force: If True, overwrite existing files. If False, skip existing files.

        Returns:
            Number of files copied
        """
        if not self.source_dir.exists():
            self.logger.error(f"Source directory does not exist: {self.source_dir}")
            return 0

        # Create destination directory if it doesn't exist
        self.dest_dir.mkdir(parents=True, exist_ok=True)

        copied_count = 0
        skipped_count = 0
        error_count = 0

        # Walk through source directory
        for source_file in self.source_dir.rglob("*.png"):
            # Calculate relative path from source_dir
            relative_path = source_file.relative_to(self.source_dir)

            # Calculate destination path
            dest_file = self.dest_dir / relative_path

            # Create parent directory if needed
            dest_file.parent.mkdir(parents=True, exist_ok=True)

            try:
                # Check if file exists and compare sizes/timestamps
                if dest_file.exists():
                    source_size = source_file.stat().st_size
                    dest_size = dest_file.stat().st_size
                    source_mtime = source_file.stat().st_mtime
                    dest_mtime = dest_file.stat().st_mtime

                    if not force and source_size == dest_size and source_mtime <= dest_mtime:
                        self.logger.debug(f"Skipping (identical): {relative_path}")
                        skipped_count += 1
                        continue

                    if source_mtime <= dest_mtime and source_size == dest_size:
                        self.logger.debug(f"Skipping (up-to-date): {relative_path}")
                        skipped_count += 1
                        continue

                # Copy file (force overwrite if force=True)
                shutil.copy2(source_file, dest_file)

                # Verify copy
                if dest_file.exists():
                    source_size = source_file.stat().st_size
                    dest_size = dest_file.stat().st_size

                    if source_size == dest_size:
                        self.logger.info(f"✓ Copied: {relative_path} ({source_size:,} bytes)")
                        copied_count += 1
                    else:
                        self.logger.error(f"✗ Size mismatch: {relative_path} "
                                        f"(source: {source_size:,}, dest: {dest_size:,})")
                        error_count += 1
                else:
                    self.logger.error(f"✗ Copy failed: {relative_path}")
                    error_count += 1

            except Exception as e:
                self.logger.error(f"✗ Error copying {relative_path}: {e}")
                error_count += 1

        # Summary
        self.logger.info("\n" + "="*80)
        self.logger.info("COPY SUMMARY")
        self.logger.info("="*80)
        self.logger.info(f"Files copied:  {copied_count}")
        self.logger.info(f"Files skipped: {skipped_count}")
        self.logger.info(f"Errors:        {error_count}")
        self.logger.info("="*80)

        return copied_count

    def verify_copy(self) -> bool:
        """
        Verify that all source files exist in destination with same size.

        Returns:
            True if all files match, False otherwise
        """
        if not self.source_dir.exists():
            self.logger.error(f"Source directory does not exist: {self.source_dir}")
            return False

        if not self.dest_dir.exists():
            self.logger.error(f"Destination directory does not exist: {self.dest_dir}")
            return False

        all_match = True
        total_files = 0

        for source_file in self.source_dir.rglob("*.png"):
            total_files += 1
            relative_path = source_file.relative_to(self.source_dir)
            dest_file = self.dest_dir / relative_path

            if not dest_file.exists():
                self.logger.error(f"✗ Missing in destination: {relative_path}")
                all_match = False
                continue

            source_size = source_file.stat().st_size
            dest_size = dest_file.stat().st_size

            if source_size != dest_size:
                self.logger.error(f"✗ Size mismatch: {relative_path} "
                                f"(source: {source_size:,}, dest: {dest_size:,})")
                all_match = False
            else:
                self.logger.debug(f"✓ Match: {relative_path}")

        if all_match:
            self.logger.info(f"\n✓ All {total_files} files verified successfully!")
        else:
            self.logger.error(f"\n✗ Verification failed for some files")

        return all_match


def main():
    """Main entry point."""
    import argparse

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s - %(name)s - %(levelname)s - %(message)s"
    )

    logger = logging.getLogger(__name__)

    parser = argparse.ArgumentParser(
        description="Copy fixed prompt analysis plots to scrittura directory"
    )
    parser.add_argument(
        "--verify-only",
        action="store_true",
        help="Only verify existing copies without copying"
    )
    parser.add_argument(
        "--no-force",
        action="store_true",
        help="Don't overwrite existing files if they appear identical"
    )
    parser.add_argument(
        "--debug",
        action="store_true",
        help="Enable debug logging"
    )

    args = parser.parse_args()

    if args.debug:
        logging.getLogger().setLevel(logging.DEBUG)

    logger.info("="*80)
    logger.info("FIXED PROMPT PLOTS COPY UTILITY")
    logger.info("="*80)

    try:
        copier = PlotCopier()

        if args.verify_only:
            logger.info("\nVerifying existing copies...")
            success = copier.verify_copy()
            return 0 if success else 1
        else:
            logger.info("\nCopying plots...")
            force = not args.no_force
            copied = copier.copy_all_plots(force=force)

            if copied > 0:
                logger.info("\nVerifying copied files...")
                success = copier.verify_copy()
                return 0 if success else 1
            else:
                logger.warning("No files were copied!")
                return 1

    except Exception as e:
        logger.error(f"Copy operation failed: {e}", exc_info=True)
        return 1


if __name__ == "__main__":
    sys.exit(main())
