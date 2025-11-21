# Pass Rate Analysis Summary Report

This report summarizes the pass rate analysis for Thesis Section 4.1.

## Global Statistics

- **Base Code Mean Pass Rate**: 100.00%
- **LLM Aggregated Mean Pass Rate**: 90.52%
- **Overall Degradation**: -9.48%

## Pass Rate by Language

| Language | Base Code | LLM Aggregated | Degradation |
|----------|-----------|----------------|-------------|
| C | 100.00% | 83.92% | -16.08% |
| C++ | 100.00% | 71.22% | -28.78% |
| Go | 100.00% | 98.18% | -1.82% |
| Java | 100.00% | 91.37% | -8.63% |
| Python | 100.00% | 94.60% | -5.40% |
| JavaScript | 100.00% | 75.49% | -24.51% |
| TypeScript | 100.00% | 95.44% | -4.56% |

## Pass Rate by Model

| Model | Mean Pass Rate |
|-------|----------------|
| OpenAI | 90.13% |
| Claude | 91.42% |
| Gemini | 89.99% |

## Pass Rate by Prompt Version

| Prompt Version | Mean Pass Rate |
|----------------|----------------|
| V1 | 90.55% |
| V2 | 91.23% |
| V3 | 89.90% |
| V4 | 90.39% |

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

