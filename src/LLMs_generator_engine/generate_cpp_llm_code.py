#!/usr/bin/env python3
"""
Generate LLM code for stable CPP entries that don't have full LLM coverage.
This script processes entries individually rather than by cluster.
"""

import os
import json
import time
import sys
from pathlib import Path

# Add parent dir to path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))

from utility_dir import utility_paths
from api import gemini_api_gestor, claude_api_gestor, openai_api_gestor
from dotenv import load_dotenv

load_dotenv()

# Read list of stable CPP entries
STABLE_ENTRIES_FILE = "/tmp/all_stable_cpp_entries.txt"

def get_stable_entries():
    """Read stable CPP entry IDs from file"""
    with open(STABLE_ENTRIES_FILE, 'r') as f:
        return [line.strip() for line in f if line.strip()]

def find_entry_in_clusters(entry_id):
    """Find the cluster and entry data for a given entry ID"""
    # Entry ID format: cpp_<exercise_name>_<source>
    # Exercise name can have underscores or hyphens
    # Source can be simple (ARPIT73881) or complex (Exercism (username))

    # Remove 'cpp_' prefix
    without_prefix = entry_id[4:]  # Remove 'cpp_'

    # Find the last '_' before the source part
    if '(' in without_prefix:
        # Source has parentheses like "Exercism (username)"
        source_start = without_prefix.rfind('_', 0, without_prefix.index('('))
    else:
        # Simple source like "ARPIT73881"
        source_start = without_prefix.rfind('_')

    if source_start == -1:
        return None, None

    exercise_name = without_prefix[:source_start]

    # Replace hyphens with underscores for cluster filename
    cluster_name = exercise_name.replace('-', '_')

    cluster_file = utility_paths.CLUSTERS_DIR_FILEPATH / f"cluster_{cluster_name}.json"

    if not cluster_file.exists():
        print(f"  ⚠️  Cluster file not found: {cluster_file}")
        return None, None

    with open(cluster_file, 'r', encoding='utf-8') as f:
        cluster_data = json.load(f)

    # Find the entry in the cluster
    if 'cpp' in cluster_data:
        for entry in cluster_data['cpp']:
            if entry['id'] == entry_id:
                return cluster_name, entry

    return None, None

def check_llm_coverage(entry):
    """Check how many LLM versions exist for an entry"""
    return len(entry.get('LLMs', []))

def generate_llm_for_entry(entry, cluster_name, gemini_api_g, claude_api_g, openai_api_g):
    """Generate LLM code for a single entry using all models and prompt versions"""

    prompt_file_paths = [
        utility_paths.PROMPTS_DIR_FILEPATH / "promptV1.txt",
        utility_paths.PROMPTS_DIR_FILEPATH / "promptV2.txt",
        utility_paths.PROMPTS_DIR_FILEPATH / "promptV3.txt",
        utility_paths.PROMPTS_DIR_FILEPATH / "promptV4.txt",
    ]

    entry_id = entry['id']
    filename = entry['filename']
    language = entry['language']

    # Build paths
    code_snippet_path = entry["codeSnippetFilePath"]
    parts = str(code_snippet_path).split("/")
    dir_name = str(parts[0]) + "/" + str(parts[1])
    exercise_dir_filepath = utility_paths.DATASET_DIR / dir_name
    code_file_path = utility_paths.DATASET_DIR / code_snippet_path

    if language == "cpp":
        code_file_path = code_file_path / filename

    total_expected = 12  # 3 models × 4 prompt versions
    total_generated = 0

    print(f"\n  Generating LLM code for: {entry_id}")
    print(f"    Cluster: {cluster_name}")
    print(f"    File: {filename}")
    print(f"    Current coverage: {check_llm_coverage(entry)}/12")

    for prompt_v, prompt_path in enumerate(prompt_file_paths, start=1):
        print(f"\n    📝 Prompt v{prompt_v}:")

        for model_name, generator in {
            "OpenAI": openai_api_g,
            "Claude": claude_api_g,
            "Gemini": gemini_api_g,
        }.items():
            try:
                success = generator.generate_and_save_LLM_code_by_files(
                    prompt_path,
                    code_file_path,
                    exercise_dir_filepath,
                    prompt_v,
                    filename,
                )

                if success:
                    total_generated += 1
                    print(f"       ✅ {model_name}")
                else:
                    print(f"       ❌ {model_name} (failed)")
            except Exception as e:
                print(f"       ❌ {model_name} (error: {e})")

            time.sleep(0.3)  # Small delay between API calls

    percent = (total_generated / total_expected * 100) if total_expected else 0
    print(f"\n    📊 Generated {total_generated}/{total_expected} files ({percent:.1f}%)")

    return total_generated, total_expected

def main():
    print("=" * 80)
    print("CPP LLM CODE GENERATOR")
    print("=" * 80)
    print()

    # Initialize API gestors
    print("Initializing API gestors...")
    gemini_api_g = gemini_api_gestor.GeminiAIApiGestor()
    claude_api_g = claude_api_gestor.ClaudeApiGestor()
    openai_api_g = openai_api_gestor.OpenAIApiGestor()
    print("✅ API gestors initialized")
    print()

    # Get stable entries
    stable_entries = get_stable_entries()
    print(f"📋 Loaded {len(stable_entries)} stable CPP entries")
    print()

    # Identify entries needing LLM code
    entries_needing_llm = []

    print("Analyzing entries...")
    for entry_id in stable_entries:
        cluster_name, entry = find_entry_in_clusters(entry_id)
        if entry:
            llm_count = check_llm_coverage(entry)
            if llm_count < 12:
                entries_needing_llm.append((entry_id, cluster_name, entry, llm_count))

    print(f"✅ Found {len(entries_needing_llm)} entries needing LLM generation")
    print()

    if not entries_needing_llm:
        print("🎉 All stable CPP entries already have full LLM coverage!")
        return

    # Summary
    print("Summary:")
    print(f"  Entries to process: {len(entries_needing_llm)}")
    print(f"  LLM files to generate: {len(entries_needing_llm) * 12}")
    print(f"  Estimated time: ~{len(entries_needing_llm) * 2} minutes")
    print()

    # Skip prompt if running non-interactively
    import sys
    if sys.stdin.isatty():
        input("Press ENTER to start generation (or Ctrl+C to cancel)...")
    else:
        print("Running non-interactively, proceeding automatically...")
    print()

    # Process entries
    start_time = time.time()
    total_entries_processed = 0
    total_files_generated = 0
    total_files_expected = 0

    for i, (entry_id, cluster_name, entry, current_llm_count) in enumerate(entries_needing_llm, 1):
        print(f"\n[{i}/{len(entries_needing_llm)}] Processing: {entry_id}")

        generated, expected = generate_llm_for_entry(
            entry, cluster_name,
            gemini_api_g, claude_api_g, openai_api_g
        )

        total_entries_processed += 1
        total_files_generated += generated
        total_files_expected += expected

        # Progress update every 10 entries
        if i % 10 == 0:
            elapsed = time.time() - start_time
            avg_time_per_entry = elapsed / i
            remaining = len(entries_needing_llm) - i
            eta_seconds = remaining * avg_time_per_entry
            eta_minutes = eta_seconds / 60

            print(f"\n  📊 Progress: {i}/{len(entries_needing_llm)} entries")
            print(f"     Files generated: {total_files_generated}/{total_files_expected}")
            print(f"     Time elapsed: {elapsed/60:.1f} min")
            print(f"     ETA: {eta_minutes:.1f} min")

        time.sleep(1)  # Delay between entries

    # Final summary
    duration = time.time() - start_time
    success_rate = (total_files_generated / total_files_expected * 100) if total_files_expected else 0

    print("\n" + "=" * 80)
    print("GENERATION COMPLETE")
    print("=" * 80)
    print(f"  Entries processed: {total_entries_processed}/{len(entries_needing_llm)}")
    print(f"  Files generated: {total_files_generated}/{total_files_expected} ({success_rate:.1f}%)")
    print(f"  Duration: {duration/60:.1f} minutes")
    print()

    # Verify final coverage
    print("Verifying final LLM coverage...")
    still_incomplete = []

    for entry_id in stable_entries:
        cluster_name, entry = find_entry_in_clusters(entry_id)
        if entry:
            llm_count = check_llm_coverage(entry)
            if llm_count < 12:
                still_incomplete.append((entry_id, llm_count))

    if still_incomplete:
        print(f"\n⚠️  {len(still_incomplete)} entries still incomplete:")
        for entry_id, count in still_incomplete[:10]:
            print(f"    {entry_id}: {count}/12")
        if len(still_incomplete) > 10:
            print(f"    ... and {len(still_incomplete) - 10} more")
    else:
        print("\n✅ ALL stable CPP entries now have full LLM coverage (12 versions each)!")

    print()

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\n\n❌ Generation cancelled by user")
        sys.exit(1)
    except Exception as e:
        print(f"\n\n❌ Error: {e}")
        import traceback
        traceback.print_exc()
        sys.exit(1)
