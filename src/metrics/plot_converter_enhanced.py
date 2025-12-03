"""
Enhanced Plot Converter - PNG to PDF with Organization by Chapter

This script converts all PNG plots to PDF format for LaTeX inclusion,
organizing them by chapter according to thesis structure.


Date: 2025-11-13
"""

import sys
import os
from pathlib import Path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))

from PIL import Image
import logging
from typing import Dict, List

# Configure logging
logging.basicConfig(level=logging.INFO, format="%(asctime)s - %(levelname)s - %(message)s")
logger = logging.getLogger(__name__)


class PlotConverterEnhanced:
    """
    Enhanced converter for PNG to PDF with chapter organization.

    Converts plots and organizes them in scrittura/plots_pdf/ by chapter.
    """

    def __init__(self, plots_source_dir: Path, plots_pdf_dest_dir: Path):
        """
        Initialize converter.

        Args:
            plots_source_dir: Source directory with PNG plots (scrittura/plots/)
            plots_pdf_dest_dir: Destination directory for PDF plots (scrittura/plots_pdf/)
        """
        self.plots_source = Path(plots_source_dir)
        self.plots_pdf_dest = Path(plots_pdf_dest_dir)

        # Create destination structure
        self.chapter_3_dir = self.plots_pdf_dest / "chapter_3_dataset"
        self.chapter_4_dir = self.plots_pdf_dest / "chapter_4_results"
        self.chapter_5_dir = self.plots_pdf_dest / "chapter_5_discussion"
        self.appendix_dir = self.plots_pdf_dest / "appendix"

        for dir_path in [self.chapter_3_dir, self.chapter_4_dir, self.chapter_5_dir, self.appendix_dir]:
            dir_path.mkdir(parents=True, exist_ok=True)

        logger.info(f"PlotConverterEnhanced initialized")
        logger.info(f"  Source: {self.plots_source}")
        logger.info(f"  Destination: {self.plots_pdf_dest}")

    def convert_png_to_pdf(self, png_path: Path, pdf_path: Path) -> bool:
        """
        Convert single PNG file to PDF.

        Args:
            png_path: Path to source PNG file
            pdf_path: Path to destination PDF file

        Returns:
            True if successful, False otherwise
        """
        try:
            # Open PNG and convert to RGB (PDF doesn't support RGBA)
            image = Image.open(png_path)
            if image.mode == 'RGBA':
                # Create white background
                rgb_image = Image.new('RGB', image.size, (255, 255, 255))
                rgb_image.paste(image, mask=image.split()[3])  # Use alpha channel as mask
                image = rgb_image
            elif image.mode != 'RGB':
                image = image.convert('RGB')

            # Save as PDF
            image.save(pdf_path, 'PDF', resolution=300.0, quality=95)
            return True
        except Exception as e:
            logger.error(f"Error converting {png_path.name}: {e}")
            return False

    def get_chapter_mapping(self) -> Dict[str, Path]:
        """
        Define mapping of plot filenames to chapter directories.

        Returns:
            Dictionary mapping filename patterns to destination directories
        """
        mapping = {
            # Chapter 3: Dataset Analysis
            'chapter_3_dataset': [
                'dataset_language_distribution',
            ],

            # Chapter 4: Results (Pass Rate + Performance)
            'chapter_4_results': [
                'language_pass_rate_aggregated',
                'language_pass_rate_by_model',
                'mean_comparison_pass_rate_barplot',
                'energy_distribution_boxplot',
                'fig_improvement_distributions',
                'energy_vs_pass_rate_tradeoff',
                'fig_improvements_by_prompt',
                'fig_heatmap_model_prompt',
                'fig_improvements_by_model',
                'fig_improvements_by_language',
                'energy_by_language_boxplot',
                'energy_by_model_barplot',
                'energy_by_prompt_version_barplot',
                'carbon_distribution_boxplot',
                'carbon_by_language_boxplot',
                'carbon_by_model_barplot',
                'carbon_by_prompt_version_barplot',
            ],

            # Chapter 5: Discussion (Patterns, Similarity)
            'chapter_5_discussion': [
                'F2_cpu_all_patterns',
                'F3_ram_all_patterns',
                'F4_time_all_patterns',
                'F5_pattern_distribution',
                'generic_patterns_distribution',
                'F6_generic_heatmap',
                'F7_c_heatmap',
                'F8_java_heatmap',
                'F9_javascript_ts_heatmap',
                'F10_python_heatmap',
                'Fig13_top_patterns',
                '01_code_similarity_vs_delta_differences',
                '02_similarity_distribution',
                '03_similarity_by_llm_pair',
                '05_delta_metrics_distribution',
                '06_similarity_by_language',
                '07_language_llm_similarity_heatmap',
            ],

            # Appendix: Additional visualizations
            'appendix': [
                'prompt_versions_',
                'languages_',
                'model_prompt_version_',
                'language_model_',
                'fig_invalid_and_outliers',
                'fig_success_rate',
                'fig_model_prompt_combinations_boxplots',
            ],
        }

        return mapping

    def organize_and_convert_all(self):
        """
        Main method to convert all PNG plots to PDF and organize by chapter.
        """
        logger.info("=" * 80)
        logger.info("Starting PNG to PDF Conversion with Chapter Organization")
        logger.info("=" * 80)

        # Get chapter mapping
        chapter_mapping = self.get_chapter_mapping()

        # Track statistics
        total_converted = 0
        total_failed = 0

        # Find all PNG files recursively
        png_files = list(self.plots_source.rglob("*.png"))
        logger.info(f"Found {len(png_files)} PNG files to process")

        for png_file in png_files:
            # Determine destination based on filename
            dest_dir = self.appendix_dir  # Default to appendix

            for chapter, patterns in chapter_mapping.items():
                for pattern in patterns:
                    if pattern in png_file.stem:
                        if chapter == 'chapter_3_dataset':
                            dest_dir = self.chapter_3_dir
                        elif chapter == 'chapter_4_results':
                            dest_dir = self.chapter_4_dir
                        elif chapter == 'chapter_5_discussion':
                            dest_dir = self.chapter_5_dir
                        break

            # Create PDF path (preserve original filename, change extension)
            pdf_filename = png_file.stem + '.pdf'
            pdf_path = dest_dir / pdf_filename

            # Convert
            if self.convert_png_to_pdf(png_file, pdf_path):
                logger.info(f"  ✓ {png_file.stem} → {dest_dir.name}/{pdf_filename}")
                total_converted += 1
            else:
                logger.error(f"  ✗ Failed: {png_file.name}")
                total_failed += 1

        # Summary
        logger.info("\n" + "=" * 80)
        logger.info("Conversion Complete!")
        logger.info("=" * 80)
        logger.info(f"Total files processed: {len(png_files)}")
        logger.info(f"Successfully converted: {total_converted}")
        logger.info(f"Failed conversions: {total_failed}")
        logger.info(f"\nPDF plots organized in:")
        logger.info(f"  • {self.chapter_3_dir}")
        logger.info(f"  • {self.chapter_4_dir}")
        logger.info(f"  • {self.chapter_5_dir}")
        logger.info(f"  • {self.appendix_dir}")
        logger.info("=" * 80)


def main():
    """Main entry point."""
    # Determine paths relative to thesis root (one level above project root)
    # Script is in: Sustainable-Code-Refactoring-with-LLMs/src/metrics/
    # Project root is: Sustainable-Code-Refactoring-with-LLMs/
    # Thesis root is: /Users/piccoletto/Desktop/Everything/pisa/tesi/
    project_root = Path(__file__).parent.parent.parent
    thesis_root = project_root.parent  # Go one level up from project root
    plots_source = thesis_root / "scrittura" / "plots"
    plots_pdf_dest = thesis_root / "scrittura" / "plots_pdf"

    if not plots_source.exists():
        logger.error(f"Source directory not found: {plots_source}")
        return 1

    try:
        converter = PlotConverterEnhanced(plots_source, plots_pdf_dest)
        converter.organize_and_convert_all()
        return 0
    except Exception as e:
        logger.error(f"Conversion failed: {e}", exc_info=True)
        return 1


if __name__ == "__main__":
    import sys
    sys.exit(main())
