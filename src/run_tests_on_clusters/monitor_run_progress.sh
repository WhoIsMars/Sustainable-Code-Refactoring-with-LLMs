#!/bin/bash
# Monitor C++ LLM Test Progress
# Adattato per monitorare /tmp/test_cpp_llm_progress.log

LOG_FILE="/tmp/test_cpp_llm_progress.log"
CLUSTERS_FILE="/tmp/stable_cpp_clusters.txt"

echo "======================================================================"
echo "  C++ LLM TEST PROGRESS MONITOR (STEP 6)"
echo "======================================================================"
echo ""

# Controlla se il file dei cluster esiste per ottenere il totale
if [ ! -f "$CLUSTERS_FILE" ]; then
    echo "❌ File cluster non trovato: $CLUSTERS_FILE"
    echo "   Impossibile calcolare il totale."
    exit 1
fi

# Controlla se il log esiste
if [ ! -f "$LOG_FILE" ]; then
    echo "❌ File di log non trovato: $LOG_FILE"
    echo "   I test potrebbero non essere ancora iniziati."
    exit 1
fi

# Ottieni il numero totale di cluster
TOTAL_CLUSTERS=$(wc -l < "$CLUSTERS_FILE" | tr -d ' ')

# Conteggio cluster completati
COMPLETED=$(grep -c "✓ SUCCESS\|✗ FAILED" "$LOG_FILE" 2>/dev/null || echo "0")
SUCCESS=$(grep -c "✓ SUCCESS" "$LOG_FILE" 2>/dev/null || echo "0")
FAILED=$(grep -c "✗ FAILED" "$LOG_FILE" 2>/dev/null || echo "0")

# Calcola percentuale
if [ "$TOTAL_CLUSTERS" -gt 0 ]; then
    PERCENT=$(echo "scale=1; ($COMPLETED / $TOTAL_CLUSTERS) * 100" | bc)
else
    PERCENT="0.0"
fi

# Trova il cluster corrente
CURRENT=$(grep "Processing cluster:" "$LOG_FILE" | tail -1)

# Calcola ETA
if [ "$COMPLETED" -gt 0 ]; then
    # Ottieni la data dalla data di modifica del file (come fallback) e l'ora dalla prima riga
    FIRST_LOG_LINE=$(head -1 "$LOG_FILE" 2>/dev/null)
    
    # Estrai l'ora (es. 14:55:01)
    LOG_TIME_PART=$(echo "$FIRST_LOG_LINE" | cut -d' ' -f1 | tr -d '[]')
    
    # Ottieni la data di modifica del file (formato YYYY-MM-DD)
    LOG_DATE_PART=$(date -j -f %s "$(stat -f %m "$LOG_FILE")" "+%Y-%m-%d" 2>/dev/null)
    
    START_TIME_STR="$LOG_DATE_PART $LOG_TIME_PART"

    # Converti in epoch (usando le flag -j per BSD/macOS)
    START_EPOCH=$(date -j -f "%Y-%m-%d %H:%M:%S" "$START_TIME_STR" +%s 2>/dev/null)
    NOW_EPOCH=$(date +%s)
    
    if [ -n "$START_EPOCH" ]; then
        ELAPSED=$((NOW_EPOCH - START_EPOCH))

        # Calcola tempo medio per cluster
        AVG_TIME=$((ELAPSED / COMPLETED))

        # Calcola tempo rimanente
        REMAINING_CLUSTERS=$((TOTAL_CLUSTERS - COMPLETED))
        REMAINING_SECONDS=$((REMAINING_CLUSTERS * AVG_TIME))

        # Converti in ore:minuti
        REMAINING_HOURS=$((REMAINING_SECONDS / 3600))
        REMAINING_MINS=$(((REMAINING_SECONDS % 3600) / 60))

        # Calcola ETA (usando -r per BSD/macOS)
        ETA_EPOCH=$((NOW_EPOCH + REMAINING_SECONDS))
        ETA=$(date -r $ETA_EPOCH "+%H:%M:%S")
    fi
fi

# Mostra stato
echo "📊 OVERALL PROGRESS"
echo "────────────────────────────────────────────────────────────────────"
echo "  Clusters completati: $COMPLETED / $TOTAL_CLUSTERS ($PERCENT%)"
echo "  ✅ Successful:         $SUCCESS"
echo "  ❌ Failed:             $FAILED"
echo ""

if [ -n "$CURRENT" ]; then
    echo "🔄 CURRENT STATUS"
    echo "────────────────────────────────────────────────────────────────────"
    echo "  $CURRENT"
    echo ""
fi

if [ "$COMPLETED" -gt 0 ] && [ -n "$ELAPSED" ]; then
    echo "⏱️  TIMING"
    echo "────────────────────────────────────────────────────────────────────"
    echo "  Iniziato:         ~ $START_TIME_STR"
    echo "  Trascorso:        $((ELAPSED / 3600))h $((ELAPSED % 3600 / 60))m"
    echo "  Media p/cluster:  $((AVG_TIME / 60))m $((AVG_TIME % 60))s"
    echo "  Tempo rimanente:  ${REMAINING_HOURS}h ${REMAINING_MINS}m"
    echo "  ETA Stimata:      $ETA"
    echo ""
fi

# Mostra attività recente
echo "📝 RECENT ACTIVITY (last 5 clusters)"
echo "────────────────────────────────────────────────────────────────────"
grep "Processing cluster:\|✓ SUCCESS\|✗ FAILED" "$LOG_FILE" | tail -10 | while read line; do
    if [[ "$line" == *"Processing cluster"* ]]; then
        echo "  🔄 $line"
    elif [[ "$line" == *"SUCCESS"* ]]; then
        echo "     ✅ Success"
    elif [[ "$line" == *"FAILED"* ]]; then
        echo "     ❌ Failed"
    fi
done
echo ""

# Barra di progresso
echo "📈 PROGRESS BAR"
echo "────────────────────────────────────────────────────────────────────"
BAR_LENGTH=50
FILLED=$(echo "scale=0; ($COMPLETED * $BAR_LENGTH) / $TOTAL_CLUSTERS" | bc)
EMPTY=$((BAR_LENGTH - FILLED))

echo -n "  ["
for i in $(seq 1 $FILLED); do echo -n "█"; done
for i in $(seq 1 $EMPTY); do echo -n "░"; done
echo "] $PERCENT%"
echo ""

# Controlla errori nei log recenti
RECENT_ERRORS=$(tail -100 "$LOG_FILE" | grep -i "error\|failed\|exception" | grep -v "✗ FAILED" | wc -l | tr -d ' ')
if [ "$RECENT_ERRORS" -gt 0 ]; then
    echo "⚠️  WARNINGS"
    echo "────────────────────────────────────────────────────────────────────"
    echo "  Trovati $RECENT_ERRORS potenziali errori (diversi da FAILED) nei log recenti"
    echo "  Controlla: tail -100 $LOG_FILE | grep -Ei \"error|exception\""
    echo ""
fi

echo "======================================================================"
echo ""
echo "Comandi:"
echo "  • Guarda live:   tail -f $LOG_FILE"
echo "  • Rilancia monitor: /tmp/monitor_cpp_llm_tests.sh"
echo "  • Controlla falliti: grep '✗ FAILED' $LOG_FILE"
echo ""