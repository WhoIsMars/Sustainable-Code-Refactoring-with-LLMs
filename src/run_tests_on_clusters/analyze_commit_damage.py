#!/usr/bin/env python3
"""
Analyze Data Loss from 'updates' Commit

This script analyzes all files modified in the 'updates' commit (735c8e59f)
to identify which ones lost language data.
"""

import json
import subprocess
from pathlib import Path
from collections import defaultdict


def get_languages_from_json(data: dict) -> set:
    """Extract language keys from JSON data."""
    if 'results' in data:
        return set(data['results'].keys())
    else:
        # Old format - languages at root level
        return {k for k in data.keys()
               if k not in ['execution_date', 'execution_metadata']}


def check_file_for_deletions(file_path: str, commit: str = '735c8e59f') -> dict:
    """
    Check if a file lost language data in the commit.

    Returns dict with:
        - has_deletions: bool
        - deleted_languages: list
        - before_langs: list
        - after_langs: list
    """
    result = {
        'has_deletions': False,
        'deleted_languages': [],
        'before_langs': [],
        'after_langs': [],
        'error': None
    }

    try:
        # Get before version
        before_result = subprocess.run(
            ['git', 'show', f'{commit}^:{file_path}'],
            capture_output=True, text=True, check=False
        )

        if before_result.returncode != 0:
            result['error'] = 'no_previous_version'
            return result

        before = json.loads(before_result.stdout)

        # Get after version
        after_result = subprocess.run(
            ['git', 'show', f'{commit}:{file_path}'],
            capture_output=True, text=True, check=False
        )

        if after_result.returncode != 0:
            result['error'] = 'no_commit_version'
            return result

        after = json.loads(after_result.stdout)

        # Compare languages
        before_langs = get_languages_from_json(before)
        after_langs = get_languages_from_json(after)

        result['before_langs'] = sorted(before_langs)
        result['after_langs'] = sorted(after_langs)

        deleted = before_langs - after_langs
        if deleted:
            result['has_deletions'] = True
            result['deleted_languages'] = sorted(deleted)

    except json.JSONDecodeError as e:
        result['error'] = f'json_error: {e}'
    except Exception as e:
        result['error'] = f'error: {e}'

    return result


def main():
    print("=" * 80)
    print("ANALYZING COMMIT DAMAGE: 735c8e59f")
    print("=" * 80)
    print()

    # Get all files modified in the commit
    result = subprocess.run(
        ['git', 'diff', '--name-only', '735c8e59f^', '735c8e59f', '--',
         'src/execution_outputs/'],
        capture_output=True,
        text=True,
        check=True
    )

    all_files = [f.strip() for f in result.stdout.split('\n') if f.strip()]

    # Categorize files
    base_files = [f for f in all_files if f.endswith('_results_1.json') or
                  f.endswith('_results_2.json') or f.endswith('_results_3.json') or
                  f.endswith('_results_4.json') or f.endswith('_results_5.json')]

    llm_files = [f for f in all_files if '_results_v' in f and
                 (f.endswith('_1.json') or f.endswith('_2.json') or
                  f.endswith('_3.json') or f.endswith('_4.json') or
                  f.endswith('_5.json'))]

    backup_files = [f for f in all_files if 'backup' in f]
    other_files = [f for f in all_files if f not in base_files and
                   f not in llm_files and f not in backup_files]

    print(f"Total files modified: {len(all_files)}")
    print(f"  Base code files:    {len(base_files)}")
    print(f"  LLM code files:     {len(llm_files)}")
    print(f"  Backup files:       {len(backup_files)}")
    print(f"  Other files:        {len(other_files)}")
    print()

    # Analyze base code files
    print("Analyzing BASE CODE files for language deletions...")
    base_damaged = []
    base_stats = defaultdict(int)

    for i, file_path in enumerate(base_files):
        if i % 50 == 0:
            print(f"  Progress: {i}/{len(base_files)}", end='\r')

        check = check_file_for_deletions(file_path)

        if check['error']:
            base_stats['error'] += 1
        elif check['has_deletions']:
            base_stats['damaged'] += 1
            base_damaged.append({
                'file': file_path,
                'deleted': check['deleted_languages'],
                'before': check['before_langs'],
                'after': check['after_langs']
            })
        else:
            base_stats['intact'] += 1

    print(f"  Progress: {len(base_files)}/{len(base_files)}")
    print()

    # Analyze LLM code files (sample)
    print("Analyzing LLM CODE files (sampling)...")
    llm_sample_size = min(100, len(llm_files))
    llm_damaged = []
    llm_stats = defaultdict(int)

    import random
    llm_sample = random.sample(llm_files, llm_sample_size) if llm_files else []

    for i, file_path in enumerate(llm_sample):
        if i % 10 == 0:
            print(f"  Progress: {i}/{llm_sample_size}", end='\r')

        check = check_file_for_deletions(file_path)

        if check['error']:
            llm_stats['error'] += 1
        elif check['has_deletions']:
            llm_stats['damaged'] += 1
            llm_damaged.append({
                'file': file_path,
                'deleted': check['deleted_languages']
            })
        else:
            llm_stats['intact'] += 1

    print(f"  Progress: {llm_sample_size}/{llm_sample_size}")
    print()

    # Print results
    print("=" * 80)
    print("ANALYSIS RESULTS")
    print("=" * 80)
    print()

    print("BASE CODE FILES:")
    print(f"  Total analyzed:     {len(base_files)}")
    print(f"  Files with damage:  {base_stats['damaged']}")
    print(f"  Files intact:       {base_stats['intact']}")
    print(f"  Files with errors:  {base_stats['error']}")
    print()

    if base_damaged:
        print(f"Sample of damaged base code files (showing first 10):")
        for item in base_damaged[:10]:
            filename = Path(item['file']).name
            deleted = ', '.join(item['deleted'])
            print(f"  {filename}")
            print(f"    Before: {', '.join(item['before'])}")
            print(f"    After:  {', '.join(item['after'])}")
            print(f"    LOST:   {deleted}")
        if len(base_damaged) > 10:
            print(f"  ... and {len(base_damaged) - 10} more damaged files")
        print()

    print("LLM CODE FILES (sample):")
    print(f"  Sample size:        {llm_sample_size}")
    print(f"  Files with damage:  {llm_stats['damaged']}")
    print(f"  Files intact:       {llm_stats['intact']}")
    print(f"  Files with errors:  {llm_stats['error']}")
    print()

    if llm_damaged:
        print(f"Damaged LLM files found:")
        for item in llm_damaged:
            filename = Path(item['file']).name
            deleted = ', '.join(item['deleted'])
            print(f"  {filename}: lost {deleted}")
        print()
    else:
        print("  No damage found in LLM files sample!")
        print()

    # Summary
    print("=" * 80)
    print("SUMMARY")
    print("=" * 80)
    print()

    if base_stats['damaged'] > 0:
        percentage = (base_stats['damaged'] / len(base_files)) * 100
        print(f"CRITICAL: {base_stats['damaged']} base code files damaged ({percentage:.1f}%)")
        print()
        print("Languages most commonly deleted:")
        lang_count = defaultdict(int)
        for item in base_damaged:
            for lang in item['deleted']:
                lang_count[lang] += 1

        for lang, count in sorted(lang_count.items(), key=lambda x: x[1], reverse=True):
            print(f"  {lang}: deleted from {count} files")
        print()

    if llm_stats['damaged'] > 0:
        print(f"WARNING: {llm_stats['damaged']} LLM files damaged in sample")
        print("  Full analysis of LLM files recommended")
        print()
    else:
        print("GOOD: No damage found in LLM files sample")
        print()

    print("Recommendation:")
    if base_stats['damaged'] > 0:
        print("  1. Run restoration script IMMEDIATELY on base code files")
        print("  2. Verify integrity of restored data")
        if llm_stats['damaged'] > 0:
            print("  3. Analyze ALL LLM files for damage")
            print("  4. Restore LLM files if needed")
    else:
        print("  No restoration needed - all files intact")

    print()
    print("=" * 80)


if __name__ == '__main__':
    main()
