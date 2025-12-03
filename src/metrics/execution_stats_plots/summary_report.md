# Execution Metrics Analysis Report

**Generated:** 2025-12-03 21:45:57

## Overview

This report summarizes execution metrics aggregated across all clusters.

**IMPORTANT**: Base code entries are filtered to include ONLY those with 100% pass rate across all 5 executions.

### Objective 1

**Metrics by Prompt Version**

- Base code entries (100% pass rate): 2338
- Prompt versions analyzed: v1, v2, v3, v4

### Objective 2

**Metrics by Programming Language**

- Languages (base code): python, cpp, java, typescript, go, javascript, c
- Languages (LLM code): python, java, cpp, javascript, typescript, c, go

### Objective 3

**Metrics by Model + Prompt Version**

- Model combinations analyzed: 12
- Improvement percentages calculated
- **Improvement interpretation**:
  - For ALL metrics: **Positive (+) is GOOD** (improvement), **Negative (-) is BAD** (degradation)
  - Formula inverted in calculator: CPU/RAM/Time improvements show as positive percentages

### Objective 4

**Metrics by Language + Model**

- Language-model combinations analyzed: 21

## Visualization Files

All plots are saved in subdirectories within `execution_stats_plots/`:

### Box Plots (show distribution and variance)
- `metrics_means_related_to_prompt_versions/`
- `metrics_means_related_to_languages/`
- `metrics_means_related_to_both_model_and_prompt_version/`
- `metrics_means_related_to_language_and_model/`

### Bar Plots (show mean comparisons)
- Available in same directories with `_barplot.png` suffix

### Scatter Plots (show base vs LLM comparison)
- Available in language metrics directory

## Metrics

The following metrics are analyzed:

- **CPU Usage (%)**: CPU utilization during execution
- **RAM Usage (KB)**: Memory consumption
- **Execution Time (ms)**: Time taken to execute tests
- **Pass Rate (%)**: Percentage of tests passed
- **Energy Consumption (J)**: Total energy in Joules (calculated from CPU, RAM, time with TDP/PUE factors)

## Data Filtering

**Base Code**: Only entries with 100% pass rate (across all 5 executions) are included.

This ensures we compare LLM-generated code against known-good baseline implementations.

## Notes

- All plots use box plots to show data distribution and variance
- Red dashed line indicates mean value
- Outliers are shown but axis limits are adjusted for clarity
- For improvement percentages (Objective 3):
  - **Positive (+) values are GOOD** for ALL metrics (improvement)
  - **Negative (-) values are BAD** for ALL metrics (degradation)
  - Green text = improvement, Red text = degradation
  - Formula inverted in calculator: reductions in CPU/RAM/Time show as positive %
