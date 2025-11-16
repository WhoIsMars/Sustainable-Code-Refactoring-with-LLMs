#!/usr/bin/env python3
"""
Script to manually generate missing Gemini LLM files for specific C++ entries.
Directly calls the Gemini API gestor to complete missing variants.
"""

import sys
from pathlib import Path

# Add parent directory to path for imports
sys.path.insert(0, str(Path(__file__).parent.parent))

from utility_dir.utility_paths import PROMPTS_DIR_FILEPATH, DATASET_DIR
from LLMs_generator_engine.api import gemini_api_gestor

# Mapping of entries and their missing Gemini versions
# codeSnippetFilePath points to src/ directory for C/C++ entries
MISSING_FILES = {
    'cpp/two-fer_exercism-stungeye': {
        'code_path': 'cpp/two-fer_exercism-stungeye/src/two_fer.cpp',
        'exercise_dir': 'cpp/two-fer_exercism-stungeye',
        'filename': 'two_fer.cpp',
        'missing_versions': ['v3', 'v4']
    },
    'cpp/vehicle-purchase_exercism-nenjotsu': {
        'code_path': 'cpp/vehicle-purchase_exercism-nenjotsu/src/vehicle_purchase.cpp',
        'exercise_dir': 'cpp/vehicle-purchase_exercism-nenjotsu',
        'filename': 'vehicle_purchase.cpp',
        'missing_versions': ['v1', 'v2', 'v3', 'v4']
    },
    'cpp/word-count_exercism-toemm': {
        'code_path': 'cpp/word-count_exercism-toemm/src/word_count.cpp',
        'exercise_dir': 'cpp/word-count_exercism-toemm',
        'filename': 'word_count.cpp',
        'missing_versions': ['v1']
    },
    'cpp/yacht_exercism-toemm': {
        'code_path': 'cpp/yacht_exercism-toemm/src/yacht.cpp',
        'exercise_dir': 'cpp/yacht_exercism-toemm',
        'filename': 'yacht.cpp',
        'missing_versions': ['v1', 'v2', 'v3']
    }
}

def main():
    print("="*80)
    print("GEMINI FILE GENERATION - TARGETED FIX")
    print("="*80)
    print(f"Total entries to fix: {len(MISSING_FILES)}")
    print(f"Total files to generate: {sum(len(v['missing_versions']) for v in MISSING_FILES.values())}")
    print()

    # Initialize Gemini API gestor
    gemini_api = gemini_api_gestor.GeminiAIApiGestor()

    # Map prompt versions to file paths
    prompt_map = {
        'v1': (PROMPTS_DIR_FILEPATH / "promptV1.txt", 1),
        'v2': (PROMPTS_DIR_FILEPATH / "promptV2.txt", 2),
        'v3': (PROMPTS_DIR_FILEPATH / "promptV3.txt", 3),
        'v4': (PROMPTS_DIR_FILEPATH / "promptV4.txt", 4),
    }

    stats = {'total': 0, 'success': 0, 'failed': 0, 'skipped': 0}

    for entry_key, config in MISSING_FILES.items():
        code_path = config['code_path']
        exercise_dir_rel = config['exercise_dir']
        filename = config['filename']
        missing_versions = config['missing_versions']

        print(f"\n📁 Processing: {entry_key}")
        print(f"   Code path: {code_path}")
        print(f"   Filename: {filename}")
        print(f"   Missing versions: {missing_versions}")

        # Construct absolute paths
        exercise_dir = DATASET_DIR / exercise_dir_rel
        code_file_path = DATASET_DIR / code_path

        if not code_file_path.exists():
            print(f"   ❌ ERROR: Code file not found: {code_file_path}")
            stats['failed'] += len(missing_versions)
            stats['total'] += len(missing_versions)
            continue

        print(f"   ✓ Code file found: {code_file_path}")

        # Generate each missing version
        for version in missing_versions:
            stats['total'] += 1
            prompt_path, prompt_num = prompt_map[version]

            print(f"   🔄 Generating {version}...", end=' ', flush=True)

            try:
                success = gemini_api.generate_and_save_LLM_code_by_files(
                    prompt_path,
                    code_file_path,
                    exercise_dir,
                    prompt_num,
                    filename
                )

                if success:
                    stats['success'] += 1
                    print("✅ SUCCESS")
                else:
                    stats['failed'] += 1
                    print("❌ FAILED")

            except Exception as e:
                stats['failed'] += 1
                print(f"❌ ERROR: {e}")

    # Summary
    print("\n" + "="*80)
    print("SUMMARY")
    print("="*80)
    print(f"Total files attempted: {stats['total']}")
    print(f"✅ Successfully generated: {stats['success']}")
    print(f"❌ Failed: {stats['failed']}")
    print(f"⏭️  Skipped (already exist): {stats['skipped']}")
    print(f"\nSuccess rate: {stats['success']/stats['total']*100:.1f}%")

if __name__ == "__main__":
    main()
