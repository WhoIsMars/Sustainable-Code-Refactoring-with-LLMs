# Summary Esecutivo: Analisi C vs C++ per Tesi

## Per Sezione 5.3 (Threats to Validity)

---

## 1. Problema Identificato

C++ è **presente** nei grafici `execution_stats` ma **assente** nei grafici `energy_improvements`.

## 2. Root Cause

La differenza NON è dovuta a problemi degli LLM, ma a:

### A. Stabilità Base Code
```
C:   76.8% entries stabili (109/142)
C++: 44.3% entries stabili (51/115)
Differenza: -32.5 punti percentuali
```

### B. Differenze Metodologiche

| Pipeline | Filtro | Risultato C++ |
|----------|--------|---------------|
| **execution_stats** | Aggregated (pass_rate su 5 exec) | ✅ 51 entries |
| **energy_improvements** | Per-execution (singola exec) | ❌ 0 entries |

---

## 3. Performance LLM: Confronto Quantitativo

### Pass Rate su Base Code Stabile

| Model | C | C++ | Differenza |
|-------|---|-----|------------|
| OpenAI | 81.4% | 86.5% | **+5.1%** |
| Claude | 81.2% | 86.5% | **+5.3%** |
| Gemini | 82.8% | 91.2% | **+8.4%** |

### Interpretazione

**GLI LLM PERFORMANO MEGLIO CON C++ CHE CON C**

Il problema non è la qualità del codice generato dagli LLM.

---

## 4. Finding Scientifici per la Tesi

### Finding #1: LLM Quality
> "Large Language Models dimostrano capacità SUPERIORI nella generazione di codice C++ rispetto a C, con pass rate tra 86.5% e 91.2% per C++ contro 81-83% per C."

### Finding #2: Dataset Stability
> "Il base code C++ presenta instabilità significativa (55.7% delle entries), riducendo il pool di dati utilizzabili per analisi comparative."

### Finding #3: Methodological Impact
> "La scelta della metodologia di filtraggio (per-execution vs aggregated) ha impatto critico sulla dimensione del dataset finale, con effetti particolarmente pronunciati su linguaggi con base code instabile."

---

## 5. Implicazioni Metodologiche

### Threat to Validity Identificato

**Category**: Internal Validity - Data Selection Bias

**Description**:
Le differenze metodologiche tra pipeline di analisi possono portare a conclusioni contraddittorie. Il caso C++ dimostra come un dataset possa essere:
- Valido e utilizzabile in un'analisi (execution_stats)
- Completamente escluso in un'altra (energy_improvements)

**Impact**:
Medio-Alto. Potrebbe influenzare conclusioni su confronti inter-linguaggio.

**Mitigation**:
1. Standardizzazione delle pipeline con stessa filosofia di filtro
2. Documentazione esplicita dei criteri di esclusione
3. Analisi di sensitività con diversi threshold di stabilità

---

## 6. Raccomandazioni per la Tesi

### Sezione 5.3 - Contenuti da Includere

1. **Tabella Comparativa Pipeline**
   - Mostrare differenze metodologiche
   - Impatto su dimensione dataset

2. **Grafico Pass Rate LLM**
   - C vs C++ per modello
   - Evidenziare performance superiore C++

3. **Discussione Stabilità**
   - Cause potenziali (test non-deterministici)
   - Impatto su riproducibilità

4. **Lesson Learned**
   - Importanza standardizzazione metodologica
   - Trade-off rigore vs dimensione dataset

### Frasi Chiave per Abstract/Conclusions

> "This work identified a critical methodological consideration: the choice of data stability criteria can significantly impact dataset size and, consequently, the generalizability of findings. Our analysis of C vs C++ implementations revealed that while LLMs demonstrate superior performance with C++ (86-91% vs 81-83% pass rate), base code instability can lead to complete exclusion of a language from certain analyses."

---

## 7. Numeri da Citare

### Dataset Size
- **Total clusters analyzed**: 119 (66 C, 53 C++)
- **Total base entries**: 257 (142 C, 115 C++)
- **Stable base entries**: 160 (109 C, 51 C++)

### LLM Performance
- **C LLM results**: 1259 total, 1030 with 100% pass (81.8%)
- **C++ LLM results**: 580 total, 511 with 100% pass (88.1%)

### Key Insight
**C++ LLM code is 6.3 percentage points more reliable than C LLM code** (88.1% vs 81.8%)

---

## 8. Visual per la Tesi

### Grafico Raccomandato #1: Pass Rate Comparison
```
              C           C++
OpenAI:    81.4%  vs   86.5%  (+5.1%)
Claude:    81.2%  vs   86.5%  (+5.3%)
Gemini:    82.8%  vs   91.2%  (+8.4%)
```

### Grafico Raccomandato #2: Base Code Stability
```
C:    [=================76.8%==============]
C++:  [======44.3%======]

Legend: █ Stable (100% pass)  ░ Unstable (<100% pass)
```

### Grafico Raccomandato #3: Pipeline Impact
```
                    execution_stats    energy_improvements
C base entries:           109                 109
C++ base entries:          51                   0
                                                 ↑
                                    Critical difference!
```

---

## 9. Citazioni da Includere

### Per Methodology Section
> "We employed two distinct analysis pipelines with different stability criteria. The execution_stats pipeline uses aggregated pass rates across 5 executions, while the energy_improvements pipeline requires 100% success rate for each individual execution. This methodological difference resulted in the complete exclusion of C++ from energy improvement analyses, despite C++ demonstrating superior LLM-generated code quality (88.1% vs 81.8% stability rate)."

### Per Results Section
> "Contrary to initial hypotheses, Large Language Models demonstrated superior performance when generating C++ code compared to C code, with average pass rates of 88.1% versus 81.8% respectively. This finding contradicts common assumptions about LLM capabilities with complex, object-oriented languages."

### Per Threats to Validity Section
> "The instability of base code implementations poses a significant threat to the validity of comparative analyses. In our dataset, 55.7% of C++ base implementations exhibited non-deterministic test behavior, compared to only 23.2% for C implementations. This instability, when combined with strict filtering criteria, can lead to systematic exclusion of entire programming languages from analyses."

---

## 10. Next Steps per Completare la Tesi

### Immediate (oggi/domani)
- [x] Generare report completo (FATTO)
- [x] Creare summary esecutivo (FATTO)
- [ ] Creare grafici visivi per tesi
- [ ] Scrivere paragrafo per Section 5.3

### Short-term (questa settimana)
- [ ] Decidere se re-run pipeline con threshold più permissivo
- [ ] Estendere analisi a altri linguaggi per generalizzazione
- [ ] Preparare slide per discussione

### Long-term (opzionale)
- [ ] Investigare cause specifiche instabilità C++
- [ ] Proporre standard metodologici per comunità
- [ ] Paper separato su metodologia

---

**File Generati:**
1. `FINAL_REPORT_C_CPP_ANALYSIS.md` - Report completo tecnico
2. `THESIS_SUMMARY.md` - Questo documento (summary esecutivo)
3. `quantitative_llm_comparison.json` - Dati raw
4. `base_code_stability_analysis.json` - Analisi stabilità
5. `global_statistics.json` - RCA statistics
6. `RCA_report.md` - Report RCA

**Tutti i file sono in**: `src/metrics/c_cpp_analysis/`
