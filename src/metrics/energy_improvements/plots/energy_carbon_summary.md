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
| Energy (J) | 136.62 | 71.29 | 2022.35 | 0.02 | 113048.83 | 14916 |
| Carbon (gCO2eq) | 0.0152 | 0.0079 | 0.2247 | 0.0000 | 12.5610 | 14916 |

### Improvements (LLM vs Base)

| Metric | Mean | Median | Std | Min | Max |
|--------|------|--------|-----|-----|-----|
| Energy Improvement (%) | 2014.23 | -37.93 | 37952.59 | -98.97 | 1256838.92 |
| Carbon Improvement (%) | 2014.23 | -37.93 | 37952.59 | -98.97 | 1256838.92 |

**Note:** Negative improvement indicates reduction (better for sustainability).

## Results by LLM Model

| Model | Energy Mean (J) | Carbon Mean (gCO2eq) | Energy Impr (%) | Carbon Impr (%) |
|-------|-----------------|----------------------|-----------------|------------------|
| openAI | 129.74 | 0.0144 | 1892.77 | 1892.77 |
| claude | 103.33 | 0.0115 | 1039.64 | 1039.64 |
| gemini | 177.44 | 0.0197 | 3116.12 | 3116.12 |

## Results by Prompt Version

| Prompt | Energy Mean (J) | Carbon Mean (gCO2eq) | Energy Impr (%) | Carbon Impr (%) |
|--------|-----------------|----------------------|-----------------|------------------|
| v1 | 144.58 | 0.0161 | 584.16 | 584.16 |
| v2 | 193.30 | 0.0215 | 4451.35 | 4451.35 |
| v3 | 132.64 | 0.0147 | 2447.69 | 2447.69 |
| v4 | 75.41 | 0.0084 | 707.70 | 707.70 |

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
