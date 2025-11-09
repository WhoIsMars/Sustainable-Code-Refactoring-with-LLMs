#!/bin/bash

###############################################################################
# Run Pass Rate Analysis (Section 4.1)
#
# This script executes the complete pass rate analysis workflow:
# 1. Calculates pass rates across all clusters
# 2. Generates 30 visualization plots (2 overview + 28 drill-down)
# 3. Creates summary report
#
# Usage: ./run_pass_rate_analysis.sh
###############################################################################

echo "================================================================================"
echo "PASS RATE ANALYSIS - Section 4.1"
echo "================================================================================"
echo ""

# Get script directory
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR"

# Colors for output
GREEN='\033[0;32m'
BLUE='\033[0;34m'
RED='\033[0;31m'
NC='\033[0m' # No Color

echo -e "${BLUE}[Step 1/2]${NC} Running pass rate analyzer..."
python3 pass_rate_analyzer.py

if [ $? -ne 0 ]; then
    echo -e "${RED}✗ Error during pass rate analysis${NC}"
    exit 1
fi

echo ""
echo -e "${GREEN}✓ Pass rate analysis completed${NC}"
echo ""

echo -e "${BLUE}[Step 2/2]${NC} Generating visualizations..."
python3 pass_rate_visualizator.py

if [ $? -ne 0 ]; then
    echo -e "${RED}✗ Error during visualization generation${NC}"
    exit 1
fi

echo ""
echo -e "${GREEN}✓ Visualizations generated${NC}"
echo ""

# Print summary
echo "================================================================================"
echo "PASS RATE ANALYSIS COMPLETE!"
echo "================================================================================"
echo ""
echo "Output files:"
echo "  📊 Statistics: execution_stats/pass_rate_aggregated.json"
echo "  📈 Overview graphs:"
echo "     - execution_stats_plots/language_pass_rate_aggregated.png"
echo "     - execution_stats_plots/language_pass_rate_by_model.png"
echo "  📉 Drill-down graphs: execution_stats_plots/language_pass_rate/v{1-4}/*.png"
echo "  📝 Summary report: execution_stats_plots/pass_rate_summary_report.md"
echo ""
echo "Total visualizations generated: 30 (2 overview + 28 drill-down)"
echo ""
echo "================================================================================"
echo ""
