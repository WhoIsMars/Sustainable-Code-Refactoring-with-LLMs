# Energy and Carbon Footprint Analysis Report
**Generated:** energy_improvements
---

## Global Statistics

### Base Code

| Metric | Mean | Median | Std | Min | Max | Count |
|--------|------|--------|-----|-----|-----|-------|
| Energy (J) | 192.97 | 16.60 | 313.60 | 0.04 | 2697.36 | 719 |
| Carbon (gCO2eq) | 0.0214 | 0.0018 | 0.0348 | 0.0000 | 0.2997 | 719 |

### LLM-Generated Code

| Metric | Mean | Median | Std | Min | Max | Count |
|--------|------|--------|-----|-----|-----|-------|
| Energy (J) | 144.68 | 71.29 | 2091.70 | 0.02 | 113048.83 | 13940 |
| Carbon (gCO2eq) | 0.0161 | 0.0079 | 0.2324 | 0.0000 | 12.5610 | 13940 |

### Improvements (LLM vs Base)

| Metric | Mean | Median | Std | Min | Max |
|--------|------|--------|-----|-----|-----|
| Energy Improvement (%) | 2106.38 | -39.74 | 38805.19 | -98.97 | 1256838.92 |
| Carbon Improvement (%) | 2106.38 | -39.74 | 38805.19 | -98.97 | 1256838.92 |

**Note:** Negative improvement indicates reduction (better for sustainability).

## Results by LLM Model

| Model | Energy Mean (J) | Carbon Mean (gCO2eq) | Energy Impr (%) | Carbon Impr (%) |
|-------|-----------------|----------------------|-----------------|------------------|
| openAI | 137.65 | 0.0153 | 1975.78 | 1975.78 |
| claude | 109.51 | 0.0122 | 1092.25 | 1092.25 |
| gemini | 187.12 | 0.0208 | 3250.29 | 3250.29 |

## Results by Prompt Version

| Prompt | Energy Mean (J) | Carbon Mean (gCO2eq) | Energy Impr (%) | Carbon Impr (%) |
|--------|-----------------|----------------------|-----------------|------------------|
| v1 | 144.58 | 0.0161 | 584.16 | 584.16 |
| v2 | 193.30 | 0.0215 | 4451.35 | 4451.35 |
| v3 | 149.56 | 0.0166 | 2690.20 | 2690.20 |
| v4 | 83.54 | 0.0093 | 777.41 | 777.41 |

## Visualizations

### Energy and Carbon Distribution

![Energy Distribution](energy_distribution_boxplot.png)

![Carbon Distribution](carbon_distribution_boxplot.png)

### Analysis by Prompt Version

![Energy by Prompt](energy_by_prompt_version_barplot.png)

![Carbon by Prompt](carbon_by_prompt_version_barplot.png)

### Analysis by Model

![Energy by Model](energy_by_model_barplot.png)

![Carbon by Model](carbon_by_model_barplot.png)

### Analysis by Programming Language

![Energy by Language](energy_by_language_boxplot.png)

![Carbon by Language](carbon_by_language_boxplot.png)

---

## Methodology

### Energy Calculation Formula

```
1. exec_time_sec = exec_time_ms / 1000
2. cpu_power_watt = TDP_CPU * (CPU_usage% / 100)
3. ram_power_watt = (RAM_KB / 1048576) * POWER_PER_GB_RAM
4. total_power = (cpu_power + ram_power) * PUE_FACTOR
5. energy_joules = total_power * exec_time_sec
```

### Carbon Calculation Formula

```
1. energy_kwh = energy_joules / 3,600,000
2. carbon_gco2eq = energy_kwh * CARBON_INTENSITY
```

### Coefficients Used

- **TDP_CPU_WATT:** 95.0 W (typical desktop CPU)
- **POWER_PER_GB_RAM_WATT:** 0.375 W/GB (DDR4 average)
- **PUE_FACTOR:** 1.5 (data center efficiency)
- **CARBON_INTENSITY:** 400.0 gCO2eq/kWh (EU average)

**Note:** These values are configurable in `energy_config.json`.
