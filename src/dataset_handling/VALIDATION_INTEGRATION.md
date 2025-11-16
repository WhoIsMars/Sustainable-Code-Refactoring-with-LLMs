# GitHub Ingestor - Test Validation Integration

## Overview

This document describes the integration of automated test validation into the GitHub ingestion pipeline for C/C++ Exercism solutions.

## Changes Summary

The `github_ingestor.py` has been modified to validate every entry with 5 test executions **before** adding it to the cluster JSON files.

### New Workflow

```
1. Find Candidate Entry (GitHub API)
   ↓
2. Download Files (src/, test/, Makefile)
   ↓
3. Validate with Tests (5 executions, 100% pass rate required)
   ↓ [PASS]                    ↓ [FAIL]
4. Save to Cluster JSON     5. Cleanup Files
   ↓                            ↓
SUCCESS                      SKIP ENTRY
```

## New Features

### 1. Test Validation (`validate_entry_with_tests`)

- Executes test suite 5 times using Docker containers
- Requires **100% pass rate** (all 5 executions must succeed)
- Verifies both `regressionTestPassed` and `success` flags
- Logs average metrics (CPU, RAM, execution time)
- Auto-generates fallback Makefile if original is incompatible

**Parameters:**
- `entry`: ExercismEntry object
- `entry_dir_name`: Directory where files are stored
- `num_executions`: Number of test runs (default: 5)

**Returns:** `True` if all tests pass, `False` otherwise

### 2. Fallback Makefile Generation (`generate_fallback_makefile`)

Automatically creates a standard Makefile when:
- No Makefile or CMakeLists.txt exists
- Original build file is incompatible with Docker environment

**Features:**
- Separate templates for C and C++
- Compiles all `.c`/`.cpp` files in `src/` and `test/`
- Standard flags: `-Wall -Wextra -std=c11/c++17 -g`
- Math library linking (`-lm`)

### 3. Failed Entry Cleanup (`cleanup_failed_entry`)

Removes entry directory when validation fails:
- Deletes entire `dataset/{lang}/{entry_name}/` directory
- Prevents orphaned files that aren't in cluster JSON
- Thread-safe operation

### 4. Parallelization (`_process_single_entry` + ThreadPoolExecutor)

Processes multiple entries simultaneously:
- **Max workers**: 3 (configurable)
- **Thread-safe**: Cluster JSON updates use lock
- **Early exit**: Stops when target count reached
- **Statistics tracking**: Download/validation/ingestion counts

### 5. Enhanced Statistics

New metrics logged at completion:
- Successfully ingested entries
- Downloaded entries
- Validated entries (passed all tests)
- Failed validation count
- Failed download count

## Architecture Changes

### New Methods in `GitHubIngestor` Class

| Method | Purpose | Returns |
|--------|---------|---------|
| `validate_entry_with_tests()` | Run test suite 5x and verify pass rate | `bool` |
| `generate_fallback_makefile()` | Create standard Makefile for C/C++ | `bool` |
| `cleanup_failed_entry()` | Remove directory after validation failure | `bool` |
| `_process_single_entry()` | Process single entry (download→validate→save) | `(bool, str, dict)` |

### Modified Methods

- **`ingest_entries()`**: Now uses ThreadPoolExecutor for parallel processing
- **`update_cluster_json()`**: Now thread-safe with lock

### New Dependencies

```python
import shutil                                    # For directory cleanup
from concurrent.futures import ThreadPoolExecutor, as_completed
from threading import Lock
from run_tests_on_clusters.run_tests_on_cluster import (
    TestExecutor,
    ContainerManager,
    BaseEntryResult
)
```

## Configuration

### Validation Parameters

| Parameter | Default | Description |
|-----------|---------|-------------|
| `num_executions` | 5 | Test runs per entry |
| `pass_rate_required` | 100% | All executions must pass |
| `max_workers` | 3 | Parallel processing threads |
| `use_cache` | True | Docker container reuse |
| `debug_mode` | False | Verbose test execution logs |

### Success Criteria

An entry is considered valid when:
1. ✅ All files downloaded successfully
2. ✅ Makefile exists or fallback generated
3. ✅ All 5 test executions pass
4. ✅ `result.regressionTestPassed == True`
5. ✅ `result.success == True`
6. ✅ Cluster JSON updated successfully

**If any step fails:** Entry is discarded and files are cleaned up.

## Usage

### Basic Usage

```python
from dataset_handling.github_ingestor import GitHubIngestor
from utility_dir.utility_paths import DATASET_DIR, CLUSTERS_DIR_FILEPATH

ingestor = GitHubIngestor(
    dataset_dir=DATASET_DIR,
    clusters_dir=CLUSTERS_DIR_FILEPATH,
    github_token="your_github_token"
)

# Ingest with validation
count = ingestor.ingest_entries(
    language='c',
    max_repos=10,
    max_entries_per_lang=20
)

print(f"Successfully ingested {count} validated entries")
```

### Command Line

```bash
cd src/dataset_handling

# Run with validation enabled
python github_ingestor.py --languages c --max-repos 5 --max-entries 10

# Test script (small dataset)
python test_github_ingestor_validation.py
```

## Testing

### Test Script

Use `test_github_ingestor_validation.py` for safe testing:

```bash
python src/dataset_handling/test_github_ingestor_validation.py
```

**Test parameters:**
- Language: C
- Max repos: 2
- Max entries: 3
- Executions per entry: 5

### Manual Testing

1. **Verify Docker is running:**
   ```bash
   docker ps
   ```

2. **Check Docker images exist:**
   ```bash
   docker images | grep -E "c_test|cpp_test"
   ```

3. **Run small ingestion:**
   ```bash
   python github_ingestor.py --languages c --max-repos 1 --max-entries 2
   ```

4. **Check results:**
   ```bash
   # Verify entry in cluster
   cat src/clusters/cluster_*.json | jq '.c | length'

   # Verify files exist
   ls -la src/dataset/c/
   ```

## Performance Considerations

### Timing Estimates

| Operation | Time per Entry | Notes |
|-----------|---------------|-------|
| Download | 2-5 seconds | Depends on file count |
| Test execution (1x) | 2-10 seconds | Compilation + run |
| Test validation (5x) | 10-50 seconds | Full validation |
| **Total per entry** | **12-60 seconds** | Average: ~30s |

**For 20 entries:**
- Sequential: 4-20 minutes
- Parallel (3 workers): 2-7 minutes

### Optimization Tips

1. **Increase workers** (if Docker can handle it):
   ```python
   # In ingest_entries(), line 973:
   with ThreadPoolExecutor(max_workers=5) as executor:
   ```

2. **Reduce test executions** (less rigorous):
   ```python
   # In _process_single_entry(), line 884:
   self.validate_entry_with_tests(entry, entry_dir_name, num_executions=3)
   ```

3. **Process more candidates** (to reach target faster):
   ```python
   # In ingest_entries(), line 961:
   entries_to_process = all_valid_entries[:max_entries_per_lang * 3]
   ```

## Troubleshooting

### Issue: Docker not available

**Error:** `ContainerManager` fails to initialize

**Solution:**
```bash
# Start Docker
open /Applications/Docker.app

# Verify running
docker ps
```

### Issue: All tests failing

**Error:** 100% validation failure rate

**Possible causes:**
1. Makefile incompatibility → Check fallback generation logs
2. Missing dependencies in Docker → Update Dockerfile
3. Test framework mismatch → Verify unity.c/unity.h presence

**Debug:**
```python
# Enable debug mode in validate_entry_with_tests():
result = test_executor.execute_test(
    ...
    debug_mode=True  # Change to True
)
```

### Issue: Slow performance

**Error:** Takes too long to process entries

**Solutions:**
1. Increase `max_workers` (if system can handle it)
2. Reduce `num_executions` from 5 to 3
3. Use SSD for dataset storage
4. Optimize Docker container caching

### Issue: Thread-safety errors

**Error:** Cluster JSON corruption or duplicate entries

**Solution:** Already handled via `cluster_write_lock`. If issues persist:
```python
# Check lock is being used correctly in update_cluster_json():
with self.cluster_write_lock:
    # All cluster file operations
```

## Logging

### Log Levels

```python
# Set in code or via environment:
logging.basicConfig(level=logging.DEBUG)  # More verbose
logging.basicConfig(level=logging.INFO)   # Default
logging.basicConfig(level=logging.WARNING)  # Quiet
```

### Key Log Messages

| Icon | Message | Meaning |
|------|---------|---------|
| 📥 | Downloading: {name} | Starting file download |
| 🧪 | Validating: {name} | Starting test validation |
| ✅ | All tests passed (5/5) | Validation success |
| ❌ | Tests failed (X/5) | Validation failure |
| 💾 | Saving to cluster | Updating cluster JSON |
| 🚀 | Processing X entries in parallel | Parallel execution started |
| 📊 | Progress: X/Y ingested | Real-time progress |

## Future Improvements

### Potential Enhancements

1. **Configurable pass rate threshold:**
   ```python
   validate_entry_with_tests(..., min_pass_rate=0.8)  # 80% instead of 100%
   ```

2. **Retry on transient failures:**
   ```python
   if failed_count == 1 and "timeout" in error_message:
       # Retry once
   ```

3. **Metrics persistence:**
   ```python
   # Save validation metrics to separate JSON
   save_validation_metrics(entry_id, results)
   ```

4. **Selective validation:**
   ```python
   # Only validate if source > 100 LOC
   if char_count > 500:
       validate_entry_with_tests(...)
   ```

## References

- Original ingestor: `github_ingestor.py` (pre-validation version)
- Test runner: `src/run_tests_on_clusters/run_tests_on_cluster.py`
- Context docs: `context.txt`, `CLAUDE.md`, `README.md`
- Docker setup: `src/docker/Dockerfile.c`, `Dockerfile.cpp`

## Version History

- **v2.0** (2025-01-10): Added test validation, parallelization, fallback Makefile
- **v1.0** (2024-11-10): Initial GitHub ingestion (no validation)
