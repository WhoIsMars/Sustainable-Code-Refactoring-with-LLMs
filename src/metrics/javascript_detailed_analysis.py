#!/usr/bin/env python3
"""
JavaScript Pass Rate - Detailed Analysis

This script provides detailed statistics about JavaScript entries
to understand the 58.46% pass rate and the limited sample size.

Usage:
    python3 javascript_detailed_analysis.py
    python3 javascript_detailed_analysis.py --export-clusters
"""

import json
import argparse
from pathlib import Path
from collections import defaultdict
from typing import Dict, List, Tuple


def analyze_javascript_coverage(execution_dir: Path) -> Dict:
    """Analyze JavaScript coverage across all base code files."""

    base_files = list(execution_dir.glob("*_results_[1-5].json"))

    stats = {
        'total_base_files': len(base_files),
        'files_with_js': 0,
        'files_without_js': 0,
        'clusters_with_js': set(),
        'clusters_without_js': set(),
        'total_js_entries': 0,
        'cluster_details': defaultdict(lambda: {
            'has_js_base': False,
            'js_entry_count': 0,
            'executions_with_js': []
        })
    }

    for file in base_files:
        cluster_name = file.stem.rsplit('_results_', 1)[0]
        exec_num = int(file.stem.rsplit('_', 1)[-1])

        try:
            with open(file, 'r') as f:
                data = json.load(f)
                js_entries = data.get('results', {}).get('javascript', [])

                if js_entries:
                    stats['files_with_js'] += 1
                    stats['clusters_with_js'].add(cluster_name)
                    stats['total_js_entries'] += len(js_entries)
                    stats['cluster_details'][cluster_name]['has_js_base'] = True
                    stats['cluster_details'][cluster_name]['js_entry_count'] = len(js_entries)
                    stats['cluster_details'][cluster_name]['executions_with_js'].append(exec_num)
                else:
                    stats['files_without_js'] += 1
                    stats['clusters_without_js'].add(cluster_name)
        except Exception:
            pass

    # Convert sets to sorted lists for reporting
    stats['clusters_with_js'] = sorted(list(stats['clusters_with_js']))
    stats['clusters_without_js'] = sorted(list(stats['clusters_without_js']))

    return stats


def analyze_pass_rates_by_cluster(execution_dir: Path, clusters_with_js: List[str]) -> Dict:
    """Analyze pass rates for JavaScript entries by cluster."""

    cluster_pass_rates = {}

    for cluster_name in clusters_with_js:
        # Gather data across all 5 executions
        entry_results = defaultdict(lambda: {'passed': 0, 'total': 0})

        for exec_num in range(1, 6):
            file = execution_dir / f"{cluster_name}_results_{exec_num}.json"

            if not file.exists():
                continue

            try:
                with open(file, 'r') as f:
                    data = json.load(f)
                    js_entries = data.get('results', {}).get('javascript', [])

                    for entry in js_entries:
                        entry_id = entry.get('id')
                        entry_results[entry_id]['total'] += 1
                        if entry.get('regressionTestPassed', False):
                            entry_results[entry_id]['passed'] += 1
            except Exception:
                pass

        # Calculate pass rates for each entry
        entry_pass_rates = {}
        for entry_id, counts in entry_results.items():
            if counts['total'] >= 5:  # Only count complete executions
                pass_rate = (counts['passed'] / 5) * 100
                entry_pass_rates[entry_id] = {
                    'pass_rate': pass_rate,
                    'passed': counts['passed'],
                    'total': 5
                }

        if entry_pass_rates:
            # Calculate cluster-level statistics
            pass_rates = [data['pass_rate'] for data in entry_pass_rates.values()]
            cluster_pass_rates[cluster_name] = {
                'entry_count': len(entry_pass_rates),
                'entries_100_percent': sum(1 for pr in pass_rates if pr == 100.0),
                'entries_80_99_percent': sum(1 for pr in pass_rates if 80 <= pr < 100),
                'entries_50_79_percent': sum(1 for pr in pass_rates if 50 <= pr < 80),
                'entries_below_50_percent': sum(1 for pr in pass_rates if pr < 50),
                'mean_pass_rate': sum(pass_rates) / len(pass_rates),
                'entry_details': entry_pass_rates
            }

    return cluster_pass_rates


def analyze_llm_vs_base(execution_dir: Path, clusters_with_js: List[str]) -> Dict:
    """Compare LLM pass rates to base pass rates for JavaScript."""

    comparison = {
        'total_entries_analyzed': 0,
        'entries_with_100_base': 0,
        'llm_performance': defaultdict(lambda: {
            'v1': {'passed': 0, 'total': 0},
            'v2': {'passed': 0, 'total': 0},
            'v3': {'passed': 0, 'total': 0},
            'v4': {'passed': 0, 'total': 0},
        }),
        'cluster_summaries': {}
    }

    for cluster_name in clusters_with_js:
        # Get base results (first execution only)
        base_file = execution_dir / f"{cluster_name}_results_1.json"
        if not base_file.exists():
            continue

        try:
            with open(base_file, 'r') as f:
                base_data = json.load(f)
                base_js = base_data.get('results', {}).get('javascript', [])

                # Identify entries with 100% base pass rate
                base_100_entries = set()
                for entry in base_js:
                    entry_id = entry.get('id')
                    # Check all 5 executions for 100% pass rate
                    all_passed = True
                    for exec_num in range(1, 6):
                        exec_file = execution_dir / f"{cluster_name}_results_{exec_num}.json"
                        if exec_file.exists():
                            exec_data = json.load(open(exec_file))
                            exec_js = exec_data.get('results', {}).get('javascript', [])
                            entry_in_exec = next((e for e in exec_js if e['id'] == entry_id), None)
                            if not entry_in_exec or not entry_in_exec.get('regressionTestPassed'):
                                all_passed = False
                                break
                        else:
                            all_passed = False
                            break

                    if all_passed:
                        base_100_entries.add(entry_id)

                if not base_100_entries:
                    continue

                comparison['entries_with_100_base'] += len(base_100_entries)

                # Check LLM results for these entries
                cluster_llm_summary = defaultdict(lambda: {'passed': 0, 'total': 0})

                for version in ['v1', 'v2', 'v3', 'v4']:
                    llm_file = execution_dir / f"{cluster_name}_results_{version}_1.json"
                    if not llm_file.exists():
                        continue

                    llm_data = json.load(open(llm_file))
                    llm_js = llm_data.get('results', {}).get('javascript', [])

                    for entry in llm_js:
                        if entry['id'] not in base_100_entries:
                            continue

                        for llm_result in entry.get('LLM_results', []):
                            llm_type = llm_result.get('LLM_type')
                            passed = llm_result.get('regressionTestPassed', False)

                            comparison['llm_performance'][llm_type][version]['total'] += 1
                            cluster_llm_summary[version]['total'] += 1

                            if passed:
                                comparison['llm_performance'][llm_type][version]['passed'] += 1
                                cluster_llm_summary[version]['passed'] += 1

                comparison['cluster_summaries'][cluster_name] = dict(cluster_llm_summary)

        except Exception as e:
            print(f"Error analyzing {cluster_name}: {e}")
            pass

    comparison['total_entries_analyzed'] = comparison['entries_with_100_base']

    return comparison


def main():
    parser = argparse.ArgumentParser(description="JavaScript Pass Rate - Detailed Analysis")
    parser.add_argument('--export-clusters', action='store_true',
                       help='Export list of clusters with/without JS base code')
    args = parser.parse_args()

    # Paths
    execution_dir = Path(__file__).parent.parent / "execution_outputs"

    print("="*80)
    print("JAVASCRIPT DETAILED PASS RATE ANALYSIS")
    print("="*80)
    print()

    # Part 1: Coverage Analysis
    print("[1] Analyzing JavaScript Coverage...")
    coverage = analyze_javascript_coverage(execution_dir)

    print(f"\n📊 JavaScript Coverage Statistics:")
    print(f"  Total base code files: {coverage['total_base_files']}")
    print(f"  Files WITH JavaScript: {coverage['files_with_js']} ({coverage['files_with_js']/coverage['total_base_files']*100:.1f}%)")
    print(f"  Files WITHOUT JavaScript: {coverage['files_without_js']} ({coverage['files_without_js']/coverage['total_base_files']*100:.1f}%)")
    print()
    print(f"  Unique clusters WITH JS base: {len(coverage['clusters_with_js'])}")
    print(f"  Unique clusters WITHOUT JS base: {len(coverage['clusters_without_js'])}")
    print(f"  Total JS entries found: {coverage['total_js_entries']}")
    print()

    # Part 2: Pass Rate Analysis
    print("[2] Analyzing Base Code Pass Rates...")
    pass_rates = analyze_pass_rates_by_cluster(execution_dir, coverage['clusters_with_js'])

    # Calculate aggregates
    total_entries = sum(data['entry_count'] for data in pass_rates.values())
    total_100 = sum(data['entries_100_percent'] for data in pass_rates.values())
    total_80_99 = sum(data['entries_80_99_percent'] for data in pass_rates.values())
    total_50_79 = sum(data['entries_50_79_percent'] for data in pass_rates.values())
    total_below_50 = sum(data['entries_below_50_percent'] for data in pass_rates.values())

    print(f"\n📈 Base Code Pass Rate Distribution:")
    print(f"  Total entries analyzed: {total_entries}")
    print(f"  Entries with 100% pass rate: {total_100} ({total_100/total_entries*100:.1f}%)")
    print(f"  Entries with 80-99% pass rate: {total_80_99} ({total_80_99/total_entries*100:.1f}%)")
    print(f"  Entries with 50-79% pass rate: {total_50_79} ({total_50_79/total_entries*100:.1f}%)")
    print(f"  Entries with <50% pass rate: {total_below_50} ({total_below_50/total_entries*100:.1f}%)")
    print()

    # Show top/bottom clusters
    sorted_clusters = sorted(pass_rates.items(),
                            key=lambda x: x[1]['entries_100_percent'],
                            reverse=True)

    print("  Top 10 clusters by entries with 100% pass rate:")
    for cluster, data in sorted_clusters[:10]:
        print(f"    {cluster}: {data['entries_100_percent']}/{data['entry_count']} (mean: {data['mean_pass_rate']:.1f}%)")
    print()

    print("  Bottom 10 clusters (lowest 100% pass rate):")
    for cluster, data in sorted_clusters[-10:]:
        if data['entry_count'] > 0:
            print(f"    {cluster}: {data['entries_100_percent']}/{data['entry_count']} (mean: {data['mean_pass_rate']:.1f}%)")
    print()

    # Part 3: LLM vs Base Comparison
    print("[3] Analyzing LLM vs Base Comparison...")
    comparison = analyze_llm_vs_base(execution_dir, coverage['clusters_with_js'])

    print(f"\n🤖 LLM Performance on Entries with 100% Base Pass Rate:")
    print(f"  Total entries with 100% base: {comparison['entries_with_100_base']}")
    print()

    for llm_type, versions in sorted(comparison['llm_performance'].items()):
        print(f"  {llm_type}:")
        for version, data in sorted(versions.items()):
            if data['total'] > 0:
                pass_rate = (data['passed'] / data['total']) * 100
                print(f"    {version}: {pass_rate:.1f}% ({data['passed']}/{data['total']})")
        print()

    # Export clusters if requested
    if args.export_clusters:
        output_file = Path(__file__).parent / "javascript_clusters_analysis.json"
        export_data = {
            'coverage': {
                'clusters_with_js_base': coverage['clusters_with_js'],
                'clusters_without_js_base': coverage['clusters_without_js'],
                'cluster_details': dict(coverage['cluster_details'])
            },
            'pass_rates': {
                cluster: {
                    'entry_count': data['entry_count'],
                    'entries_100_percent': data['entries_100_percent'],
                    'mean_pass_rate': data['mean_pass_rate']
                }
                for cluster, data in pass_rates.items()
            },
            'llm_comparison': {
                'total_entries_100_base': comparison['entries_with_100_base'],
                'llm_performance': dict(comparison['llm_performance']),
                'cluster_summaries': comparison['cluster_summaries']
            }
        }

        with open(output_file, 'w') as f:
            json.dump(export_data, f, indent=2)

        print(f"✓ Detailed analysis exported to: {output_file}")

    print("="*80)
    print("Analysis complete!")
    print("="*80)


if __name__ == "__main__":
    main()
