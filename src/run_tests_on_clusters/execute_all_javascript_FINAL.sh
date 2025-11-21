#!/bin/bash

################################################################################
# SURGICAL JAVASCRIPT EXECUTION - BASE + LLM CODE (PER CLUSTER)
################################################################################
#
# This script executes ALL JavaScript tests (both base and LLM-generated code)
# by iterating through clusters in src/clusters.
#
# What this does:
# 1. Iterates over cluster files in src/clusters
# 2. Skips clusters matching exclusion patterns
# 3. For each valid cluster:
#    a. Executes 5 runs for base code
#    b. Executes 5 runs × 4 prompt versions for LLM code
# 4. Uses 2-minute timeout per entry
# 5. Preserves all other language data (Python, C++, Java, etc.)
#
################################################################################

set -e  # Exit on error

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
TIMESTAMP=$(date +%Y%m%d_%H%M%S)
LOG_DIR="$SCRIPT_DIR/js_full_execution_logs"
CLUSTER_DIR="$SCRIPT_DIR/../clusters"

mkdir -p "$LOG_DIR"

echo -e "${BLUE}=========================================================================${NC}"
echo -e "${BLUE}SURGICAL JAVASCRIPT EXECUTION - ITERATING ALL CLUSTERS${NC}" 
echo -e "${BLUE}=========================================================================${NC}"
echo ""
echo -e "${YELLOW}Configuration:${NC}"
echo -e "  Language:        ${GREEN}JavaScript ONLY${NC}"
echo -e "  Mode:            ${GREEN}BASE + LLM CODE${NC}"
echo -e "  Runs per entry:  ${GREEN}5${NC}"
echo -e "  LLM versions:    ${GREEN}v1, v2, v3, v4${NC}"
echo -e "  Timeout:         ${GREEN}120 seconds (2 minutes) per entry${NC}"
echo ""
echo -e "${YELLOW}Safety Features:${NC}"
echo -e "  ✅ Language-aware overwrite (only JavaScript)"
echo -e "  ✅ Selective-rerun merge (preserves other languages)"
echo -e "  ✅ 2-minute timeout catches infinite loops"
echo -e "  ✅ Automatic backup before file modifications"
echo ""
echo -e "${BLUE}=========================================================================${NC}"
echo ""

read -p "$(echo -e ${YELLOW}Proceed with execution? [y/N]:${NC} )" -n 1 -r
echo
if [[ ! $REPLY =~ ^[Yy]$ ]]; then
    echo -e "${RED}Cancelled by user.${NC}"
    exit 1
fi

echo ""
echo -e "${GREEN}Starting execution...${NC}"
echo ""

# MODIFICA: Definizione dei file di log principali
BASE_LOG="$LOG_DIR/js_base_${TIMESTAMP}.log"
LLM_LOG="$LOG_DIR/js_llm_${TIMESTAMP}.log"

# MODIFICA: Inizializza gli stati di uscita generali
OVERALL_BASE_EXIT=0
OVERALL_LLM_EXIT=0

# MODIFICA: Verifica se la directory dei cluster esiste
if [ ! -d "$CLUSTER_DIR" ]; then
    echo -e "${RED}Error: Cluster directory not found at $CLUSTER_DIR${NC}"
    exit 1
fi

echo -e "${BLUE}=========================================================================${NC}"
echo -e "${BLUE}STARTING CLUSTER ITERATION${NC}"
echo -e "${BLUE}=========================================================================${NC}"
echo ""

# MODIFICA: Inizio del loop sui file cluster
# Usiamo find ... | while read ... per gestire correttamente nomi di file con spazi
find "$CLUSTER_DIR" -maxdepth 1 -name "cluster_*.json" | while read -r cluster_file; do
    
    # Estrae il nome del file (es. cluster_myCluster.json)
    filename=$(basename "$cluster_file")
    
    # Estrae il nome del cluster (es. myCluster)
    temp_name="${filename#cluster_}" 
    cluster_name="${temp_name%.json}"

    # --- Logica di filtraggio ---
    if [[ "$cluster_name" == *debug* || \
          "$cluster_name" == *test* || \
          "$cluster_name" == *bad_entries* || \
          "$cluster_name" == *focused_* || \
          "$cluster_name" == *with_metrics* ]]; then
        
        echo -e "${YELLOW}--- Skipping cluster: $cluster_name (matches filter) ---${NC}"
        echo ""
        continue # Salta al prossimo file
    fi
    
    echo -e "${GREEN}>>> Processing cluster: $cluster_name <<<${NC}"
    echo ""

    ################################################################################
    # PHASE 1: Execute BASE CODE (per cluster)
    ################################################################################

    echo -e "${BLUE}--- PHASE 1: BASE CODE ($cluster_name) ---${NC}"

    python3 "$SCRIPT_DIR/run_tests_on_cluster.py" \
        --cluster-name "$cluster_name" \
        --base-only \
        --languages javascript \
        --selective-rerun \
        --overwrite-results \
        --run-quantity 5 \
        --not-check-pending \
        2>&1 | tee -a "$BASE_LOG" # 'tee -a' per appendere al log

    BASE_EXIT=${PIPESTATUS[0]} # Cattura l'exit code di python3, non di tee

    if [ $BASE_EXIT -eq 0 ]; then
        echo -e "\n${GREEN}✓ BASE CODE ($cluster_name) completed successfully${NC}"
    else
        echo -e "\n${RED}✗ BASE CODE ($cluster_name) failed (exit $BASE_EXIT)${NC}"
        OVERALL_BASE_EXIT=1 # Segna fallimento generale
        echo -e "${YELLOW}Proceeding with LLM phase for $cluster_name despite BASE failure.${NC}"
    fi

    ################################################################################
    # PHASE 2: Execute LLM CODE (per cluster)
    ################################################################################

    echo ""
    echo -e "${BLUE}--- PHASE 2: LLM CODE ($cluster_name) ---${NC}"

    python3 "$SCRIPT_DIR/run_tests_on_cluster.py" \
        --cluster-name "$cluster_name" \
        --llm-only \
        --languages javascript \
        --selective-rerun \
        --overwrite-results \
        --run-quantity 5 \
        --not-check-pending \
        2>&1 | tee -a "$LLM_LOG" #'tee -a' per appendere al log

    LLM_EXIT=${PIPESTATUS[0]} # Cattura l'exit code di python3

    if [ $LLM_EXIT -eq 0 ]; then
        echo -e "\n${GREEN}✓ LLM CODE ($cluster_name) completed successfully${NC}"
    else
        echo -e "\n${RED}✗ LLM CODE ($cluster_name) failed (exit $LLM_EXIT)${NC}"
        OVERALL_LLM_EXIT=1 #  Segna fallimento generale
    fi

    echo ""
    echo -e "${BLUE}-------------------------------------------------------------------------${NC}"
    echo ""

done 

################################################################################
# SUMMARY
################################################################################

echo ""
echo -e "${BLUE}=========================================================================${NC}"
echo -e "${BLUE}EXECUTION COMPLETE${NC}"
echo -e "${BLUE}=========================================================================${NC}"
echo ""
echo -e "${YELLOW}Overall Results:${NC}" # MODIFICA: Titolo aggiornato
# MODIFICA: Controlla gli stati di uscita generali
echo -e "  BASE: $([ $OVERALL_BASE_EXIT -eq 0 ] && echo -e "${GREEN}SUCCESS (all clusters)${NC}" || echo -e "${RED}FAILED (at least one cluster)${NC}")"
echo -e "  LLM:  $([ $OVERALL_LLM_EXIT -eq 0 ] && echo -e "${GREEN}SUCCESS (all clusters)${NC}" || echo -e "${RED}FAILED (at least one cluster)${NC}")"
echo ""
echo -e "${YELLOW}Logs (contain all cluster runs):${NC}" # MODIFICA: Descrizione aggiornata
echo -e "  BASE: $BASE_LOG"
echo -e "  LLM:  $LLM_LOG"
echo ""
echo -e "${BLUE}=========================================================================${NC}"

# MODIFICA: Esce con errore se uno qualsiasi dei fallimenti generali è stato segnato
[ $OVERALL_BASE_EXIT -ne 0 ] || [ $OVERALL_LLM_EXIT -ne 0 ] && exit 1
exit 0