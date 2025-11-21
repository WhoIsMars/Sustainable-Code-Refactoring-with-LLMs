"""
Check which CPP entries have LLM codes available in cluster files.
"""

import json
from pathlib import Path
from collections import defaultdict

def check_llm_codes(clusters_dir: Path):
    """Check which CPP entries have LLM codes in cluster files."""

    stats = {
        'total_cpp_entries': 0,
        'entries_with_llm_codes': 0,
        'llm_codes_by_version': defaultdict(int),
        'llm_codes_by_model': defaultdict(int),
        'entries_without_codes': [],
        'entries_with_codes': [],
        'entry_coverage': {},  # (cluster, entry_id) -> {model: [versions]}
    }

    cluster_files = list(clusters_dir.glob("cluster_*.json"))

    print(f"Checking {len(cluster_files)} cluster files...\n")

    for cluster_file in cluster_files:
        cluster_name = cluster_file.stem.replace("cluster_", "")

        try:
            with open(cluster_file) as f:
                cluster_data = json.load(f)
        except:
            continue

        if 'cpp' not in cluster_data:
            continue

        for entry in cluster_data['cpp']:
            entry_id = entry.get('id')
            if not entry_id:
                continue

            stats['total_cpp_entries'] += 1

            if 'LLMs' in entry and entry['LLMs']:
                stats['entries_with_llm_codes'] += 1
                stats['entries_with_codes'].append((cluster_name, entry_id))

                # Track coverage for this entry
                entry_key = (cluster_name, entry_id)
                if entry_key not in stats['entry_coverage']:
                    stats['entry_coverage'][entry_key] = defaultdict(set)

                # Count by version and model
                # Extract version from filename (e.g., "ChatGPT4_pacman_rules_v1.cpp" -> v1)
                for llm_code in entry['LLMs']:
                    filename = llm_code.get('filename', '')
                    model = llm_code.get('type', 'unknown')

                    # Extract version from filename
                    version = 'unknown'
                    if '_v1.' in filename:
                        version = 'v1'
                    elif '_v2.' in filename:
                        version = 'v2'
                    elif '_v3.' in filename:
                        version = 'v3'
                    elif '_v4.' in filename:
                        version = 'v4'

                    stats['llm_codes_by_version'][version] += 1
                    stats['llm_codes_by_model'][model] += 1
                    stats['entry_coverage'][entry_key][model].add(version)
            else:
                stats['entries_without_codes'].append((cluster_name, entry_id))

    # Print results
    print("=" * 80)
    print("LLM CODES AVAILABILITY CHECK")
    print("=" * 80)
    print(f"Total CPP entries in clusters: {stats['total_cpp_entries']}")
    print(f"Entries with LLM codes: {stats['entries_with_llm_codes']}")
    print(f"Entries WITHOUT LLM codes: {len(stats['entries_without_codes'])}")
    print(f"Coverage: {stats['entries_with_llm_codes'] / stats['total_cpp_entries'] * 100:.1f}%")
    print()

    print("LLM codes by prompt version:")
    for version in sorted(stats['llm_codes_by_version'].keys()):
        count = stats['llm_codes_by_version'][version]
        print(f"  {version}: {count}")
    print()

    print("LLM codes by model:")
    for model in sorted(stats['llm_codes_by_model'].keys()):
        count = stats['llm_codes_by_model'][model]
        print(f"  {model}: {count}")
    print()

    if stats['entries_without_codes']:
        print(f"\nFirst 20 entries WITHOUT LLM codes:")
        for cluster, entry_id in stats['entries_without_codes'][:20]:
            print(f"  {cluster}/{entry_id}")
        if len(stats['entries_without_codes']) > 20:
            print(f"  ... and {len(stats['entries_without_codes']) - 20} more")

    # Analyze coverage completeness
    print(f"\n{'='*80}")
    print("COVERAGE ANALYSIS BY MODEL AND VERSION")
    print(f"{'='*80}")

    complete_entries = []  # All 3 models, all 4 versions
    incomplete_entries = []  # Missing some models or versions

    for entry_key, coverage in stats['entry_coverage'].items():
        # Check if entry has all 3 models with all 4 versions
        has_openai_complete = 'openAI' in coverage and len(coverage['openAI']) == 4
        has_claude_complete = 'claude' in coverage and len(coverage['claude']) == 4
        has_gemini_complete = 'gemini' in coverage and len(coverage['gemini']) == 4

        if has_openai_complete and has_claude_complete and has_gemini_complete:
            complete_entries.append(entry_key)
        else:
            incomplete_entries.append((entry_key, coverage))

    print(f"Entries with COMPLETE coverage (3 models × 4 versions = 12 codes): {len(complete_entries)}")
    print(f"Entries with INCOMPLETE coverage: {len(incomplete_entries)}")
    print()

    if incomplete_entries:
        print(f"Coverage breakdown for incomplete entries:")
        # Group by missing pattern
        missing_patterns = defaultdict(list)
        for entry_key, coverage in incomplete_entries:
            openai_count = len(coverage.get('openAI', set()))
            claude_count = len(coverage.get('claude', set()))
            gemini_count = len(coverage.get('gemini', set()))
            pattern = f"openAI:{openai_count}/4, claude:{claude_count}/4, gemini:{gemini_count}/4"
            missing_patterns[pattern].append(entry_key)

        for pattern, entries in sorted(missing_patterns.items(), key=lambda x: len(x[1]), reverse=True):
            print(f"\n  {pattern}: {len(entries)} entries")
            for cluster, entry_id in entries[:5]:
                print(f"    - {cluster}/{entry_id}")
            if len(entries) > 5:
                print(f"    ... and {len(entries) - 5} more")

    return stats


if __name__ == "__main__":
    clusters_dir = Path("../clusters")
    check_llm_codes(clusters_dir)
