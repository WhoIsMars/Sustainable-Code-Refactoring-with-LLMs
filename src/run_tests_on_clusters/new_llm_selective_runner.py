"""
Run only LLM entires never runned before
(necessary for main_pipeline.sh)

Date : 25/11/2025
"""

import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))


from utility_dir.utility_paths import (
    CLUSTERS_DIR_FILEPATH,
    OUTPUT_DIR_FILEPATH,
    ANALISYS_REPORT_FILE_PATH,
)
from utility_dir.general_utils import (
    get_cluster_path_list,
    read_json,
    CodeEntry,
    BaseEntryResult,
    LLMentryResult,
    get_prompt_version_by_filename,
    LANGUAGES,
)
from collections import defaultdict
import time
import subprocess
from pathlib import Path
import json
import multiprocessing
from typing import List, Tuple
import argparse


def _batch_entries(
    entry_id_list: List[str], cluster_list: List[str], num_batches: int
) -> List[Tuple[List[str], List[str]]]:
    """
    Split entry IDs and clusters into evenly distributed batches.

    Args:
        entry_id_list: List of entry IDs
        cluster_list: List of cluster names (1:1 mapping with entry_id_list)
        num_batches: Number of batches to create

    Returns:
        List of tuples, each containing (batch_entry_ids, batch_clusters)
    """
    total = len(entry_id_list)
    batch_size = total // num_batches
    remainder = total % num_batches

    batches = []
    start_idx = 0

    for i in range(num_batches):
        # Distribute remainder entries across first batches
        current_batch_size = batch_size + (1 if i < remainder else 0)
        end_idx = start_idx + current_batch_size

        batch_entries = entry_id_list[start_idx:end_idx]
        batch_clusters = cluster_list[start_idx:end_idx]

        if batch_entries:  # Only add non-empty batches
            batches.append((batch_entries, batch_clusters))

        start_idx = end_idx

    return batches


def _run_batch_for_process(args: Tuple[int, List[str], List[str], List[str], int, Path], return_dict):
    """
    Execute a batch of entries in a separate Process (not Pool worker).
    Stores result in shared dictionary.

    Args:
        args: Tuple of (process_id, entry_ids, clusters, target_languages, max_workers, script_dir)
        return_dict: Shared dictionary to store results
    """
    process_id = args[0]
    import os
    print(f"\n[DEBUG] _run_batch_for_process STARTED for Process {process_id} with PID {os.getpid()}", flush=True)
    sys.stdout.flush()

    result = _run_batch(args)
    return_dict[result[0]] = result  # Store by process_id

    print(f"[DEBUG] _run_batch_for_process COMPLETED for Process {process_id}", flush=True)
    sys.stdout.flush()


def _run_batch(args: Tuple[int, List[str], List[str], List[str], int, Path]) -> Tuple[int, bool, str]:
    """
    Execute a batch of entries in a separate process.

    Args:
        args: Tuple of (process_id, entry_ids, clusters, target_languages, max_workers, script_dir)

    Returns:
        Tuple of (process_id, success, message)
    """
    process_id, entry_ids, clusters, target_languages, max_workers, script_dir = args

    # Build language command
    lang_cmd = ", ".join(target_languages)

    # Create unique container prefix to avoid conflicts between parallel processes
    container_prefix = f"test_runner_p{process_id}"

    # Build command
    cmd = [
        "python3",
        "./run_tests_on_cluster.py",
        "--llm-only",
        "--run-quantity",
        "5",
        "--prompt-version",
        "-1",
        "--languages",
        lang_cmd,
        "--entry-ids",
    ] + entry_ids + [
        "--entry-clusters",
    ] + clusters + [
        "--max-workers", str(max_workers),
        "--container-prefix", container_prefix,
    ]

    try:
        exec_start = time.time()

        # Write to stdout immediately with flush
        msg = f"\n[Process {process_id}] Starting execution of {len(entry_ids)} entries at {time.strftime('%H:%M:%S')}..."
        print(msg, flush=True)
        sys.stdout.flush()

        print(f"[DEBUG] Process {process_id}: About to call subprocess.run() with container_prefix={container_prefix}", flush=True)
        sys.stdout.flush()

        # Run subprocess without capturing output so it goes directly to terminal
        # This allows real-time monitoring
        result = subprocess.run(
            cmd, cwd=script_dir
        )

        print(f"[DEBUG] Process {process_id}: subprocess.run() returned with code {result.returncode}", flush=True)
        sys.stdout.flush()

        exec_elapsed = time.time() - exec_start

        if result.returncode != 0:
            error_msg = f"Process {process_id}: Failed with exit code {result.returncode} after {exec_elapsed:.1f}s"
            print(error_msg, flush=True)
            return (process_id, False, error_msg)
        else:
            success_msg = f"Process {process_id}: Completed {len(entry_ids)} entries in {exec_elapsed:.1f}s ({exec_elapsed / 60:.1f} min)"
            print(f"\n✅ {success_msg}", flush=True)
            return (process_id, True, success_msg)

    except Exception as e:
        error_msg = f"Process {process_id}: Exception: {str(e)}"
        print(error_msg, flush=True)
        return (process_id, False, error_msg)


class SelectiveRerunner:
    """execute entries LLM never executed"""

    def __init__(self, target_languages=LANGUAGES, parallel_process_quantity=1):
        self.target_languages = target_languages
        self.parallel_process_quantity = parallel_process_quantity

        self.stats = {
            "before": 0,  # language -> prompt_version -> count
            "after": 0,
        }

    def execute(self, max_workers=4):  # main method
        llm_not_executed_report = find_llm_entries_not_executed()

        cluster_list = []
        entry_id_list = []

        for cluster in llm_not_executed_report.keys():
            entries_in_cluster = llm_not_executed_report[cluster]
            for entry_tuple in entries_in_cluster:
                (entry_id, _prompt_v) = entry_tuple

                if entry_id not in entry_id_list:
                    cluster_list.append(cluster)
                    entry_id_list.append(entry_id)

        # TEST only 1 cluster 1 entry :
        #cluster_list = [cluster_list[0]]
        #entry_id_list = [entry_id_list[0]]

        total = len(entry_id_list)
        assert len(cluster_list) == total

        total_exec = total * 4 * 5
        print(
            f"\n\nGoing to execute {total} LLM entries\nTotal exec quantity : {total}\nEstimated time : {2 * total_exec}s = {2 * total_exec / 60}m = {2 * total_exec / 3600}h\n"
        )

        self.stats["before"] = total

        # Determine actual number of processes to use
        num_processes = min(self.parallel_process_quantity, total)

        if num_processes <= 0:
            num_processes = 1

        print(f"Using {num_processes} parallel process(es) for execution\n")

        try:
            exec_start = time.time()

            if num_processes == 1:
                # Sequential execution (backward compatible)
                self._execute_sequential(entry_id_list, cluster_list, max_workers)
            else:
                # Parallel execution with multiple processes
                self._execute_parallel(entry_id_list, cluster_list, max_workers, num_processes)

            exec_elapsed = time.time() - exec_start

            print(
                f"\n  ✅ All processes completed in {exec_elapsed:.1f}s ({exec_elapsed / 60:.1f} min)"
            )

            self.analyze_execution()

        except Exception as e:
            print(f"❌ ERROR:\n{e}")

    def _execute_sequential(self, entry_id_list: List[str], cluster_list: List[str], max_workers: int):
        """
        Execute entries sequentially in a single process (original behavior).
        """
        # Build command using --entry-ids and --entry-clusters
        lang_cmd = ", ".join(self.target_languages)

        cmd = (
            [
                "python3",
                "./run_tests_on_cluster.py",
                "--llm-only",
                "--run-quantity",
                "5",
                "--prompt-version",
                "-1",
                "--languages",
                lang_cmd,
                "--entry-ids",
            ]
            + entry_id_list
            + ["--entry-clusters"]
            + cluster_list
            + ["--max-workers", str(max_workers)]
        )

        result = subprocess.run(
            cmd, capture_output=False, text=True, cwd=Path(__file__).parent
        )

        if result.returncode != 0:
            raise RuntimeError(f"Execution failed with exit code {result.returncode}")

    def _execute_parallel(self, entry_id_list: List[str], cluster_list: List[str], max_workers: int, num_processes: int):
        """
        Execute entries in parallel across multiple processes.

        Args:
            entry_id_list: List of all entry IDs to execute
            cluster_list: List of all clusters (1:1 mapping with entry_id_list)
            max_workers: Max workers for each process's ThreadPoolExecutor
            num_processes: Number of parallel processes to spawn
        """
        # Batch entries evenly across processes
        batches = _batch_entries(entry_id_list, cluster_list, num_processes)

        print(f"Distributing {len(entry_id_list)} entries across {len(batches)} process(es):")
        for i, (batch_entries, _) in enumerate(batches):
            print(f"  Process {i}: {len(batch_entries)} entries")
        print()

        # Prepare arguments for each process
        script_dir = Path(__file__).parent
        process_args = [
            (i, batch_entries, batch_clusters, self.target_languages, max_workers, script_dir)
            for i, (batch_entries, batch_clusters) in enumerate(batches)
        ]

        print("🚀 Launching processes in parallel...")
        print(f"⏰ Started at: {time.strftime('%Y-%m-%d %H:%M:%S')}")
        print("=" * 80)
        print()

        # Execute in parallel using multiprocessing.Process (not Pool)
        # This ensures truly independent processes
        processes = []
        manager = multiprocessing.Manager()
        return_dict = manager.dict()

        for i, (batch_entries, batch_clusters) in enumerate(batches):
            args = (i, batch_entries, batch_clusters, self.target_languages, max_workers, script_dir)
            p = multiprocessing.Process(target=_run_batch_for_process, args=(args, return_dict))
            print(f"[DEBUG] About to start Process {i}...", flush=True)
            p.start()
            print(f"[DEBUG] Process {i} p.start() called, PID={p.pid}, is_alive={p.is_alive()}", flush=True)
            processes.append((i, p))
            print(f"   ✓ Process {i} launched (PID {p.pid})", flush=True)

        print()
        print(f"⏳ All {num_processes} process(es) launched!")
        print("   Processes are running in parallel...")
        print("   (Check monitor in separate terminal to see progress)")
        print("   (Use 'ps aux | grep run_tests_on_cluster' to see active processes)")
        print()

        # Give processes a moment to spawn their subprocesses
        import time as time_module
        time_module.sleep(3)

        # Check which processes are alive
        print("\n[DEBUG] Process status after 3s sleep:")
        for process_id, p in processes:
            print(f"   Process {process_id}: PID={p.pid}, is_alive={p.is_alive()}", flush=True)
        print()

        # Now wait for all processes to complete
        print("⏱️  Waiting for all processes to complete...")
        print("   (You can monitor progress in another terminal)", flush=True)
        print()

        for process_id, p in processes:
            p.join()  # Wait for this process to finish
            print(f"   ✓ Process {process_id} completed", flush=True)

        # Collect results from shared dictionary
        results = [return_dict[i] for i in range(len(processes))]

        print("\n✅ All processes have completed!", flush=True)

        # Report results from all processes
        print("\n" + "=" * 80)
        print("PARALLEL EXECUTION RESULTS")
        print("=" * 80)

        all_successful = True
        for process_id, success, message in results:
            status = "✅" if success else "❌"
            print(f"{status} {message}")
            if not success:
                all_successful = False

        if not all_successful:
            raise RuntimeError("One or more processes failed during execution")

    def analyze_execution(self):
        """
        Analyze how many LLM entries were executed after run.
        """
        print("\n" + "=" * 80)
        print("ANALYZING LLM EXEC RESULTS")
        print("=" * 80)

        new_report = find_llm_entries_not_executed()
        cluster_list = []
        entry_id_list = []

        for cluster in new_report.keys():
            entries_in_cluster = new_report[cluster]
            for entry_tuple in entries_in_cluster:
                (entry_id, _prompt_v) = entry_tuple

                if entry_id not in entry_id_list:
                    cluster_list.append(cluster)
                    entry_id_list.append(entry_id)

        total = len(entry_id_list)
        self.stats["after"] = total

        # Save recovery report
        report_file = ANALISYS_REPORT_FILE_PATH / "llm_recovery_report.json"
        report_file.parent.mkdir(parents=True, exist_ok=True)

        recovery_data = {
            "target_languages": self.target_languages,
            "statistics": {
                "before": (self.stats["before"]),
                "after": (self.stats["after"]),
                "executed": self.stats["after"] - self.stats["before"],
            },
            # "total_failed_entries_rerun": sum(
            #    len(pv_entries)
            #    for lang_dict in self.failed_llm_by_language.values()
            #    for pv_entries in lang_dict.values()
            # ),
        }

        with open(report_file, "w") as f:
            json.dump(recovery_data, f, indent=2)

        print(f"LLM recovery report saved to: {report_file}")


def check_base_entry_pass_rate(code_entry: CodeEntry, cluster_name: str) -> bool:
    passed = 0
    for exec_num in range(1, 6):
        res_path = OUTPUT_DIR_FILEPATH / f"{cluster_name}_results_{exec_num}.json"
        if not res_path.exists():
            print(f"⚠️ path does not exist for cluster name {cluster_name}:\n{res_path}")
            return False
        content = read_json(res_path)
        for _lang, entries in content["results"].items():
            for raw_entry in entries:
                entry_res: BaseEntryResult = BaseEntryResult.from_json(raw_entry)
                if entry_res.id == code_entry.id:
                    if not entry_res.regressionTestPassed:
                        return False
                    else:
                        passed += 1

    return passed == 5


LLM_MODELS = ["openAI", "claude", "gemini"]


def check_llm_entry_has_5_exec(
    entry_id: str, cluster_name: str, prompt_v_str: str
) -> bool:
    """
    Check if ALL 3 models (openAI, claude, gemini) have 5 executions for this entry.
    Returns True only if every model appears in all 5 execution files.
    """
    # Track which models have been found in each execution file
    # model_name -> count of files where it was found for this entry
    model_file_counts = {model: 0 for model in LLM_MODELS}

    for exec_num in range(1, 6):
        related_exec_file = (
            OUTPUT_DIR_FILEPATH
            / f"{cluster_name}_results_{prompt_v_str}_{exec_num}.json"
        )

        if not related_exec_file.exists():
            return False

        content = read_json(related_exec_file)

        # Track which models are found in this specific file
        models_found_in_file = set()

        for _lang, raw_llm_results in content["results"].items():
            for llm_raw_res in raw_llm_results:
                llm_entry_results: LLMentryResult = LLMentryResult.from_json(
                    llm_raw_res
                )

                if llm_entry_results.id == entry_id:
                    # Check each LLM result to see which model it belongs to
                    for llm_res in llm_entry_results.LLM_results:
                        if llm_res.LLM_type in LLM_MODELS:
                            models_found_in_file.add(llm_res.LLM_type)

        # Update counts for models found in this file
        for model in models_found_in_file:
            model_file_counts[model] += 1

    # All 3 models must have been found in all 5 files
    return all(count == 5 for count in model_file_counts.values())


def find_llm_entries_not_executed():
    # cluster (defaultdict)
    # -> entry (base) set di prompt v

    report = defaultdict(set)

    c_paths = get_cluster_path_list(CLUSTERS_DIR_FILEPATH)
    total = len(c_paths)
    for i, cluster_path in enumerate(c_paths):
        cluster_name = str(cluster_path).split("src/clusters/")[1]
        assert "cluster_" in cluster_name and cluster_name.endswith(".json")
        cluster_name = cluster_name.removesuffix(".json")
        print(f"\nProcessing cluster {cluster_name} ({i + 1}/{total})")

        cluster_data = read_json(cluster_path)

        cluster_name = cluster_name.removeprefix(
            "cluster_"
        )  # mantain only the name, without prefix

        for _lang, entries in cluster_data.items():
            for entry in entries:
                code_entry: CodeEntry = CodeEntry.from_dict(entry)
                # check if base entry has 5/5 successfull execution
                if check_base_entry_pass_rate(code_entry, cluster_name):
                    for llm_entry in code_entry.LLMs:
                        try:
                            prompt_v = get_prompt_version_by_filename(
                                llm_entry.filename
                            )
                            prompt_v_str = f"v{prompt_v}"

                            if len(prompt_v_str) > 2:
                                print(
                                    f"WrongPrompt V str : {prompt_v_str}\nllm_entry.filename = {llm_entry.filename}"
                                )
                                continue

                            # check if llm - prompt V has 5 executions (not necessary successful)
                            if not check_llm_entry_has_5_exec(
                                code_entry.id, cluster_name, prompt_v_str
                            ):
                                report[cluster_name].add((code_entry.id, prompt_v_str))
                        except Exception as e:
                            print(f"\nFilename = {llm_entry.filename}\n")
                            raise e

    return report


def main():
    """
    Main entry point with command-line argument parsing.
    """
    parser = argparse.ArgumentParser(
        description="Run only LLM entries never executed before with optional parallel processing"
    )

    parser.add_argument(
        "--parallel-processes",
        type=int,
        default=1,
        help="Number of parallel processes to use for execution (default: 1 - sequential execution)",
    )

    parser.add_argument(
        "--max-workers",
        type=int,
        default=4,
        help="Maximum number of parallel workers per process (default: 4)",
    )

    parser.add_argument(
        "--languages",
        type=str,
        nargs="+",
        default=LANGUAGES,
        help="Target languages to execute (default: all languages)",
    )

    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Only calculate and report missing LLM entries without executing",
    )

    args = parser.parse_args()

    # Validate parallel-processes argument
    if args.parallel_processes < 1:
        print(f"Error: --parallel-processes must be >= 1, got {args.parallel_processes}")
        return 1

    print("=" * 80)
    if args.dry_run:
        print("LLM SELECTIVE RUNNER - DRY RUN MODE")
    else:
        print("LLM SELECTIVE RUNNER - PARALLEL EXECUTION MODE")
    print("=" * 80)
    print("Configuration:")
    print(f"  - Parallel processes: {args.parallel_processes}")
    print(f"  - Max workers per process: {args.max_workers}")
    print(f"  - Target languages: {', '.join(args.languages)}")
    print(f"  - Dry run: {args.dry_run}")
    print("=" * 80 + "\n")

    if args.dry_run:
        # Dry run: only calculate and report missing entries
        print("Calculating missing LLM entries (no execution)...\n")
        llm_not_executed_report = find_llm_entries_not_executed()

        # Collect unique entry_id list
        cluster_list = []
        entry_id_list = []
        total_pairs = 0

        for cluster in llm_not_executed_report.keys():
            entries_in_cluster = llm_not_executed_report[cluster]
            total_pairs += len(entries_in_cluster)
            for entry_tuple in entries_in_cluster:
                (entry_id, _prompt_v) = entry_tuple

                if entry_id not in entry_id_list:
                    cluster_list.append(cluster)
                    entry_id_list.append(entry_id)

        total_unique_entries = len(entry_id_list)

        print("\n" + "=" * 80)
        print("DRY RUN REPORT")
        print("=" * 80)
        print(f"\nTotal unique entry IDs missing executions: {total_unique_entries}")
        print(f"Total (entry_id, prompt_v) pairs missing: {total_pairs}")

        # Calculate estimated executions
        # Each pair needs 3 models × 5 executions = 15 executions
        estimated_exec = total_pairs * 3 * 5  # 3 models, 5 runs each
        print(f"\nEstimated total executions needed: {estimated_exec}")
        print(f"Estimated time (at ~2s per exec): ~{2 * estimated_exec}s = {2 * estimated_exec / 60:.1f}m = {2 * estimated_exec / 3600:.2f}h")

        # Show breakdown by cluster
        print(f"\n--- Breakdown by cluster ---")
        for cluster in sorted(llm_not_executed_report.keys()):
            entries = llm_not_executed_report[cluster]
            print(f"  {cluster}: {len(entries)} (entry_id, prompt_v) pairs")

        # Save report to file
        report_file = ANALISYS_REPORT_FILE_PATH / "llm_dry_run_report.json"
        report_file.parent.mkdir(parents=True, exist_ok=True)

        report_data = {
            "mode": "dry_run",
            "total_unique_entries": total_unique_entries,
            "total_pairs": total_pairs,
            "estimated_executions": estimated_exec,
            "clusters": {
                cluster: list(entries)
                for cluster, entries in llm_not_executed_report.items()
            },
        }

        with open(report_file, "w") as f:
            json.dump(report_data, f, indent=2, default=str)

        print(f"\nDry run report saved to: {report_file}")
        print("\nTo execute, run without --dry-run flag.")
    else:
        runner = SelectiveRerunner(
            target_languages=args.languages,
            parallel_process_quantity=args.parallel_processes
        )
        runner.execute(max_workers=args.max_workers)


if __name__ == "__main__":
    main()
