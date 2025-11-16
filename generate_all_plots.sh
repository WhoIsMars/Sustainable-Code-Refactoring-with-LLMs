#!/bin/bash

################################################################################
# Master Script for Thesis Plot Generation Pipeline
#
# This script orchestrates the complete plot generation workflow:
# 1. Generates all statistical plots from source data
# 2. Copies plots to scrittura/plots/ maintaining organization
# 3. Converts PNG plots to PDF for LaTeX inclusion
#
# Date: 2025-11-13
################################################################################

set -e  # Exit immediately if a command exits with a non-zero status

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Get script directory and project paths
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# The script is in Sustainable-Code-Refactoring-with-LLMs, but the thesis root is one level up
THESIS_ROOT="$( cd "$SCRIPT_DIR/.." && pwd )"
SRC_DIR="$SCRIPT_DIR/src"
PLOTS_DEST="$THESIS_ROOT/scrittura/plots"
PLOTS_PDF_DEST="$THESIS_ROOT/scrittura/plots_pdf"

# Log file - in the script directory (project directory)
LOG_FILE="$SCRIPT_DIR/plot_generation.log"
echo "=== Plot Generation Pipeline Started at $(date) ===" > "$LOG_FILE"

# Helper function for logging
log_info() {
    echo -e "${BLUE}[INFO]${NC} $1" | tee -a "$LOG_FILE"
}

log_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1" | tee -a "$LOG_FILE"
}

log_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1" | tee -a "$LOG_FILE"
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $1" | tee -a "$LOG_FILE"
}

# Check if Python is available
if ! command -v python3 &> /dev/null; then
    log_error "Python3 is not installed or not in PATH"
    exit 1
fi

log_info "Starting plot generation pipeline..."
log_info "Script directory: $SCRIPT_DIR"
log_info "Thesis root: $THESIS_ROOT"
log_info "Plots destination: $PLOTS_DEST"
echo ""

################################################################################
# STEP 1: Dataset Statistics
################################################################################
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
log_info "[1/8] Generating dataset statistics..."
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"

cd "$SRC_DIR/stats_dataset"
if python3 dataset_stats_creator.py >> "$LOG_FILE" 2>&1; then
    log_success "Dataset statistics generated"
else
    log_error "Failed to generate dataset statistics"
    exit 1
fi
cd "$SCRIPT_DIR"
echo ""

################################################################################
# STEP 2: Execution Metrics Analysis
################################################################################
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
log_info "[2/8] Generating execution metrics and pass rate analysis..."
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"

cd "$SRC_DIR/metrics"
if python3 main_exec_metrics_analysis.py >> "$LOG_FILE" 2>&1; then
    log_success "Execution metrics and pass rate analysis completed"
else
    log_error "Failed to generate execution metrics"
    exit 1
fi
cd "$SCRIPT_DIR"
echo ""

################################################################################
# STEP 3: Energy Improvements Analysis
################################################################################
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
log_info "[3/8] Generating energy improvements analysis..."
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"

cd "$SRC_DIR/metrics/energy_improvements"
if python3 analyze_energy_improvements.py >> "$LOG_FILE" 2>&1; then
    log_success "Energy improvements analysis completed"
else
    log_error "Failed to generate energy improvements analysis"
    exit 1
fi
cd "$SCRIPT_DIR"
echo ""

################################################################################
# STEP 4: Energy and Carbon Analyzer
################################################################################
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
log_info "[4/8] Generating energy and carbon footprint plots..."
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"

cd "$SRC_DIR/metrics/energy_improvements"
if python3 energy_analyzer.py >> "$LOG_FILE" 2>&1; then
    log_success "Energy and carbon plots generated"
else
    log_error "Failed to generate energy and carbon plots"
    exit 1
fi
cd "$SCRIPT_DIR"
echo ""

################################################################################
# STEP 5: Fixed Prompt Analysis (v1 and v4)
################################################################################
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
log_info "[5/8] Generating fixed prompt analysis (v1 and v4)..."
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"

cd "$SRC_DIR/metrics"
if python3 fixed_prompt_analysis.py >> "$LOG_FILE" 2>&1; then
    log_success "Fixed prompt analysis completed"

    # Copy plots to scrittura directory
    log_info "Copying fixed prompt plots to scrittura..."
    if python3 copy_plots_to_scrittura.py >> "$LOG_FILE" 2>&1; then
        log_success "Fixed prompt plots copied to scrittura"
    else
        log_error "Failed to copy fixed prompt plots to scrittura"
        exit 1
    fi
else
    log_warning "Fixed prompt analysis script may not exist yet or failed"
fi
cd "$SCRIPT_DIR"
echo ""

################################################################################
# STEP 6: Pattern Analysis
################################################################################
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
log_info "[6/8] Generating pattern analysis plots..."
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"

cd "$SRC_DIR/metrics/patterns"
if python3 main_correct_pattern_analysis.py >> "$LOG_FILE" 2>&1; then
    log_success "Pattern analysis completed"
else
    log_error "Failed to generate pattern analysis"
    exit 1
fi
cd "$SCRIPT_DIR"
echo ""

################################################################################
# STEP 7: Copy Plots to scrittura/plots/
################################################################################
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
log_info "[7/8] Copying plots to scrittura/plots/ directories..."
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"

# Create directories if they don't exist
mkdir -p "$PLOTS_DEST/dataset"
mkdir -p "$PLOTS_DEST/execution_stats_plots"
mkdir -p "$PLOTS_DEST/improvements"
mkdir -p "$PLOTS_DEST/patterns"
mkdir -p "$PLOTS_DEST/similarity"
mkdir -p "$PLOTS_DEST/fixed_prompt_analysis"

# Copy dataset plots
log_info "Copying dataset plots..."
if [ -d "$SRC_DIR/stats_dataset/reports" ]; then
    cp -f "$SRC_DIR/stats_dataset/reports"/*.png "$PLOTS_DEST/dataset/" 2>/dev/null || log_warning "No dataset PNG files found"
    cp -f "$SRC_DIR/stats_dataset/reports"/*.svg "$PLOTS_DEST/dataset/" 2>/dev/null || true
fi

# Copy execution stats plots - RECURSIVE COPY TO PRESERVE STRUCTURE
log_info "Copying execution stats plots..."
if [ -d "$SRC_DIR/metrics/execution_stats_plots" ]; then
    # Remove old content to ensure clean copy
    rm -rf "$PLOTS_DEST/execution_stats_plots"/*
    # Copy entire structure recursively
    cp -R "$SRC_DIR/metrics/execution_stats_plots"/* "$PLOTS_DEST/execution_stats_plots/" 2>/dev/null || log_warning "No execution stats files found"
    log_info "  Copied execution_stats_plots/ with full subdirectory structure"
fi

# Copy energy improvements plots
log_info "Copying energy improvements plots..."
mkdir -p "$PLOTS_DEST/improvements/metrics"
if [ -d "$SRC_DIR/metrics/energy_improvements" ]; then
    cp -f "$SRC_DIR/metrics/energy_improvements"/fig_*.png "$PLOTS_DEST/improvements/metrics/" 2>/dev/null || log_warning "No fig_*.png files found"
fi

# Copy energy analyzer plots from plots/ subdirectory
if [ -d "$SRC_DIR/metrics/energy_improvements/plots" ]; then
    mkdir -p "$PLOTS_DEST/improvements/energy_improvements"
    mkdir -p "$PLOTS_DEST/improvements/carbon_improvements"
    cp -f "$SRC_DIR/metrics/energy_improvements/plots"/energy*.png "$PLOTS_DEST/improvements/energy_improvements/" 2>/dev/null || true
    cp -f "$SRC_DIR/metrics/energy_improvements/plots"/carbon*.png "$PLOTS_DEST/improvements/carbon_improvements/" 2>/dev/null || true
fi

# Copy pattern analysis plots
log_info "Copying pattern analysis plots..."
if [ -d "$SRC_DIR/metrics/patterns/pattern_analysis" ]; then
    mkdir -p "$PLOTS_DEST/patterns"
    cp -f "$SRC_DIR/metrics/patterns/pattern_analysis"/*.png "$PLOTS_DEST/patterns/" 2>/dev/null || log_warning "No pattern analysis PNG files found"
    log_success "  Copied $(ls "$SRC_DIR/metrics/patterns/pattern_analysis"/*.png 2>/dev/null | wc -l) pattern plots"
fi

# Copy fixed prompt analysis plots (if generated)
log_info "Copying fixed prompt analysis plots..."
if [ -d "$SRC_DIR/metrics/fixed_prompt_plots" ]; then
    # FIRST: Remove all existing content to ensure clean copy
    log_info "  Removing old fixed_prompt_analysis plots..."
    rm -rf "$PLOTS_DEST/fixed_prompt_analysis"

    # SECOND: Recreate directory
    mkdir -p "$PLOTS_DEST/fixed_prompt_analysis"

    # THIRD: Copy entire structure recursively with verbose output
    log_info "  Copying new fixed_prompt_analysis plots..."
    if cp -Rv "$SRC_DIR/metrics/fixed_prompt_plots"/* "$PLOTS_DEST/fixed_prompt_analysis/" >> "$LOG_FILE" 2>&1; then
        # Count copied files
        COPIED_COUNT=$(find "$PLOTS_DEST/fixed_prompt_analysis" -type f -name "*.png" | wc -l | tr -d ' ')
        log_success "  Copied $COPIED_COUNT fixed prompt analysis plot files"
    else
        log_error "  Failed to copy fixed prompt plots - check permissions"
        exit 1
    fi
else
    log_warning "  Source directory $SRC_DIR/metrics/fixed_prompt_plots not found"
fi

log_success "All plots copied to scrittura/plots/"
echo ""

################################################################################
# STEP 8: Convert PNG to PDF
################################################################################
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
log_info "[8/8] Converting PNG plots to PDF for LaTeX inclusion..."
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"

cd "$SRC_DIR/metrics"
if python3 plot_converter_enhanced.py >> "$LOG_FILE" 2>&1; then
    log_success "PNG to PDF conversion completed"
else
    log_warning "Plot converter may not exist yet or failed"
fi
cd "$SCRIPT_DIR"
echo ""

################################################################################
# COMPLETION SUMMARY
################################################################################
echo ""
echo -e "${GREEN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
echo -e "${GREEN}                   PLOT GENERATION PIPELINE COMPLETED                    ${NC}"
echo -e "${GREEN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
echo ""
log_success "All plot generation tasks completed successfully!"
echo ""
echo -e "${YELLOW}Output locations:${NC}"
echo "  • Source plots (PNG):  $PLOTS_DEST"
echo "  • PDF plots (LaTeX):   $PLOTS_PDF_DEST"
echo "  • Log file:            $LOG_FILE"
echo ""
echo -e "${YELLOW}Next steps:${NC}"
echo "  1. Review generated plots in scrittura/plots/"
echo "  2. Check PDF conversions in scrittura/plots_pdf/"
echo "  3. Compile thesis: cd scrittura/main && ./compile.sh"
echo ""
echo "=== Plot Generation Pipeline Completed at $(date) ===" >> "$LOG_FILE"
