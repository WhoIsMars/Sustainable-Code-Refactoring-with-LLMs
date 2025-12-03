#!/bin/bash

echo "--- 1. Fermo tutti i container Docker attivi ---"
docker stop $(docker ps -q) 2>/dev/null

echo "--- 2. Rimuovo tutti i container (anche quelli fermi) ---"
docker rm $(docker ps -aq) 2>/dev/null

echo "--- 3. Verifico i container rimanenti (dovrebbe essere vuoto) ---"
docker ps -a

echo "--- 4. Uccido eventuali processi Python di test specifici ---"
#pkill -f "run_tests_on_cluster.py"
pkill -f "run_javascript_v3_v4_completion.py"

echo "--- 5. Verifico processi Python o Docker ancora attivi ---"
ps aux | grep -E "python.*run_|docker run" | grep -v grep

echo "--- Pulizia completata ---"


#ferma e rimuove containers Docker ed uccede processi ancora attivi