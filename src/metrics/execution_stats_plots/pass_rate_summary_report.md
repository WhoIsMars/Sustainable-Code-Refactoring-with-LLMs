# Pass Rate Analysis Summary Report

This report summarizes the pass rate analysis for Thesis Section 4.1.

## Global Statistics

- **Base Code Mean Pass Rate**: 100.00%
- **LLM Aggregated Mean Pass Rate**: 86.33%
- **Overall Degradation**: -13.67%

## Pass Rate by Language

| Language | Base Code | LLM Aggregated | Degradation |
|----------|-----------|----------------|-------------|
| C | 100.00% | 83.67% | -16.33% |
| C++ | 100.00% | 64.69% | -35.31% |
| Go | 100.00% | 95.28% | -4.72% |
| Java | 100.00% | 91.00% | -9.00% |
| Python | 100.00% | 88.17% | -11.83% |
| JavaScript | 100.00% | 84.88% | -15.12% |
| TypeScript | 100.00% | 92.12% | -7.88% |

## Pass Rate by Model

| Model | Mean Pass Rate |
|-------|----------------|
| OpenAI | 83.90% |
| Claude | 89.05% |
| Gemini | 86.05% |

## Pass Rate by Prompt Version

| Prompt Version | Mean Pass Rate |
|----------------|----------------|
| V1 | 86.83% |
| V2 | 85.41% |
| V3 | 86.55% |
| V4 | 86.55% |

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

