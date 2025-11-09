#!/usr/bin/env python3
"""
Update cluster JSON metadata for CPP entries.
Scans dataset directories, updates the LLMs field in cluster JSON files
to the correct format, and calculates similarity metrics.
"""

import json
import os
import sys
import re
from pathlib import Path

# Aggiungi la directory parent (src) al path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))

from utility_dir import utility_paths
from utility_dir.general_utils import read_json, write_json
# Importa il SimilarityCalculator per eseguire il "Passo 4"
try:
    from metrics.similarity.similarity_calculator import SimilarityCalculator
except ImportError:
    print("Errore: Impossibile importare SimilarityCalculator.")
    print("Assicurati che 'src/metrics/similarity/similarity_calculator.py' esista.")
    sys.exit(1)

# Definiamo il linguaggio target
TARGET_LANGUAGE = "cpp"

def _extract_prompt_version(filename: str) -> int | None:
    """Extract prompt version number from filename"""
    # Pattern: ModelName_exercise_v{N}.cpp
    match = re.search(r'_v(\d+)\.cpp$', filename)
    if match:
        return int(match.group(1))
    return None

def scan_and_build_llm_metadata(entry: dict) -> list[dict]:
    """
    Scansiona il filesystem per i file LLM e costruisce il blocco
    di metadati nel FORMATO CORRETTO (simile a ClusterJSONUpdater).
    """
    llm_metadata = []

    code_snippet_path = entry.get("codeSnippetFilePath", "")
    if not code_snippet_path:
        return llm_metadata

    parts = str(code_snippet_path).split("/")
    if len(parts) < 2:
        return llm_metadata

    dir_name = str(parts[0]) + "/" + str(parts[1])
    exercise_dir = utility_paths.DATASET_DIR / dir_name

    if not exercise_dir.exists():
        return llm_metadata

    # Mappatura corretta dei nomi delle directory
    llm_mappings = {
        "openAI": "ChatGPT4",
        "claude": "ClaudeSonnet4",
        "gemini": "GeminiFlash"
    }

    for model_dir, file_prefix in llm_mappings.items():
        llm_dir_path = exercise_dir / model_dir
        if not llm_dir_path.exists():
            continue

        # Trova tutti i file .cpp in questa directory
        for generated_file in llm_dir_path.glob("*.cpp"):
            if not generated_file.is_file():
                continue

            prompt_version = _extract_prompt_version(generated_file.name)
            if prompt_version is None:
                continue

            # Leggi il file per le statistiche
            try:
                with open(generated_file, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()
                
                char_count = len(content)
                word_count = len(content.split())
                relative_path = str(generated_file.relative_to(utility_paths.DATASET_DIR))

                # Costruisci il metadata block nel FORMATO CORRETTO
                llm_meta = {
                    "type": model_dir,  # Chiave corretta
                    "path": relative_path,  # Chiave corretta
                    "word_quantity": word_count,
                    "char_quantity": char_count,
                    "filename": generated_file.name,
                    "prompt_version": prompt_version,
                    "fuzzy_score": 0.0,  # Segnaposto
                    "cosine_similarity_score": 0.0,  # Segnaposto
                    "similarity_index": 0.0  # Segnaposto
                }
                llm_metadata.append(llm_meta)
            
            except Exception as e:
                print(f"  ⚠️  Errore lettura file {generated_file}: {e}")
                continue

    # Ordina per coerenza (come fa l'orchestrator)
    llm_metadata.sort(key=lambda x: (x["type"], x["prompt_version"]))
    return llm_metadata

def update_cluster_metadata(cluster_file: Path, similarity_calculator: SimilarityCalculator) -> tuple[bool, int, int]:
    """
    Aggiorna un singolo file cluster:
    1. Legge il file JSON.
    2. Controlla le entry 'cpp'.
    3. Se il formato 'LLMs' è errato (vecchio), lo sovrascrive con quello nuovo.
    4. Salva il file.
    5. Esegue il ricalcolo della similarità sul file appena salvato.
    """

    try:
        cluster_data = read_json(cluster_file)
    except json.JSONDecodeError:
        print(f"  ❌ Errore: Impossibile decodificare JSON in {cluster_file}")
        return False, 0, 0

    if TARGET_LANGUAGE not in cluster_data:
        return False, 0, 0  # Nessuna entry 'cpp' in questo cluster

    modified = False
    total_entries = 0
    updated_entries = 0
    cluster_name = cluster_file.stem

    for entry in cluster_data[TARGET_LANGUAGE]:
        total_entries += 1
        llm_list = entry.get('LLMs', [])

        # Controlla se l'aggiornamento è necessario
        # Criterio: se la lista LLM non è vuota E la prima entry ha il formato errato
        if llm_list and ('llm_type' in llm_list[0] or 'generated_code_path' in llm_list[0]):
            print(f"  🔧 Formato obsoleto trovato per: {entry['id']}. Aggiornamento...")
            
            # PASSO 3: Ricostruisci il blocco LLMs
            new_llm_metadata = scan_and_build_llm_metadata(entry)
            
            if len(new_llm_metadata) > 0:
                entry['LLMs'] = new_llm_metadata
                modified = True
                updated_entries += 1
                print(f"    -> Ricostruito con {len(new_llm_metadata)} file LLM.")
            else:
                print(f"    -> Attenzione: Nessun file LLM trovato sul disco per {entry['id']}")
                entry['LLMs'] = [] # Svuota la lista errata
                modified = True


    # Se abbiamo modificato il file, salviamolo
    if modified:
        try:
            write_json(cluster_file, cluster_data)
            print(f"  💾 File cluster salvato: {cluster_name}")
            
            # PASSO 4: Calcola la similarità
            # Ora che il file ha il formato corretto con segnaposto 0.0,
            # eseguiamo il calcolatore di similarità per riempire i valori.
            print(f"  🧠 Calcolo similarità per: {cluster_name}...")
            try:
                # Il calculator legge il file, calcola, e salva di nuovo.
                similarity_calculator.calculate_similarities_for_cluster(cluster_file.name)
                print("    -> Similarità calcolata e salvata.")
            except Exception as e:
                print(f"  ❌ Errore durante il calcolo della similarità: {e}")

        except Exception as e:
            print(f"  ❌ Errore durante il salvataggio del file {cluster_name}: {e}")
            return False, total_entries, 0

    return modified, total_entries, updated_entries

def main():
    print("=" * 80)
    print("CPP CLUSTER METADATA FIXER (Formato + Similarità)")
    print("=" * 80)
    print()

    # Inizializza il calcolatore di similarità (da 'metrics.similarity')
    try:
        similarity_calculator = SimilarityCalculator()
        print("✅ SimilarityCalculator inizializzato.")
    except Exception as e:
        print(f"❌ Impossibile inizializzare SimilarityCalculator: {e}")
        return 1

    clusters_dir = utility_paths.CLUSTERS_DIR_FILEPATH

    if not clusters_dir.exists():
        print(f"❌ Directory clusters non trovata: {clusters_dir}")
        return 1

    print(f"Scansione clusters in: {clusters_dir}")
    print(f"Target language: {TARGET_LANGUAGE}")
    print()

    cluster_files = sorted(clusters_dir.glob("cluster_*.json"))

    if not cluster_files:
        print("❌ Nessun file cluster trovato.")
        return 1

    print(f"Trovati {len(cluster_files)} file cluster.")
    print()

    total_clusters_modified = 0
    total_entries_scanned = 0
    total_entries_updated = 0

    for cluster_file in cluster_files:
        cluster_name = cluster_file.stem.replace("cluster_", "")

        # Salta file non necessari
        if any(skip in cluster_file.name for skip in ["debug", "test", "bad_entries", "focused_", "with_metrics"]):
            continue

        modified, entries, updated = update_cluster_metadata(cluster_file, similarity_calculator)

        total_entries_scanned += entries
        total_entries_updated += updated

        if modified:
            total_clusters_modified += 1
            print(f"✅ Cluster aggiornato: {cluster_name} ({updated}/{entries} entries fixate)")
        else:
            # Stampa un messaggio solo se conteneva entry cpp
            if entries > 0:
                print(f"   {cluster_name}: Nessuna modifica necessaria ({entries} entries OK)")

    print()
    print("=" * 80)
    print("AGGIORNAMENTO COMPLETATO")
    print("=" * 80)
    print(f"Cluster scansionati (con entry 'cpp'): {total_clusters_modified}")
    print(f"Totale entry 'cpp' scansionate: {total_entries_scanned}")
    print(f"Totale entry 'cpp' aggiornate: {total_entries_updated}")
    print()

    return 0

if __name__ == "__main__":
    sys.exit(main())