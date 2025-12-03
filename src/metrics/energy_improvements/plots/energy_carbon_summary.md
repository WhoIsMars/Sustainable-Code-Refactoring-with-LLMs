# Energy and Carbon Footprint Analysis Report
**Generated:** energy_improvements
---

## Global Statistics

### Base Code

| Metric | Mean | Median | Std | Min | Max | Count |
|--------|------|--------|-----|-----|-----|-------|
| Energy (J) | 166.45 | 8.95 | 353.11 | 0.04 | 2001.94 | 2338 |
| Carbon (gCO2eq) | 0.0185 | 0.0010 | 0.0392 | 0.0000 | 0.2224 | 2338 |

### LLM-Generated Code

| Metric | Mean | Median | Std | Min | Max | Count |
|--------|------|--------|-----|-----|-----|-------|
| Energy (J) | 101.36 | 20.44 | 1521.48 | 0.04 | 113048.83 | 26711 |
| Carbon (gCO2eq) | 0.0113 | 0.0023 | 0.1691 | 0.0000 | 12.5610 | 26711 |

### Improvements (LLM vs Base)

| Metric | Mean | Median | Std | Min | Max |
|--------|------|--------|-----|-----|-----|
| Energy Improvement (%) | 1071.52 | -6.22 | 10112.73 | -99.78 | 165751.68 |
| Carbon Improvement (%) | 1071.52 | -6.22 | 10112.73 | -99.78 | 165751.68 |

**Note:** Negative improvement indicates reduction (better for sustainability).

## Results by LLM Model

| Model | Energy Mean (J) | Carbon Mean (gCO2eq) | Energy Impr (%) | Carbon Impr (%) |
|-------|-----------------|----------------------|-----------------|------------------|
| openAI | 98.61 | 0.0110 | 1139.09 | 1139.09 |
| claude | 82.80 | 0.0092 | 985.91 | 985.91 |
| gemini | 123.27 | 0.0137 | 1094.55 | 1094.55 |

## Results by Prompt Version

| Prompt | Energy Mean (J) | Carbon Mean (gCO2eq) | Energy Impr (%) | Carbon Impr (%) |
|--------|-----------------|----------------------|-----------------|------------------|
| v1 | 99.80 | 0.0111 | 836.16 | 836.16 |
| v2 | 136.63 | 0.0152 | 1080.97 | 1080.97 |
| v3 | 102.11 | 0.0113 | 1219.23 | 1219.23 |
| v4 | 67.53 | 0.0075 | 1150.08 | 1150.08 |

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
