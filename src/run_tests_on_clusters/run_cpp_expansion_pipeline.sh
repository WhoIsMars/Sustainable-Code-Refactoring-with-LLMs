#!/bin/bash
################################################################################
# C++ Dataset Expansion Pipeline with Test Validation
#
# This script orchestrates the complete pipeline for adding validated C++ entries:
# 1. Ingest & Validate: Download entries + run 5 test executions
# 2. Generate LLM: Create 12 LLM variants per entry
# 3. Execute LLM Tests: Run 5 test executions for each LLM variant
# 4. Analyze Metrics: Recalculate statistics and generate plots
#
# Author: Sustainable Code Refactoring with LLMs Research Project
# Date: 2025-01-10
################################################################################

set -o pipefail  # Exit on pipe failures

#=============================================================================
# CONFIGURATION
#=============================================================================

# Default values
TARGET_ENTRIES=100
LANGUAGE="cpp"
MAX_REPOS=50
DRY_RUN=false
PROJECT_ROOT="$(cd "$(dirname "$0")/../.." && pwd)"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

#=============================================================================
# PARSE ARGUMENTS
#=============================================================================

usage() {
    echo "Usage: $0 [OPTIONS]"
    echo ""
    echo "Options:"
    echo "  --dry-run          Show what would be executed without running"
    echo "  --target N         Target number of entries to ingest (default: 100)"
    echo "  --language LANG    Language to process: cpp or c (default: cpp)"
    echo "  --max-repos N      Maximum repositories to search (default: 50)"
    echo "  --help             Show this help message"
    echo ""
    echo "Example:"
    echo "  $0 --target 50 --dry-run"
    echo "  $0 --language cpp --target 100"
    exit 1
}

while [[ $# -gt 0 ]]; do
    case $1 in
        --dry-run)
            DRY_RUN=true
            shift
            ;;
        --target)
            TARGET_ENTRIES="$2"
            shift 2
            ;;
        --language)
            LANGUAGE="$2"
            shift 2
            ;;
        --max-repos)
            MAX_REPOS="$2"
            shift 2
            ;;
        --help)
            usage
            ;;
        *)
            echo "Unknown option: $1"
            usage
            ;;
    esac
done

#=============================================================================
# SETUP LOGGING
#=============================================================================

TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
LOG_DIR="$PROJECT_ROOT/src/logs/pipeline"
mkdir -p "$LOG_DIR"
LOG_FILE="$LOG_DIR/${LANGUAGE}_expansion_${TIMESTAMP}.log"

START_TIME=$(date +%s)

# Logging functions
log() {
    echo -e "${BLUE}[$(date +'%Y-%m-%d %H:%M:%S')]${NC} $*" | tee -a "$LOG_FILE"
}

log_success() {
    echo -e "${GREEN}[$(date +'%Y-%m-%d %H:%M:%S')] ✓${NC} $*" | tee -a "$LOG_FILE"
}

log_warning() {
    echo -e "${YELLOW}[$(date +'%Y-%m-%d %H:%M:%S')] ⚠${NC} $*" | tee -a "$LOG_FILE"
}

log_error() {
    echo -e "${RED}[$(date +'%Y-%m-%d %H:%M:%S')] ✗${NC} $*" | tee -a "$LOG_FILE"
}

log_phase() {
    echo -e "\n${BLUE}========================================${NC}" | tee -a "$LOG_FILE"
    echo -e "${BLUE}$*${NC}" | tee -a "$LOG_FILE"
    echo -e "${BLUE}========================================${NC}" | tee -a "$LOG_FILE"
}

#=============================================================================
# HELPER FUNCTIONS
#=============================================================================

check_prerequisites() {
    log "Checking prerequisites..."

    # Check Python
    if ! command -v python3 &> /dev/null; then
        log_error "python3 not found"
        exit 1
    fi
    log_success "Python 3 found: $(python3 --version)"

    # Check Docker
    if ! docker info &> /dev/null; then
        log_error "Docker not running. Please start Docker."
        exit 1
    fi
    log_success "Docker is running"

    # Check project structure
    if [ ! -f "$PROJECT_ROOT/src/dataset_handling/github_ingestor.py" ]; then
        log_error "github_ingestor.py not found at expected location"
        exit 1
    fi
    log_success "Project structure validated"
}

get_latest_manifest() {
    ls -t "$PROJECT_ROOT/src/logs"/ingestion_manifest_${LANGUAGE}_*.json 2>/dev/null | head -1
}

#=============================================================================
# PHASE 1: INGEST & VALIDATE
#=============================================================================

phase1_ingest_and_validate() {
    log_phase "PHASE 1: INGEST & VALIDATE (Base Code)"

    cd "$PROJECT_ROOT/src/dataset_handling" || exit 1

    COMMAND="python3 github_ingestor.py --languages $LANGUAGE --max-repos $MAX_REPOS --max-entries $TARGET_ENTRIES --no-interactive"

    if [ "$DRY_RUN" = true ]; then
        log "[DRY-RUN] Would execute: $COMMAND"
        log "[DRY-RUN] Expected outputs:"
        log "  - New entries in src/dataset/$LANGUAGE/"
        log "  - Updated cluster JSONs in src/clusters/"
        log "  - Base test results in src/execution_outputs/"
        log "  - Manifest in src/logs/ingestion_manifest_${LANGUAGE}_*.json"
        return 0
    fi

    log "Executing: $COMMAND"
    $COMMAND 2>&1 | tee -a "$LOG_FILE"

    local exit_code=${PIPESTATUS[0]}

    if [ $exit_code -ne 0 ]; then
        log_error "Ingestion failed with exit code $exit_code"
        return 1
    fi

    # Read manifest
    MANIFEST=$(get_latest_manifest)

    if [ -z "$MANIFEST" ] || [ ! -f "$MANIFEST" ]; then
        log_error "No manifest file found"
        return 1
    fi

    # Parse manifest with jq
    if ! command -v jq &> /dev/null; then
        log_warning "jq not installed - cannot parse manifest details"
        INGESTED_COUNT=$(grep -oP '"entry_count"\s*:\s*\K\d+' "$MANIFEST" || echo "0")
        CLUSTERS="unknown"
    else
        INGESTED_COUNT=$(jq -r '.entry_count' "$MANIFEST")
        CLUSTERS=$(jq -r '.clusters[]' "$MANIFEST" | tr '\n' ' ')
    fi

    log_success "Phase 1 completed: $INGESTED_COUNT entries ingested"
    log "Modified clusters: $(echo "$CLUSTERS" | wc -w) ($CLUSTERS)"

    # Verify base test results
    BASE_FILES=$(find "$PROJECT_ROOT/src/execution_outputs" -name "*_results_[1-5].json" -mtime -1 2>/dev/null | wc -l)
    EXPECTED_BASE=$((INGESTED_COUNT * 5))
    log "Base test results: $BASE_FILES files (expected: $EXPECTED_BASE)"

    if [ "$INGESTED_COUNT" -lt 10 ]; then
        log_warning "Only $INGESTED_COUNT entries ingested (target: $TARGET_ENTRIES)"
        log_warning "Continuing with partial dataset..."
    fi

    return 0
}

#=============================================================================
# PHASE 2: GENERATE LLM VARIANTS
#=============================================================================

phase2_generate_llm() {
    log_phase "PHASE 2: GENERATE LLM VARIANTS"

    cd "$PROJECT_ROOT/src/LLMs_generator_engine" || exit 1

    # Dry-run to check how many orphans
    log "Checking for orphan entries (entries needing LLM generation)..."
    # Use grep -o instead of -P for macOS compatibility
    ORPHAN_COUNT=$(python3 run_llm_and_similarity.py --dry-run 2>&1 | grep -o 'Found [0-9]* orphan' | grep -o '[0-9]*' || echo "0")
    log "Found $ORPHAN_COUNT orphan entries requiring LLM generation"

    if [ "$ORPHAN_COUNT" -eq 0 ]; then
        log_warning "No orphan entries found - skipping LLM generation"
        return 0
    fi

    COMMAND="python3 run_llm_and_similarity.py --max-entries $INGESTED_COUNT --languages $LANGUAGE"

    if [ "$DRY_RUN" = true ]; then
        log "[DRY-RUN] Would execute: $COMMAND"
        log "[DRY-RUN] Expected outputs:"
        log "  - $(( INGESTED_COUNT * 12 )) LLM files in src/out_improvements_metadata/"
        log "  - Updated cluster JSONs with LLM metadata"
        return 0
    fi

    log "Executing: $COMMAND"
    log "This may take 3-5 minutes per entry (total: $(( INGESTED_COUNT * 4 )) min estimated)..."

    $COMMAND 2>&1 | tee -a "$LOG_FILE"

    local exit_code=${PIPESTATUS[0]}

    if [ $exit_code -ne 0 ]; then
        log_error "LLM generation failed with exit code $exit_code"
        log_warning "Continuing with available generations..."
        return 1
    fi

    # Verify LLM files generated
    LLM_FILES=$(find "$PROJECT_ROOT/src/out_improvements_metadata" -name "*.${LANGUAGE}pp" -o -name "*.${LANGUAGE}" -mtime -1 2>/dev/null | wc -l)
    EXPECTED_LLM=$(( INGESTED_COUNT * 12 ))
    log_success "Phase 2 completed: $LLM_FILES LLM files generated (expected: $EXPECTED_LLM)"

    return 0
}

#=============================================================================
# PHASE 3: UPDATE METADATA (Optional/Skipped)
#=============================================================================

phase3_update_metadata() {
    log_phase "PHASE 3: UPDATE METADATA"

    log "Metadata update is SKIPPED (run_llm_and_similarity.py already updates metadata)"
    log "If manual refresh needed, run: cd src/LLMs_generator_engine && python3 update_cluster_metadata.py"

    return 0
}

#=============================================================================
# PHASE 4: EXECUTE LLM TESTS
#=============================================================================

phase4_execute_llm_tests() {
    log_phase "PHASE 4: EXECUTE LLM TESTS"

    cd "$PROJECT_ROOT/src/run_tests_on_clusters" || exit 1

    # Get clusters from manifest
    MANIFEST=$(get_latest_manifest)

    if [ -z "$MANIFEST" ]; then
        log_error "No manifest found - cannot determine which clusters to test"
        return 1
    fi

    if ! command -v jq &> /dev/null; then
        log_error "jq is required for parsing manifest in Phase 4"
        return 1
    fi

    CLUSTERS_ARRAY=$(jq -r '.clusters[]' "$MANIFEST")

    if [ -z "$CLUSTERS_ARRAY" ]; then
        log_warning "No clusters found in manifest"
        return 0
    fi

    log "Testing $(echo "$CLUSTERS_ARRAY" | wc -w) clusters for LLM variants"

    FAILED_CLUSTERS=()
    TESTED_CLUSTERS=0
    TOTAL_CLUSTERS=$(echo "$CLUSTERS_ARRAY" | wc -w)

    for cluster in $CLUSTERS_ARRAY; do
        log "[$((TESTED_CLUSTERS + 1))/$TOTAL_CLUSTERS] Testing cluster: $cluster"

        COMMAND="python3 run_tests_on_cluster.py --cluster-name $cluster --llm-only --run-quantity 5 --languages $LANGUAGE"

        if [ "$DRY_RUN" = true ]; then
            log "[DRY-RUN] Would execute: $COMMAND"
            continue
        fi

        $COMMAND 2>&1 | tee -a "$LOG_FILE"

        if [ ${PIPESTATUS[0]} -eq 0 ]; then
            TESTED_CLUSTERS=$((TESTED_CLUSTERS + 1))
            log_success "Cluster $cluster: tests completed"
        else
            FAILED_CLUSTERS+=("$cluster")
            log_error "Cluster $cluster: tests FAILED"
        fi
    done

    log_success "Phase 4 completed: $TESTED_CLUSTERS/$TOTAL_CLUSTERS clusters tested successfully"

    if [ ${#FAILED_CLUSTERS[@]} -gt 0 ]; then
        log_warning "Failed clusters: ${FAILED_CLUSTERS[*]}"
        return 1
    fi

    # Verify LLM test results
    LLM_RESULT_FILES=$(find "$PROJECT_ROOT/src/execution_outputs" -name "*_results_v*_*.json" -mtime -1 2>/dev/null | wc -l)
    EXPECTED_LLM_RESULTS=$(( INGESTED_COUNT * 12 * 5 ))
    log "LLM test results: $LLM_RESULT_FILES files (expected: ~$EXPECTED_LLM_RESULTS)"

    return 0
}

#=============================================================================
# PHASE 5: ANALYZE METRICS
#=============================================================================

phase5_analyze_metrics() {
    log_phase "PHASE 5: ANALYZE METRICS"

    cd "$PROJECT_ROOT/src/metrics" || exit 1

    COMMAND="python3 main_exec_metrics_analysis.py"

    if [ "$DRY_RUN" = true ]; then
        log "[DRY-RUN] Would execute: $COMMAND"
        log "[DRY-RUN] Expected outputs:"
        log "  - Statistics JSON in src/metrics/execution_stats/"
        log "  - Box plots in src/metrics/execution_stats_plots/"
        log "  - Summary report: src/metrics/execution_stats_plots/summary_report.md"
        return 0
    fi

    log "Executing: $COMMAND"
    $COMMAND 2>&1 | tee -a "$LOG_FILE"

    local exit_code=${PIPESTATUS[0]}

    if [ $exit_code -ne 0 ]; then
        log_error "Metrics analysis failed with exit code $exit_code"
        return 1
    fi

    # Verify outputs
    STATS_FILES=$(find "$PROJECT_ROOT/src/metrics/execution_stats" -name "*.json" -mtime -1 2>/dev/null | wc -l)
    PLOT_FILES=$(find "$PROJECT_ROOT/src/metrics/execution_stats_plots" -name "*.png" -mtime -1 2>/dev/null | wc -l)

    log_success "Phase 5 completed"
    log "Generated: $STATS_FILES stats files, $PLOT_FILES plots"

    if [ -f "$PROJECT_ROOT/src/metrics/execution_stats_plots/summary_report.md" ]; then
        TOTAL_ENTRIES=$(grep -oP '(?<=Total entries: )\d+' "$PROJECT_ROOT/src/metrics/execution_stats_plots/summary_report.md" 2>/dev/null || echo "N/A")
        log "Summary report updated: $TOTAL_ENTRIES total entries analyzed"
    else
        log_warning "summary_report.md not found"
    fi

    return 0
}

#=============================================================================
# FINAL REPORT
#=============================================================================

generate_final_report() {
    local end_time=$(date +%s)
    local duration=$((end_time - START_TIME))
    local minutes=$((duration / 60))
    local seconds=$((duration % 60))

    log_phase "PIPELINE EXECUTION SUMMARY"

    log "Configuration:"
    log "  Language:          $LANGUAGE"
    log "  Target entries:    $TARGET_ENTRIES"
    log "  Max repositories:  $MAX_REPOS"
    log "  Dry-run mode:      $DRY_RUN"
    log ""

    if [ "$DRY_RUN" = false ]; then
        log "Results:"
        log "  Entries ingested:  $INGESTED_COUNT"
        log "  Clusters modified: $(echo "$CLUSTERS" | wc -w)"
        log "  LLM files:         $LLM_FILES"
        log "  Clusters tested:   $TESTED_CLUSTERS"
        log ""
    fi

    log "Logs saved to: $LOG_FILE"

    if [ -n "$MANIFEST" ]; then
        log "Manifest: $MANIFEST"
    fi

    log ""
    log "Total execution time: ${minutes}m ${seconds}s"
    log_phase "PIPELINE COMPLETED"
}

#=============================================================================
# MAIN EXECUTION
#=============================================================================

main() {
    log_phase "C++ DATASET EXPANSION PIPELINE"
    log "Started at: $(date)"
    log "Target: $TARGET_ENTRIES new $LANGUAGE entries with test validation"
    log "Dry-run: $DRY_RUN"
    log ""

    # Check prerequisites
    if [ "$DRY_RUN" = false ]; then
        check_prerequisites || exit 1
    fi

    # Execute phases
    phase1_ingest_and_validate || { log_error "Phase 1 failed"; exit 1; }
    phase2_generate_llm || log_warning "Phase 2 had issues (continuing)"
    phase3_update_metadata
    phase4_execute_llm_tests || log_warning "Phase 4 had issues (continuing)"
    phase5_analyze_metrics || log_warning "Phase 5 had issues"

    # Final report
    generate_final_report

    # Exit code logic
    if [ "$DRY_RUN" = true ]; then
        log_success "Dry-run completed successfully"
        exit 0
    elif [ "$INGESTED_COUNT" -eq 0 ]; then
        log_error "CRITICAL: No entries ingested - pipeline failed"
        exit 1
    elif [ "$INGESTED_COUNT" -lt $((TARGET_ENTRIES / 2)) ]; then
        log_warning "WARNING: Only $INGESTED_COUNT/$TARGET_ENTRIES entries ingested"
        exit 2
    else
        log_success "SUCCESS: Pipeline completed"
        exit 0
    fi
}

# Run main function
main "$@"
