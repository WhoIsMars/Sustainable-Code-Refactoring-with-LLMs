"""
Check Base Entries Status
Analyzes current state of base code entries with 100% pass rate (5/5 executions)
"""

import json
from pathlib import Path
from collections import defaultdict


def analyze_base_entries():
    """Analyze base entries with 100% pass rate."""

    execution_outputs_dir = Path('../execution_outputs/')

    # Target languages
    target_languages = ['c', 'python', 'javascript', 'java']

    # Load all base execution results
    base_files = []
    for file in execution_outputs_dir.glob("*_results_*.json"):
        # Skip LLM files
        if "_v1_" in file.name or "_v2_" in file.name or "_v3_" in file.name or "_v4_" in file.name:
            continue
        if "backup" in file.name or "selective" in file.name or "entry_execution" in file.name:
            continue
        base_files.append(file)

    print(f"\n{'='*80}")
    print("BASE CODE ENTRIES STATUS ANALYSIS")
    print(f"{'='*80}")
    print(f"Found {len(base_files)} base execution files")
    print()

    # Track entries by cluster and language
    cluster_executions = defaultdict(lambda: defaultdict(list))  # cluster -> language -> [execution_data]

    for file in base_files:
        try:
            with open(file, 'r') as f:
                data = json.load(f)

            # Extract cluster name
            filename = file.stem
            parts = filename.rsplit('_results_', 1)
            if len(parts) != 2:
                continue
            cluster_name = parts[0]

            # Store by language
            if 'results' in data:
                for language, entries in data['results'].items():
                    if language in target_languages:
                        cluster_executions[cluster_name][language].extend(entries)
        except Exception as e:
            print(f"Warning: Could not load {file}: {e}")
            continue

    print(f"Processed {len(cluster_executions)} unique clusters\n")

    # Statistics by language
    stats = defaultdict(lambda: {
        'total_entries': 0,
        'valid_entries_100': 0,  # 100% pass rate (5/5)
        'valid_entries_80': 0,   # >= 80% pass rate
        'valid_entries_60': 0,   # >= 60% pass rate
        'failed_entries': 0,     # < 60% pass rate
        'pass_rate_distribution': defaultdict(int)  # pass_rate -> count
    })

    # Analyze entries
    for cluster_name, languages_data in cluster_executions.items():
        for language, entries in languages_data.items():
            # Get unique entries
            unique_ids = set(e.get('id') for e in entries if e.get('id'))

            for entry_id in unique_ids:
                stats[language]['total_entries'] += 1

                # Check pass rate across all executions
                entry_executions = [e for e in entries if e.get('id') == entry_id]
                passed = sum(1 for e in entry_executions if e.get('regressionTestPassed', False))
                total = len(entry_executions)

                if total > 0:
                    pass_rate = (passed / total) * 100.0

                    # Track distribution
                    pass_rate_bucket = int(pass_rate // 10) * 10  # Round to nearest 10
                    stats[language]['pass_rate_distribution'][pass_rate_bucket] += 1

                    # Categorize
                    if pass_rate == 100.0:
                        stats[language]['valid_entries_100'] += 1
                    if pass_rate >= 80.0:
                        stats[language]['valid_entries_80'] += 1
                    if pass_rate >= 60.0:
                        stats[language]['valid_entries_60'] += 1
                    else:
                        stats[language]['failed_entries'] += 1

    # Print results
    print(f"{'='*80}")
    print("ENTRIES STATUS BY LANGUAGE")
    print(f"{'='*80}\n")

    for lang in target_languages:
        s = stats[lang]
        total = s['total_entries']

        if total == 0:
            continue

        print(f"\n{lang.upper()} - Total entries: {total}")
        print(f"  {'='*70}")
        print(f"  100% pass rate (5/5):  {s['valid_entries_100']:>3} ({s['valid_entries_100']/total*100:>5.1f}%)")
        print(f"  ≥80% pass rate (4-5/5): {s['valid_entries_80']:>3} ({s['valid_entries_80']/total*100:>5.1f}%)")
        print(f"  ≥60% pass rate (3-5/5): {s['valid_entries_60']:>3} ({s['valid_entries_60']/total*100:>5.1f}%)")
        print(f"  <60% pass rate:         {s['failed_entries']:>3} ({s['failed_entries']/total*100:>5.1f}%)")

        print(f"\n  Pass Rate Distribution:")
        for rate in sorted(s['pass_rate_distribution'].keys(), reverse=True):
            count = s['pass_rate_distribution'][rate]
            bar = '█' * int(count / total * 50)
            print(f"    {rate:>3}%: {count:>3} ({count/total*100:>5.1f}%) {bar}")

    # Summary comparison
    print(f"\n{'='*80}")
    print("SUMMARY - Entries with 100% pass rate (TARGET for LLM comparison)")
    print(f"{'='*80}")
    print(f"{'Language':<12} | {'Total':<8} | {'Valid (100%)':<14} | {'%':<8} | Status")
    print(f"{'-'*80}")

    targets = {
        'c': 150,
        'python': 150,
        'javascript': 150,
        'java': 150
    }

    for lang in target_languages:
        s = stats[lang]
        total = s['total_entries']
        valid = s['valid_entries_100']
        pct = (valid / total * 100) if total > 0 else 0
        target = targets[lang]

        if valid >= target:
            status = "✅ TARGET REACHED"
        elif valid >= target * 0.8:
            status = f"⚠️  Need ~{target - valid} more"
        else:
            status = f"❌ Need ~{target - valid} more"

        print(f"{lang.upper():<12} | {total:<8} | {valid:<14} | {pct:<7.1f}% | {status}")

    print(f"{'='*80}\n")

    # Save detailed report
    report_file = Path("reports/base_entries_status.json")
    report_file.parent.mkdir(parents=True, exist_ok=True)

    report_data = {
        'analysis_date': '2025-11-18',
        'total_base_files': len(base_files),
        'total_clusters': len(cluster_executions),
        'statistics_by_language': {
            lang: dict(stats[lang]) for lang in target_languages
        }
    }

    with open(report_file, 'w') as f:
        json.dump(report_data, f, indent=2)

    print(f"Detailed report saved to: {report_file}")


if __name__ == "__main__":
    analyze_base_entries()
