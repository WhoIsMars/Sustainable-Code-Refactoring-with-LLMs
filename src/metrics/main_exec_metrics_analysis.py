"""
Main script per l'analisi delle metriche di esecuzione.
Calcola e visualizza statistiche aggregate su tutto il dataset.
"""

import sys
import os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
from utility_dir import general_utils
import logging

# Try relative imports first, fallback to absolute
try:
    from .exec_metrics_calculator import ExecMetricCalculator
    from .execMetricStatsVisualizator import ExecMetricStatsVisualizator
    from .pass_rate_analyzer import PassRateAnalyzer
    from .pass_rate_visualizator import PassRateVisualizator
except ImportError:
    # Fallback for direct execution
    from exec_metrics_calculator import ExecMetricCalculator
    from execMetricStatsVisualizator import ExecMetricStatsVisualizator
    from pass_rate_analyzer import PassRateAnalyzer
    from pass_rate_visualizator import PassRateVisualizator


def main():
    """Main function per eseguire l'analisi completa aggregata."""

    # Setup logging
    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s - %(name)s - %(levelname)s - %(message)s",
        handlers=[
            logging.FileHandler("exec_metrics_analysis.log"),
            logging.StreamHandler()
        ]
    )
    logger = logging.getLogger(__name__)

    logger.info("=" * 80)
    logger.info("Starting Cross-Cluster Execution Metrics Analysis")
    logger.info("=" * 80)

    try:
        # Inizializza il calcolatore
        calculator = ExecMetricCalculator(
            logger_level=general_utils.LoggerLevel.INFO
        )
        logger.info("Calculator initialized")

        # Aggrega tutti i dati da tutti i cluster
        logger.info("Aggregating data across all clusters...")
        aggregated_data = calculator.aggregate_across_clusters()

        # Inizializza il visualizzatore
        visualizator = ExecMetricStatsVisualizator()
        logger.info(f"Visualizator initialized. Output dir: {visualizator.output_dir}")

        # Visualizza tutte le statistiche
        logger.info("Generating visualizations...")
        visualizator.visualize_all_objectives(aggregated_data)

        # Crea summary report
        visualizator.create_summary_report(aggregated_data)

        # === NEW: Pass Rate Analysis (Section 4.1) ===
        logger.info("\n" + "=" * 80)
        logger.info("Starting Pass Rate Analysis (Section 4.1)")
        logger.info("=" * 80)

        try:
            # Initialize pass rate analyzer
            pass_rate_analyzer = PassRateAnalyzer()
            logger.info("Pass rate analyzer initialized")

            # Run pass rate analysis
            logger.info("Analyzing pass rates across all clusters...")
            pass_rate_data = pass_rate_analyzer.aggregate_across_clusters()

            # Save pass rate results
            pass_rate_analyzer.save_results()

            # Print pass rate summary
            pass_rate_analyzer.print_summary()

            # Initialize pass rate visualizator
            pass_rate_visualizator = PassRateVisualizator()
            logger.info("Pass rate visualizator initialized")

            # Generate pass rate visualizations
            logger.info("Generating pass rate visualizations...")
            pass_rate_visualizator.generate_all_visualizations()

            # Generate pass rate summary report
            pass_rate_visualizator.generate_summary_report()

            logger.info("✓ Pass rate analysis completed successfully!")
            logger.info(f"Pass rate plots saved to: {pass_rate_visualizator.output_dir}")

        except Exception as e:
            logger.error(f"Error during pass rate analysis: {e}", exc_info=True)
            logger.warning("Continuing with main analysis despite pass rate analysis error")

        logger.info("=" * 80)
        logger.info("Analysis completed successfully!")
        logger.info(f"Statistics saved to: {calculator.stats_output_dir}")
        logger.info(f"Plots saved to: {visualizator.output_dir}")
        logger.info("=" * 80)

        # Print summary
        print("\n" + "=" * 80)
        print("SUMMARY")
        print("=" * 80)

        for objective_name in ["objective_1", "objective_2", "objective_3", "objective_4"]:
            if objective_name in aggregated_data:
                print(f"\n{objective_name.upper().replace('_', ' ')}:")

                if objective_name == "objective_1":
                    print("  - Metrics aggregated by prompt version")
                    base_count = len(aggregated_data[objective_name].get("base", {}).get("pass_rate", []))
                    print(f"  - Base code entries: {base_count}")

                elif objective_name == "objective_2":
                    print("  - Metrics aggregated by programming language")
                    base_langs = len(aggregated_data[objective_name].get("base_by_language", {}))
                    llm_langs = len(aggregated_data[objective_name].get("llm_by_language", {}))
                    print(f"  - Base code languages: {base_langs}")
                    print(f"  - LLM code languages: {llm_langs}")

                elif objective_name == "objective_3":
                    print("  - Metrics aggregated by model + prompt version")
                    combos = len(aggregated_data[objective_name].get("model_version_stats", {}))
                    print(f"  - Model-version combinations: {combos}")
                    print("  - Improvement percentages calculated")

                elif objective_name == "objective_4":
                    print("  - Metrics aggregated by language + model")
                    combos = len(aggregated_data[objective_name].get("language_model_stats", {}))
                    print(f"  - Language-model combinations: {combos}")

        print("\n" + "=" * 80)
        print("Visualizations created in:")
        print(f"  - {visualizator.output_dir / 'metrics_means_related_to_prompt_versions'}")
        print(f"  - {visualizator.output_dir / 'metrics_means_related_to_languages'}")
        print(f"  - {visualizator.output_dir / 'metrics_means_related_to_both_model_and_prompt_version'}")
        print(f"  - {visualizator.output_dir / 'metrics_means_related_to_language_and_model'}")
        print("\nSummary report: " + str(visualizator.output_dir / "summary_report.md"))
        print("=" * 80 + "\n")

        return aggregated_data

    except Exception as e:
        logger.error(f"Error during analysis: {e}", exc_info=True)
        raise


def test_single_cluster():
    """Test function per testare l'analisi su un singolo cluster."""

    logging.basicConfig(level=logging.DEBUG)
    logger = logging.getLogger(__name__)

    logger.info("Testing with single cluster")

    calculator = ExecMetricCalculator(
        logger_level=general_utils.LoggerLevel.DEBUG
    )

    # Test loading and extraction for a single cluster
    cluster_name = "accumulate"

    logger.info(f"Testing data loading for cluster: {cluster_name}")
    base_results, llm_results = calculator.load_execution_results(cluster_name)

    print(f"\nBase results found: {len(base_results)} executions")
    print(f"LLM results found: {len(llm_results)} prompt versions")

    # Test extraction
    if base_results:
        first_exec = list(base_results.values())[0]
        extracted = calculator.extract_metrics_from_base_result(first_exec)
        print(f"\nBase entries extracted: {len(extracted)}")
        if extracted:
            sample_key = list(extracted.keys())[0]
            print(f"Sample entry: {sample_key}")
            print(f"  Language: {extracted[sample_key]['language']}")
            print(f"  Passed: {extracted[sample_key]['passed']}")
            print(f"  Metrics: {extracted[sample_key]['metrics']}")

    logger.info("Single cluster test completed")


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(
        description="Execution Metrics Analysis Tool - Cross-Cluster Aggregation"
    )
    parser.add_argument(
        "--test",
        action="store_true",
        help="Run test mode with single cluster"
    )
    parser.add_argument(
        "--cluster",
        type=str,
        default="accumulate",
        help="Specify a cluster name for test mode (default: accumulate)"
    )

    args = parser.parse_args()

    if args.test:
        test_single_cluster()
    else:
        main()
