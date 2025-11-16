#!/usr/bin/env python3
"""Verify JavaScript LLM execution completion"""

import json
from pathlib import Path

def main():
    clusters_dir = Path('../clusters')
    results_dir = Path('../execution_outputs')

    skip_patterns = ['debug', 'test', 'bad_entries', 'focused_', 'with_metrics']

    # Get all JS clusters
    js_clusters = []
    for f in sorted(clusters_dir.glob('cluster_*.json')):
        if any(skip in f.name for skip in skip_patterns):
            continue
        try:
            with open(f) as fp:
                data = json.load(fp)
                if 'javascript' in data and len(data['javascript']) > 0:
                    cluster_name = f.stem.replace('cluster_', '')
                    if not any(skip in cluster_name for skip in skip_patterns):
                        js_clusters.append(cluster_name)
        except:
            continue

    print(f"Total JavaScript clusters: {len(js_clusters)}")
    print()

    # Check v3 and v4 completion
    missing_v3 = []
    missing_v4 = []
    incomplete_v3 = []
    incomplete_v4 = []

    for cluster in js_clusters:
        # Check v3
        v3_files = list(results_dir.glob(f'{cluster}_results_v3_*.json'))
        v3_files = [f for f in v3_files if 'backup' not in f.name]
        if len(v3_files) == 0:
            missing_v3.append(cluster)
        elif len(v3_files) < 5:
            incomplete_v3.append((cluster, len(v3_files)))

        # Check v4
        v4_files = list(results_dir.glob(f'{cluster}_results_v4_*.json'))
        v4_files = [f for f in v4_files if 'backup' not in f.name]
        if len(v4_files) == 0:
            missing_v4.append(cluster)
        elif len(v4_files) < 5:
            incomplete_v4.append((cluster, len(v4_files)))

    print(f"=== V3 Results ===")
    print(f"Complete (5 runs): {len(js_clusters) - len(missing_v3) - len(incomplete_v3)}")
    print(f"Incomplete: {len(incomplete_v3)}")
    print(f"Missing: {len(missing_v3)}")
    if missing_v3:
        print(f"  Missing clusters: {', '.join(missing_v3[:10])}")
    if incomplete_v3:
        print(f"  Incomplete: {incomplete_v3[:10]}")
    print()

    print(f"=== V4 Results ===")
    print(f"Complete (5 runs): {len(js_clusters) - len(missing_v4) - len(incomplete_v4)}")
    print(f"Incomplete: {len(incomplete_v4)}")
    print(f"Missing: {len(missing_v4)}")
    if missing_v4:
        print(f"  Missing clusters: {', '.join(missing_v4[:10])}")
    if incomplete_v4:
        print(f"  Incomplete: {incomplete_v4[:10]}")
    print()

    total_expected = len(js_clusters) * 2  # v3 + v4
    total_complete = (len(js_clusters) - len(missing_v3) - len(incomplete_v3)) + \
                     (len(js_clusters) - len(missing_v4) - len(incomplete_v4))

    print(f"=== Overall ===")
    print(f"Expected versions: {total_expected}")
    print(f"Complete: {total_complete}")
    print(f"Completion: {total_complete * 100 / total_expected:.1f}%")

    if not missing_v3 and not missing_v4 and not incomplete_v3 and not incomplete_v4:
        print("\n✅ ALL CLUSTERS COMPLETE!")
    else:
        print(f"\n⚠️  Some clusters need attention")

if __name__ == '__main__':
    main()
