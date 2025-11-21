"""
Check completeness of LLM metadata in cluster JSON files.
Verifies that all LLM entries have required fields: type, path, word_quantity, char_quantity, filename
"""

import json
from pathlib import Path
from collections import defaultdict

def check_metadata_completeness(clusters_dir: Path, language: str = 'cpp'):
    """Check if all LLM metadata has required fields."""

    required_fields = ['type', 'path', 'word_quantity', 'char_quantity', 'filename']

    stats = {
        'total_entries': 0,
        'total_llm_codes': 0,
        'complete_llm_codes': 0,
        'incomplete_llm_codes': 0,
        'missing_fields': defaultdict(int),
        'incomplete_entries': [],
    }

    cluster_files = list(clusters_dir.glob("cluster_*.json"))

    for cluster_file in cluster_files:
        try:
            with open(cluster_file) as f:
                data = json.load(f)
        except:
            continue

        if language not in data:
            continue

        for entry in data[language]:
            entry_id = entry.get('id')
            stats['total_entries'] += 1

            llms = entry.get('LLMs', [])

            for llm in llms:
                stats['total_llm_codes'] += 1

                # Check all required fields
                missing = []
                for field in required_fields:
                    if field not in llm:
                        missing.append(field)
                        stats['missing_fields'][field] += 1

                if missing:
                    stats['incomplete_llm_codes'] += 1
                    stats['incomplete_entries'].append({
                        'cluster': cluster_file.stem,
                        'entry_id': entry_id,
                        'llm_file': llm.get('filename', 'unknown'),
                        'missing_fields': missing
                    })
                else:
                    stats['complete_llm_codes'] += 1

    # Print results
    print("=" * 80)
    print("LLM METADATA COMPLETENESS CHECK")
    print("=" * 80)
    print(f"Language: {language}")
    print(f"Total entries: {stats['total_entries']}")
    print(f"Total LLM codes: {stats['total_llm_codes']}")
    print()

    print(f"Complete LLM codes: {stats['complete_llm_codes']}/{stats['total_llm_codes']}")
    print(f"Incomplete LLM codes: {stats['incomplete_llm_codes']}/{stats['total_llm_codes']}")

    if stats['incomplete_llm_codes'] > 0:
        print(f"\n⚠️  WARNING: {stats['incomplete_llm_codes']} LLM codes have incomplete metadata!")
        print("\nMissing fields breakdown:")
        for field, count in sorted(stats['missing_fields'].items(), key=lambda x: x[1], reverse=True):
            print(f"  {field}: missing in {count} codes")

        print(f"\nFirst 10 incomplete entries:")
        for item in stats['incomplete_entries'][:10]:
            print(f"  {item['entry_id']} ({item['llm_file']})")
            print(f"    Missing: {', '.join(item['missing_fields'])}")

        return False
    else:
        print("\n✅ All LLM codes have complete metadata!")
        return True


if __name__ == "__main__":
    import sys
    sys.path.insert(0, str(Path(__file__).parent.parent))
    from utility_dir import utility_paths

    is_complete = check_metadata_completeness(utility_paths.CLUSTERS_DIR_FILEPATH, language='cpp')

    if is_complete:
        print("\n🎉 Ready to proceed with test execution!")
    else:
        print("\n❌ Need to run adjust_LLMs_metadata.py to fix incomplete metadata")

    sys.exit(0 if is_complete else 1)
