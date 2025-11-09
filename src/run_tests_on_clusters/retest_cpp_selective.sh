#!/bin/bash
LOG_FILE="/tmp/retest_cpp_selective_progress.log"
CLUSTER_FILE="/tmp/new_cpp_clusters.txt"
TOTAL=$(cat "$CLUSTER_FILE" | grep -v '^$' | wc -l | tr -d ' ')
COUNT=0

# === Inizializza il file di log (sovrascrive quello vecchio) ===
echo "Re-testing C++ entries with selective-rerun at $(date)" > "$LOG_FILE"
echo "Mode: selective-rerun --languages cpp --overwrite-results" >> "$LOG_FILE"
echo "This will test ALL CPP entries (new + existing) in these 67 clusters" >> "$LOG_FILE"
echo "========================================" >> "$LOG_FILE"

# === Ora, esegui il loop e mostra l'output sia sul terminale che sul log ===
cat "$CLUSTER_FILE" | grep -v '^$' | while read cluster; do
  COUNT=$((COUNT + 1))
  
  # Mostra questo messaggio sia sul terminale che sul log
  echo "" | tee -a "$LOG_FILE"
  echo "[$COUNT/$TOTAL] Re-testing C++ in cluster: $cluster at $(date)" | tee -a "$LOG_FILE"
  
  # Esegui lo script Python e manda l'output a TEE
  python3 run_tests_on_cluster.py \
    --cluster-name "$cluster" \
    --run-quantity 5 \
    --base-only \
    --selective-rerun \
    --languages cpp \
    --overwrite-results \
    2>&1 | tee -a "$LOG_FILE"
  
  # NOTA: In bash/zsh, $? dopo una pipe si riferisce all'ultimo comando (tee).
  # Per ottenere l'exit code di python (il primo comando), usiamo ${PIPESTATUS[0]}
  EXIT_CODE=${PIPESTATUS[0]}
  
  if [ $EXIT_CODE -eq 0 ]; then
    echo "  ✓ SUCCESS" | tee -a "$LOG_FILE"
  else
    echo "  ✗ FAILED (exit code: $EXIT_CODE)" | tee -a "$LOG_FILE"
  fi
done

# === Messaggi finali ===
echo "" | tee -a "$LOG_FILE"
echo "========================================" | tee -a "$LOG_FILE"
echo "All re-tests completed at $(date)" | tee -a "$LOG_FILE"le