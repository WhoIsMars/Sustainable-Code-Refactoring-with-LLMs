# Pass Rate Analysis Summary Report

This report summarizes the pass rate analysis for Thesis Section 4.1.

## Global Statistics

- **Base Code Mean Pass Rate**: 100.00%
- **LLM Aggregated Mean Pass Rate**: 94.21%
- **Overall Degradation**: -5.79%

## Pass Rate by Language

| Language | Base Code | LLM Aggregated | Degradation |
|----------|-----------|----------------|-------------|
| C | 100.00% | 84.43% | -15.57% |
| C++ | 100.00% | 69.59% | -30.41% |
| Go | 100.00% | 98.89% | -1.11% |
| Java | 100.00% | 84.51% | -15.49% |
| Python | 100.00% | 90.59% | -9.41% |
| JavaScript | 100.00% | 82.59% | -17.41% |
| TypeScript | 100.00% | 97.46% | -2.54% |

## Pass Rate by Model

| Model | Mean Pass Rate |
|-------|----------------|
| OpenAI | 93.31% |
| Claude | 94.11% |
| Gemini | 95.47% |

## Pass Rate by Prompt Version

| Prompt Version | Mean Pass Rate |
|----------------|----------------|
| V1 | 93.10% |
| V2 | 94.78% |
| V3 | 94.45% |
| V4 | 94.52% |

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

