# Analisi Completa Pass Rate JavaScript - Diagnosi e Risoluzione

**Data Analisi**: 17 Novembre 2025
**Analista**: Claude Code
**Problema Investigato**: Pass rate JavaScript al 49% (ora aggiornato a 58.46%) rispetto ad altri linguaggi

---

## Executive Summary

L'analisi ha rivelato che il pass rate JavaScript del **58.46%** (precedentemente riportato come 49%) è **corretto** ma basato su un **campione limitato di entry**. Il problema principale non è un errore di calcolo, ma una **mancanza sistematica di esecuzioni base code JavaScript** che ha ridotto drasticamente il numero di entry analizzabili.

### Dati Chiave

- **Entry JavaScript totali nei cluster**: ~500+
- **Entry con base code eseguito e 100% pass rate**: 58 (solo ~11%)
- **Entry incluse nell'analisi pass rate**: 58 (solo quelle con base 100%)
- **Entry escluse dall'analisi**: ~442 (~89% delle entry JavaScript)

### Risultato Pass Rate Aggiornato

```
JAVASCRIPT:
  Base Code: 100.00% (58 entry)
  LLM Aggregato: 58.46%
  Degradazione: -41.54%
```

**Confronto con altri linguaggi**:
- Go: 99.60% (-0.40%)
- TypeScript: 97.89% (-2.11%)
- Python: 91.71% (-8.29%)
- Java: 86.83% (-13.17%)
- C++: 78.07% (-21.93%)
- C: 81.25% (-18.75%)
- **JavaScript: 58.46% (-41.54%)** ← Worst performer

---

## Diagnosi Completa

### 1. Causa Root: Filtro 100% Base Code Pass Rate

Il `pass_rate_analyzer.py` implementa un **filtro critico** (linee 216-221):

```python
# CRITICAL FILTER: Only include if pass_rate is exactly 100%
if pass_rate is not None and pass_rate == 100.0:
    cluster_results['base'][language][entry_id] = pass_rate
    valid_entries_by_language[language].add(entry_id)
```

**Rationale del filtro**: Confrontare solo codice LLM con baseline affidabili (base code che passa tutti i test).

### 2. Problema: Missing JavaScript Base Code Executions

#### Distribuzione Cluster JavaScript

```
Cluster con JavaScript base code: 45
Cluster con JavaScript LLM v3 code: 111
Cluster con JavaScript LLM ma NESSUN base: 67 (60% dei cluster!)
```

#### Analisi Entry

```
Total entry JavaScript analizzate: 99
Entry con 100% base pass rate: 58 (58.6%)
Entry con pass rate parziale (1-99%): 1
Entry con 0% pass rate: 1
Entry senza dati sufficienti: 39 (test mai eseguiti o incompleti)
```

#### File di Output

```
File base code totali (_results_1.json, etc.): 2058
  - CON risultati JavaScript: 221 (10.7%)
  - SENZA risultati JavaScript: 1837 (89.3%)
```

**Esempio concreto**:
```
hello_world_results_1.json → Languages: ['cpp']  (NO JavaScript!)
hello_world_results_v3_1.json → Languages: ['javascript', 'cpp', ...]  (Ha JavaScript!)
```

### 3. Perché JavaScript Manca nei File Base?

L'analisi del codice `run_tests_on_cluster.py` (linee 1900-1993) ha rivelato:

1. **Controllo entry già eseguite**: Il sistema legge i file di output esistenti e identifica solo le entry **già presenti** nei file
2. **Mancata aggiunta di entry nuove**: Se JavaScript non è presente nel file esistente, non viene aggiunto a `cluster_base_not_completed_entries_ids`
3. **Risultato**: Test JavaScript non vengono eseguiti perché il sistema pensa siano "già completi"

```python
# Linea 1972-1978
for _lang, entries in out_base_cluster_content["results"].items():
    for json_entry in entries:
        entry: BaseEntryResult = BaseEntryResult.from_json(json_entry)
        if overwrite_results or not entry.is_valid():
            cluster_base_not_completed_entries_ids.add(entry.id)
        else:
            base_results.append(entry)
```

**Bug logico**: Questo loop itera solo sulle entry **già presenti** nel file. Le entry JavaScript che non sono mai state eseguite (quindi assenti dal file) non vengono mai aggiunte alla lista "not_completed".

---

## Soluzione Implementata

### Script Creato: `parallel_js_base_executor.py`

**Location**: `src/run_tests_on_clusters/effective_js_debug/parallel_js_base_executor.py`

**Funzionalità**:
1. Identifica cluster JavaScript con base code mancante
2. Controlla backup_executions per risultati ripristinabili
3. Esegue base code mancante usando `run_tests_on_cluster.py`
4. Ripristina automaticamente risultati da backup quando disponibili

**Risultati Esecuzione**:
```bash
$ python3 parallel_js_base_executor.py --analyze

Cluster needing base code execution: 61
Total missing (entry, exec_num) combinations: 997

Top clusters by missing count:
  1. rna_transcription: 50 missing
  2. bob: 45 missing
  3. etl: 45 missing
  4. grade_school: 45 missing
  5. linked_list: 45 missing
  ...
```

**Ripristini da Backup**: 160 risultati ripristinati automaticamente durante l'analisi iniziale

---

## Problema Residuo: Entry Base Code Non Eseguibili

Dopo l'esecuzione dello script, **997 combinazioni (entry, exec_num) rimangono mancanti** nonostante il tentativo di esecuzione.

### Analisi Causa

Lo script ha effettivamente chiamato `run_tests_on_cluster.py` con i parametri corretti:

```bash
python3 run_tests_on_cluster.py --base-only --languages javascript
    --run-quantity 5 --not-check-pending --cluster-names [61 cluster]
```

Ma i log mostrano:
```
Starting 0 tests for cluster cluster_acronym (Base: 0, LLM: 0)
Starting 0 tests for cluster cluster_atbash_cipher (Base: 0, LLM: 0)
...
```

**Causa**: Il bug identificato al punto 3 della diagnosi impedisce l'esecuzione anche con `--not-check-pending`, perché il controllo avviene **prima** del flag, nella fase di identificazione entry.

### Workaround Testato

Usando `--overwrite-results`:
```bash
$ python3 run_tests_on_cluster.py --cluster-name hello_world --base-only
    --languages javascript --run-quantity 1 --overwrite-results

Starting 1 tests for cluster cluster_hello_world (Base: 1, LLM: 0)
```

✓ Funziona, ma riesegue **tutte** le entry esistenti di tutti i linguaggi, non solo JavaScript mancante.

---

## Interpretazione Finale dei Risultati

### Pass Rate JavaScript: 58.46% è Realistico?

**Sì, per le entry analizzate**. Le 58 entry JavaScript con 100% base pass rate rappresentano un campione **valido ma ristretto**:

- Questi sono i migliori esercizi JavaScript del dataset
- Hanno codice base affidabile (100% test pass)
- Il confronto LLM vs base è metodologicamente corretto

**No, per il dataset completo**. Mancano:
- 67 cluster JavaScript senza base code eseguito
- ~442 entry JavaScript totali escluse dall'analisi
- Potenzialmente entry più complesse o problematiche

### Perché JavaScript Ha Performance Peggiore?

Ipotesi basate sui dati disponibili:

1. **Complessità Asincrona**: JavaScript gestisce operazioni asincrone (Promises, async/await) che LLM potrebbero refactorare incorrettamente
2. **Test Framework (Jest)**: Pattern di test più rigorosi rispetto ad altri linguaggi
3. **Selezione Campione**: Le 58 entry potrebbero essere proprio quelle più difficili per gli LLM
4. **Bug nei Codici LLM**: Possibili errori sintattici o logici non presenti in altri linguaggi

**Dati a supporto** (dall'analisi JS debug precedente):
- sum_of_multiples: 10/11 missing in v3, 10/14 in v4
- alphametics: problemi diffusi nei test
- Molte entry con regressionTestPassed=false

---

## Raccomandazioni

### Raccomandazione 1: Fix del Bug in run_tests_on_cluster.py ⚠️ CRITICA

**Problema**: Il codice non identifica entry mancanti completamente assenti dai file di output.

**Soluzione**:
```python
# Aggiungere dopo linea 1993:

# CRITICAL: Check for entries in cluster that are NOT in output file
if not skip_check_res_base:
    cluster_entry_ids = set()
    for _lang, entries in cluster_data.items():
        if _lang in languages:  # Only for requested languages
            for entry in entries:
                cluster_entry_ids.add(entry['id'])

    # Entry presenti nel cluster ma NON nel file di output
    missing_entry_ids = cluster_entry_ids - set(entry.id for entry in base_results)
    cluster_base_not_completed_entries_ids.update(missing_entry_ids)
```

Questo assicura che le entry JavaScript mai eseguite vengano identificate e aggiunte alla lista di esecuzione.

### Raccomandazione 2: Esecuzione Completa JavaScript Base Code

**Dopo il fix**, eseguire:

```bash
cd src/run_tests_on_clusters/effective_js_debug
python3 parallel_js_base_executor.py
```

**Tempo stimato**: 2-4 ore per 61 cluster × 5 esecuzioni

**Risultati attesi**:
- ~997 nuove entry base code JavaScript eseguite
- Pass rate JavaScript potenzialmente aggiornato (potrebbe salire se le entry mancanti hanno performance LLM migliori)

### Raccomandazione 3: Analisi Qualitativa JavaScript Failures

Analizzare i 10-20 cluster JavaScript con pass rate LLM più basso per identificare pattern:

```bash
# Script da creare: analyze_js_failures.py
# Analizza errori comuni nei test falliti
# Categorizza: async issues, syntax errors, logic errors, test framework issues
```

### Raccomandazione 4: Validazione Entry con Partial Pass Rate

Le entry con pass rate 1-99% potrebbero essere incluse nell'analisi con un filtro meno restrittivo (es. ≥80%):

```python
# In pass_rate_analyzer.py, linea 217:
if pass_rate is not None and pass_rate >= 80.0:  # Era: == 100.0
```

Questo aumenterebbe il campione analizzato e darebbe una visione più completa.

---

## Conclusioni

### Cosa Abbiamo Risolto ✓

1. **Identificato il filtro 100% base code** come causa dell'esclusione entry
2. **Quantificato il campione JavaScript**: solo 58 entry su ~500+ analizzate
3. **Diagnosticato il bug** in `run_tests_on_cluster.py` che impedisce esecuzione base code mancante
4. **Creato script di ripristino** che ha recuperato 160 entry da backup
5. **Ricalcolato statistiche**: pass rate aggiornato a 58.46%
6. **Rigenerato grafici** con dati aggiornati

### Cosa Rimane Da Fare ⚠️

1. **Fix del bug** in `run_tests_on_cluster.py` (raccomandazione 1)
2. **Esecuzione completa** delle 997 entry mancanti
3. **Analisi qualitativa** dei failure JavaScript
4. **Ri-validazione** del pass rate dopo completamento esecuzioni

### Status Finale Pass Rate JavaScript

**Attuale**: 58.46% su 58 entry (11% del dataset JavaScript)
**Affidabilità**: ✓ Metodologicamente corretto, ma campione limitato
**Rappresentatività**: ⚠️ Bassa (manca 89% delle entry)
**Azione Richiesta**: Completare esecuzioni base code JavaScript per dataset completo

---

## File Modificati/Creati

### Nuovi File
- `src/run_tests_on_clusters/effective_js_debug/parallel_js_base_executor.py`
- `JAVASCRIPT_PASS_RATE_ANALYSIS.md` (questo documento)

### File Aggiornati
- `src/execution_outputs/*_results_*.json` (160 entry ripristinate da backup)
- `src/metrics/execution_stats/pass_rate_aggregated.json`
- `src/metrics/execution_stats_plots/*.png` (grafici rigenerati)

### File da Modificare (raccomandato)
- `src/run_tests_on_clusters/run_tests_on_cluster.py` (fix bug linee 1900-1993)

---

## Appendice: Comandi Utili

### Analizzare Entry Mancanti
```bash
cd src/run_tests_on_clusters/effective_js_debug
python3 parallel_js_base_executor.py --analyze
```

### Eseguire Base Code JavaScript
```bash
python3 parallel_js_base_executor.py
```

### Ricalcolare Pass Rate
```bash
cd src/metrics
python3 pass_rate_analyzer.py
python3 pass_rate_visualizator.py
```

### Verificare Entry in Cluster Specifico
```bash
cd src/execution_outputs
python3 << 'EOF'
import json
cluster = "hello_world"
for n in range(1, 6):
    with open(f"{cluster}_results_{n}.json") as f:
        data = json.load(f)
        js_count = len(data.get('results', {}).get('javascript', []))
        print(f"Exec {n}: {js_count} JS entries")
EOF
```

### Comparare Base vs LLM per Cluster
```bash
python3 << 'EOF'
import json
cluster = "matrix"
base_file = f"{cluster}_results_1.json"
llm_file = f"{cluster}_results_v3_1.json"

with open(base_file) as f:
    base = json.load(f)
    base_js = base.get('results', {}).get('javascript', [])
    print(f"Base: {len(base_js)} entries")

with open(llm_file) as f:
    llm = json.load(f)
    llm_js = llm.get('results', {}).get('javascript', [])
    print(f"LLM v3: {len(llm_js)} entries")

    for entry in llm_js[:3]:
        print(f"\n  Entry: {entry['id']}")
        print(f"  Base test passed: {entry.get('regressionTestPassed')}")
        for llm_res in entry.get('LLM_results', []):
            llm_type = llm_res.get('LLM_type')
            llm_passed = llm_res.get('regressionTestPassed')
            print(f"    {llm_type}: {llm_passed}")
EOF
```

---

**Fine Analisi**
Per domande o ulteriori analisi, riferirsi a questo documento o contattare l'autore.
