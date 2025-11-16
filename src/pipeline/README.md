# C++ Dataset Validation and Completion Pipeline

This pipeline validates and completes the C++ dataset through three sequential phases.

## Overview

The script `validate_and_complete_cpp.py` addresses three common issues in the C++ dataset:

1. **Invalid Base Entries**: Some entries fail their test suites
2. **Missing Gemini Variants**: LLM generation failures leave incomplete metadata
3. **Missing Test Results**: Execution outputs are incomplete

## Usage

### Basic Commands

```bash
# Run all phases
python src/pipeline/validate_and_complete_cpp.py --steps all

# Run specific phases
python src/pipeline/validate_and_complete_cpp.py --steps 1        # Only validation
python src/pipeline/validate_and_complete_cpp.py --steps 2 3      # Regeneration + tests
python src/pipeline/validate_and_complete_cpp.py --steps 1 2      # Validation + regeneration

# Dry run (report only, no modifications)
python src/pipeline/validate_and_complete_cpp.py --steps all --dry-run
```

### Phases Explained

#### Phase 1: Validation and Pruning

**Objective**: Ensure every C++ base entry passes its test suite

**Process**:
1. Scans all `cluster_*.json` files
2. For each C++ base entry:
   - **Checks existing test results** in `execution_outputs/` (NO re-execution!)
   - Verifies all 5 test runs exist and passed (100% pass rate)
3. Removes invalid entries (< 100% pass rate or no results) from cluster JSON
4. Logs all removed entry IDs with categorization:
   - Entries without test results (never executed)
   - Entries with failed tests

**Output**:
- Modified cluster JSON files (only valid entries remain)
- Log of removed entries
- Statistics: entries checked, removed, clusters modified

**Example Output**:
```
PHASE 1 SUMMARY
================================================================================
Entries checked: 505
Entries removed: 462
  - With no results: 458
  - With failed tests: 4
Clusters modified: 92

Entries without test results:
  - cpp_01-hello-world_ARPIT73881
  - cpp_02-lasagna_ARPIT73881
  ...

Entries with failed tests:
  - cpp_binary_johnngugi
  - cpp_binary_chrisnp
  ...
```

#### Phase 2: Gemini Variant Regeneration

**Objective**: Complete missing Gemini LLM variants (v1-v4)

**Process**:
1. Scans cleaned cluster files (after Phase 1)
2. For each valid C++ base entry:
   - Checks for 4 Gemini variants (v1, v2, v3, v4)
   - If any are missing, generates them using `llm_generator.py`
3. Updates cluster JSON with new LLM metadata

**Output**:
- Updated cluster JSON files with complete Gemini variants
- Generated code files in `out_improvements_metadata/`
- Statistics: variants generated, errors encountered

**Example Output**:
```
PHASE 2 SUMMARY
================================================================================
Entries checked: 138
Gemini variants generated: 45
Clusters modified: 15
Generation errors: 2
```

#### Phase 3: Missing Test Execution

**Objective**: Complete execution outputs for all LLM variants

**Process**:
1. Scans cluster files with complete metadata
2. For each LLM entry (including new Gemini variants):
   - Checks if 5 execution results exist in `execution_outputs/`
   - Pattern: `{cluster}_results_v{version}_{1-5}.json`
3. Runs tests for missing executions

**Output**:
- Complete execution result files in `execution_outputs/`
- Statistics: tests executed, errors encountered

**Example Output**:
```
PHASE 3 SUMMARY
================================================================================
Entries checked: 552
Tests executed: 225
Execution errors: 3
```

## Implementation Details

### Data Structures

**Cluster JSON Structure**:
```json
{
  "cpp": [
    {
      "id": "cpp_example_user123",
      "filename": "example.cpp",
      "codeSnippetFilePath": "dataset/cpp/example/example.cpp",
      "testUnitFilePath": "dataset/cpp/example/test/example_test.cpp",
      "llm_variants": {
        "gemini": [
          {
            "prompt_version": "v1",
            "generated_code_path": "out_improvements_metadata/...",
            "generation_timestamp": "2025-11-12T10:30:00"
          }
        ],
        "claude": [...],
        "openAI": [...]
      }
    }
  ]
}
```

**Execution Output Structure**:
```json
{
  "results": {
    "cpp": [
      {
        "id": "cpp_example_user123",
        "execution_time_ms": 5.2,
        "CPU_usage": 45.0,
        "RAM_usage": 10496,
        "regressionTestPassed": true
      }
    ]
  }
}
```

### Dependencies

The script uses:
- `utility_dir.utility_paths`: Path constants
- `utility_dir.general_utils`: JSON read/write utilities
- `run_tests_on_clusters.run_tests_on_cluster`: Test execution
- `LLMs_generator_engine.llm_generator`: LLM code generation

### Logging

Logs are saved to `src/logs/cpp_validation_YYYYMMDD_HHMMSS.log` with:
- INFO level: Progress and summary statistics
- DEBUG level: Detailed per-entry validation results
- ERROR level: Failures and exceptions

## Common Scenarios

### Scenario 1: After Failed Pipeline Run

If the C++ expansion pipeline partially failed:

```bash
# First validate and remove broken entries
python src/pipeline/validate_and_complete_cpp.py --steps 1

# Then regenerate missing Gemini variants
python src/pipeline/validate_and_complete_cpp.py --steps 2

# Finally, complete test executions
python src/pipeline/validate_and_complete_cpp.py --steps 3
```

### Scenario 2: Gemini API Key Issues

If Gemini generation failed due to API key problems:

```bash
# Fix API key in .env file first, then:
python src/pipeline/validate_and_complete_cpp.py --steps 2
```

### Scenario 3: Check Status Without Changes

```bash
# Dry run to see what would be done
python src/pipeline/validate_and_complete_cpp.py --steps all --dry-run
```

### Scenario 4: Complete Dataset Validation

```bash
# Run all phases in sequence
python src/pipeline/validate_and_complete_cpp.py --steps all
```

## Performance Considerations

- **Phase 1** is very fast (reads existing results only)
  - ~505 entries checked in < 1 second
  - **No test re-execution** - validates from `execution_outputs/`
  - Estimated time: < 1 second
- **Phase 2** depends on LLM API rate limits
  - ~45 variants × API latency
  - Estimated time: 30-60 minutes
- **Phase 3** depends on number of missing tests
  - Variable based on previous failures
  - Estimated time: 30 minutes - 2 hours

**Key Optimization**: Phase 1 validates entries by checking existing test results in `execution_outputs/` instead of re-running tests. This reduces validation time from hours to seconds.

## Error Handling

The script continues execution even if individual entries fail:
- Invalid entries are logged and skipped
- LLM generation errors are counted but don't stop the pipeline
- Test execution errors are reported but processing continues

All errors are logged to the log file for post-analysis.

## Exit Codes

- `0`: Success
- `1`: Partial success (some entries failed but pipeline completed)
- `2`: Fatal error (e.g., missing dependencies)

## Example Full Workflow

```bash
cd /path/to/Sustainable-Code-Refactoring-with-LLMs

# 1. Check current status (dry run)
python src/pipeline/validate_and_complete_cpp.py --steps all --dry-run

# 2. Run validation and pruning
python src/pipeline/validate_and_complete_cpp.py --steps 1

# 3. Review removed entries
cat src/logs/cpp_validation_*.log | grep "Removed entry IDs" -A 50

# 4. Regenerate Gemini variants
python src/pipeline/validate_and_complete_cpp.py --steps 2

# 5. Complete test executions
python src/pipeline/validate_and_complete_cpp.py --steps 3

# 6. Verify completeness
python src/unified_analyzer/validators/completeness_validator.py
```

## Troubleshooting

### "Test runner not available"
- Ensure `run_tests_on_clusters/run_tests_on_cluster.py` is accessible
- Check Docker is running for test execution

### "LLM generator not available"
- Verify `LLMs_generator_engine/llm_generator.py` exists
- Check API keys in `src/.env` file

### "Permission denied"
- Make script executable: `chmod +x src/pipeline/validate_and_complete_cpp.py`

### Tests fail unexpectedly
- Check Docker images are built: `docker images | grep test_runner_cpp`
- Rebuild if needed: `cd src/docker/cpp && docker build -t test_runner_cpp_persistent .`

## See Also

- `src/unified_analyzer/validators/completeness_validator.py`: Check dataset completeness
- `src/run_tests_on_clusters/run_cpp_expansion_pipeline.sh`: Full dataset expansion pipeline
- `src/metrics/README_exec_metrics.md`: Metrics analysis documentation
