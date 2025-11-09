#!/usr/bin/env python3
"""
Convert PNG plots to PDF for LaTeX inclusion
"""

import os
from pathlib import Path
from PIL import Image

# Directories
PLOTS_DIR = Path("/Users/piccoletto/Desktop/Everything/pisa/tesi/Sustainable-Code-Refactoring-with-LLMs/src/metrics/execution_stats_plots")
OUTPUT_DIR = Path("/Users/piccoletto/Desktop/Everything/pisa/tesi/Sustainable-Code-Refactoring-with-LLMs/scrittura/main/plots_pdf")

# Key plots needed for Chapter 3
REQUIRED_PLOTS = {
    # Section 3.3 - Prompt versions
    "prompt_versions_energy_joules_boxplot.png": "prompt_versions_energy_joules_boxplot.pdf",

    # Section 3.1 - Dataset distribution (we'll need to create this)
    # For now, we'll convert what we have
}

# Additional plots that might be useful
ADDITIONAL_PLOTS = [
    # Prompt versions
    "metrics_means_related_to_prompt_versions/prompt_versions_energy_joules_boxplot.png",
    "metrics_means_related_to_prompt_versions/prompt_versions_CPU_usage_boxplot.png",
    "metrics_means_related_to_prompt_versions/prompt_versions_RAM_usage_boxplot.png",
    "metrics_means_related_to_prompt_versions/prompt_versions_execution_time_ms_boxplot.png",

    # Languages
    "metrics_means_related_to_languages/languages_llm_energy_joules_boxplot.png",
    "metrics_means_related_to_languages/languages_llm_CPU_usage_boxplot.png",
    "metrics_means_related_to_languages/languages_llm_RAM_usage_boxplot.png",

    # Pass rate
    "language_pass_rate_aggregated.png",
    "language_pass_rate_by_model.png",
]

def convert_png_to_pdf(png_path: Path, pdf_path: Path):
    """Convert a PNG image to PDF"""
    try:
        image = Image.open(png_path)
        # Convert RGBA to RGB if necessary
        if image.mode == 'RGBA':
            # Create a white background
            background = Image.new('RGB', image.size, (255, 255, 255))
            background.paste(image, mask=image.split()[3])  # 3 is the alpha channel
            image = background
        elif image.mode != 'RGB':
            image = image.convert('RGB')

        image.save(pdf_path, 'PDF', resolution=100.0)
        print(f"✓ Converted: {png_path.name} -> {pdf_path.name}")
        return True
    except Exception as e:
        print(f"✗ Failed to convert {png_path.name}: {e}")
        return False

def main():
    print("=" * 80)
    print("Converting PNG plots to PDF for LaTeX")
    print("=" * 80)
    print()

    # Create output directory if it doesn't exist
    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)
    print(f"Output directory: {OUTPUT_DIR}")
    print()

    converted = 0
    failed = 0

    # Convert all additional plots
    for plot_rel_path in ADDITIONAL_PLOTS:
        png_path = PLOTS_DIR / plot_rel_path

        if not png_path.exists():
            print(f"⚠ Skipping (not found): {plot_rel_path}")
            continue

        # Create output filename
        pdf_filename = png_path.stem + ".pdf"
        pdf_path = OUTPUT_DIR / pdf_filename

        if convert_png_to_pdf(png_path, pdf_path):
            converted += 1
        else:
            failed += 1

    print()
    print("=" * 80)
    print(f"Conversion complete: {converted} succeeded, {failed} failed")
    print(f"PDF files saved to: {OUTPUT_DIR}")
    print("=" * 80)

if __name__ == "__main__":
    main()
