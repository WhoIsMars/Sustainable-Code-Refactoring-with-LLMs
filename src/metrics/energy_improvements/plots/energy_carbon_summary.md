# Energy and Carbon Footprint Analysis Report
**Generated:** energy_improvements
---

## Global Statistics

### Base Code

| Metric | Mean | Median | Std | Min | Max | Count |
|--------|------|--------|-----|-----|-----|-------|
| Energy (J) | 258.61 | 38.27 | 418.54 | 0.04 | 2001.94 | 1467 |
| Carbon (gCO2eq) | 0.0287 | 0.0043 | 0.0465 | 0.0000 | 0.2224 | 1467 |

### LLM-Generated Code

| Metric | Mean | Median | Std | Min | Max | Count |
|--------|------|--------|-----|-----|-----|-------|
| Energy (J) | 115.00 | 71.29 | 1840.06 | 0.02 | 113048.83 | 18030 |
| Carbon (gCO2eq) | 0.0128 | 0.0079 | 0.2045 | 0.0000 | 12.5610 | 18030 |

### Improvements (LLM vs Base)

| Metric | Mean | Median | Std | Min | Max |
|--------|------|--------|-----|-----|-----|
| Energy Improvement (%) | 2701.76 | -29.99 | 15498.25 | -99.87 | 165751.68 |
| Carbon Improvement (%) | 2701.76 | -29.99 | 15498.25 | -99.87 | 165751.68 |

**Note:** Negative improvement indicates reduction (better for sustainability).

## Results by LLM Model

| Model | Energy Mean (J) | Carbon Mean (gCO2eq) | Energy Impr (%) | Carbon Impr (%) |
|-------|-----------------|----------------------|-----------------|------------------|
| openAI | 109.22 | 0.0121 | 2723.93 | 2723.93 |
| claude | 87.00 | 0.0097 | 2649.64 | 2649.64 |
| gemini | 149.66 | 0.0166 | 2733.23 | 2733.23 |

## Results by Prompt Version

| Prompt | Energy Mean (J) | Carbon Mean (gCO2eq) | Energy Impr (%) | Carbon Impr (%) |
|--------|-----------------|----------------------|-----------------|------------------|
| v1 | 126.90 | 0.0141 | 1360.34 | 1360.34 |
| v2 | 161.14 | 0.0179 | 3129.17 | 3129.17 |
| v3 | 109.90 | 0.0122 | 3150.26 | 3150.26 |
| v4 | 63.12 | 0.0070 | 3142.07 | 3142.07 |

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
