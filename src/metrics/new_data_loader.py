"""
New data loader for fixed_prompt_analysis.py that loads energy metrics directly
from execution_outputs with proper base 100% pass rate filtering.

This replicates the logic of pass_rate_analyzer.py but for energy metrics.
"""

import json
import sys
import os
from pathlib import Path
from collections import defaultdict
from typing import Dict, List

# Add parent dirs to path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
from utility_dir import utility_paths, general_utils
from metrics.energy_improvements.energy_analyzer import EnergyConfig, calculate_energy_joules


def load_energy_improvements_from_raw(
    clusters_dir: Path,
    execution_dir: Path,
    min_base_pass_rate: float = 100.0
) -> Dict:
    """
    Load energy improvement data directly from execution_outputs files.

    Uses same filtering logic as pass_rate_analyzer.py:
    - Only includes entries where base code has >= min_base_pass_rate% pass rate
    - Calculates energy from CPU, RAM, execution_time
    - Computes improvement % for each valid entry

    Returns:
        Dictionary: {prompt_version: {model: {language: {metric: [improvements]}}}}
    """

    energy_config = EnergyConfig()
    languages = ['c', 'cpp', 'go', 'java', 'python', 'javascript', 'typescript']
    models = ['openAI', 'claude', 'gemini']
    prompt_versions = ['prompt_v1', 'prompt_v2', 'prompt_v3', 'prompt_v4']
    metrics = ['CPU_usage', 'RAM_usage', 'execution_time_ms', 'energy_joules']

    # Result structure
    data = defaultdict(lambda: defaultdict(lambda: defaultdict(lambda: defaultdict(list))))

    # Get all clusters
    cluster_files = list(clusters_dir.glob("cluster_*.json"))
    print(f"Loading energy improvements from {len(cluster_files)} clusters...")

    stats = {
        'processed_clusters': 0,
        'valid_entries': 0,
        'total_improvements': 0,
        'cpp_base_entries': 0,
        'cpp_base_100_pass': 0,
        'cpp_llm_entries_found': defaultdict(lambda: defaultdict(set)),  # version -> model -> set of entry_ids
        'cpp_improvements_generated': defaultdict(lambda: defaultdict(int)),  # version -> model -> count
        # Additional debug stats for CPP
        'cpp_llm_total_executions': defaultdict(lambda: defaultdict(int)),  # version -> model -> count
        'cpp_llm_passed_executions': defaultdict(lambda: defaultdict(int)),  # version -> model -> count
        'cpp_llm_with_metrics': defaultdict(lambda: defaultdict(int)),  # version -> model -> count
        'cpp_llm_found_in_files': defaultdict(lambda: defaultdict(set)),  # version -> model -> set of (cluster, entry_id)
        'cpp_base_filtered': defaultdict(lambda: defaultdict(set)),  # version -> model -> entries filtered by base check
    }

    for cluster_file in cluster_files:
        cluster_name = cluster_file.stem.replace("cluster_", "")

        # Load cluster metadata
        try:
            with open(cluster_file) as f:
                cluster_data = json.load(f)
        except:
            continue

        # PHASE 1: Identify entries with 100% base pass rate
        valid_entries_by_language = defaultdict(set)

        # Load base executions (1-5)
        base_metrics = defaultdict(list)  # entry_id -> list of MetricData

        # Debug: track entries per cluster
        cluster_cpp_entries = set()

        for execution_num in range(1, 6):
            base_file = execution_dir / f"{cluster_name}_results_{execution_num}.json"
            if not base_file.exists():
                continue

            try:
                with open(base_file) as f:
                    base_data = json.load(f)
            except:
                continue

            if 'results' not in base_data:
                continue

            for language in languages:
                if language not in base_data['results']:
                    continue

                for entry in base_data['results'][language]:
                    entry_id = entry.get('id')
                    if not entry_id:
                        continue

                    # Track CPP entries in this cluster
                    if language == 'cpp':
                        cluster_cpp_entries.add(entry_id)

                    passed = entry.get('regressionTestPassed', False)

                    # Convert to float, handle strings
                    def safe_float(val):
                        if val is None:
                            return None
                        try:
                            return float(val)
                        except:
                            return None

                    cpu = safe_float(entry.get('CPU_usage'))
                    ram = safe_float(entry.get('RAM_usage'))
                    time_ms = safe_float(entry.get('execution_time_ms'))

                    # Calculate energy if metrics available
                    energy = None
                    if cpu is not None and ram is not None and time_ms is not None:
                        try:
                            energy = calculate_energy_joules(cpu, ram, time_ms, energy_config)
                        except:
                            pass

                    base_metrics[entry_id].append({
                        'passed': passed,
                        'cpu': cpu,
                        'ram': ram,
                        'time_ms': time_ms,
                        'energy': energy,
                        'language': language
                    })

        # Filter entries with 100% base pass rate
        for entry_id, metrics_list in base_metrics.items():
            if not metrics_list:
                continue

            pass_count = sum(1 for m in metrics_list if m['passed'])
            pass_rate = (pass_count / len(metrics_list)) * 100.0

            language = metrics_list[0]['language']

            # Track CPP stats
            if language == 'cpp':
                stats['cpp_base_entries'] += 1
                if pass_rate >= min_base_pass_rate:
                    stats['cpp_base_100_pass'] += 1

            if pass_rate >= min_base_pass_rate:
                valid_entries_by_language[language].add(entry_id)

                # Calculate base means for this entry
                valid_metrics = [m for m in metrics_list if m['passed']]
                if valid_metrics:
                    stats['valid_entries'] += 1

        # Debug: print cluster stats if it has CPP
        if cluster_cpp_entries:
            cpp_valid = sum(1 for eid in cluster_cpp_entries if eid in valid_entries_by_language['cpp'])
            if stats['processed_clusters'] < 3:  # Only first 3 clusters for brevity
                print(f"\nCluster {cluster_name}: {len(cluster_cpp_entries)} CPP entries, {cpp_valid} with 100% pass rate")

        # PHASE 2: Load LLM executions for valid entries
        for prompt_version in prompt_versions:
            version_num = prompt_version.replace('prompt_v', '')

            # Load LLM executions (v1-v4, 1-5 runs)
            llm_metrics = defaultdict(lambda: defaultdict(list))  # (entry_id, model) -> list

            for execution_num in range(1, 6):
                llm_file = execution_dir / f"{cluster_name}_results_v{version_num}_{execution_num}.json"
                if not llm_file.exists():
                    continue

                try:
                    with open(llm_file) as f:
                        llm_data = json.load(f)
                except:
                    continue

                if 'results' not in llm_data:
                    continue

                for language in languages:
                    if language not in llm_data['results']:
                        continue

                    for entry in llm_data['results'][language]:
                        entry_id = entry.get('id')
                        if not entry_id:
                            continue

                        # Track all CPP entries found in LLM files (before filtering)
                        if language == 'cpp' and 'LLM_results' in entry:
                            for llm in entry['LLM_results']:
                                model = llm.get('LLM_type')
                                if model in models:
                                    stats['cpp_llm_found_in_files'][prompt_version][model].add((cluster_name, entry_id))

                        # Only process if base passed
                        if entry_id not in valid_entries_by_language[language]:
                            # Track entries filtered by base check
                            if language == 'cpp' and 'LLM_results' in entry:
                                for llm in entry['LLM_results']:
                                    model = llm.get('LLM_type')
                                    if model in models:
                                        stats['cpp_base_filtered'][prompt_version][model].add((cluster_name, entry_id))
                            continue

                        if 'LLM_results' not in entry:
                            continue

                        for llm_result in entry['LLM_results']:
                            model = llm_result.get('LLM_type')
                            if model not in models:
                                continue

                            # Track CPP LLM total executions
                            if language == 'cpp':
                                stats['cpp_llm_total_executions'][prompt_version][model] += 1

                            passed = llm_result.get('regressionTestPassed', False)

                            # Track CPP LLM passed executions
                            if language == 'cpp' and passed:
                                stats['cpp_llm_passed_executions'][prompt_version][model] += 1

                            # Convert to float
                            def safe_float(val):
                                if val is None:
                                    return None
                                try:
                                    return float(val)
                                except:
                                    return None

                            cpu = safe_float(llm_result.get('CPU_usage'))
                            ram = safe_float(llm_result.get('RAM_usage'))
                            time_ms = safe_float(llm_result.get('execution_time_ms'))

                            # Calculate energy
                            energy = None
                            if cpu is not None and ram is not None and time_ms is not None:
                                try:
                                    energy = calculate_energy_joules(cpu, ram, time_ms, energy_config)
                                except:
                                    pass

                            # Track CPP LLM with valid metrics
                            if language == 'cpp' and passed and cpu is not None and ram is not None and time_ms is not None:
                                stats['cpp_llm_with_metrics'][prompt_version][model] += 1

                            llm_metrics[(entry_id, model)][language].append({
                                'passed': passed,
                                'cpu': cpu,
                                'ram': ram,
                                'time_ms': time_ms,
                                'energy': energy
                            })

                            # Track CPP LLM entries found (use cluster-scoped key)
                            if language == 'cpp':
                                stats['cpp_llm_entries_found'][prompt_version][model].add((cluster_name, entry_id))

            # Calculate improvements for each entry-model combination
            for (entry_id, model), lang_dict in llm_metrics.items():
                for language, metrics_list in lang_dict.items():
                    if not metrics_list:
                        continue

                    # Get base means for this entry
                    base_list = base_metrics.get(entry_id, [])
                    if not base_list:
                        continue

                    # Only use passed base executions
                    base_passed = [m for m in base_list if m['passed']]
                    if not base_passed:
                        continue

                    # Calculate base means (only from executions with valid metrics)
                    base_cpu_vals = [m['cpu'] for m in base_passed if m['cpu'] is not None]
                    base_ram_vals = [m['ram'] for m in base_passed if m['ram'] is not None]
                    base_time_vals = [m['time_ms'] for m in base_passed if m['time_ms'] is not None]
                    base_energy_vals = [m['energy'] for m in base_passed if m['energy'] is not None]

                    base_cpu = sum(base_cpu_vals) / len(base_cpu_vals) if base_cpu_vals else None
                    base_ram = sum(base_ram_vals) / len(base_ram_vals) if base_ram_vals else None
                    base_time = sum(base_time_vals) / len(base_time_vals) if base_time_vals else None
                    base_energy = sum(base_energy_vals) / len(base_energy_vals) if base_energy_vals else None

                    # Only use passed LLM executions with valid metrics
                    llm_passed = [m for m in metrics_list if m['passed']]
                    if not llm_passed:
                        continue

                    # Calculate LLM means (only from executions with valid metrics)
                    llm_cpu_vals = [m['cpu'] for m in llm_passed if m['cpu'] is not None]
                    llm_ram_vals = [m['ram'] for m in llm_passed if m['ram'] is not None]
                    llm_time_vals = [m['time_ms'] for m in llm_passed if m['time_ms'] is not None]
                    llm_energy_vals = [m['energy'] for m in llm_passed if m['energy'] is not None]

                    llm_cpu = sum(llm_cpu_vals) / len(llm_cpu_vals) if llm_cpu_vals else None
                    llm_ram = sum(llm_ram_vals) / len(llm_ram_vals) if llm_ram_vals else None
                    llm_time = sum(llm_time_vals) / len(llm_time_vals) if llm_time_vals else None
                    llm_energy = sum(llm_energy_vals) / len(llm_energy_vals) if llm_energy_vals else None

                    # Calculate improvements (positive = reduction = good)
                    def calc_improvement(base_val, llm_val):
                        if base_val is None or llm_val is None or base_val == 0:
                            return None
                        return ((base_val - llm_val) / base_val) * 100.0

                    improvements = {
                        'CPU_usage': calc_improvement(base_cpu, llm_cpu),
                        'RAM_usage': calc_improvement(base_ram, llm_ram),
                        'execution_time_ms': calc_improvement(base_time, llm_time),
                        'energy_joules': calc_improvement(base_energy, llm_energy) if base_energy else None
                    }

                    # Store valid improvements
                    for metric, improvement in improvements.items():
                        if improvement is not None:
                            # Apply outlier threshold (±200%)
                            if abs(improvement) <= 200.0:
                                data[prompt_version][model][language][metric].append(improvement)
                                stats['total_improvements'] += 1

                                # Track CPP improvements generated
                                if language == 'cpp':
                                    stats['cpp_improvements_generated'][prompt_version][model] += 1

        stats['processed_clusters'] += 1

    print(f"Processed {stats['processed_clusters']} clusters")
    print(f"Found {stats['valid_entries']} valid base entries (all languages)")
    print(f"Generated {stats['total_improvements']} improvement values (all languages)")

    print(f"\n{'='*80}")
    print("CPP-SPECIFIC STATISTICS:")
    print(f"{'='*80}")
    print(f"Total CPP base entries found: {stats['cpp_base_entries']}")
    print(f"CPP entries with 100% base pass rate: {stats['cpp_base_100_pass']}")

    print(f"\nCPP LLM entries found by version and model:")
    for version in ['prompt_v1', 'prompt_v2', 'prompt_v3', 'prompt_v4']:
        print(f"\n  {version}:")
        for model in ['openAI', 'claude', 'gemini']:
            found_in_files = len(stats['cpp_llm_found_in_files'][version][model])
            filtered_by_base = len(stats['cpp_base_filtered'][version][model])
            found = len(stats['cpp_llm_entries_found'][version][model])
            total_exec = stats['cpp_llm_total_executions'][version][model]
            passed_exec = stats['cpp_llm_passed_executions'][version][model]
            with_metrics = stats['cpp_llm_with_metrics'][version][model]
            generated = stats['cpp_improvements_generated'][version][model]
            print(f"    {model}:")
            print(f"      - {found_in_files} entries found in v{version[-1]} files")
            print(f"      - {filtered_by_base} entries FILTERED OUT (base not 100% pass)")
            print(f"      - {found} unique entries processed (from {total_exec} total executions)")
            print(f"      - {passed_exec} executions passed test ({passed_exec/total_exec*100 if total_exec else 0:.1f}%)")
            print(f"      - {with_metrics} executions have valid metrics (CPU+RAM+time)")
            print(f"      - {generated} improvements generated")

    return dict(data)


if __name__ == "__main__":
    # Test the loader
    clusters_dir = utility_paths.CLUSTERS_DIR_FILEPATH
    execution_dir = utility_paths.OUTPUT_DIR_FILEPATH

    data = load_energy_improvements_from_raw(clusters_dir, execution_dir)

    print("\nSample data for CPP:")
    for prompt_version in ['prompt_v1', 'prompt_v4']:
        print(f"\n{prompt_version}:")
        for model in ['openAI', 'claude', 'gemini']:
            for metric in ['energy_joules']:
                count = len(data.get(prompt_version, {}).get(model, {}).get('cpp', {}).get(metric, []))
                print(f"  {model} cpp {metric}: {count} values")
