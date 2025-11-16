#!/bin/bash
#
# Re-execute JavaScript Tests Only
#
# This script uses run_tests_on_cluster.py with language-selective execution
# to re-run ONLY JavaScript tests and merge results into existing JSON files.
#
# Purpose:
# - Diagnose and fix JavaScript 5.1% pass rate issue
# - Execute all 328 JavaScript entries across 107 clusters
# - Merge results without overwriting other languages
#
# Usage:
#   ./rerun_javascript.sh [options]
#
# Options:
#   --cluster NAME    Run specific cluster only
#   --dry-run         List clusters without executing
#   --base-only       Run only base code (not LLM)
#   --llm-only        Run only LLM code (all prompts)
#   --prompt VERSION  Run specific prompt version (v1-v4)
#   --executions N    Number of executions per entry (default: 5)
#
# Date: 2025-01-14

# Don't exit on errors - we want to continue even if one cluster fails
# set -e

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Default values
CLUSTER=""
DRY_RUN=false
BASE_ONLY=false
LLM_ONLY=false
PROMPT_VERSION=""
NUM_EXECUTIONS=5
LANGUAGE="javascript"
SKIP_CONFIRMATION=false

# Parse arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --cluster)
            CLUSTER="$2"
            shift 2
            ;;
        --dry-run)
            DRY_RUN=true
            shift
            ;;
        --base-only)
            BASE_ONLY=true
            shift
            ;;
        --llm-only)
            LLM_ONLY=true
            shift
            ;;
        --prompt)
            PROMPT_VERSION="$2"
            shift 2
            ;;
        --executions)
            NUM_EXECUTIONS="$2"
            shift 2
            ;;
        --yes|-y)
            SKIP_CONFIRMATION=true
            shift
            ;;
        --help|-h)
            echo "Usage: $0 [options]"
            echo ""
            echo "Options:"
            echo "  --cluster NAME      Run specific cluster only"
            echo "  --dry-run           List clusters without executing"
            echo "  --base-only         Run only base code (not LLM)"
            echo "  --llm-only          Run only LLM code (all prompts)"
            echo "  --prompt VERSION    Run specific prompt version (v1-v4)"
            echo "  --executions N      Number of executions per entry (default: 5)"
            echo "  --help, -h          Show this help message"
            exit 0
            ;;
        *)
            echo -e "${RED}Unknown option: $1${NC}"
            echo "Use --help for usage information"
            exit 1
            ;;
    esac
done

echo -e "${YELLOW}============================================================${NC}"
echo -e "${YELLOW}JavaScript-Only Test Re-Execution${NC}"
echo -e "${YELLOW}============================================================${NC}"
echo ""
echo -e "${BLUE}Configuration:${NC}"
echo -e "  Language: ${GREEN}${LANGUAGE}${NC}"
echo -e "  Executions per entry: ${NUM_EXECUTIONS}"
if [ -n "$CLUSTER" ]; then
    echo -e "  Target cluster: ${GREEN}${CLUSTER}${NC}"
else
    echo -e "  Target: ${GREEN}All clusters with JavaScript${NC}"
fi

if [ "$BASE_ONLY" = true ]; then
    echo -e "  Mode: ${YELLOW}Base code only${NC}"
elif [ "$LLM_ONLY" = true ]; then
    if [ -n "$PROMPT_VERSION" ]; then
        echo -e "  Mode: ${YELLOW}LLM code - ${PROMPT_VERSION} only${NC}"
    else
        echo -e "  Mode: ${YELLOW}LLM code - all prompts (v1-v4)${NC}"
    fi
else
    echo -e "  Mode: ${YELLOW}Full execution (base + LLM)${NC}"
fi

echo ""

# Count JavaScript clusters
echo -e "${BLUE}Analyzing clusters...${NC}"
cd ../clusters
JS_CLUSTER_COUNT=$(python3 -c "
import json, glob
count = 0
clusters = []
skip_patterns = ['debug', 'test', 'bad_entries', 'focused_', 'with_metrics']
for f in sorted(glob.glob('cluster_*.json')):
    # Skip clusters with exclusion patterns
    if any(skip in f for skip in skip_patterns):
        continue
    try:
        with open(f) as fp:
            data = json.load(fp)
            if 'javascript' in data and len(data['javascript']) > 0:
                cluster_name = f.replace('cluster_', '').replace('.json', '')
                # Double-check cluster name doesn't contain patterns
                if not any(skip in cluster_name for skip in skip_patterns):
                    count += 1
                    clusters.append(cluster_name)
    except:
        pass
print(count)
for c in clusters:
    print(c)
" 2>/dev/null)

JS_CLUSTERS=$(echo "$JS_CLUSTER_COUNT" | tail -n +2)
JS_COUNT=$(echo "$JS_CLUSTER_COUNT" | head -n 1)

echo -e "${GREEN}Found ${JS_COUNT} clusters with JavaScript entries${NC}"

if [ "$DRY_RUN" = true ]; then
    echo ""
    echo -e "${YELLOW}DRY RUN MODE - No execution will occur${NC}"
    echo ""
    echo "Clusters with JavaScript:"
    echo "$JS_CLUSTERS" | nl
    exit 0
fi

# Return to test runner directory
cd ../run_tests_on_clusters

# Create log file
LOG_FILE="javascript_rerun_$(date +%Y%m%d_%H%M%S).log"
echo -e "${BLUE}Logging to: ${LOG_FILE}${NC}"
echo ""

# Confirmation
if [ -z "$CLUSTER" ] && [ "$SKIP_CONFIRMATION" = false ]; then
    echo -e "${YELLOW}About to re-execute JavaScript tests for ${JS_COUNT} clusters${NC}"
    read -p "Continue? (y/n) " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        echo "Aborted."
        exit 1
    fi
elif [ -z "$CLUSTER" ]; then
    echo -e "${YELLOW}About to re-execute JavaScript tests for ${JS_COUNT} clusters${NC}"
fi

echo ""
echo -e "${GREEN}Starting execution...${NC}"
echo ""

# Build base command
BASE_CMD="python3 run_tests_on_cluster.py"
BASE_CMD+=" --languages javascript"
BASE_CMD+=" --run-quantity ${NUM_EXECUTIONS}"
BASE_CMD+=" --selective-rerun"  # Enable language-selective merging
BASE_CMD+=" --overwrite-results"  # Force overwrite to fix existing bad results

# Track statistics
TOTAL_EXECUTED=0
TOTAL_SUCCESS=0
TOTAL_FAILED=0

# Function to execute single cluster
execute_cluster() {
    local cluster_name=$1
    local mode=$2  # "base", "llm", or "full"
    local prompt_ver=$3  # Optional prompt version

    echo -e "${BLUE}[$(date +%H:%M:%S)]${NC} Processing cluster: ${GREEN}${cluster_name}${NC}"

    CMD="${BASE_CMD} --cluster-name ${cluster_name}"

    if [ "$mode" = "llm" ]; then
        CMD+=" --llm-only"
        if [ -n "$prompt_ver" ]; then
            # Extract version number (v1 -> 1)
            ver_num="${prompt_ver#v}"
            CMD+=" --prompt-version ${ver_num}"
        fi
    elif [ "$mode" = "base" ]; then
        CMD+=" --base-only"
    fi

    # Execute with logging
    if $CMD >> "${LOG_FILE}" 2>&1; then
        echo -e "  ${GREEN}✓ Success${NC}"
        ((TOTAL_SUCCESS++))
    else
        echo -e "  ${RED}✗ Failed${NC} (see ${LOG_FILE})"
        ((TOTAL_FAILED++))
    fi

    ((TOTAL_EXECUTED++))
}

# Execute based on mode
if [ -n "$CLUSTER" ]; then
    # Single cluster mode
    if [ "$BASE_ONLY" = true ]; then
        execute_cluster "$CLUSTER" "base"
    elif [ "$LLM_ONLY" = true ]; then
        if [ -n "$PROMPT_VERSION" ]; then
            execute_cluster "$CLUSTER" "llm" "$PROMPT_VERSION"
        else
            for pv in v1 v2 v3 v4; do
                execute_cluster "$CLUSTER" "llm" "$pv"
            done
        fi
    else
        # Full execution
        execute_cluster "$CLUSTER" "base"
        for pv in v1 v2 v3 v4; do
            execute_cluster "$CLUSTER" "llm" "$pv"
        done
    fi
else
    # All clusters mode
    for cluster in $JS_CLUSTERS; do
        if [ "$BASE_ONLY" = true ]; then
            execute_cluster "$cluster" "base"
        elif [ "$LLM_ONLY" = true ]; then
            if [ -n "$PROMPT_VERSION" ]; then
                execute_cluster "$cluster" "llm" "$PROMPT_VERSION"
            else
                for pv in v1 v2 v3 v4; do
                    execute_cluster "$cluster" "llm" "$pv"
                done
            fi
        else
            # Full execution
            execute_cluster "$cluster" "base"
            for pv in v1 v2 v3 v4; do
                execute_cluster "$cluster" "llm" "$pv"
            done
        fi
    done
fi

echo ""
echo -e "${YELLOW}============================================================${NC}"
echo -e "${YELLOW}Execution Complete${NC}"
echo -e "${YELLOW}============================================================${NC}"
echo ""
echo -e "${BLUE}Statistics:${NC}"
echo -e "  Total executions: ${TOTAL_EXECUTED}"
echo -e "  Successful: ${GREEN}${TOTAL_SUCCESS}${NC}"
echo -e "  Failed: ${RED}${TOTAL_FAILED}${NC}"
echo ""
echo -e "${BLUE}Log file: ${LOG_FILE}${NC}"
echo ""

# Analyze results
echo -e "${BLUE}Analyzing JavaScript pass rates...${NC}"
cd ../metrics
python3 pass_rate_analyzer.py

echo ""
echo -e "${GREEN}Done!${NC}"
