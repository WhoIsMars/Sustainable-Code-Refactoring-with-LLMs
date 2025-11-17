# Pass Rate Analysis Summary Report

This report summarizes the pass rate analysis for Thesis Section 4.1.

## Global Statistics

- **Base Code Mean Pass Rate**: 100.00%
- **LLM Aggregated Mean Pass Rate**: 93.56%
- **Overall Degradation**: -6.44%

## Pass Rate by Language

| Language | Base Code | LLM Aggregated | Degradation |
|----------|-----------|----------------|-------------|
| C | 100.00% | 85.03% | -14.97% |
| C++ | 100.00% | 78.07% | -21.93% |
| Go | 100.00% | 98.89% | -1.11% |
| Java | 100.00% | 84.51% | -15.49% |
| Python | 100.00% | 90.59% | -9.41% |
| JavaScript | 100.00% | 59.46% | -40.54% |
| TypeScript | 100.00% | 97.43% | -2.57% |

## Pass Rate by Model

| Model | Mean Pass Rate |
|-------|----------------|
| OpenAI | 93.49% |
| Claude | 93.56% |
| Gemini | 93.66% |

## Pass Rate by Prompt Version

| Prompt Version | Mean Pass Rate |
|----------------|----------------|
| V1 | 95.61% |
| V2 | 95.56% |
| V3 | 91.42% |
| V4 | 91.67% |

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

