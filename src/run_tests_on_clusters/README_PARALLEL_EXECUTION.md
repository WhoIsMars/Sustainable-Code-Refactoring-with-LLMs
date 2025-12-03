# Parallel Execution & Monitoring System

Sistema di esecuzione parallela e monitoraggio per le entries LLM del progetto Sustainable Code Refactoring.

## 📋 Indice

- [Novità](#novità)
- [Script Disponibili](#script-disponibili)
- [Esecuzione Parallela](#esecuzione-parallela)
- [Monitoraggio Esecuzioni](#monitoraggio-esecuzioni)
- [Esempi d'Uso](#esempi-duso)
- [Best Practices](#best-practices)

---

## 🆕 Novità

### 1. **Esecuzione Parallela con Multiprocessing**
Il nuovo sistema di esecuzione parallela (`new_llm_selective_runner.py`) permette di distribuire il carico di lavoro tra più processi, riducendo significativamente i tempi di esecuzione.

**Benefici:**
- ⚡ Riduzione dei tempi di esecuzione fino a 1/N (dove N = numero di processi)
- 🔄 Distribuzione equa del carico di lavoro
- 🛡️ Isolamento tra processi (container Docker univoci per processo)
- 🔙 Backward compatibility completa

### 2. **Monitor Esecuzioni in Tempo Reale**
Il nuovo script `execution_monitor.py` fornisce visibilità completa sullo stato delle esecuzioni con:
- 📊 Progress bar visuale
- 📈 Statistiche dettagliate per base ed LLM entries
- 🔄 Aggiornamento periodico automatico
- 📱 Output formattato e user-friendly

---

## 📦 Script Disponibili

### `new_llm_selective_runner.py`
Script principale per l'esecuzione parallela delle entries LLM non ancora eseguite.

**Features:**
- Identificazione automatica delle entries da eseguire
- Distribuzione intelligente del carico tra processi
- Container Docker univoci per ogni processo
- Report dettagliato post-esecuzione

### `execution_monitor.py`
Script di monitoraggio per tracking real-time dello stato delle esecuzioni.

**Features:**
- Scansione di tutti i cluster
- Analisi stato base entries (con filtro 100% pass rate)
- Analisi stato LLM entries (12 versioni per base entry)
- Progress tracking con percentuali e barre visuali
- Modalità snapshot o continuous monitoring

### `monitor.sh`
Wrapper bash per facilitare l'utilizzo del monitor.

**Features:**
- Interfaccia semplificata
- Preset comuni (once, continuous, fast, detailed)
- Modalità interattiva
- Output colorato

---

## ⚡ Esecuzione Parallela

### Uso Base

```bash
# Esecuzione sequenziale (comportamento originale)
python3 new_llm_selective_runner.py

# Esecuzione parallela con 4 processi
python3 new_llm_selective_runner.py --parallel-processes 4

# Esecuzione parallela con 8 processi e 2 worker per processo
python3 new_llm_selective_runner.py --parallel-processes 8 --max-workers 2
```

### Parametri Disponibili

| Parametro | Default | Descrizione |
|-----------|---------|-------------|
| `--parallel-processes` | 1 | Numero di processi paralleli da utilizzare |
| `--max-workers` | 4 | Numero di worker ThreadPoolExecutor per processo |
| `--languages` | all | Linguaggi target (es: `c cpp java`) |

### Come Funziona

1. **Scansione Clusters**: Identifica tutte le entries LLM non ancora eseguite
2. **Batching**: Divide equamente le entries tra N processi
3. **Esecuzione Parallela**: Ogni processo esegue `run_tests_on_cluster.py` con:
   - Proprio batch di entries
   - Container Docker prefix univoco (`test_runner_p0`, `test_runner_p1`, etc.)
4. **Aggregazione Risultati**: Raccoglie i risultati da tutti i processi
5. **Report**: Genera report unificato post-esecuzione

### Calcolo Numero Processi Ottimale

**Regola generale:**
```
N = min(CPU_cores / 2, total_entries / 10)
```

**Esempio:**
- Sistema con 8 core CPU
- 100 entries da eseguire
- Numero ottimale: `min(8/2, 100/10) = min(4, 10) = 4 processi`

**Nota:** Ogni processo usa `max-workers` thread per parallelizzazione interna, quindi:
- Parallelizzazione totale = `parallel-processes × max-workers`
- Esempio: 4 processi × 4 workers = 16 esecuzioni parallele

---

## 📊 Monitoraggio Esecuzioni

### Uso Base

```bash
# Snapshot singolo (esegui una volta)
python3 execution_monitor.py --once

# Monitoraggio continuo (refresh ogni 30s)
python3 execution_monitor.py

# Monitoraggio continuo con dettagli (refresh ogni 30s)
python3 execution_monitor.py --details

# Monitoraggio rapido (refresh ogni 10s)
python3 execution_monitor.py --interval 10
```

### Uso Wrapper Shell

```bash
# Snapshot
./monitor.sh once

# Monitoraggio continuo (30s)
./monitor.sh continuous

# Monitoraggio rapido (10s)
./monitor.sh fast

# Monitoraggio dettagliato (30s)
./monitor.sh detailed

# Modalità interattiva
./monitor.sh custom
```

### Informazioni Visualizzate

#### 1. Overall Progress
- Barra di progresso generale (base + LLM)
- Percentuale completamento totale
- Esecuzioni completate / esecuzioni attese

#### 2. Base Entries
- Numero totale base entries
- Entries con 100% pass rate (5/5 esecuzioni)
- Esecuzioni completate/mancanti
- Breakdown per linguaggio (con `--details`)

#### 3. LLM Entries
- Numero atteso di LLM entries (basato su base con 100% pass)
- Numero trovato nel dataset
- Esecuzioni completate/mancanti
- Breakdown per prompt version (con `--details`)
- Breakdown per linguaggio (con `--details`)

### Logica di Calcolo

**Per ogni base entry con 100% pass rate:**
```
Expected LLM entries = 3 modelli × 4 prompt versions = 12
Expected executions per entry = 12 × 5 = 60
```

**Modelli LLM:**
1. ChatGPT4 (openAI)
2. ClaudeSonnet4 (claude)
3. GeminiFlash (gemini)

**Prompt Versions:** v1, v2, v3, v4

---

## 💡 Esempi d'Uso

### Scenario 1: Esecuzione Iniziale
Avviare l'esecuzione parallela e monitorare i progressi in tempo reale.

**Terminal 1 - Esecuzione:**
```bash
cd src/run_tests_on_clusters
python3 new_llm_selective_runner.py --parallel-processes 4
```

**Terminal 2 - Monitoraggio:**
```bash
cd src/run_tests_on_clusters
./monitor.sh fast
```

### Scenario 2: Recovery Esecuzioni Fallite
Eseguire solo le entries mancanti con monitoraggio dettagliato.

```bash
# Terminal 1
python3 new_llm_selective_runner.py --parallel-processes 8 --max-workers 2

# Terminal 2
./monitor.sh detailed
```

### Scenario 3: Snapshot Rapido
Controllare lo stato attuale senza monitoraggio continuo.

```bash
./monitor.sh once
```

Output:
```
🔍 Scanning 409 clusters...

====================================================================================================
📊 EXECUTION STATUS MONITOR - REAL-TIME STATISTICS
====================================================================================================
⏰ Last updated: 2025-12-01 11:32:43

🎯 OVERALL PROGRESS
[███████████████████████████████████████████████████████████░░░░░░░░░░░░░░░░░░░░] 76.3%
   Total executions: 115,268 / 151,020

📦 BASE ENTRIES
----------------------------------------------------------------------------------------------------
Progress: [███████████████████████████████████████████████████████████░] 98.6%
  • Total base entries: 2,568
  • Entries with 100% pass rate (5/5): 2,303 (89.7%)
  • Executions completed: 12,654 / 12,840
  • Executions remaining: 186

🤖 LLM ENTRIES
----------------------------------------------------------------------------------------------------
Progress: [████████████████████████████████████████████░░░░░░░░░░░░░░░░] 74.3%
  • Expected LLM entries (from base with full pass): 27,636
  • LLM entries found in dataset: 30,622
  • Executions completed: 102,614 / 138,180
  • Executions remaining: 35,566

====================================================================================================

💡 Tip: Use 'new_llm_selective_runner.py --parallel-processes N' to speed up execution
```

### Scenario 4: Test su Linguaggi Specifici
Eseguire solo specifici linguaggi.

```bash
python3 new_llm_selective_runner.py \
  --parallel-processes 4 \
  --languages c cpp java
```

---

## 🎯 Best Practices

### 1. Numero di Processi

**✅ Consigliato:**
```bash
# Sistema con 8 CPU cores
python3 new_llm_selective_runner.py --parallel-processes 4
```

**❌ Evitare:**
```bash
# Troppi processi = overhead, contention risorse
python3 new_llm_selective_runner.py --parallel-processes 32
```

### 2. Monitoraggio durante Esecuzioni Lunghe

**✅ Consigliato:**
```bash
# Terminal separato con refresh automatico
./monitor.sh fast
```

**❌ Evitare:**
```bash
# Snapshot continui manuali = inefficiente
while true; do ./monitor.sh once; sleep 10; done
```

### 3. Gestione Errori

Se un processo fallisce, il sistema:
1. ❌ Segnala l'errore
2. 📝 Mostra gli ultimi 20 log di errore
3. ✅ Continua con gli altri processi
4. 📊 Genera report finale con stato completo

Per riprovare entries fallite:
```bash
# Lo script identifica automaticamente entries non completate
python3 new_llm_selective_runner.py --parallel-processes 4
```

### 4. Utilizzo Risorse

**Monitoring:**
```bash
# Controllare utilizzo CPU/memoria durante esecuzione
htop
# oppure
top
```

**Ridurre carico:**
```bash
# Meno processi E meno worker per processo
python3 new_llm_selective_runner.py \
  --parallel-processes 2 \
  --max-workers 2
```

### 5. Integrazione con Pipeline

```bash
#!/bin/bash
# main_pipeline.sh

# 1. Esegui entries mancanti in parallelo
python3 src/run_tests_on_clusters/new_llm_selective_runner.py \
  --parallel-processes 4

# 2. Genera snapshot finale
python3 src/run_tests_on_clusters/execution_monitor.py \
  --once \
  --details > execution_report.txt

# 3. Continua con analisi...
```

---

## 🔧 Troubleshooting

### Problema: "Container name conflict"
**Causa:** Due processi tentano di usare lo stesso nome container Docker.

**Soluzione:** Questo è già gestito automaticamente tramite `--container-prefix`, ma se persiste:
```bash
# Pulisci container esistenti
docker ps -a | grep test_runner | awk '{print $1}' | xargs docker rm -f
```

### Problema: "Out of memory"
**Causa:** Troppi processi/worker paralleli.

**Soluzione:**
```bash
# Riduci parallelizzazione
python3 new_llm_selective_runner.py \
  --parallel-processes 2 \
  --max-workers 2
```

### Problema: Monitor lento durante scansione
**Causa:** Molti cluster da analizzare.

**Soluzione:** Usa intervalli più lunghi:
```bash
python3 execution_monitor.py --interval 60
```

---

## 📝 Note Tecniche

### Compatibilità

- ✅ **Backward compatible**: Esecuzione senza parametri usa comportamento originale (1 processo)
- ✅ **Output format**: Identico al sistema precedente
- ✅ **Result merging**: Automatico e trasparente

### Requisiti

- Python 3.8+
- Modulo `multiprocessing` (standard library)
- Docker per esecuzioni
- Dipendenze progetto esistenti

### File Generati

**Esecuzione parallela:**
- `src/execution_outputs/{cluster}_results_{prompt_v}_{exec_num}.json`
- `src/analysis_outputs/llm_recovery_report.json`

**Monitor:**
- Nessun file (output solo a terminale)

---

## 📚 Riferimenti

- Script originale: `run_tests_on_cluster.py`
- Utility: `src/utility_dir/general_utils.py`
- Paths: `src/utility_dir/utility_paths.py`

---

**Data aggiornamento:** 01/12/2024
**Autore:** Development Team
**Versione:** 2.0
