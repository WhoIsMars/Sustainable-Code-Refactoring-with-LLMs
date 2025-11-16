# Pass Rate Analysis Summary Report

This report summarizes the pass rate analysis for Thesis Section 4.1.

## Global Statistics

- **Base Code Mean Pass Rate**: 100.00%
- **LLM Aggregated Mean Pass Rate**: 90.86%
- **Overall Degradation**: -9.14%

## Pass Rate by Language

| Language | Base Code | LLM Aggregated | Degradation |
|----------|-----------|----------------|-------------|
| C | 100.00% | 81.25% | -18.75% |
| C++ | 100.00% | 78.07% | -21.93% |
| Go | 100.00% | 99.60% | -0.40% |
| Java | 100.00% | 86.83% | -13.17% |
| Python | 100.00% | 91.71% | -8.29% |
| JavaScript | 100.00% | 49.01% | -50.99% |
| TypeScript | 100.00% | 97.89% | -2.11% |

## Pass Rate by Model

| Model | Mean Pass Rate |
|-------|----------------|
| OpenAI | 93.00% |
| Claude | 89.39% |
| Gemini | 89.18% |

## Pass Rate by Prompt Version

| Prompt Version | Mean Pass Rate |
|----------------|----------------|
| V1 | 95.41% |
| V2 | 94.38% |
| V3 | 86.51% |
| V4 | 87.14% |

## Generated Visualizations

### 4.1.A - Overview Graphs

1. `language_pass_rate_aggregated.png` - Pass rate by language (LLM aggregated)
2. `language_pass_rate_by_model.png` - Pass rate by language and model

### 4.1.B - Drill-down Graphs

28 individual graphs organized by prompt version:

- `language_pass_rate/v1/` - 7 language-specific graphs for V1
- `language_pass_rate/v2/` - 7 language-specific graphs for V2
- `language_pass_rate/v3/` - 7 language-specific graphs for V3
- `language_pass_rate/v4/` - 7 language-specific graphs for V4

