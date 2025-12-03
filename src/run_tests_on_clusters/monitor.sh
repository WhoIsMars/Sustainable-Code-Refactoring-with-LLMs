#!/bin/bash
#
# Execution Monitor Wrapper Script
# Provides easy access to execution status monitoring with common configurations
#
# Date: 01/12/2024
#

# Script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
MONITOR_SCRIPT="${SCRIPT_DIR}/execution_monitor.py"

# Colors for output
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Print colored message
print_info() {
    echo -e "${BLUE}ℹ️  $1${NC}"
}

print_success() {
    echo -e "${GREEN}✅ $1${NC}"
}

print_warning() {
    echo -e "${YELLOW}⚠️  $1${NC}"
}

print_error() {
    echo -e "${RED}❌ $1${NC}"
}

# Check if Python script exists
if [ ! -f "$MONITOR_SCRIPT" ]; then
    print_error "Monitor script not found: $MONITOR_SCRIPT"
    exit 1
fi

# Check Python version
if ! command -v python3 &> /dev/null; then
    print_error "python3 not found. Please install Python 3."
    exit 1
fi

# Display help
show_help() {
    cat << EOF
${GREEN}Execution Status Monitor - Wrapper Script${NC}

${BLUE}Usage:${NC}
  ./monitor.sh [option]

${BLUE}Options:${NC}
  once              Run once and exit (snapshot mode)
  continuous        Run continuously with 30s refresh (default)
  fast              Run continuously with 10s refresh
  detailed          Run continuously with details (30s refresh)
  detailed-fast     Run continuously with details (10s refresh)
  custom            Interactive mode - specify custom parameters
  help              Show this help message

${BLUE}Features:${NC}
  - Real-time progress tracking with visual progress bar
  - Estimated time remaining (ETA) calculated from execution rate
  - Execution rate in executions/minute
  - Detailed statistics by language and prompt version

${BLUE}Examples:${NC}
  ${YELLOW}./monitor.sh${NC}
    Run with default settings (continuous, 30s refresh)

  ${YELLOW}./monitor.sh once${NC}
    Get a single snapshot of current execution status

  ${YELLOW}./monitor.sh fast${NC}
    Monitor with faster 10s refresh rate

  ${YELLOW}./monitor.sh detailed${NC}
    Show detailed breakdown by language and prompt version

${BLUE}Note:${NC}
  ETA is calculated after the first refresh interval based on execution rate.
  For more accurate estimates, let the monitor run for a few intervals.

${BLUE}Direct Python Usage:${NC}
  ${YELLOW}python3 execution_monitor.py --help${NC}
    Show all available Python options

  ${YELLOW}python3 execution_monitor.py --interval 60 --details${NC}
    Custom configuration example

EOF
}

# Run monitor with specified parameters
run_monitor() {
    local args=("$@")

    print_info "Starting execution monitor..."
    print_info "Press Ctrl+C to stop"
    echo ""

    python3 "$MONITOR_SCRIPT" "${args[@]}"

    local exit_code=$?
    if [ $exit_code -ne 0 ]; then
        print_error "Monitor exited with error code: $exit_code"
        return $exit_code
    fi

    return 0
}

# Main script logic
main() {
    local mode="${1:-continuous}"

    case "$mode" in
        once|snapshot)
            print_info "Running in snapshot mode (once)"
            run_monitor --once
            ;;

        continuous|default|"")
            print_info "Running in continuous mode (30s refresh)"
            run_monitor --interval 30
            ;;

        fast)
            print_info "Running in fast mode (10s refresh)"
            run_monitor --interval 10
            ;;

        detailed)
            print_info "Running in detailed mode (30s refresh)"
            run_monitor --interval 30 --details
            ;;

        detailed-fast)
            print_info "Running in detailed fast mode (10s refresh)"
            run_monitor --interval 10 --details
            ;;

        custom|interactive)
            print_info "Interactive mode"
            echo ""
            echo "Available options:"
            echo "  1) Snapshot (run once)"
            echo "  2) Continuous (30s)"
            echo "  3) Fast (10s)"
            echo "  4) Detailed (30s)"
            echo "  5) Custom interval"
            echo ""
            read -p "Select option [1-5]: " choice

            case "$choice" in
                1)
                    run_monitor --once
                    ;;
                2)
                    run_monitor --interval 30
                    ;;
                3)
                    run_monitor --interval 10
                    ;;
                4)
                    run_monitor --interval 30 --details
                    ;;
                5)
                    read -p "Enter refresh interval (seconds): " interval
                    read -p "Show details? [y/N]: " show_details

                    args=(--interval "$interval")
                    if [[ "$show_details" =~ ^[Yy]$ ]]; then
                        args+=(--details)
                    fi

                    run_monitor "${args[@]}"
                    ;;
                *)
                    print_error "Invalid option"
                    exit 1
                    ;;
            esac
            ;;

        help|-h|--help)
            show_help
            ;;

        *)
            print_error "Unknown option: $mode"
            echo ""
            show_help
            exit 1
            ;;
    esac
}

# Execute main function
main "$@"
