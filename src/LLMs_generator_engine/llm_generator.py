import os
import json
import time
import sys

# Aggiungi la directory parent (src) al path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))

from utility_dir import utility_paths
from LLMs_generator_engine.api import gemini_api_gestor, claude_api_gestor, openai_api_gestor
from discordInteraction import DiscordWebhookReporter
from dotenv import load_dotenv
from datetime import datetime
import atexit

clusters_already_processed = []

clusters_not_completed = []

clusters_not_processed = []

prompt_file_paths = [
    utility_paths.PROMPTS_DIR_FILEPATH / "promptV1.txt",
    utility_paths.PROMPTS_DIR_FILEPATH / "promptV2.txt",
    utility_paths.PROMPTS_DIR_FILEPATH / "promptV3.txt",
    utility_paths.PROMPTS_DIR_FILEPATH / "promptV4.txt",
]


# Note: atexit handler removed - status is checked explicitly in main if needed


class LLMGenerator:
    def __init__(self, languages=None):
        """
        Initialize LLM Generator.

        Args:
            languages: List of language codes to process (e.g., ['cpp', 'python']).
                      If None, all languages are processed.
        """
        load_dotenv()
        WEBHOOK_URL = os.getenv("DISCORD_WEBHOOK")
        print(f"WEBHOOK_URL = {WEBHOOK_URL}")
        if not WEBHOOK_URL:
            raise Exception("missing WEBHOOK_URL")
        self.reporter = DiscordWebhookReporter(WEBHOOK_URL, "LLM Generation Bot")
        self.languages = languages  # None means all languages

    def generate_llms_files_for_chosen_clusters(self):
        gemini_api_g = gemini_api_gestor.GeminiAIApiGestor()
        claude_api_g = claude_api_gestor.ClaudeApiGestor()
        openai_api_g = openai_api_gestor.OpenAIApiGestor()

        try:
            for cluster_name in os.listdir(
                utility_paths.CLUSTERS_DIR_FILEPATH
            ):  # itera i clusters
                if (
                    cluster_name in clusters_already_processed
                    or "with_metrics" in cluster_name
                    or "debug_" in cluster_name
                    or "focused_" in cluster_name
                    or "bad_entries" in cluster_name
                ):
                    continue
                cluster_name = cluster_name.replace("cluster_", "").removesuffix(
                    ".json"
                )
                if (
                    cluster_name in clusters_already_processed
                    # or cluster_name in clusters_not_completed
                ):
                    continue
                else:
                    print(f"\n- Generating LLMs files for cluster {cluster_name}\n")

                    file_name = f"cluster_{cluster_name}.json"
                    cluster_path = utility_paths.CLUSTERS_DIR_FILEPATH / file_name

                    json_file_content = None
                    with open(cluster_path, "r", encoding="utf-8") as f:
                        json_file_content = json.load(f)

                    if not json_file_content:
                        raise Exception(
                            f"json file content is none for file path : {cluster_path}"
                        )

                    total_expected_files = 0
                    total_generated_files = 0
                    start_time = time.time()

                    for language, entries in json_file_content.items():
                        # Skip if language filter is set and this language is not in the list
                        if self.languages and language not in self.languages:
                            print(f"⏭️  Skipping language '{language}' (not in filter: {self.languages})")
                            continue

                        print(f"\n📝 Processing language: {language}")
                        time.sleep(2)
                        for entry in entries:  # itera le entries
                            for prompt_v, prompt_path in enumerate(
                                prompt_file_paths, start=1
                            ):
                                code_file_path = (
                                    utility_paths.DATASET_DIR
                                    / entry["codeSnippetFilePath"]
                                )
                                parts = str(entry["codeSnippetFilePath"]).split("/")
                                dir_name = str(parts[0]) + "/" + str(parts[1])
                                exercise_dir_filepath = (
                                    utility_paths.DATASET_DIR / dir_name
                                )
                                filename = entry["filename"]
                                if language == "c" or language == "cpp":
                                    code_file_path = code_file_path / filename

                                # Ogni modello dovrebbe generare 1 file
                                total_expected_files += 3

                                print(
                                    f"📄 [{cluster_name}] Generating for `{filename}` | Prompt v{prompt_v}"
                                )

                                for model_name, generator in {
                                    "OpenAI": openai_api_g,
                                    "Claude": claude_api_g,
                                    "Gemini": gemini_api_g,
                                }.items():
                                    success = (
                                        generator.generate_and_save_LLM_code_by_files(
                                            prompt_path,
                                            code_file_path,
                                            exercise_dir_filepath,
                                            prompt_v,
                                            filename,
                                        )
                                    )

                                    if success:
                                        total_generated_files += 1
                                        print(
                                            f"   ✅ {model_name} generation successful"
                                        )
                                    else:
                                        print(f"   ❌ {model_name} generation failed")

                                time.sleep(0.5)

                    duration = time.time() - start_time
                    percent = (
                        (total_generated_files / total_expected_files * 100)
                        if total_expected_files
                        else 0
                    )

                    print(
                        f"\n📊 Cluster {cluster_name} complete: {total_generated_files}/{total_expected_files} files ({percent:.1f}%)\n"
                    )

                    # Invia webhook Discord
                    self.reporter.send_file_generation_report(
                        cluster_name=cluster_name,
                        generated_files=total_generated_files,
                        expected_files=total_expected_files,
                        additional_info={
                            "Duration": f"{duration:.1f}s",
                            "Timestamp": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
                        },
                        custom_message=f"📦 Generazione file per cluster `{cluster_name}` completata!",
                    )

                    if (
                        percent >= 99.99
                        or total_generated_files == total_expected_files
                    ):
                        clusters_already_processed.append(cluster_name)
                    elif percent > 0:
                        clusters_not_completed.append(cluster_name)

                    else:
                        clusters_not_processed.append(cluster_name)

        except Exception as e:
            print(f"❌ Exception in generate_llms_files_for_chosen_clusters:\n{e}")
            self.reporter.send_simple_message(
                f"❌ Errore durante la generazione dei file: {e}"
            )

    def check_status(self):
        for cluster_name in clusters_not_completed:
            if cluster_name in clusters_already_processed:
                clusters_not_completed.remove(cluster_name)

        for cluster_name in clusters_not_processed:
            if cluster_name in clusters_already_processed:
                clusters_not_processed.remove(cluster_name)

        entries_to_process = 0
        for cluster_name in os.listdir(
            utility_paths.CLUSTERS_DIR_FILEPATH
        ):  # itera i clusters
            if (
                cluster_name in clusters_already_processed
                or "with_metrics" in cluster_name
                or "debug_" in cluster_name
                or "focused_" in cluster_name
                or "bad_entries" in cluster_name
            ):
                continue
            cluster_name = cluster_name.replace("cluster_", "").removesuffix(".json")
            if cluster_name in clusters_already_processed:
                continue

            else:
                print(f"\n- Checking status for cluster {cluster_name}\n")

                file_name = f"cluster_{cluster_name}.json"
                cluster_path = utility_paths.CLUSTERS_DIR_FILEPATH / file_name

                json_file_content = None
                with open(cluster_path, "r", encoding="utf-8") as f:
                    json_file_content = json.load(f)

                if json_file_content:
                    total_cluster_entries = 0
                    processed = 0
                    partially_processed = 0
                    NOT_processed = 0

                    for _language, entries in json_file_content.items():
                        # Skip if language filter is set and this language is not in the list
                        if self.languages and _language not in self.languages:
                            continue

                        total_cluster_entries += len(entries)

                        for i, entry in enumerate(entries):
                            if len(entry["LLMs"]) == 12:
                                # print(f"🟢 entry {entry['id']} with all 12 LLMs files | {i}/{total_cluster_entries} | cluster = {cluster_name}")
                                processed += 1
                            elif len(entry["LLMs"]) > 0:
                                # print(f"🟡 entry {entry['id']} with all > 0 LLMs files | {i}/{total_cluster_entries} | cluster = {cluster_name} added to cluster not completed")
                                partially_processed += 1
                            else:
                                # print(f"🔴 entry {entry['id']} with all 12 LLMs files | {i}/{total_cluster_entries} | cluster = {cluster_name}")
                                NOT_processed += 1

                    print(
                        f"Cluster {cluster_name}:\nprocessed : {processed}/{total_cluster_entries}\nNOT_processed : {NOT_processed}/{total_cluster_entries}\npartially_processed : {partially_processed}/{total_cluster_entries}\n\n"
                    )
                    if processed == total_cluster_entries:
                        clusters_already_processed.append(cluster_name)
                    elif NOT_processed == total_cluster_entries:
                        clusters_not_processed.append(cluster_name)
                        entries_to_process += NOT_processed
                    else:
                        clusters_not_completed.append(cluster_name)

        m1 = f"\nclusters not processed : {len(clusters_not_processed)}"

        m2 = f"\nclusters not completed : {len(clusters_not_completed)}"

        m3 = f"\nclusters processed : {len(clusters_already_processed)}"

        msg = f"Generation by LLMs status:\n{m1}\n{m2}\n{m3}"

        self.reporter.send_simple_message(msg)

        print(m1 + f"\n\n{clusters_not_processed}")
        print(m2 + f"\n\n{clusters_not_completed}")
        print(m3 + f"\n\n{clusters_already_processed}")

        print(
            f"\nTotal entries to processed : {entries_to_process}\nEstimated $ : {entries_to_process * 0.02} $"
        )


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(
        description="Generate LLM code improvements for cluster entries",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Generate for all languages in all clusters
  python llm_generator.py

  # Generate only for CPP entries
  python llm_generator.py --languages cpp

  # Generate for CPP and Python entries
  python llm_generator.py --languages cpp python

  # Check status only
  python llm_generator.py --check-status

  # Check status for CPP only
  python llm_generator.py --check-status --languages cpp
        """
    )

    parser.add_argument(
        '--languages',
        nargs='+',
        choices=['c', 'cpp', 'go', 'java', 'python', 'javascript', 'typescript', 'rust'],
        help='Filter by programming language(s). If not specified, all languages are processed.'
    )

    parser.add_argument(
        '--check-status',
        action='store_true',
        help='Only check generation status without generating new files'
    )

    args = parser.parse_args()

    # Create generator with language filter
    generator = LLMGenerator(languages=args.languages)

    if args.languages:
        print(f"\n🎯 Language filter enabled: {args.languages}")
    else:
        print("\n🌍 Processing all languages")

    if args.check_status:
        print("\n📊 Checking status only...\n")
        generator.check_status()
    else:
        print("\n🚀 Starting LLM code generation...\n")
        generator.generate_llms_files_for_chosen_clusters()
