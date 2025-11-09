# Step 5 - Azione Correttiva in Corso

**Data**: 2025-11-09 08:56
**Status**: ⏳ Test C++ Fresh Run IN ESECUZIONE

---

## Problema Identificato

### Selective-Rerun Mode Non Funzionante
La modalità `--selective-rerun --languages cpp` ha **FALLITO** perché:

1. **Non ha testato le nuove entries**: Anche se i cluster contengono nuove entries C++, il test runner non le ha eseguite
2. **Ha sovrascritto i risultati**: Ha cancellato entries esistenti dai file di risultati senza sostituirle
3. **Risultato netto**: Perso ~160 entries C++ dai risultati (da 244 a 84)

### Esempio Concreto
**Cluster `acronym`**:
- Entries nel cluster JSON: 2 (1 vecchia + 1 nuova)
  - OLD: `cpp_acronym_Exercism (thefullarcticfox)` (2025-07-31)
  - NEW: `cpp_acronym_Akshive` (2025-11-08)
- Entries nei risultati PRIMA selective-rerun: 1 (solo vecchia)
- Entries nei risultati DOPO selective-rerun: 1 (solo vecchia)
- **Nuova entry MAI testata**

---

## Soluzione Implementata

### Fresh Test Run
**Script**: `/tmp/test_cpp_fresh.sh`

**Strategia**:
1. ✅ Backup risultati esistenti → `/tmp/results_backup_1762674939/`
2. ✅ Cancellazione file risultati per i 67 cluster
3. ⏳ Esecuzione fresh test su TUTTI i 244 CPP entries

**Comando**:
```bash
# Per ogni cluster nei 67:
python3 run_tests_on_cluster.py \
  --cluster-name "$cluster" \
  --run-quantity 5 \
  --base-only
```

**NO selective-rerun** - questo forza il test di TUTTE le entries nel cluster

---

## Progresso Attuale

### Test Execution Status

**Started**: 2025-11-09 08:55:40
**Current cluster**: 05_log_levels (1/67)
**Estimated completion**: ~08:55 + 3.5 ore = **12:25**

### Stima Tempi
- Total CPP entries: 244
- Tests per entry: 5 runs
- Total executions: 1,220
- Time per test: ~10 seconds
- **Total time**: ~3.4 ore

### Progresso Real-Time
```bash
# Monitor progress
tail -f /tmp/test_cpp_fresh_progress.log

# Check current cluster
grep "\[.*Testing cluster:" /tmp/test_cpp_fresh_progress.log | tail -1

# Count completed
grep "✓ SUCCESS" /tmp/test_cpp_fresh_progress.log | wc -l
```

---

## File e Directory

### Backup
**Location**: `/tmp/results_backup_1762674939/`
- Contiene TUTTI i risultati pre-existing per i 67 cluster
- Total files: 335 (67 clusters × 5 runs)
- **Può essere ripristinato** se necessario

### Log
**Main log**: `/tmp/test_cpp_fresh_progress.log`
- Contiene output completo del test run
- Include test results per ogni entry
- Timestamp di ogni cluster processed

### Results Output
**Directory**: `/Users/piccoletto/Desktop/Everything/pisa/tesi/Sustainable-Code-Refactoring-with-LLMs/src/execution_outputs/`
- File naming: `{cluster}_results_{1-5}.json`
- Progressivamente popolato mentre i test vengono eseguiti

---

## Entries C++ nel Dataset

### Totale per i 67 Cluster
```
Total CPP entries: 244
  - Nuove (2025-11-08): 150 entries
  - Vecchie (pre 2025-11-08): ~94 entries
```

### Distribuzione Esempi
```
05_log_levels: 1 entry (NEW)
acronym: 2 entries (1 OLD + 1 NEW)
hello_world: 7 entries (4 OLD + 3 NEW)
grade_school: 7 entries (4 OLD + 3 NEW)
leap: 8 entries (5 OLD + 3 NEW)
...etc
```

---

## Post-Completion: Step 5b

### Quando i test completano

**Script già pronto**: `/tmp/analyze_new_cpp_base_results.py`

**Eseguire**:
```bash
python3 /tmp/analyze_new_cpp_base_results.py
```

**Output atteso**:
- Identificazione delle 150 nuove entries
- Calcolo pass rate (5/5 = 100% stable)
- Lista entries stabili → `/tmp/stable_new_cpp_entries.txt`
- Lista entries instabili → `/tmp/unstable_new_cpp_entries.txt`

**Criterio successo**:
- ≥100 entries stabili dalle 150 nuove
- ≥95% stability rate

---

## Prossimi Step Dopo Step 5b

### Step 4: LLM Code Generation
**Solo per entries stabili** identificate in Step 5b

**Comando**:
```bash
cd /Users/piccoletto/Desktop/Everything/pisa/tesi/Sustainable-Code-Refactoring-with-LLMs/src/LLMs_generator_engine

# Generate for stable entries only
python3 llm_generator.py \
  --entry-list /tmp/stable_new_cpp_entries.txt \
  --models openai,claude,gemini \
  --prompt-versions 1,2,3,4
```

**Output**:
- Stable entries × 3 models × 4 versions = ~1,200-1,800 LLM files
- Tempo stimato: ~3-5 ore

### Step 6: Test LLM Code
**Eseguire test su codice LLM generato**

**Comando**:
```bash
cd /Users/piccoletto/Desktop/Everything/pisa/tesi/Sustainable-Code-Refactoring-with-LLMs/src/run_tests_on_clusters

# Test LLM code for clusters with new stable entries
python3 run_tests_on_cluster.py \
  --clusters-from-file /tmp/stable_cpp_clusters.txt \
  --run-quantity 5 \
  --llm-only
```

**Output**:
- Stable entries × 12 variants × 5 runs = ~6,000-9,000 test executions
- Tempo stimato: ~8-10 ore

### Step 7-8: Analysis & Plots
Analizzare risultati e rigenerare tutti i grafici

---

## Lezioni Apprese

### ❌ Cosa NON Funziona
1. **`--selective-rerun`** mode - Non testa nuove entries aggiunte a cluster esistenti
2. **`--overwrite-results`** flag - Può cancellare dati senza sostituirli

### ✅ Cosa Funziona
1. **Cancellare risultati esistenti** prima di testare - Forza fresh execution
2. **`--base-only`** senza selective-rerun - Testa TUTTE le entries nel cluster
3. **Backup preventivo** - Sempre creare backup prima di operazioni distruttive

### 📝 Best Practice
- Per aggiungere entries a cluster esistenti: **rimuovere i risultati esistenti** del cluster
- Test runner lavora a **livello cluster**, non a livello entry
- Usare **backup incrementali** con timestamp

---

## Monitoraggio Consigliato

### Ogni 30 minuti
```bash
# Check progress
COMPLETED=$(grep -c "✓ SUCCESS" /tmp/test_cpp_fresh_progress.log)
echo "Clusters completed: $COMPLETED / 67"

# Check current
grep "\[.*Testing cluster:" /tmp/test_cpp_fresh_progress.log | tail -1

# Check failures
grep "✗ FAILED" /tmp/test_cpp_fresh_progress.log
```

### Verificare completion
```bash
# Count result files created
ls /Users/piccoletto/Desktop/Everything/pisa/tesi/Sustainable-Code-Refactoring-with-LLMs/src/execution_outputs/ | grep -E "^(05_log_levels|acronym|hello_world)_results_[1-5].json$" | wc -l

# Should be 15 for 3 clusters (3 × 5 runs)
```

---

## Recovery Plan

### Se il test fallisce a metà

**Identificare ultimo cluster completato**:
```bash
grep "✓ SUCCESS\|✗ FAILED" /tmp/test_cpp_fresh_progress.log | tail -5
```

**Riprendere da cluster specifico**:
```bash
# Modify /tmp/new_cpp_clusters.txt to start from failed cluster
# Re-run /tmp/test_cpp_fresh.sh
```

### Se serve ripristinare backup
```bash
cp /tmp/results_backup_1762674939/* \
   /Users/piccoletto/Desktop/Everything/pisa/tesi/Sustainable-Code-Refactoring-with-LLMs/src/execution_outputs/
```

---

**Last Updated**: 2025-11-09 08:56:00
**Background Process ID**: ad1f05
**Expected Completion**: 2025-11-09 12:25:00
**Status**: ✅ Running smoothly
