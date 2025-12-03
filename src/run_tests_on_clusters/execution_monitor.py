#!/usr/bin/env python3
"""
Execution Status Monitor
Monitors and displays the execution progress of base and LLM entries across all clusters.

Features:
- Real-time progress tracking with visual progress bar
- Detailed statistics on base and LLM executions
- Filtering for base entries with 100% pass rate
- Periodic refresh with configurable interval
- Color-coded output for better readability

Date: 01/12/2024
"""

import sys
import os
from pathlib import Path
from typing import Dict, List, Tuple, Set
from dataclasses import dataclass, field
from collections import defaultdict
import time
import argparse
from datetime import datetime

# Add parent directory to path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))

from utility_dir.utility_paths import (
    CLUSTERS_DIR_FILEPATH,
    OUTPUT_DIR_FILEPATH,
)
from utility_dir.general_utils import (
    get_cluster_path_list,
    read_json,
    CodeEntry,
    BaseEntryResult,
    LLMentryResult,
    get_prompt_version_by_filename,
)


# Constants
EXPECTED_BASE_EXECUTIONS = 5
EXPECTED_LLM_MODELS = 3  # openAI, claude, gemini
LLM_MODEL_NAMES = ["openAI", "claude", "gemini"]
EXPECTED_PROMPT_VERSIONS = 4  # v1, v2, v3, v4
EXPECTED_LLM_ENTRIES_PER_BASE = EXPECTED_LLM_MODELS * EXPECTED_PROMPT_VERSIONS  # 12
EXPECTED_LLM_EXECUTIONS_PER_ENTRY = 5
EXPECTED_TOTAL_LLM_EXECUTIONS_PER_BASE = EXPECTED_LLM_ENTRIES_PER_BASE * EXPECTED_LLM_EXECUTIONS_PER_ENTRY  # 60


@dataclass
class BaseEntryStatus:
    """Status of a base entry execution"""
    entry_id: str
    cluster_name: str
    language: str
    executions_completed: int
    executions_passed: int
    has_full_pass_rate: bool


@dataclass
class LLMEntryStatus:
    """Status of an LLM entry execution"""
    entry_id: str
    cluster_name: str
    language: str
    prompt_version: int
    llm_type: str
    executions_completed: int
    executions_passed: int


@dataclass
class ExecutionStats:
    """Overall execution statistics"""

    # Base entry stats
    total_base_entries: int = 0
    base_entries_with_full_pass: int = 0
    total_base_executions_expected: int = 0
    total_base_executions_completed: int = 0

    # LLM entry stats
    total_llm_entries_expected: int = 0  # Based on base entries with full pass
    total_llm_entries_found: int = 0
    total_llm_executions_expected: int = 0
    total_llm_executions_completed: int = 0

    # Breakdown by prompt version
    llm_executions_by_version: Dict[int, int] = field(default_factory=dict)

    # Breakdown by language
    base_entries_by_language: Dict[str, int] = field(default_factory=dict)
    llm_entries_by_language: Dict[str, int] = field(default_factory=dict)

    # Timestamp for ETA calculation
    timestamp: datetime = field(default_factory=datetime.now)

    # Historical rate from file timestamps (executions per second)
    historical_rate: float = 0.0

    def base_progress_percentage(self) -> float:
        if self.total_base_executions_expected == 0:
            return 0.0
        return (self.total_base_executions_completed / self.total_base_executions_expected) * 100

    def llm_progress_percentage(self) -> float:
        if self.total_llm_executions_expected == 0:
            return 0.0
        pct = (self.total_llm_executions_completed / self.total_llm_executions_expected) * 100
        return min(pct, 100.0)  # Cap at 100%

    def overall_progress_percentage(self) -> float:
        total_expected = self.total_base_executions_expected + self.total_llm_executions_expected
        total_completed = self.total_base_executions_completed + self.total_llm_executions_completed
        if total_expected == 0:
            return 0.0
        pct = (total_completed / total_expected) * 100
        return min(pct, 100.0)  # Cap at 100%


def format_time_delta(seconds: float) -> str:
    """Format seconds into human-readable time string."""
    if seconds < 0:
        return "N/A"

    days = int(seconds // 86400)
    hours = int((seconds % 86400) // 3600)
    minutes = int((seconds % 3600) // 60)
    secs = int(seconds % 60)

    parts = []
    if days > 0:
        parts.append(f"{days}d")
    if hours > 0:
        parts.append(f"{hours}h")
    if minutes > 0:
        parts.append(f"{minutes}m")
    if secs > 0 or not parts:
        parts.append(f"{secs}s")

    return " ".join(parts)


class ExecutionMonitor:
    """Monitor execution status of base and LLM entries"""

    def __init__(self, clusters_dir: Path, output_dir: Path):
        self.clusters_dir = clusters_dir
        self.output_dir = output_dir
        self.base_entries_status: Dict[Tuple[str, str], BaseEntryStatus] = {}  # (cluster, entry_id) -> status
        self.llm_entries_status: Dict[Tuple[str, str, int], List[LLMEntryStatus]] = defaultdict(list)  # (cluster, entry_id, prompt_v) -> [status]

        # For ETA calculation
        self.first_stats: ExecutionStats = None
        self.previous_stats: ExecutionStats = None

    def analyze_base_entry_executions(self, entry: CodeEntry, cluster_name: str) -> BaseEntryStatus:
        """
        Analyze execution status of a base entry across all 5 executions.

        Returns:
            BaseEntryStatus with completion and pass rate information
        """
        executions_completed = 0
        executions_passed = 0

        for exec_num in range(1, EXPECTED_BASE_EXECUTIONS + 1):
            result_path = self.output_dir / f"{cluster_name}_results_{exec_num}.json"

            if not result_path.exists():
                continue

            content = read_json(result_path)
            if not content or "results" not in content:
                continue

            for lang, entries in content["results"].items():
                for raw_entry in entries:
                    try:
                        entry_result = BaseEntryResult.from_json(raw_entry)
                        if entry_result.id == entry.id:
                            executions_completed += 1
                            if entry_result.regressionTestPassed:
                                executions_passed += 1
                            break
                    except Exception:
                        continue

        has_full_pass = (executions_completed == EXPECTED_BASE_EXECUTIONS and
                        executions_passed == EXPECTED_BASE_EXECUTIONS)

        return BaseEntryStatus(
            entry_id=entry.id,
            cluster_name=cluster_name,
            language=entry.language,
            executions_completed=executions_completed,
            executions_passed=executions_passed,
            has_full_pass_rate=has_full_pass
        )

    def analyze_llm_entry_executions(
        self,
        entry_id: str,
        cluster_name: str,
        language: str,
        prompt_version: int,
        llm_type: str
    ) -> LLMEntryStatus:
        """
        Analyze execution status of an LLM entry for a specific prompt version.

        Returns:
            LLMEntryStatus with completion information
        """
        executions_completed = 0
        executions_passed = 0
        prompt_v_str = f"v{prompt_version}"

        for exec_num in range(1, EXPECTED_LLM_EXECUTIONS_PER_ENTRY + 1):
            result_path = self.output_dir / f"{cluster_name}_results_{prompt_v_str}_{exec_num}.json"

            if not result_path.exists():
                continue

            content = read_json(result_path)
            if not content or "results" not in content:
                continue

            for lang, raw_llm_results in content["results"].items():
                for llm_raw_res in raw_llm_results:
                    try:
                        llm_entry_result = LLMentryResult.from_json(llm_raw_res)
                        if llm_entry_result.id == entry_id:
                            executions_completed += 1
                            # Check if at least one LLM result passed
                            for llm_res in llm_entry_result.LLM_results:
                                if llm_res.LLM_type == llm_type and llm_res.regressionTestPassed:
                                    executions_passed += 1
                                    break
                            break
                    except Exception:
                        continue

        return LLMEntryStatus(
            entry_id=entry_id,
            cluster_name=cluster_name,
            language=language,
            prompt_version=prompt_version,
            llm_type=llm_type,
            executions_completed=executions_completed,
            executions_passed=executions_passed
        )

    def scan_all_clusters(self) -> ExecutionStats:
        """
        Scan all clusters and analyze execution status by reading from execution_outputs directory.

        Returns:
            ExecutionStats with comprehensive statistics
        """
        stats = ExecutionStats()
        cluster_paths = get_cluster_path_list(self.clusters_dir)

        print(f"\n🔍 Scanning {len(cluster_paths)} clusters and execution outputs...")

        # First pass: analyze base entries from clusters and count unique (entry_id, prompt_v) pairs
        # We count pairs, not individual LLM entries, since runner works on pairs
        expected_pairs_in_clusters: Set[Tuple[str, str, int]] = set()  # (cluster, entry_id, prompt_v)

        # Track base entry IDs with full pass rate (cluster_name -> set of entry_ids)
        base_entries_with_full_pass_ids: Dict[str, Set[str]] = defaultdict(set)

        for cluster_path in cluster_paths:
            cluster_name = str(cluster_path).split("src/clusters/")[1]
            cluster_name = cluster_name.removesuffix(".json").removeprefix("cluster_")

            cluster_data = read_json(cluster_path)
            if not cluster_data:
                continue

            for lang, entries in cluster_data.items():
                for entry_dict in entries:
                    try:
                        entry = CodeEntry.from_dict(entry_dict)

                        # Analyze base entry
                        base_status = self.analyze_base_entry_executions(entry, cluster_name)
                        self.base_entries_status[(cluster_name, entry.id)] = base_status

                        stats.total_base_entries += 1
                        stats.total_base_executions_expected += EXPECTED_BASE_EXECUTIONS
                        stats.total_base_executions_completed += base_status.executions_completed
                        stats.base_entries_by_language[lang] = stats.base_entries_by_language.get(lang, 0) + 1

                        if base_status.has_full_pass_rate:
                            stats.base_entries_with_full_pass += 1
                            # Track this entry_id as having full pass
                            base_entries_with_full_pass_ids[cluster_name].add(entry.id)

                            # Count unique (entry_id, prompt_v) pairs from LLM entries
                            for llm_entry in entry.LLMs:
                                try:
                                    prompt_v = get_prompt_version_by_filename(llm_entry.filename)
                                    expected_pairs_in_clusters.add((cluster_name, entry.id, prompt_v))
                                except Exception:
                                    pass

                    except Exception:
                        continue

        # Second pass: scan execution_outputs directory for all LLM results
        # Count (entry_id, prompt_v) pairs where ALL 3 models have 5 executions
        # ONLY for base entries with 100% pass rate
        #
        # Structure: (cluster, prompt_v, entry_id) -> {exec_num -> set of models found}
        # A pair is "complete" if all 3 models appear in all 5 exec files

        # Map: (cluster, prompt_v, entry_id) -> {exec_num -> set of llm_types found}
        entry_model_coverage: Dict[Tuple[str, int, str], Dict[int, Set[str]]] = defaultdict(lambda: defaultdict(set))

        # Track file modification times for historical rate calculation
        file_mtimes = []
        llm_executions_by_version = defaultdict(int)
        llm_executions_by_language = defaultdict(int)

        # Pattern: {cluster_name}_results_v{1-4}_{1-5}.json
        result_files = list(self.output_dir.glob("*_results_v*_*.json"))

        for result_file in result_files:
            filename = result_file.name

            # Skip backup files
            if ".backup_" in filename:
                continue

            # Parse filename: {cluster}_results_v{N}_{M}.json
            try:
                parts = filename.replace("_results_v", "|").replace(".json", "").split("|")
                if len(parts) != 2:
                    continue

                cluster_name = parts[0]
                version_exec = parts[1].split("_")
                if len(version_exec) != 2:
                    continue

                prompt_v = int(version_exec[0])
                exec_num = int(version_exec[1])

                # Get file modification time
                mtime = result_file.stat().st_mtime

                # Read file and collect models found for each entry
                content = read_json(result_file)
                if not content or "results" not in content:
                    continue

                file_exec_count = 0
                for lang, llm_results_list in content["results"].items():
                    for llm_result in llm_results_list:
                        entry_id = llm_result.get("id")
                        llm_results = llm_result.get("LLM_results", [])

                        # Only count if the base entry has full pass rate
                        if entry_id and entry_id in base_entries_with_full_pass_ids.get(cluster_name, set()):
                            # Track which models are present for this entry in this exec file
                            for llm_res in llm_results:
                                llm_type = llm_res.get("LLM_type", "unknown")
                                if llm_type in LLM_MODEL_NAMES:
                                    entry_model_coverage[(cluster_name, prompt_v, entry_id)][exec_num].add(llm_type)
                                    file_exec_count += 1
                                    llm_executions_by_language[lang] = llm_executions_by_language.get(lang, 0) + 1

                # Store mtime with execution count for rate calculation
                if file_exec_count > 0:
                    file_mtimes.append((mtime, file_exec_count))

            except Exception:
                continue

        # Count (entry_id, prompt_v) pairs where ALL 3 models have 5 executions
        # Each such pair = 3 models × 5 executions = 15 executions complete
        total_complete_pairs = 0  # Pairs (entry_id, prompt_v) with all models complete
        pairs_by_version = defaultdict(int)

        for (cluster_name, prompt_v, entry_id), exec_models in entry_model_coverage.items():
            # Check if all 5 exec files exist for this entry
            if len(exec_models) < 5:
                continue

            # Check if ALL 3 models appear in ALL 5 exec files
            all_models_complete = True
            for exec_num in range(1, 6):
                if exec_num not in exec_models:
                    all_models_complete = False
                    break
                models_in_file = exec_models[exec_num]
                if not all(model in models_in_file for model in LLM_MODEL_NAMES):
                    all_models_complete = False
                    break

            if all_models_complete:
                total_complete_pairs += 1
                pairs_by_version[prompt_v] += 1

        # Each complete (entry_id, prompt_v) pair represents 3 models × 5 executions = 15 executions
        total_llm_executions = total_complete_pairs * EXPECTED_LLM_MODELS * EXPECTED_LLM_EXECUTIONS_PER_ENTRY

        # Store statistics
        # Each complete pair = 15 executions
        stats.llm_executions_by_version = {v: c * EXPECTED_LLM_MODELS * EXPECTED_LLM_EXECUTIONS_PER_ENTRY for v, c in pairs_by_version.items()}
        stats.llm_entries_by_language = dict(llm_executions_by_language)
        stats.total_llm_executions_completed = total_llm_executions

        # total_llm_entries_found now represents complete (entry_id, prompt_v) pairs × 3 models
        stats.total_llm_entries_found = total_complete_pairs * EXPECTED_LLM_MODELS

        # Calculate expected LLM statistics based on unique (entry_id, prompt_v) pairs in clusters
        # Each pair needs 3 models × 5 executions = 15 executions
        total_expected_pairs = len(expected_pairs_in_clusters)
        stats.total_llm_entries_expected = total_expected_pairs * EXPECTED_LLM_MODELS
        stats.total_llm_executions_expected = total_expected_pairs * EXPECTED_LLM_MODELS * EXPECTED_LLM_EXECUTIONS_PER_ENTRY

        # Calculate historical rate from file timestamps
        # Use files modified in the last 2 hours for rate estimation
        if file_mtimes:
            now = time.time()
            two_hours_ago = now - 7200  # 2 hours in seconds

            recent_files = [(mtime, count) for mtime, count in file_mtimes if mtime > two_hours_ago]

            if len(recent_files) >= 2:
                # Sort by modification time
                recent_files.sort(key=lambda x: x[0])
                oldest_mtime = recent_files[0][0]
                newest_mtime = recent_files[-1][0]
                time_span = newest_mtime - oldest_mtime

                if time_span > 0:
                    total_recent_execs = sum(count for _, count in recent_files)
                    stats.historical_rate = total_recent_execs / time_span

        return stats


def create_progress_bar(percentage: float, width: int = 50) -> str:
    """
    Create a visual progress bar.

    Args:
        percentage: Progress percentage (0-100)
        width: Width of the progress bar in characters

    Returns:
        String representation of the progress bar
    """
    filled = int(width * percentage / 100)
    bar = '█' * filled + '░' * (width - filled)
    return f"[{bar}] {percentage:.1f}%"


def calculate_eta(
    current_stats: ExecutionStats,
    first_stats: ExecutionStats = None,
    previous_stats: ExecutionStats = None
) -> str:
    """
    Calculate estimated time remaining based on execution rate.

    Uses a weighted average of:
    - Overall rate since monitoring started (for stability)
    - Recent rate from last interval (for responsiveness)
    - Historical rate from file timestamps (as fallback)

    Args:
        current_stats: Current execution statistics
        first_stats: First recorded stats (for overall rate)
        previous_stats: Previous stats (for recent rate)

    Returns:
        Formatted ETA string or None if cannot calculate
    """
    total_expected = (current_stats.total_base_executions_expected +
                      current_stats.total_llm_executions_expected)
    total_completed = (current_stats.total_base_executions_completed +
                       current_stats.total_llm_executions_completed)
    remaining = total_expected - total_completed

    if remaining <= 0:
        return None

    # Calculate rate from first stats (overall average since monitor started)
    overall_rate = None
    if first_stats is not None and first_stats is not current_stats:
        first_completed = (first_stats.total_base_executions_completed +
                          first_stats.total_llm_executions_completed)
        completed_since_start = total_completed - first_completed
        time_elapsed = (current_stats.timestamp - first_stats.timestamp).total_seconds()

        if time_elapsed > 0 and completed_since_start > 0:
            overall_rate = completed_since_start / time_elapsed  # executions per second

    # Calculate rate from previous stats (recent rate)
    recent_rate = None
    if previous_stats is not None and previous_stats is not current_stats:
        prev_completed = (previous_stats.total_base_executions_completed +
                         previous_stats.total_llm_executions_completed)
        completed_since_prev = total_completed - prev_completed
        time_since_prev = (current_stats.timestamp - previous_stats.timestamp).total_seconds()

        if time_since_prev > 0 and completed_since_prev > 0:
            recent_rate = completed_since_prev / time_since_prev

    # Get historical rate from file timestamps
    historical_rate = current_stats.historical_rate if current_stats.historical_rate > 0 else None

    # Determine which rate to use
    rate = None
    rate_source = ""

    if overall_rate is not None and recent_rate is not None:
        # Weighted average: 70% overall, 30% recent for stability
        rate = 0.7 * overall_rate + 0.3 * recent_rate
        rate_source = "live"
    elif overall_rate is not None:
        rate = overall_rate
        rate_source = "live"
    elif recent_rate is not None:
        rate = recent_rate
        rate_source = "live"
    elif historical_rate is not None:
        # Fallback to historical rate from file timestamps
        rate = historical_rate
        rate_source = "historical"

    if rate is None or rate <= 0:
        return None

    # Calculate ETA
    eta_seconds = remaining / rate
    eta_formatted = format_time_delta(eta_seconds)

    # Also show rate
    rate_per_min = rate * 60
    if rate_source == "historical":
        return f"{eta_formatted} (~{rate_per_min:.1f} exec/min, based on file timestamps)"
    else:
        return f"{eta_formatted} (~{rate_per_min:.1f} exec/min)"


def display_stats(
    stats: ExecutionStats,
    show_details: bool = False,
    first_stats: ExecutionStats = None,
    previous_stats: ExecutionStats = None
):
    """
    Display execution statistics with visual formatting.

    Args:
        stats: ExecutionStats object to display
        show_details: Whether to show detailed breakdown
        first_stats: First recorded stats for ETA calculation
        previous_stats: Previous stats for rate calculation
    """
    print("\n" + "=" * 100)
    print("📊 EXECUTION STATUS MONITOR - REAL-TIME STATISTICS")
    print("=" * 100)
    print(f"⏰ Last updated: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print()

    # Overall progress
    overall_pct = stats.overall_progress_percentage()
    print("🎯 OVERALL PROGRESS")
    print(create_progress_bar(overall_pct, 80))
    total_expected = stats.total_base_executions_expected + stats.total_llm_executions_expected
    total_completed = stats.total_base_executions_completed + stats.total_llm_executions_completed
    # Show completed/expected, capping completed at expected for display
    display_completed = min(total_completed, total_expected)
    print(f"   Total executions: {display_completed:,} / {total_expected:,}")

    # Calculate and display ETA
    if total_completed >= total_expected:
        print(f"   ✓ All executions completed!")
    else:
        eta_str = calculate_eta(stats, first_stats, previous_stats)
        if eta_str:
            print(f"   ⏳ Estimated time remaining: {eta_str}")
        else:
            print(f"   ⏳ Estimated time remaining: calculating... (wait for next refresh)")
    print()

    # Base entries section
    print("📦 BASE ENTRIES")
    print("-" * 100)
    base_pct = stats.base_progress_percentage()
    print("Progress: " + create_progress_bar(base_pct, 60))
    print(f"  • Total base entries: {stats.total_base_entries:,}")
    print(f"  • Entries with 100% pass rate (5/5): {stats.base_entries_with_full_pass:,} ({stats.base_entries_with_full_pass / max(stats.total_base_entries, 1) * 100:.1f}%)")
    print(f"  • Executions completed: {stats.total_base_executions_completed:,} / {stats.total_base_executions_expected:,}")
    base_remaining = stats.total_base_executions_expected - stats.total_base_executions_completed
    if base_remaining <= 0:
        print(f"  • Executions remaining: ✓ Completed")
    else:
        print(f"  • Executions remaining: {base_remaining:,}")

    if show_details and stats.base_entries_by_language:
        print("\n  Breakdown by language:")
        for lang in sorted(stats.base_entries_by_language.keys()):
            count = stats.base_entries_by_language[lang]
            print(f"    - {lang}: {count:,} entries")

    print()

    # LLM entries section
    print("🤖 LLM ENTRIES (entry_id, prompt_v pairs with all 3 models)")
    print("-" * 100)
    llm_pct = stats.llm_progress_percentage()
    print("Progress: " + create_progress_bar(llm_pct, 60))

    # Calculate pairs from entries (entries = pairs × 3 models)
    expected_pairs = stats.total_llm_entries_expected // EXPECTED_LLM_MODELS
    completed_pairs = stats.total_llm_entries_found // EXPECTED_LLM_MODELS
    missing_pairs = expected_pairs - completed_pairs

    print(f"  • Expected (entry_id, prompt_v) pairs: {expected_pairs:,}")
    print(f"  • Complete pairs (all 3 models in all 5 files): {completed_pairs:,}")
    print(f"  • Missing pairs: {missing_pairs:,}")
    print(f"  • Executions completed: {stats.total_llm_executions_completed:,} / {stats.total_llm_executions_expected:,}")
    llm_remaining = stats.total_llm_executions_expected - stats.total_llm_executions_completed
    if llm_remaining <= 0:
        print(f"  • Executions remaining: ✓ Completed")
    else:
        print(f"  • Executions remaining: {llm_remaining:,}")

    if show_details:
        print("\n  Per pair:")
        print(f"    - Each pair needs {EXPECTED_LLM_MODELS} models × {EXPECTED_LLM_EXECUTIONS_PER_ENTRY} executions = {EXPECTED_LLM_MODELS * EXPECTED_LLM_EXECUTIONS_PER_ENTRY} executions")

        if stats.llm_executions_by_version:
            print("\n  Executions by prompt version:")
            for version in sorted(stats.llm_executions_by_version.keys()):
                count = stats.llm_executions_by_version[version]
                print(f"    - v{version}: {count:,} executions")

        if stats.llm_entries_by_language:
            print("\n  LLM entries by language:")
            for lang in sorted(stats.llm_entries_by_language.keys()):
                count = stats.llm_entries_by_language[lang]
                print(f"    - {lang}: {count:,} entries")

    print()
    print("=" * 100)

    # Estimated time remaining (rough estimate)
    if 0 < overall_pct < 100:
        # This is a very rough estimate - adjust based on actual execution speed
        print("\n💡 Tip: Use 'new_llm_selective_runner.py --parallel-processes N' to speed up execution")

    print()


def monitor_loop(
    clusters_dir: Path,
    output_dir: Path,
    interval: int = 30,
    show_details: bool = False,
    continuous: bool = True
):
    """
    Main monitoring loop.

    Args:
        clusters_dir: Path to clusters directory
        output_dir: Path to execution outputs directory
        interval: Refresh interval in seconds
        show_details: Whether to show detailed statistics
        continuous: Whether to run continuously or just once
    """
    monitor = ExecutionMonitor(clusters_dir, output_dir)

    # For ETA tracking
    first_stats: ExecutionStats = None
    previous_stats: ExecutionStats = None

    try:
        iteration = 0
        while True:
            iteration += 1

            # Clear screen (works on Unix-like systems)
            if continuous and iteration > 1:
                os.system('clear' if os.name != 'nt' else 'cls')

            # Scan and display statistics
            stats = monitor.scan_all_clusters()

            # Store first stats for ETA calculation
            if first_stats is None:
                first_stats = stats

            # Display with ETA information
            display_stats(stats, show_details, first_stats, previous_stats)

            # Update previous stats for next iteration
            previous_stats = stats

            if not continuous:
                break

            # Wait for next iteration
            print(f"⏱️  Refreshing in {interval} seconds... (Press Ctrl+C to stop)")
            time.sleep(interval)

    except KeyboardInterrupt:
        print("\n\n⚠️  Monitoring stopped by user")
        print("👋 Goodbye!")


def main():
    """Main entry point with argument parsing"""
    parser = argparse.ArgumentParser(
        description="Monitor execution status of base and LLM entries",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Run once and exit
  python3 execution_monitor.py --once

  # Continuous monitoring with 60 second interval
  python3 execution_monitor.py --interval 60

  # Show detailed breakdown by language and prompt version
  python3 execution_monitor.py --details

  # Continuous monitoring with details
  python3 execution_monitor.py --interval 30 --details
        """
    )

    parser.add_argument(
        "--interval",
        type=int,
        default=30,
        help="Refresh interval in seconds (default: 30)"
    )

    parser.add_argument(
        "--once",
        action="store_true",
        help="Run once and exit (no continuous monitoring)"
    )

    parser.add_argument(
        "--details",
        action="store_true",
        help="Show detailed breakdown by language and prompt version"
    )

    parser.add_argument(
        "--clusters-dir",
        type=Path,
        default=CLUSTERS_DIR_FILEPATH,
        help="Path to clusters directory (default: src/clusters)"
    )

    parser.add_argument(
        "--output-dir",
        type=Path,
        default=OUTPUT_DIR_FILEPATH,
        help="Path to execution outputs directory (default: src/execution_outputs)"
    )

    args = parser.parse_args()

    # Validate directories
    if not args.clusters_dir.exists():
        print(f"❌ Error: Clusters directory not found: {args.clusters_dir}")
        return 1

    if not args.output_dir.exists():
        print(f"❌ Error: Output directory not found: {args.output_dir}")
        return 1

    # Start monitoring
    monitor_loop(
        clusters_dir=args.clusters_dir,
        output_dir=args.output_dir,
        interval=args.interval,
        show_details=args.details,
        continuous=not args.once
    )

    return 0


if __name__ == "__main__":
    sys.exit(main())