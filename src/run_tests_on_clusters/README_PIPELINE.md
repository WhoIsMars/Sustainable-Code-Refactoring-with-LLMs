# C++ Dataset Expansion Pipeline

## Overview

This pipeline automates the complete workflow for expanding the C/C++ dataset with validated entries from Exercism repositories on GitHub.

### Key Innovation

Unlike the previous manual workflow, this pipeline **saves base test results immediately during ingestion**, eliminating the need to re-execute tests later. Each entry is validated with 5 test executions before being added to the dataset, and these results are automatically saved to `execution_outputs/`.

### Pipeline Phases

1. **Ingest & Validate** - Download entries + run 5 test executions (results saved)
2. **Generate LLM** - Create 12 LLM variants per entry (3 models × 4 prompts)
3. **Update Metadata** - (Skipped - done automatically by Phase 2)
4. **Execute LLM Tests** - Run 5 test executions for each LLM variant only
5. **Analyze Metrics** - Recalculate statistics and generate plots

---

## Quick Start

### Prerequisites

1. **Docker running** (required for test execution)
```bash
# Verify Docker is running
docker info
```

2. **Python 3.8+** with dependencies installed
```bash
# Install requirements
pip install -r requirements.txt
```

3. **jq installed** (for JSON parsing)
```bash
# macOS
brew install jq

# Ubuntu/Debian
sudo apt-get install jq
```

4. **API Keys configured** in `src/.env`:
```bash
OPENAI_API_KEY=sk-...
ANTHROPIC_API_KEY=sk-ant-...
GEMINI_API_KEY=...
GITHUB_TOKEN=ghp_...  # Optional but recommended for rate limits
```

### Basic Usage

```bash
cd src/run_tests_on_clusters

# Dry-run to see what would happen
./run_cpp_expansion_pipeline.sh --dry-run --target 100

# Execute for real (100 C++ entries)
./run_cpp_expansion_pipeline.sh --target 100

# Execute for C language (50 entries)
./run_cpp_expansion_pipeline.sh --language c --target 50
```

---

## Command-Line Options

| Option | Description | Default |
|--------|-------------|---------|
| `--dry-run` | Show commands without executing | false |
| `--target N` | Target number of entries to ingest | 100 |
| `--language LANG` | Language: `cpp` or `c` | `cpp` |
| `--max-repos N` | Maximum GitHub repositories to search | 50 |
| `--help` | Show help message | - |

### Examples

```bash
# Full pipeline for 100 C++ entries
./run_cpp_expansion_pipeline.sh

# Dry-run to verify before executing
./run_cpp_expansion_pipeline.sh --dry-run --target 50

# Process 20 C entries
./run_cpp_expansion_pipeline.sh --language c --target 20

# Search more repositories for better variety
./run_cpp_expansion_pipeline.sh --target 100 --max-repos 100
```

---

## Detailed Phase Descriptions

### Phase 1: Ingest & Validate (Base)

**Script:** `src/dataset_handling/github_ingestor.py`

**What it does:**
1. Searches GitHub for Exercism C/C++ repositories
2. Validates each entry has source files, tests, and build files
3. Downloads files to `src/dataset/{language}/{exercise}_exercism-{owner}/`
4. **Executes 5 test runs** per entry for validation (100% pass rate required)
5. **Saves test results** to `src/execution_outputs/{cluster}_results_{1-5}.json`
6. Updates cluster JSON files in `src/clusters/cluster_{exercise}.json`
7. Saves manifest to `src/logs/ingestion_manifest_{language}_{timestamp}.json`

**Duration:** ~30 seconds per entry (3-5 min for 10 entries)

**Outputs:**
- `src/dataset/{lang}/{exercise}_exercism-{user}/` - Entry directories
- `src/clusters/cluster_{exercise}.json` - Updated cluster metadata
- `src/execution_outputs/{cluster}_results_{1-5}.json` - **Base test results (NEW!)**
- `src/logs/ingestion_manifest_{lang}_{timestamp}.json` - Manifest file

**Verification:**
```bash
# Check how many entries were ingested
jq '.entry_count' src/logs/ingestion_manifest_cpp_*.json | tail -1

# List clusters modified
jq -r '.clusters[]' src/logs/ingestion_manifest_cpp_*.json | tail -1

# Count base test results (should be entry_count × 5)
ls src/execution_outputs/*_results_[1-5].json 2>/dev/null | wc -l
```

---

### Phase 2: Generate LLM Variants

**Script:** `src/LLMs_generator_engine/run_llm_and_similarity.py`

**What it does:**
1. Identifies "orphan entries" (entries with `LLMs.length < 12`)
2. Generates 12 variants per entry:
   - 3 models: OpenAI GPT-4, Anthropic Claude, Google Gemini
   - 4 prompts: v1 (baseline), v2 (sustainability), v3 (performance), v4 (hybrid)
3. Calculates similarity metrics (fuzzy score, cosine similarity)
4. Updates cluster JSON files with LLM metadata

**Duration:** ~3-5 minutes per entry (30-50 min for 10 entries)

**Outputs:**
- `src/out_improvements_metadata/{lang}/{cluster}/{model}_{exercise}_v{1-4}.{ext}` - LLM files
- `src/clusters/cluster_{exercise}.json` - Updated with `"LLMs": [...]` metadata

**Verification:**
```bash
# Check dry-run to see how many orphans
cd src/LLMs_generator_engine
python run_llm_and_similarity.py --dry-run

# Count LLM files generated (should be entry_count × 12)
find src/out_improvements_metadata -name "*.cpp" -mtime -1 | wc -l

# Check cluster has 12 LLM entries
jq '.cpp[0].LLMs | length' src/clusters/cluster_hamming.json
```

---

### Phase 3: Update Metadata (Skipped)

**Status:** Automatically handled by Phase 2

`run_llm_and_similarity.py` already updates cluster metadata during generation, so this phase is unnecessary in the normal workflow.

**Manual refresh (if needed):**
```bash
cd src/LLMs_generator_engine
python update_cluster_metadata.py
```

---

### Phase 4: Execute LLM Tests

**Script:** `src/run_tests_on_clusters/run_tests_on_cluster.py`

**What it does:**
1. Reads manifest to identify modified clusters
2. For each cluster, executes **LLM tests only** (not base - already done!)
3. Runs 5 test executions per LLM variant
4. Saves results to `src/execution_outputs/{cluster}_results_v{1-4}_{1-5}.json`

**Duration:** ~2 minutes per LLM variant (24 min per entry for 12 variants)

**Command used:**
```bash
python run_tests_on_cluster.py \
  --cluster-name {cluster} \
  --llm-only \
  --run-quantity 5 \
  --languages cpp
```

**Outputs:**
- `src/execution_outputs/{cluster}_results_v{1-4}_{1-5}.json` - LLM test results
- 60 files per cluster (12 variants × 5 executions)

**Verification:**
```bash
# Count LLM test results for a cluster (should be 60)
ls src/execution_outputs/hamming_results_v*_*.json 2>/dev/null | wc -l

# Check all variants tested
for v in 1 2 3 4; do
  echo "Prompt v$v: $(ls src/execution_outputs/hamming_results_v${v}_*.json 2>/dev/null | wc -l)/5 executions"
done
```

---

### Phase 5: Analyze Metrics

**Script:** `src/metrics/main_exec_metrics_analysis.py`

**What it does:**
1. Reads ALL result files from `src/execution_outputs/`
2. Calculates statistics for 4 objectives:
   - Objective 1: Metrics per prompt version
   - Objective 2: Metrics per language
   - Objective 3: Metrics per model + prompt (improvement %)
   - Objective 4: Metrics per language + model
3. Generates box plot visualizations
4. Creates summary report

**Duration:** ~2-5 minutes (depends on dataset size)

**Outputs:**
- `src/metrics/execution_stats/objective_{1-4}_*.json` - Statistics
- `src/metrics/execution_stats_plots/*.png` - Box plots
- `src/metrics/execution_stats_plots/summary_report.md` - Summary

**Verification:**
```bash
# Check summary report
cat src/metrics/execution_stats_plots/summary_report.md

# Count plots generated
ls src/metrics/execution_stats_plots/*.png | wc -l

# View specific objective stats
jq '.summary' src/metrics/execution_stats/objective_1_prompt_version_metrics.json
```

---

## File Structure & Outputs

```
src/
├── dataset/                          # Source code entries
│   └── cpp/
│       └── hamming_exercism-user1/
│           ├── src/hamming.cpp
│           ├── test/test_hamming.cpp
│           └── Makefile
│
├── clusters/                         # Cluster metadata
│   └── cluster_hamming.json         # Contains base + LLM metadata
│
├── out_improvements_metadata/       # LLM-generated code
│   └── cpp/hamming/
│       ├── ChatGPT4_hamming_v1.cpp
│       ├── Claude_hamming_v2.cpp
│       └── ...                      # 12 variants per entry
│
├── execution_outputs/               # Test execution results
│   ├── hamming_results_1.json       # Base execution 1
│   ├── hamming_results_5.json       # Base execution 5
│   ├── hamming_results_v1_1.json    # LLM prompt v1, execution 1
│   └── ...                          # 60 LLM files per cluster
│
├── logs/                            # Pipeline logs
│   ├── pipeline/
│   │   └── cpp_expansion_20250110_143000.log
│   └── ingestion_manifest_cpp_20250110_143000.json
│
└── metrics/
    ├── execution_stats/             # Statistics JSON
    │   └── objective_1_prompt_version_metrics.json
    └── execution_stats_plots/       # Visualizations
        ├── box_plot_objective_1_cpu.png
        └── summary_report.md
```

---

## Manifest File Format

**Location:** `src/logs/ingestion_manifest_{language}_{timestamp}.json`

**Purpose:** Tracks which clusters were modified for pipeline Phase 4

**Format:**
```json
{
  "timestamp": "2025-01-10 14:30:00",
  "language": "cpp",
  "clusters": ["hamming", "two_sum", "reverse_string"],
  "entry_count": 10,
  "validated_count": 10,
  "failed_count": 2,
  "success_rate": "100.0%"
}
```

**Usage in Pipeline:**
```bash
# Get latest manifest
MANIFEST=$(ls -t src/logs/ingestion_manifest_cpp_*.json | head -1)

# Extract cluster list
CLUSTERS=$(jq -r '.clusters[]' "$MANIFEST")

# Iterate for Phase 4
for cluster in $CLUSTERS; do
  python run_tests_on_cluster.py --cluster-name $cluster --llm-only
done
```

---

## Timing Estimates

### Per Entry Timings

| Phase | Time per Entry | Notes |
|-------|---------------|-------|
| Phase 1: Ingest & Validate | 30s | Includes 5 test executions |
| Phase 2: LLM Generation | 3-5 min | 12 variants, includes similarity |
| Phase 4: LLM Tests | 24 min | 12 variants × 5 executions |
| Phase 5: Metrics (total) | 2-5 min | Processes entire dataset |

### Total Pipeline Estimates

| Entries | Phase 1 | Phase 2 | Phase 4 | Total |
|---------|---------|---------|---------|-------|
| 10 | 5 min | 30 min | 4 hours | **4.5 hours** |
| 20 | 10 min | 1 hour | 8 hours | **9 hours** |
| 50 | 25 min | 2.5 hours | 20 hours | **23 hours** |
| 100 | 50 min | 5 hours | 40 hours | **46 hours** |

**Optimization tip:** Phase 4 dominates execution time. Consider:
- Running pipeline overnight
- Using `--target 10` for testing before full run
- Parallelizing cluster testing (future enhancement)

---

## Monitoring & Debugging

### Real-Time Monitoring

```bash
# Watch log file in real-time
tail -f src/logs/pipeline/cpp_expansion_*.log

# Monitor Docker containers
watch docker ps

# Check disk space (LLM files are large)
du -sh src/out_improvements_metadata src/execution_outputs
```

### Check Phase Status

```bash
# Phase 1: Count entries ingested
jq '.entry_count' src/logs/ingestion_manifest_cpp_*.json | tail -1

# Phase 2: Count LLM files
find src/out_improvements_metadata -name "*.cpp" -mtime -1 | wc -l

# Phase 4: Count test results
ls src/execution_outputs/*_results_v*_*.json 2>/dev/null | wc -l

# Phase 5: Check metrics updated
ls -lt src/metrics/execution_stats/*.json | head -5
```

### Common Issues

#### Issue: Docker not running

**Error:** `Docker not running. Please start Docker.`

**Solution:**
```bash
open /Applications/Docker.app  # macOS
docker info  # Verify
```

#### Issue: jq not installed

**Error:** `jq: command not found`

**Solution:**
```bash
brew install jq  # macOS
sudo apt-get install jq  # Linux
```

#### Issue: API rate limits

**Error:** `GitHub API rate limit exceeded`

**Solution:**
1. Add GitHub token to `.env`:
```bash
GITHUB_TOKEN=ghp_your_token_here
```

2. Use `--max-repos` to reduce API calls:
```bash
./run_cpp_expansion_pipeline.sh --max-repos 20
```

#### Issue: LLM API quota exceeded

**Error:** `OpenAI API quota exceeded` or similar

**Solution:**
1. Check API quotas/billing
2. Reduce `--target` entries
3. Process in smaller batches

#### Issue: Low disk space

**Warning:** Pipeline generates large files

**Solution:**
```bash
# Check space
df -h

# Clean old execution outputs
find src/execution_outputs -name "*.json" -mtime +30 -delete

# Clean old LLM files
find src/out_improvements_metadata -name "*.cpp" -mtime +60 -delete
```

---

## Advanced Usage

### Run Specific Phases Only

If pipeline fails mid-execution, you can re-run specific phases:

```bash
cd src

# Re-run Phase 2 only (LLM generation)
cd LLMs_generator_engine
python run_llm_and_similarity.py --max-entries 10

# Re-run Phase 4 for specific cluster
cd ../run_tests_on_clusters
python run_tests_on_cluster.py --cluster-name hamming --llm-only --run-quantity 5

# Re-run Phase 5 only (metrics)
cd ../metrics
python main_exec_metrics_analysis.py
```

### Custom Validation

```bash
# Verify all base results exist
for cluster in $(jq -r '.clusters[]' src/logs/ingestion_manifest_cpp_*.json | tail -1); do
  count=$(ls src/execution_outputs/${cluster}_results_[1-5].json 2>/dev/null | wc -l)
  echo "$cluster: $count/5 base results"
done

# Verify all LLM results exist
for cluster in $(jq -r '.clusters[]' src/logs/ingestion_manifest_cpp_*.json | tail -1); do
  count=$(ls src/execution_outputs/${cluster}_results_v*_*.json 2>/dev/null | wc -l)
  echo "$cluster: $count/60 LLM results"
done
```

### Incremental Expansion

To add more entries to existing dataset:

```bash
# Add 20 more entries
./run_cpp_expansion_pipeline.sh --target 20

# Metrics in Phase 5 will include ALL entries (old + new)
```

---

## Troubleshooting Checklist

Before running pipeline:

- [ ] Docker is running (`docker info`)
- [ ] Python dependencies installed (`pip install -r requirements.txt`)
- [ ] jq installed (`jq --version`)
- [ ] API keys configured in `src/.env`
- [ ] Sufficient disk space (>10GB for 100 entries)
- [ ] GitHub token (optional but recommended)

During execution:

- [ ] Monitor log file (`tail -f src/logs/pipeline/*.log`)
- [ ] Check Docker containers active (`docker ps`)
- [ ] Verify no API rate limit errors in logs
- [ ] Check intermediate outputs exist

After completion:

- [ ] Verify manifest file created
- [ ] Check base test results (entry_count × 5 files)
- [ ] Check LLM files generated (entry_count × 12 files)
- [ ] Check LLM test results (entry_count × 60 files)
- [ ] Verify metrics updated

---

## Exit Codes

| Code | Meaning | Action |
|------|---------|--------|
| 0 | Success | Pipeline completed successfully |
| 1 | Critical failure | No entries ingested, check logs |
| 2 | Partial success | <50% of target ingested, review logs |

---

## Performance Tips

1. **Use dry-run first**
```bash
./run_cpp_expansion_pipeline.sh --dry-run --target 100
```

2. **Start small, scale up**
```bash
# Test with 10 entries first
./run_cpp_expansion_pipeline.sh --target 10

# If successful, scale to 100
./run_cpp_expansion_pipeline.sh --target 100
```

3. **Monitor resource usage**
```bash
# CPU/Memory
htop

# Disk I/O
iotop

# Docker stats
docker stats
```

4. **Run overnight for large batches**
```bash
# Run in background with nohup
nohup ./run_cpp_expansion_pipeline.sh --target 100 > pipeline.out 2>&1 &

# Or use screen/tmux
screen -S pipeline
./run_cpp_expansion_pipeline.sh --target 100
# Ctrl+A, D to detach
```

---

## Future Enhancements

Potential improvements for future versions:

1. **Parallel cluster testing in Phase 4**
   - Currently sequential
   - Could use GNU parallel or ThreadPoolExecutor

2. **Resume from checkpoint**
   - Save progress after each cluster
   - Resume if pipeline interrupted

3. **Configurable parallelization**
   - `--workers N` flag for Phase 1
   - Default: 3 workers (current)

4. **Selective re-execution**
   - `--phase N` to run specific phase only
   - `--clusters cluster1,cluster2` to test specific clusters

5. **Email/Discord notifications**
   - Alert when phases complete
   - Summary report delivery

---

## References

- Original ingestor: `src/dataset_handling/github_ingestor.py`
- LLM generator: `src/LLMs_generator_engine/run_llm_and_similarity.py`
- Test runner: `src/run_tests_on_clusters/run_tests_on_cluster.py`
- Metrics analyzer: `src/metrics/main_exec_metrics_analysis.py`
- Project docs: `context.txt`, `CLAUDE.md`, `README.md`

---

## Contact & Support

For issues or questions:

1. Check this documentation first
2. Review log files in `src/logs/pipeline/`
3. Check GitHub repository issues
4. Contact project maintainer

---

**Last Updated:** 2025-01-10
**Pipeline Version:** 2.0
**Compatible with:** Python 3.8+, Docker 20+
