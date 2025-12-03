#!/opt/homebrew/bin/bash

################################################################################
#Pipeline for :
# Add base entry (+ run) -> add LLM entries -> run LLM -> compute new statistics -> generate new charts -> save / update them in /scrittura dir 

# 1) Add entries for languages in the dataset 
# -> use github ingestor to add new base entries in the dataset 
# -- -> choose languages and entry quantity 
# -- -> validate entries by running them (5/5 exec success to add a new base entry)
# -- -> save base results in execution_output dir (no need to re run base entries)

# 2) Generate LLM code variants for each new entry (orphan base entry)
# -> use orphan orchestrator to :  
#    • find orphand entries for the chosen languages
#    • generate LLM entries for them and save them in clusters (.json files in src/clusters)
#    • adjust metadata (similarity index included)

# 3) Execute only new LLM entries (not yet executed) 

# 4) Regenerate all statistics (+charts) and update them (=> run generate_all_plots.sh)
#    • improvements 
#    • metrics 
#    • patterns 
#    • dataset 
#    • 
################################################################################

set -e  # Exit on error (will be selectively disabled where needed)

#===============================================================================
# CONFIGURATION
#===============================================================================

# Color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
BOLD='\033[1m'
NC='\033[0m' # No Color

# Paths
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SRC_DIR="$SCRIPT_DIR/src"
THESIS_ROOT="$( cd "$SCRIPT_DIR/.." && pwd )"

# Log file
TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
LOG_DIR="$SRC_DIR/logs/pipeline_runs"
mkdir -p "$LOG_DIR"
LOG_FILE="$LOG_DIR/pipeline_run_$TIMESTAMP.log"

# Supported languages (from general_utils.py)
SUPPORTED_LANGUAGES=("c" "cpp" "java" "javascript" "go" "typescript" "python")

# Default values
DEFAULT_MAX_REPOS=10
DEFAULT_MAX_ENTRIES=20
MAX_WORKERS=4

#===============================================================================
# UTILITY FUNCTIONS
#===============================================================================

log() {
    local level="$1"
    local message="$2"
    local timestamp=$(date "+%Y-%m-%d %H:%M:%S")
    echo -e "[$timestamp] [$level] $message" >> "$LOG_FILE"

    case "$level" in
        "INFO")    echo -e "${BLUE}[INFO]${NC} $message" ;;
        "SUCCESS") echo -e "${GREEN}[SUCCESS]${NC} $message" ;;
        "WARNING") echo -e "${YELLOW}[WARNING]${NC} $message" ;;
        "ERROR")   echo -e "${RED}[ERROR]${NC} $message" ;;
        "STEP")    echo -e "${MAGENTA}${BOLD}[STEP]${NC} $message" ;;
        *)         echo -e "$message" ;;
    esac
}

print_banner() {
    echo -e "${CYAN}"
    echo "╔══════════════════════════════════════════════════════════════════════════════╗"
    echo "║                                                                              ║"
    echo "║         ${BOLD}SUSTAINABLE CODE REFACTORING WITH LLMs - MAIN PIPELINE${NC}${CYAN}            ║"
    echo "║                                                                              ║"
    echo "╠══════════════════════════════════════════════════════════════════════════════╣"
    echo "║  1. GitHub Ingestor    -> Add new base entries from Exercism                ║"
    echo "║  2. Orphan Orchestrator -> Generate LLM variants for new entries            ║"
    echo "║  3. Selective Runner   -> Execute new LLM entries (5 runs each)             ║"
    echo "║  4. Plot Generation    -> Regenerate all statistics and charts              ║"
    echo "╚══════════════════════════════════════════════════════════════════════════════╝"
    echo -e "${NC}"
}

print_separator() {
    echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
}

print_step_header() {
    local step_num="$1"
    local step_title="$2"
    echo ""
    print_separator
    echo -e "${MAGENTA}${BOLD}  STEP $step_num: $step_title${NC}"
    print_separator
    echo ""
}

confirm_proceed() {
    local message="$1"
    echo -e "${YELLOW}$message${NC}"
    read -p "Continue? [y/N]: " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        log "INFO" "User cancelled operation"
        return 1
    fi
    return 0
}

check_python_dependencies() {
    log "INFO" "Checking Python environment..."

    if ! command -v python3 &> /dev/null; then
        log "ERROR" "Python3 is not installed or not in PATH"
        exit 1
    fi

    # Check if we can import required modules
    python3 -c "import requests, dotenv" 2>/dev/null || {
        log "WARNING" "Some Python dependencies may be missing. Run: pip install requests python-dotenv"
    }

    log "SUCCESS" "Python environment OK"
}

#===============================================================================
# STEP 1: LANGUAGE AND QUANTITY SELECTION
#===============================================================================

declare -A SELECTED_LANGUAGES  # Associative array: language -> entry_count

select_languages_interactive() {
    echo ""
    echo -e "${CYAN}${BOLD}=== Language Selection ===${NC}"
    echo ""
    echo "Available languages:"
    echo ""

    for i in "${!SUPPORTED_LANGUAGES[@]}"; do
        echo "  $((i+1)). ${SUPPORTED_LANGUAGES[$i]}"
    done
    echo "  A. All languages"
    echo "  Q. Quit"
    echo ""

    read -p "Select languages (comma-separated numbers, 'A' for all, or 'Q' to quit): " selection

    if [[ "$selection" =~ ^[Qq]$ ]]; then
        log "INFO" "User quit during language selection"
        exit 0
    fi

    if [[ "$selection" =~ ^[Aa]$ ]]; then
        # Select all languages
        for lang in "${SUPPORTED_LANGUAGES[@]}"; do
            SELECTED_LANGUAGES["$lang"]=0
        done
        log "INFO" "Selected all languages"
    else
        # Parse comma-separated numbers
        IFS=',' read -ra SELECTIONS <<< "$selection"
        for sel in "${SELECTIONS[@]}"; do
            sel=$(echo "$sel" | tr -d ' ')  # Remove whitespace
            if [[ "$sel" =~ ^[0-9]+$ ]] && [ "$sel" -ge 1 ] && [ "$sel" -le ${#SUPPORTED_LANGUAGES[@]} ]; then
                local lang="${SUPPORTED_LANGUAGES[$((sel-1))]}"
                SELECTED_LANGUAGES["$lang"]=0
                log "INFO" "Selected language: $lang"
            else
                log "WARNING" "Invalid selection: $sel (ignoring)"
            fi
        done
    fi

    if [ ${#SELECTED_LANGUAGES[@]} -eq 0 ]; then
        log "ERROR" "No valid languages selected"
        exit 1
    fi

    echo ""
    echo -e "${GREEN}Selected languages: ${!SELECTED_LANGUAGES[*]}${NC}"
}

select_entry_quantities() {
    echo ""
    echo -e "${CYAN}${BOLD}=== Entry Quantity Selection ===${NC}"
    echo ""

    read -p "Use same quantity for all languages? [Y/n]: " -n 1 -r same_qty
    echo ""

    if [[ ! $same_qty =~ ^[Nn]$ ]]; then
        # Same quantity for all
        read -p "Enter number of entries per language (default: $DEFAULT_MAX_ENTRIES): " qty
        qty=${qty:-$DEFAULT_MAX_ENTRIES}

        if ! [[ "$qty" =~ ^[0-9]+$ ]] || [ "$qty" -lt 1 ]; then
            log "WARNING" "Invalid quantity, using default: $DEFAULT_MAX_ENTRIES"
            qty=$DEFAULT_MAX_ENTRIES
        fi

        for lang in "${!SELECTED_LANGUAGES[@]}"; do
            SELECTED_LANGUAGES["$lang"]=$qty
        done
    else
        # Different quantity per language
        for lang in "${!SELECTED_LANGUAGES[@]}"; do
            read -p "Entries for $lang (default: $DEFAULT_MAX_ENTRIES): " qty
            qty=${qty:-$DEFAULT_MAX_ENTRIES}

            if ! [[ "$qty" =~ ^[0-9]+$ ]] || [ "$qty" -lt 1 ]; then
                log "WARNING" "Invalid quantity for $lang, using default: $DEFAULT_MAX_ENTRIES"
                qty=$DEFAULT_MAX_ENTRIES
            fi

            SELECTED_LANGUAGES["$lang"]=$qty
        done
    fi

    echo ""
    echo -e "${GREEN}Configuration summary:${NC}"
    for lang in "${!SELECTED_LANGUAGES[@]}"; do
        echo "  - $lang: ${SELECTED_LANGUAGES[$lang]} entries"
    done
}

select_max_repos() {
    echo ""
    read -p "Max repositories to search per language (default: $DEFAULT_MAX_REPOS): " max_repos
    MAX_REPOS=${max_repos:-$DEFAULT_MAX_REPOS}

    if ! [[ "$MAX_REPOS" =~ ^[0-9]+$ ]] || [ "$MAX_REPOS" -lt 1 ]; then
        log "WARNING" "Invalid max repos, using default: $DEFAULT_MAX_REPOS"
        MAX_REPOS=$DEFAULT_MAX_REPOS
    fi

    echo -e "${GREEN}Max repositories per language: $MAX_REPOS${NC}"
}

#===============================================================================
# STEP 1: GITHUB INGESTOR
#===============================================================================

run_github_ingestor() {
    print_step_header "1/4" "GITHUB INGESTOR - Adding Base Entries"

    log "INFO" "Starting GitHub Ingestor..."

    local ingestor_script="$SRC_DIR/dataset_handling/github_ingestor.py"

    if [ ! -f "$ingestor_script" ]; then
        log "ERROR" "GitHub Ingestor script not found: $ingestor_script"
        exit 1
    fi

    local total_ingested=0
    local languages_processed=0

    for lang in "${!SELECTED_LANGUAGES[@]}"; do
        local qty="${SELECTED_LANGUAGES[$lang]}"

        echo ""
        log "STEP" "Processing $lang ($qty entries, max $MAX_REPOS repos)..."

        cd "$SRC_DIR/dataset_handling"

        # Run ingestor for this language
        if python3 github_ingestor.py \
            --languages "$lang" \
            --max-repos "$MAX_REPOS" \
            --max-entries "$qty" \
            --no-interactive \
            2>&1 | tee -a "$LOG_FILE"; then

            log "SUCCESS" "GitHub Ingestor completed for $lang"
            ((languages_processed++))
        else
            log "WARNING" "GitHub Ingestor had issues with $lang (continuing...)"
        fi

        cd "$SCRIPT_DIR"
    done

    echo ""
    log "SUCCESS" "GitHub Ingestor completed: $languages_processed languages processed"

    return 0
}

#===============================================================================
# STEP 2: ORPHAN ORCHESTRATOR
#===============================================================================

run_orphan_orchestrator() {
    print_step_header "2/4" "ORPHAN ORCHESTRATOR - Generating LLM Variants"

    log "INFO" "Starting Orphan Orchestrator..."

    local orchestrator_script="$SRC_DIR/LLMs_generator_engine/orphan_orchestrator.py"

    if [ ! -f "$orchestrator_script" ]; then
        log "ERROR" "Orphan Orchestrator script not found: $orchestrator_script"
        exit 1
    fi

    # Build language list for orchestrator
    local lang_args=""
    for lang in "${!SELECTED_LANGUAGES[@]}"; do
        lang_args="$lang_args $lang"
    done

    cd "$SRC_DIR/LLMs_generator_engine"

    echo ""
    log "INFO" "Scanning for orphan entries and generating LLM variants..."
    log "INFO" "This may take a while depending on API rate limits..."
    echo ""

    # Run orchestrator
    if python3 orphan_orchestrator.py \
        --languages $lang_args \
        2>&1 | tee -a "$LOG_FILE"; then

        log "SUCCESS" "Orphan Orchestrator completed successfully"
    else
        log "WARNING" "Orphan Orchestrator completed with some issues"
    fi

    cd "$SCRIPT_DIR"

    return 0
}

#===============================================================================
# STEP 3: SELECTIVE RUNNER
#===============================================================================

run_selective_runner() {
    print_step_header "3/4" "SELECTIVE RUNNER - Executing New LLM Entries"

    log "INFO" "Starting Selective LLM Runner..."

    local runner_script="$SRC_DIR/run_tests_on_clusters/new_llm_selective_runner.py"

    if [ ! -f "$runner_script" ]; then
        log "ERROR" "Selective Runner script not found: $runner_script"
        exit 1
    fi

    cd "$SRC_DIR/run_tests_on_clusters"

    echo ""
    log "INFO" "Finding LLM entries with 0 executions and running them..."
    log "INFO" "Each entry will be executed 5 times for statistical validity..."
    echo ""

    # Run selective runner with max workers
    if python3 new_llm_selective_runner.py \
        2>&1 | tee -a "$LOG_FILE"; then

        log "SUCCESS" "Selective Runner completed successfully"
    else
        log "WARNING" "Selective Runner completed with some issues"
    fi

    cd "$SCRIPT_DIR"

    return 0
}

#===============================================================================
# STEP 4: PLOT GENERATION
#===============================================================================

run_plot_generation() {
    print_step_header "4/4" "PLOT GENERATION - Regenerating Statistics & Charts"

    log "INFO" "Starting Plot Generation Pipeline..."

    local plot_script="$SCRIPT_DIR/generate_all_plots.sh"

    if [ ! -f "$plot_script" ]; then
        log "ERROR" "Plot generation script not found: $plot_script"
        exit 1
    fi

    echo ""
    log "INFO" "Regenerating all statistics, charts, and copying to scrittura/..."
    echo ""

    # Run plot generation script
    if bash "$plot_script" 2>&1 | tee -a "$LOG_FILE"; then
        log "SUCCESS" "Plot Generation completed successfully"
    else
        log "WARNING" "Plot Generation completed with some issues"
    fi

    return 0
}

#===============================================================================
# PIPELINE SUMMARY
#===============================================================================

print_final_summary() {
    local end_time=$(date +%s)
    local duration=$((end_time - START_TIME))
    local hours=$((duration / 3600))
    local minutes=$(((duration % 3600) / 60))
    local seconds=$((duration % 60))

    echo ""
    echo -e "${GREEN}"
    echo "╔══════════════════════════════════════════════════════════════════════════════╗"
    echo "║                                                                              ║"
    echo "║                    ${BOLD}PIPELINE COMPLETED SUCCESSFULLY${NC}${GREEN}                        ║"
    echo "║                                                                              ║"
    echo "╠══════════════════════════════════════════════════════════════════════════════╣"
    printf "║  Duration: %02d:%02d:%02d                                                         ║\n" $hours $minutes $seconds
    echo "║                                                                              ║"
    echo "║  Steps completed:                                                            ║"
    echo "║    1. GitHub Ingestor    - Base entries added                               ║"
    echo "║    2. Orphan Orchestrator - LLM variants generated                          ║"
    echo "║    3. Selective Runner   - New LLM entries executed                         ║"
    echo "║    4. Plot Generation    - Statistics and charts regenerated                ║"
    echo "║                                                                              ║"
    echo "╠══════════════════════════════════════════════════════════════════════════════╣"
    echo "║  Output locations:                                                           ║"
    echo "║    - Plots (PNG): $THESIS_ROOT/scrittura/plots/"
    echo "║    - Plots (PDF): $THESIS_ROOT/scrittura/plots_pdf/"
    echo "║    - Log file:    $LOG_FILE"
    echo "║                                                                              ║"
    echo "╚══════════════════════════════════════════════════════════════════════════════╝"
    echo -e "${NC}"
}

#===============================================================================
# COMMAND LINE ARGUMENT PARSING
#===============================================================================

show_help() {
    echo "Usage: $0 [OPTIONS]"
    echo ""
    echo "Options:"
    echo "  -h, --help           Show this help message"
    echo "  -l, --languages      Languages to process (comma-separated)"
    echo "  -n, --entries        Number of entries per language"
    echo "  -r, --max-repos      Max repositories to search (default: $DEFAULT_MAX_REPOS)"
    echo "  -w, --workers        Max parallel workers (default: $MAX_WORKERS)"
    echo "  --skip-ingest        Skip step 1 (GitHub Ingestor)"
    echo "  --skip-generate      Skip step 2 (Orphan Orchestrator)"
    echo "  --skip-execute       Skip step 3 (Selective Runner)"
    echo "  --skip-plots         Skip step 4 (Plot Generation)"
    echo "  --only-plots         Only run step 4 (Plot Generation)"
    echo "  -y, --yes            Skip all confirmation prompts"
    echo ""
    echo "Examples:"
    echo "  $0                              # Interactive mode"
    echo "  $0 -l c,cpp -n 10               # Process C and C++ with 10 entries each"
    echo "  $0 --only-plots                 # Only regenerate plots"
    echo "  $0 -l python -n 5 --skip-plots  # Add Python entries, skip plot generation"
}

# Flags for skipping steps
SKIP_INGEST=false
SKIP_GENERATE=false
SKIP_EXECUTE=false
SKIP_PLOTS=false
ONLY_PLOTS=false
AUTO_YES=false
CLI_LANGUAGES=""
CLI_ENTRIES=""

parse_arguments() {
    while [[ $# -gt 0 ]]; do
        case $1 in
            -h|--help)
                show_help
                exit 0
                ;;
            -l|--languages)
                CLI_LANGUAGES="$2"
                shift 2
                ;;
            -n|--entries)
                CLI_ENTRIES="$2"
                shift 2
                ;;
            -r|--max-repos)
                MAX_REPOS="$2"
                shift 2
                ;;
            -w|--workers)
                MAX_WORKERS="$2"
                shift 2
                ;;
            --skip-ingest)
                SKIP_INGEST=true
                shift
                ;;
            --skip-generate)
                SKIP_GENERATE=true
                shift
                ;;
            --skip-execute)
                SKIP_EXECUTE=true
                shift
                ;;
            --skip-plots)
                SKIP_PLOTS=true
                shift
                ;;
            --only-plots)
                ONLY_PLOTS=true
                shift
                ;;
            -y|--yes)
                AUTO_YES=true
                shift
                ;;
            *)
                log "ERROR" "Unknown option: $1"
                show_help
                exit 1
                ;;
        esac
    done
}

setup_from_cli() {
    # Parse languages from CLI
    if [ -n "$CLI_LANGUAGES" ]; then
        IFS=',' read -ra LANG_ARRAY <<< "$CLI_LANGUAGES"
        for lang in "${LANG_ARRAY[@]}"; do
            lang=$(echo "$lang" | tr -d ' ')
            # Validate language
            local valid=false
            for supported in "${SUPPORTED_LANGUAGES[@]}"; do
                if [ "$lang" == "$supported" ]; then
                    valid=true
                    break
                fi
            done

            if $valid; then
                SELECTED_LANGUAGES["$lang"]=${CLI_ENTRIES:-$DEFAULT_MAX_ENTRIES}
            else
                log "WARNING" "Unsupported language: $lang (ignoring)"
            fi
        done
    fi
}

#===============================================================================
# MAIN EXECUTION
#===============================================================================

main() {
    START_TIME=$(date +%s)

    # Parse command line arguments
    parse_arguments "$@"

    # Print banner
    print_banner

    # Initialize log
    echo "=== Pipeline Started at $(date) ===" > "$LOG_FILE"
    log "INFO" "Log file: $LOG_FILE"

    # Check dependencies
    check_python_dependencies

    # Handle --only-plots shortcut
    if $ONLY_PLOTS; then
        log "INFO" "Running only plot generation (--only-plots)"
        run_plot_generation
        print_final_summary
        exit 0
    fi

    # Setup from CLI or interactive
    if [ -n "$CLI_LANGUAGES" ]; then
        setup_from_cli
        MAX_REPOS=${MAX_REPOS:-$DEFAULT_MAX_REPOS}
    else
        # Interactive mode
        select_languages_interactive
        select_entry_quantities
        select_max_repos
    fi

    # Validate we have languages selected
    if [ ${#SELECTED_LANGUAGES[@]} -eq 0 ]; then
        log "ERROR" "No languages selected"
        exit 1
    fi

    # Show configuration and confirm
    echo ""
    print_separator
    echo -e "${CYAN}${BOLD}  PIPELINE CONFIGURATION${NC}"
    print_separator
    echo ""
    echo "Languages and entries:"
    for lang in "${!SELECTED_LANGUAGES[@]}"; do
        echo "  - $lang: ${SELECTED_LANGUAGES[$lang]} entries"
    done
    echo ""
    echo "Max repositories per language: $MAX_REPOS"
    echo "Max workers: $MAX_WORKERS"
    echo ""
    echo "Steps to execute:"
    $SKIP_INGEST   && echo "  1. GitHub Ingestor      [SKIPPED]" || echo "  1. GitHub Ingestor      [ENABLED]"
    $SKIP_GENERATE && echo "  2. Orphan Orchestrator  [SKIPPED]" || echo "  2. Orphan Orchestrator  [ENABLED]"
    $SKIP_EXECUTE  && echo "  3. Selective Runner     [SKIPPED]" || echo "  3. Selective Runner     [ENABLED]"
    $SKIP_PLOTS    && echo "  4. Plot Generation      [SKIPPED]" || echo "  4. Plot Generation      [ENABLED]"
    echo ""

    if ! $AUTO_YES; then
        if ! confirm_proceed "Ready to start the pipeline?"; then
            log "INFO" "Pipeline cancelled by user"
            exit 0
        fi
    fi

    # Execute steps
    echo ""
    log "INFO" "Starting pipeline execution..."

    # Step 1: GitHub Ingestor
    if ! $SKIP_INGEST; then
        run_github_ingestor
    else
        log "INFO" "Skipping Step 1: GitHub Ingestor"
    fi

    # Step 2: Orphan Orchestrator
    if ! $SKIP_GENERATE; then
        run_orphan_orchestrator
    else
        log "INFO" "Skipping Step 2: Orphan Orchestrator"
    fi

    # Step 3: Selective Runner
    if ! $SKIP_EXECUTE; then
        run_selective_runner
    else
        log "INFO" "Skipping Step 3: Selective Runner"
    fi

    # Step 4: Plot Generation
    if ! $SKIP_PLOTS; then
        run_plot_generation
    else
        log "INFO" "Skipping Step 4: Plot Generation"
    fi

    # Final summary
    print_final_summary

    log "INFO" "Pipeline completed successfully"
    echo "=== Pipeline Completed at $(date) ===" >> "$LOG_FILE"
}

# Run main with all arguments
main "$@"