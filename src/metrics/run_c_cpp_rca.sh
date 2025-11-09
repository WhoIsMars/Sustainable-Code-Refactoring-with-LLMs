#!/bin/bash

###############################################################################
# Run C vs C++ Root Cause Analysis (Section 5.3)
#
# This script executes comprehensive Root Cause Analysis to investigate
# why C++ has systematically lower pass rates compared to C.
#
# Features:
# - Global pass rate comparison (C vs C++)
# - Error classification and quantification
# - Code diff generation (side-by-side comparisons)
# - Build configuration analysis
# - Comprehensive markdown report for thesis
#
# Usage: ./run_c_cpp_rca.sh [OPTIONS]
#
# Options:
#   --top-n N        Analyze top N clusters in detail (default: 5)
#   --quick          Run quick analysis (top 3 clusters)
#   --full           Run comprehensive analysis (all available clusters)
#   --help           Show this help message
###############################################################################

# Get script directory
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR"

# Colors for output
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Default parameters
TOP_N=5

# Parse arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --top-n)
            TOP_N="$2"
            shift 2
            ;;
        --quick)
            TOP_N=3
            shift
            ;;
        --full)
            TOP_N=999
            shift
            ;;
        --help)
            head -n 24 "$0" | tail -n +3
            exit 0
            ;;
        *)
            echo -e "${RED}Unknown option: $1${NC}"
            echo "Use --help for usage information"
            exit 1
            ;;
    esac
done

echo "================================================================================"
echo "C vs C++ ROOT CAUSE ANALYSIS - Section 5.3"
echo "================================================================================"
echo ""
echo -e "${BLUE}Configuration:${NC}"
echo "  - Clusters for detailed analysis: $TOP_N"
echo "  - Output directory: c_cpp_analysis/"
echo ""
echo -e "${YELLOW}⚠️  This analysis may take several minutes depending on dataset size${NC}"
echo ""
read -p "Press Enter to continue or Ctrl+C to cancel..."
echo ""

echo "================================================================================"
echo "Starting Root Cause Analysis..."
echo "================================================================================"
echo ""

# Run the analysis
python3 c_cpp_comparator.py --top-n "$TOP_N" --generate-diffs --full-report

EXIT_CODE=$?

if [ $EXIT_CODE -ne 0 ]; then
    echo ""
    echo -e "${RED}✗ Error during Root Cause Analysis${NC}"
    echo "Exit code: $EXIT_CODE"
    exit $EXIT_CODE
fi

echo ""
echo "================================================================================"
echo -e "${GREEN}ROOT CAUSE ANALYSIS COMPLETE!${NC}"
echo "================================================================================"
echo ""
echo "📁 Output files in: c_cpp_analysis/"
echo ""
echo "Generated files:"
echo "  📊 global_statistics.json       - Pass rate statistics (C vs C++)"
echo "  📋 error_classification.json    - Error types and root causes"
echo "  📝 RCA_report.md                - Comprehensive markdown report"
echo "  📂 cluster_reports/             - Individual cluster diff files"
echo ""
echo -e "${BLUE}Next steps:${NC}"
echo "  1. Review RCA_report.md for comprehensive analysis"
echo "  2. Check global_statistics.json for quantitative data"
echo "  3. Examine cluster_reports/ for specific code examples"
echo "  4. Incorporate findings into thesis Section 5.3"
echo ""
echo "================================================================================"
echo ""
