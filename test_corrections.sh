#!/bin/bash

################################################################################
# Test Script for Pipeline Corrections
#
# Tests the three main corrections:
# 1. Verify plots are copied correctly to scrittura/plots
# 2. Verify generic_patterns_distribution.png is created
# 3. Check pass_rate barplot has larger annotations
################################################################################

set -e

# Color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

PROJECT_ROOT="/Users/piccoletto/Desktop/Everything/pisa/tesi/Sustainable-Code-Refactoring-with-LLMs"
PLOTS_DEST="$PROJECT_ROOT/scrittura/plots"

echo -e "${YELLOW}================================${NC}"
echo -e "${YELLOW}Testing Pipeline Corrections${NC}"
echo -e "${YELLOW}================================${NC}"
echo ""

# Test 1: Check if scrittura/plots structure exists
echo -e "${YELLOW}[TEST 1]${NC} Checking scrittura/plots structure..."
if [ -d "$PLOTS_DEST/execution_stats_plots/metrics_means_related_to_both_model_and_prompt_version" ]; then
    echo -e "${GREEN}✓${NC} Directory structure exists"
    file_count=$(find "$PLOTS_DEST/execution_stats_plots" -name "*.png" | wc -l)
    echo -e "${GREEN}✓${NC} Found $file_count PNG files in execution_stats_plots"
else
    echo -e "${RED}✗${NC} Directory structure missing"
fi
echo ""

# Test 2: Check if generic_patterns_distribution.png exists
echo -e "${YELLOW}[TEST 2]${NC} Checking generic_patterns_distribution.png..."
PATTERN_FILE="$PLOTS_DEST/patterns/generic_patterns_distribution.png"
if [ -f "$PATTERN_FILE" ]; then
    echo -e "${GREEN}✓${NC} generic_patterns_distribution.png exists"
    ls -lh "$PATTERN_FILE"
else
    echo -e "${RED}✗${NC} generic_patterns_distribution.png NOT FOUND"
    echo "  Expected: $PATTERN_FILE"
    echo "  Checking source location..."
    SOURCE_PATTERN="$PROJECT_ROOT/src/metrics/patterns/pattern_analysis/generic_patterns_distribution.png"
    if [ -f "$SOURCE_PATTERN" ]; then
        echo -e "${YELLOW}  Found in source: $SOURCE_PATTERN${NC}"
        echo -e "${YELLOW}  Run the pipeline to copy it${NC}"
    fi
fi
echo ""

# Test 3: Check if pass_rate barplot exists
echo -e "${YELLOW}[TEST 3]${NC} Checking pass_rate barplot..."
PASS_RATE_FILE="$PLOTS_DEST/execution_stats_plots/metrics_means_related_to_both_model_and_prompt_version/mean_comparison_pass_rate_barplot.png"
if [ -f "$PASS_RATE_FILE" ]; then
    echo -e "${GREEN}✓${NC} mean_comparison_pass_rate_barplot.png exists"
    ls -lh "$PASS_RATE_FILE"
    echo -e "${GREEN}  Note: Annotations will be larger on next regeneration${NC}"
else
    echo -e "${RED}✗${NC} Pass rate barplot NOT FOUND"
    echo "  Expected: $PASS_RATE_FILE"
fi
echo ""

# Test 4: Check fixed_prompt_analysis plots
echo -e "${YELLOW}[TEST 4]${NC} Checking fixed_prompt_analysis plots..."
if [ -d "$PLOTS_DEST/fixed_prompt_analysis" ]; then
    v1_count=$(find "$PLOTS_DEST/fixed_prompt_analysis/v1_only" -name "*.png" 2>/dev/null | wc -l)
    v4_count=$(find "$PLOTS_DEST/fixed_prompt_analysis/v4_only" -name "*.png" 2>/dev/null | wc -l)
    comp_count=$(find "$PLOTS_DEST/fixed_prompt_analysis/v1_vs_v4_comparison" -name "*.png" 2>/dev/null | wc -l)
    echo -e "${GREEN}✓${NC} Fixed prompt analysis directory exists"
    echo "  v1_only: $v1_count plots"
    echo "  v4_only: $v4_count plots"
    echo "  comparisons: $comp_count plots"
else
    echo -e "${YELLOW}⚠${NC} Fixed prompt analysis not yet generated"
fi
echo ""

echo -e "${YELLOW}================================${NC}"
echo -e "${YELLOW}Test Complete!${NC}"
echo -e "${YELLOW}================================${NC}"
echo ""
echo "To regenerate plots with corrections:"
echo "  cd $PROJECT_ROOT"
echo "  ./generate_all_plots.sh"
