#!/usr/bin/env python3
"""
Emergency Data Restoration Script

This script restores data that was deleted from execution_outputs files
in the 'updates' commit (735c8e59f) on Nov 16, 2025.

The commit deleted multiple languages from base code result files, leaving
only one language (typically cpp) in each file. This script:
1. Identifies all affected files
2. Compares before/after versions
3. Restores deleted languages from previous commit
4. Preserves existing valid data
"""

import json
import subprocess
import sys
from pathlib import Path
from typing import Dict, List, Set
from collections import defaultdict

# Add parent directory to path for imports
sys.path.insert(0, str(Path(__file__).parent.parent))
from utility_dir import utility_paths


def get_file_from_commit(commit: str, file_path: str) -> dict:
    """Get JSON content of a file from a specific commit."""
    try:
        result = subprocess.run(
            ['git', 'show', f'{commit}:{file_path}'],
            capture_output=True,
            text=True,
            check=True
        )
        return json.loads(result.stdout)
    except (subprocess.CalledProcessError, json.JSONDecodeError) as e:
        return None


def compare_languages(before: dict, after: dict) -> tuple[Set[str], Set[str], Set[str]]:
    """
    Compare languages in before/after versions.

    Returns:
        (deleted_languages, added_languages, kept_languages)
    """
    before_langs = set()
    after_langs = set()

    if 'results' in before:
        before_langs = set(before['results'].keys())
    else:
        before_langs = {k for k in before.keys()
                       if k not in ['execution_date', 'execution_metadata']}

    if 'results' in after:
        after_langs = set(after['results'].keys())
    else:
        after_langs = {k for k in after.keys()
                      if k not in ['execution_date', 'execution_metadata']}

    deleted = before_langs - after_langs
    added = after_langs - before_langs
    kept = before_langs & after_langs

    return deleted, added, kept


def restore_file(file_path: str, bad_commit: str = '735c8e59f') -> dict:
    """
    Restore deleted languages from a file.

    Args:
        file_path: Path relative to repo root (e.g., 'src/execution_outputs/bob_results_1.json')
        bad_commit: Commit that deleted the data

    Returns:
        Dictionary with restoration info
    """
    result = {
        'file': file_path,
        'status': 'unknown',
        'deleted_languages': [],
        'restored_languages': [],
        'error': None
    }

    try:
        # Get current version
        full_path = Path(file_path)
        if not full_path.exists():
            result['status'] = 'file_not_found'
            result['error'] = 'File does not exist'
            return result

        with open(full_path) as f:
            current = json.load(f)

        # Get version before bad commit
        before = get_file_from_commit(f'{bad_commit}^', file_path)
        if not before:
            result['status'] = 'no_previous_version'
            result['error'] = 'Could not retrieve previous version from git'
            return result

        # Get version after bad commit (what was committed)
        after = get_file_from_commit(bad_commit, file_path)
        if not after:
            result['status'] = 'no_commit_version'
            result['error'] = 'Could not retrieve commit version from git'
            return result

        # Compare to find deletions
        deleted, added, kept = compare_languages(before, after)
        result['deleted_languages'] = list(deleted)

        if not deleted:
            result['status'] = 'no_deletions'
            return result

        # Check if current version has the deleted languages
        # (they might have been restored already)
        if 'results' in current:
            current_langs = set(current['results'].keys())
        else:
            current_langs = {k for k in current.keys()
                           if k not in ['execution_date', 'execution_metadata']}

        # Only restore languages that are still missing
        to_restore = deleted - current_langs

        if not to_restore:
            result['status'] = 'already_restored'
            return result

        # Restore deleted languages from before version
        restored = []
        if 'results' in before:
            # New format (with "results" key)
            if 'results' not in current:
                current['results'] = {}

            for lang in to_restore:
                if lang in before['results']:
                    current['results'][lang] = before['results'][lang]
                    restored.append(lang)
        else:
            # Old format (languages at root level)
            for lang in to_restore:
                if lang in before:
                    current[lang] = before[lang]
                    restored.append(lang)

        if restored:
            # Save restored version
            with open(full_path, 'w') as f:
                json.dump(current, f, indent=2, ensure_ascii=False)

            result['status'] = 'restored'
            result['restored_languages'] = restored
        else:
            result['status'] = 'nothing_to_restore'

    except Exception as e:
        result['status'] = 'error'
        result['error'] = str(e)

    return result


def main():
    print("=" * 80)
    print("EMERGENCY DATA RESTORATION")
    print("=" * 80)
    print()
    print("This script will restore data deleted by the 'updates' commit (735c8e59f)")
    print("on November 16, 2025.")
    print()

    # Get list of files modified in the bad commit
    result = subprocess.run(
        ['git', 'diff', '--name-only', '735c8e59f^', '735c8e59f', '--',
         'src/execution_outputs/'],
        capture_output=True,
        text=True,
        check=True
    )

    all_files = [f.strip() for f in result.stdout.strip().split('\n') if f.strip()]

    # Include both base code and LLM files
    # Base files: name_results_N.json where N is 1-5
    # LLM files: name_results_vN_M.json where N is 1-4, M is 1-5
    modified_files = []
    for f in all_files:
        # Skip backup files
        if 'backup' in f or 'selective' in f:
            continue

        # Check if it's a base file
        if (f.endswith('_results_1.json') or f.endswith('_results_2.json') or
            f.endswith('_results_3.json') or f.endswith('_results_4.json') or
            f.endswith('_results_5.json')):
            # Make sure it's not an LLM file (no _v in the name)
            if '_results_v' not in f:
                modified_files.append(f)
            continue

        # Check if it's an LLM file
        if '_results_v' in f:
            if (f.endswith('_1.json') or f.endswith('_2.json') or
                f.endswith('_3.json') or f.endswith('_4.json') or
                f.endswith('_5.json')):
                modified_files.append(f)

    base_files = [f for f in modified_files if '_results_v' not in f]
    llm_files = [f for f in modified_files if '_results_v' in f]

    print(f"Found {len(modified_files)} result files modified in commit:")
    print(f"  Base code files: {len(base_files)}")
    print(f"  LLM code files:  {len(llm_files)}")
    print()

    # Analyze a sample to show the problem
    print("Analyzing sample file: bob_results_1.json")
    bob_path = 'src/execution_outputs/bob_results_1.json'
    before = get_file_from_commit('735c8e59f^', bob_path)
    after = get_file_from_commit('735c8e59f', bob_path)

    if before and after:
        deleted, added, kept = compare_languages(before, after)
        print(f"  Before commit: {sorted(before.get('results', before).keys() if 'results' in before else [k for k in before.keys() if k not in ['execution_date', 'execution_metadata']])}")
        print(f"  After commit:  {sorted(after.get('results', after).keys() if 'results' in after else [k for k in after.keys() if k not in ['execution_date', 'execution_metadata']])}")
        print(f"  DELETED: {sorted(deleted)}")
        print()

    # Ask for confirmation
    response = input(f"Proceed with restoration of {len(modified_files)} files? (yes/no): ")
    if response.lower() not in ['yes', 'y']:
        print("Restoration cancelled.")
        return 1

    print()
    print("=" * 80)
    print("RESTORING FILES...")
    print("=" * 80)
    print()

    # Restore all files
    stats = defaultdict(int)
    files_restored = []
    files_with_errors = []

    for i, file_path in enumerate(modified_files, 1):
        print(f"\r[{i}/{len(modified_files)}] Processing: {Path(file_path).name}...",
              end='', flush=True)

        result = restore_file(file_path)
        stats[result['status']] += 1

        if result['status'] == 'restored':
            files_restored.append({
                'file': file_path,
                'languages': result['restored_languages']
            })
        elif result['status'] == 'error':
            files_with_errors.append({
                'file': file_path,
                'error': result['error']
            })

    print()  # New line after progress
    print()
    print("=" * 80)
    print("RESTORATION COMPLETE")
    print("=" * 80)
    print()

    # Print statistics
    print("Statistics:")
    for status, count in sorted(stats.items()):
        print(f"  {status}: {count}")
    print()

    # Show successfully restored files
    if files_restored:
        print(f"Successfully restored {len(files_restored)} files:")
        for item in files_restored[:20]:
            langs = ', '.join(item['languages'])
            print(f"  {Path(item['file']).name}: {langs}")
        if len(files_restored) > 20:
            print(f"  ... and {len(files_restored) - 20} more files")
        print()

    # Show errors
    if files_with_errors:
        print(f"Errors in {len(files_with_errors)} files:")
        for item in files_with_errors[:10]:
            print(f"  {Path(item['file']).name}: {item['error']}")
        if len(files_with_errors) > 10:
            print(f"  ... and {len(files_with_errors) - 10} more errors")
        print()

    print("=" * 80)
    print()

    if stats['restored'] > 0:
        print("Next steps:")
        print("1. Verify restored data integrity")
        print("2. Run: cd src/metrics && python3 pass_rate_analyzer.py")
        print("3. Resume JavaScript base execution if needed")
        print()

    return 0 if not files_with_errors else 1


if __name__ == '__main__':
    sys.exit(main())
