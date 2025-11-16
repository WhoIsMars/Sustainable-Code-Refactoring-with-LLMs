# Fix per JavaScript LLM v3 e v4

## Problema Identificato

Le versioni v3 e v4 del prompt hanno solo ~46% delle entries JavaScript completate rispetto a v1 e v2.

**Causa principale**: Il codice tracciava le entries completate usando solo l'`entry_id`, ma ogni entry JavaScript ha **3 varianti LLM** (openAI, claude, gemini). Se una variante era completata, le altre venivano saltate.

### Statistiche Attuali
```
v3: 422/906 combinazioni completate (46.6%)
v4: 414/906 combinazioni completate (45.7%)
```

## Soluzioni Implementate

### 1. Fix in `run_tests_on_cluster.py`
- Traccia le combinazioni `(entry_id, llm_type)` invece del solo `entry_id`
- Esegue le varianti LLM mancanti anche se altre varianti sono già completate
- Preserva i risultati esistenti senza sovrascriverli

### 2. Fix in `language_selective_runner.py`
- Modifica il merger per gestire correttamente le varianti LLM
- Preserva le varianti esistenti quando fa il merge
- Evita duplicati nei risultati finali

### 3. Nuovi Script di Supporto
- `run_javascript_v3_v4_completion.py` - Script principale per completare le entries mancanti
- `complete_javascript_llm_variants.py` - Script di analisi dettagliata

## Come Completare le Entries Mancanti

### Passo 1: Analizzare lo Stato Attuale

```bash
cd /path/to/src/run_tests_on_clusters

# Analizza lo stato attuale
python3 run_javascript_v3_v4_completion.py --analyze-only
```

Output atteso:
```
Prompt Version 3:
  Expected combinations: 906
  Found: 422
  Missing: 484
  Completion: 46.6%

Prompt Version 4:
  Expected combinations: 906
  Found: 414
  Missing: 492
  Completion: 45.7%
```

### Passo 2: Eseguire il Completamento

**Opzione A: Eseguire una versione alla volta (raccomandato)**

```bash
# Completare v3
python3 run_javascript_v3_v4_completion.py --prompt-version 3

# Completare v4
python3 run_javascript_v3_v4_completion.py --prompt-version 4
```

**Opzione B: Eseguire entrambe le versioni**

```bash
python3 run_javascript_v3_v4_completion.py --all
```

**Opzione C: Dry Run (vedere cosa verrà eseguito)**

```bash
python3 run_javascript_v3_v4_completion.py --dry-run --prompt-version 3
```

### Passo 3: Verificare i Risultati

```bash
# Verificare che le entries siano state completate
python3 run_javascript_v3_v4_completion.py --analyze-only
```

Output atteso dopo completamento:
```
Prompt Version 3:
  Expected combinations: 906
  Found: 906
  Missing: 0
  Completion: 100.0%

Prompt Version 4:
  Expected combinations: 906
  Found: 906
  Missing: 0
  Completion: 100.0%
```

## Tempo di Esecuzione Stimato

- Ogni cluster richiede circa 5-15 minuti
- 107 cluster JavaScript × 2 versioni = 214 esecuzioni
- Tempo totale stimato: **18-36 ore**

Si raccomanda di eseguire il completamento in background usando `nohup` o `screen`:

```bash
# Con nohup
nohup python3 run_javascript_v3_v4_completion.py --all > completion.log 2>&1 &

# Con screen
screen -S js_completion
python3 run_javascript_v3_v4_completion.py --all
# Ctrl+A, D per uscire
```

## Nota Importante sul Comportamento

Con la fix implementata:

1. **I risultati esistenti vengono preservati** - Non vengono cancellati né sovrascritti
2. **Vengono aggiunte solo le varianti mancanti** - Se claude è già completato, vengono eseguite solo openAI e gemini
3. **Merging intelligente** - Il merger combina i nuovi risultati con quelli esistenti senza duplicati

## Verificare il Fix

Per verificare che il fix funzioni correttamente, controlla che dopo l'esecuzione:

```bash
python3 -c "
import json
from pathlib import Path

# Check a specific cluster
outputs_dir = Path('../execution_outputs')
with open(outputs_dir / 'matrix_results_v3_1.json') as f:
    data = json.load(f)
    js_entries = data['results']['javascript']
    print(f'JavaScript entries: {len(js_entries)}')

    # Count unique LLM types
    llm_types = set()
    for entry in js_entries:
        for llm in entry.get('LLM_results', []):
            llm_types.add(llm.get('LLM_type'))
    print(f'LLM types: {llm_types}')
"
```

Output atteso (dopo il fix):
```
JavaScript entries: 33  # 11 entries × 3 LLM types
LLM types: {'openAI', 'claude', 'gemini'}
```

## Files Modificati

1. `run_tests_on_cluster.py` - Linee 1985-1986, 2119-2122, 2177-2203
2. `language_selective_runner.py` - Linee 274-342
3. `run_javascript_v3_v4_completion.py` (nuovo)
4. `complete_javascript_llm_variants.py` (nuovo)

## Troubleshooting

### Errori di Timeout
Alcuni cluster potrebbero andare in timeout. Puoi rieseguirli singolarmente:

```bash
python3 run_tests_on_cluster.py \
  --cluster-name NOME_CLUSTER \
  --languages javascript \
  --llm-only \
  --prompt-version 3 \
  --run-quantity 5 \
  --selective-rerun
```

### Verificare i Log degli Errori

```bash
ls errors/cluster_*_v3_error.log
ls errors/cluster_*_v4_error.log
```

## Conclusione

Dopo aver eseguito il completamento, dovresti avere:

- **v1**: ~9400 JavaScript entries (già completo)
- **v2**: ~8800 JavaScript entries (già completo)
- **v3**: ~9060 JavaScript entries (era 4422)
- **v4**: ~9060 JavaScript entries (era 4543)

Questo garantisce risultati completi e consistenti per tutte le versioni del prompt.
