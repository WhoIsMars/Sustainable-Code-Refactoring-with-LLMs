# C++ Dataset Cleanup and Expansion - Progress Report

**Data**: 2025-11-08
**Obiettivo**: Pulire dataset C++ e aggiungere almeno 128 nuove entries (il doppio delle 64 eliminate)

---

## 📊 Status Attuale

### ✅ Step 1: COMPLETATO - Identificazione Entries Instabili

**Risultati**:
- Total C++ entries analizzate: **115**
- Entries stabili (100% pass rate): **51 (44.3%)**
- Entries instabili (<100% pass rate): **64 (55.7%)**
- Clusters affetti: **26**

**Report salvato in**:
- `src/cluster_backups/backups/20251108_163425/step1_unstable_entries_report.json`

**Distribuzione instabilità**:
- 0% pass rate (fallimento totale): ~40 entries
- 20-80% pass rate (intermittente): ~24 entries

---

### ✅ Step 2: COMPLETATO - Marcatura Entries Instabili

**Risultati**:
- Entries marchiate con flag `_unstable`: **64**
- Clusters modificati: **26**
- Backup clusters creati: ✅

**Modifiche apportate ai cluster files**:
Ogni entry instabile ora ha:
```json
{
  "_unstable": true,
  "_instability_reason": "Pass rate: XX.X%",
  "_pass_pattern": [true, false, true, ...],
  "_marked_date": "2025-11-08T16:34:25",
  "_excluded_from_analysis": true
}
```

**Backup directory**:
- `src/cluster_backups/backups/20251108_163425/`

---

### 🔄 Step 3: IN CORSO - Ingestion Nuove Entries GitHub

**Obiettivo**: Aggiungere **150 entries** C++ da GitHub Exercism

**Comando in esecuzione**:
```bash
python3 github_ingestor.py --languages cpp --max-repos 30 --max-entries 150 --token "***"
```

**Progresso attuale**:
- ✅ Token GitHub autenticato
- ✅ Caricati 484 entries esistenti dal dataset
- ✅ Trovati 29 repository Exercism rilevanti
- 🔄 Download in corso (con rate limiting GitHub API)
- ✅ Entries valide trovate: 10+ (anagram, beer-song, binary, clock, etc.)

**Log file**: `/tmp/github_ingest_cpp_run2.log`

**Estimated completion**: ~15-20 minuti (a causa rate limiting GitHub API)

---

## 📝 Prossimi Step

### Step 4: Generazione Codice LLM (PENDING)

**Tool da utilizzare**:
- `src/LLMs_generator_engine/llm_generator.py`

**Piano**:
1. Identificare nuove entries aggiunte in Step 3
2. Per ogni nuova entry, generare 4 versioni di codice LLM:
   - OpenAI (v1, v2, v3, v4)
   - Claude (v1, v2, v3, v4)
   - Gemini (v1, v2, v3, v4)
3. Salvare metadata in `out_improvements_metadata/`

**Comando stimato**:
```bash
cd src/LLMs_generator_engine
python3 llm_generator.py --clusters [new_cpp_clusters] --languages cpp
```

---

### Step 5: Esecuzione Test (PENDING)

**Tool da utilizzare**:
- `src/run_tests_on_clusters/run_tests_on_cluster.py`

**Piano**:
1. Eseguire test su nuove entries base code (5 volte ciascuna)
2. Eseguire test su codice LLM generato (5 volte per ogni versione)
3. Salvare risultati in `execution_outputs/`

**Comandi stimati**:
```bash
cd src/run_tests_on_clusters

# Test base code
python3 run_tests_on_cluster.py --languages cpp --run-quantity 5 --base-only

# Test LLM code
python3 run_tests_on_cluster.py --languages cpp --run-quantity 5 --llm-only
```

---

### Step 6: Analisi Risultati (PENDING)

**Piano**:
1. Verificare pass rate nuove entries base code
2. Verificare pass rate codice LLM
3. Calcolare metriche (CPU, RAM, execution_time)
4. Validare che entries siano stabili (100% pass rate)

**Metriche da verificare**:
- Pass rate base code ≥ 95%
- Pass rate LLM code ≥ 80%
- Metriche valide (no None values)

---

### Step 7: Rigenerazione Grafici (PENDING)

**Tool da utilizzare**:
- `src/metrics/exec_metrics_calculator.py`
- `src/metrics/execMetricStatsVisualizator.py`
- `src/metrics/energy_improvements/improvement_calculator.py`

**Piano**:
1. Ricalcolare statistics aggregate
2. Rigenerare grafici `execution_stats_plots/`
3. Rigenerare grafici `energy_improvements/`
4. **Verificare che C++ ora appaia in `fig_improvements_by_language.png`**

**Comandi stimati**:
```bash
cd src/metrics

# Ricalcola execution stats
python3 main_exec_metrics_analysis.py

# Ricalcola energy improvements
cd energy_improvements
python3 improvement_calculator.py
python3 analyze_energy_improvements.py
```

---

## 🎯 Obiettivi Finali

### Successo Criteri

1. ✅ **Dataset C++ pulito**:
   - Solo entries con 100% pass rate in base code
   - Nessuna entry instabile inclusa nelle analisi

2. ✅ **Dataset C++ espanso**:
   - Almeno 128 nuove entries aggiunte
   - Total entries stabili: 51 + 128 = **179 entries**
   - Improvement rispetto a situazione attuale: **+250%**

3. ✅ **LLM Coverage completo**:
   - Tutte le nuove entries hanno codice LLM generato
   - 3 modelli × 4 versioni prompt = 12 varianti per entry

4. ✅ **Risultati validati**:
   - Pass rate base code: 100% (per definition)
   - Pass rate LLM: >80% (obiettivo)
   - Metriche complete per analisi

5. ✅ **C++ visibile nei grafici**:
   - `execution_stats_plots/`: ✅ (già presente)
   - `energy_improvements/fig_improvements_by_language.png`: ⏳ (OBIETTIVO FINALE)

---

## 📈 Expected Results

### Before Cleanup

| Metric | Value |
|--------|-------|
| C++ base entries | 115 |
| Stable entries (100%) | 51 (44.3%) |
| Unstable entries | 64 (55.7%) |
| Present in energy_improvements | ❌ NO (0 entries) |

### After Cleanup & Expansion

| Metric | Target Value |
|--------|--------------|
| C++ base entries | ~179 |
| Stable entries (100%) | ~179 (100%) |
| Unstable entries | 0 (marked, excluded) |
| Present in energy_improvements | ✅ YES (~150+ entries) |

**Improvement**: +250% stable entries, C++ fully integrated in all analyses

---

## 🔧 Technical Notes

### Pipeline Files Created

1. **Main Orchestrator**:
   - `src/dataset_handling/cpp_dataset_cleanup_and_expansion.py`
   - Handles Step 1-3 automation

2. **Existing Tools Reused**:
   - `github_ingestor.py` - GitHub ingestion
   - `llm_generator.py` - LLM code generation
   - `run_tests_on_cluster.py` - Test execution
   - Various metrics calculators

### Backup Strategy

**All backups in**: `src/cluster_backups/backups/20251108_163425/`

Files backed up:
- 26 cluster JSON files (original state)
- `step1_unstable_entries_report.json`
- `step2_marking_report.json`
- `pipeline_complete_report.json`

**Rollback capability**: ✅ Full rollback possible

---

## ⏭️ Next Actions

### Immediate (when Step 3 completes)

1. ✅ Verify ingestion results
2. ✅ Check number of entries added
3. ✅ Validate new clusters created

### Short-term (oggi)

1. 📝 Run Step 4: LLM generation
2. 📝 Run Step 5: Test execution
3. 📝 Run Step 6: Results analysis

### Final (oggi/domani)

1. 📝 Run Step 7: Regenerate all plots
2. 📝 Verify C++ appears in energy_improvements
3. 📝 Update thesis with new findings

---

## 📞 Monitoring

**Check ingestion progress**:
```bash
tail -f /tmp/github_ingest_cpp_run2.log
```

**Check process status**:
```bash
ps aux | grep github_ingestor
```

**Count new entries added**:
```bash
cd src/clusters
git diff --stat  # Shows modified cluster files
```

---

**Last Updated**: 2025-11-08 16:40:00
**Status**: Step 3 in progress, Steps 1-2 complete
**Next Checkpoint**: When ingestion completes (~16:55)
