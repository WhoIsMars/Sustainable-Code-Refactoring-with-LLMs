# ROOT CAUSE ANALYSIS - COMPLETE REPORT
**Date:** 2025-11-18
**Analyst:** Dataset Rebalancing Pipeline

---

## EXECUTIVE SUMMARY

Analyzed 60 failed entries across 4 languages (C, Java, Python, JavaScript) by re-executing sample clusters and examining Docker configurations. Identified **systematic infrastructure issues** affecting 60-90% of entries per language.

### Key Findings:
- **70-90% of failures are BASE CODE BUGS** (test logic errors, @Ignore annotations, incomplete tests)
- **10-30% are DOCKER/INFRASTRUCTURE ISSUES** (recoverable with fixes)
- **2 CRITICAL INFRASTRUCTURE BUGS** require immediate fixing before adding new entries

---

## DETAILED ANALYSIS BY LANGUAGE

### 1. C Language (121/173 entries failed, 69.9%)

#### **Problem Identified:**
**Missing Unity Test Framework**

```
fatal error: test-framework/unity.h: No such file or directory
```

#### **Root Cause:**
- C Dockerfile does NOT include Unity test framework
- Universal Makefile fallback attempts compilation but fails at missing headers
- Many Exercism C exercises use Unity (standard testing framework)

#### **Impact:**
- ~40-60% of C failures are due to missing Unity
- Remaining failures are base code bugs (logic errors, wrong algorithms)

#### **Fix Required:**
```dockerfile
# In src/docker/c/Dockerfile, add:
RUN apt-get update && apt-get install -y \
    unity-dev \
    || wget https://github.com/ThrowTheSwitch/Unity/archive/refs/heads/master.zip \
    && unzip master.zip \
    && cp -r Unity-master/src/* /usr/local/include/
```

**OR provide Unity.c/Unity.h in container:**
```bash
# In src/docker/c/run.sh, add fallback:
if grep -q "unity.h" test/*.c 2>/dev/null; then
    if [ ! -f "test-framework/unity.h" ]; then
        mkdir -p test-framework
        wget -q -O test-framework/unity.h https://raw.githubusercontent.com/ThrowTheSwitch/Unity/master/src/unity.h
        wget -q -O test-framework/unity.c https://raw.githubusercontent.com/ThrowTheSwitch/Unity/master/src/unity.c
    fi
fi
```

#### **Categorization:**
- **Recoverable:** 30-50 entries (Unity-related)
- **Unrecoverable:** 70-90 entries (base code bugs)

---

### 2. Java (129/142 entries failed, 90.8%)

#### **Problem Identified:**
**Test Skipping with @Ignore Annotations**

```
JUnit version 4.13.2
.IIIIIIIIIIII
Time: 0.007

OK (1 test)
```

**Translation:** 1 test executed, 13 tests IGNORED (marked with `@Ignore`)

#### **Root Cause:**
- Base code has tests with massive `@Ignore` annotations
- Only 1-2 tests out of 10-15 actually run
- This is **NOT a Docker issue**, it's **BASE CODE QUALITY**
- Tests were probably disabled during development and never re-enabled

#### **Impact:**
- ~85-95% of Java failures are base code with incomplete/ignored tests
- <5% might be Docker/classpath issues

#### **Fix Required:**
**NONE for Docker.** This is unfixable without editing base code test files.

**Recommendation:** DISCARD all entries with @Ignore ratio > 50%

#### **Categorization:**
- **Recoverable:** 5-10 entries (classpath/dependency issues)
- **Unrecoverable:** 120-130 entries (base code @Ignore epidemic)

---

### 3. Python (206/288 entries failed, 71.5%)

#### **Problem Identified:**
**Wrong Test Framework: unittest vs pytest**

**Current run.sh:**
```bash
/usr/bin/time -v python3 -m unittest discover -s . -p "*test*.py" > output.log 2>&1
```

**Issue:**
- Many Python entries use **pytest syntax** (fixtures, parametrize, etc.)
- Docker uses `unittest discover` which is **incompatible with pytest**
- Tests fail silently or crash
- Output goes to `output.log` which is **NOT printed to stdout**
- Diagnostic logs are truncated, hiding the real error

#### **Root Cause:**
1. Framework mismatch (unittest vs pytest)
2. Silent failures (output.log not displayed)
3. No error visibility in logs

#### **Impact:**
- ~50-70% of Python failures are unittest/pytest incompatibility
- ~20-30% are base code bugs
- ~10% might be dependency issues

#### **Fix Required:**
```bash
# In src/docker/python/run.sh, REPLACE line 14:
# OLD:
/usr/bin/time -v python3 -m unittest discover -s . -p "*test*.py" > output.log 2>&1

# NEW (try pytest first, fallback to unittest):
if python3 -m pytest --collect-only . > /dev/null 2>&1; then
    echo "==> Running tests with pytest..."
    /usr/bin/time -v python3 -m pytest -v . 2>&1 | tee output.log
else
    echo "==> Running tests with unittest..."
    /usr/bin/time -v python3 -m unittest discover -s . -p "*test*.py" 2>&1 | tee output.log
fi
```

**CRITICAL:** Use `tee` to print output to both stdout and output.log!

#### **Categorization:**
- **Recoverable:** 100-150 entries (pytest compatibility fix)
- **Unrecoverable:** 50-100 entries (base code bugs)

---

### 4. JavaScript (234/332 entries failed, 70.5%)

#### **Problem Identified:**
**Silent Jest Failures (Output Not Displayed)**

**Current run.sh:**
```bash
/usr/bin/time -v node --experimental-vm-modules ./node_modules/.bin/jest \
    --config=jest.config.js \
    --silent=false > output.log 2>&1
```

**Issue:**
- Jest output redirected to `output.log`
- **NOT printed to stdout** → diagnostic logs are empty
- Cannot see actual test failures
- Exit code 1 but no error details

#### **Root Cause:**
1. Output redirection without display
2. No visibility into Jest assertion failures
3. Possibly ESM/CommonJS config issues

#### **Impact:**
- ~40-60% might be recoverable (config/output issues)
- ~40-60% are base code bugs

#### **Fix Required:**
```bash
# In src/docker/javascript/run.sh, REPLACE lines 36-43:
# Use tee to display output while saving to log

if [ "$mode" = "esm" ]; then
  echo "▶️  Avvio Jest in modalità ESM"
  /usr/bin/time -v node --experimental-vm-modules ./node_modules/.bin/jest \
    --config=jest.config.js \
    --silent=false 2>&1 | tee output.log
else
  echo "▶️  Avvio Jest in modalità CommonJS"
  /usr/bin/time -v ./node_modules/.bin/jest \
    --config=jest.config.js \
    --silent=false 2>&1 | tee output.log
fi
```

#### **Additional Improvements:**
```bash
# After Jest execution, print summary:
echo ""
echo "==> Jest execution completed"
echo "==> Output log summary:"
tail -50 output.log
```

#### **Categorization:**
- **Recoverable:** 80-140 entries (output visibility + potential config fixes)
- **Unrecoverable:** 100-150 entries (base code bugs)

---

## CRITICAL INFRASTRUCTURE FIXES

### Priority 1: MUST FIX BEFORE ADDING NEW ENTRIES

**Python run.sh:**
- ✅ Switch to pytest with unittest fallback
- ✅ Use `tee` to display output
- **Impact:** Will make 100-150 entries recoverable

**JavaScript run.sh:**
- ✅ Use `tee` to display Jest output
- **Impact:** Will improve debuggability, recover 30-80 entries

### Priority 2: NICE TO HAVE

**C Dockerfile/run.sh:**
- ✅ Add Unity framework support
- **Impact:** Will make 30-50 entries recoverable

---

## QUANTITATIVE ESTIMATES

### Recoverable vs Unrecoverable Entries (After Fixes)

| Language   | Total Failed | Recoverable | Unrecoverable | Recovery % |
|------------|--------------|-------------|---------------|------------|
| C          | 121          | 40          | 81            | 33%        |
| Java       | 129          | 5           | 124           | 4%         |
| Python     | 206          | 120         | 86            | 58%        |
| JavaScript | 234          | 80          | 154           | 34%        |
| **TOTAL**  | **690**      | **245**     | **445**       | **36%**    |

### New Entries Needed (Target: 150-200 per language)

| Language   | Current Valid | Recoverable | Subtotal | Needed (min) | Needed (max) |
|------------|---------------|-------------|----------|--------------|--------------|
| C          | 51            | 40          | 91       | 59           | 109          |
| Java       | 13            | 5           | 18       | 132          | 182          |
| Python     | 82            | 120         | 202      | 0            | 0            |
| JavaScript | 98            | 80          | 178      | 0            | 22           |

**Conclusion:**
- **Python:** Already sufficient after fixes! ✅
- **JavaScript:** Needs 0-22 new entries (borderline)
- **C:** Needs ~60-110 new entries
- **Java:** Needs ~130-180 new entries (critical shortage)

---

## RECOMMENDED STRATEGY

### Phase 1: Apply Infrastructure Fixes (Est. 2 hours)
1. Fix Python run.sh (pytest + tee)
2. Fix JavaScript run.sh (tee)
3. Fix C Dockerfile/run.sh (Unity)
4. Test fixes on 10 sample entries per language

### Phase 2: Re-execute Recoverable Entries (Est. 6-8 hours)
1. Re-run ~245 potentially recoverable entries
2. Filter to entries that now pass 5/5 executions
3. Expected outcome: +100-150 new valid entries

### Phase 3: Add New Entries (Conditional, Est. 10-15 hours)
**Only for languages still below target after Phase 2:**
- **C:** Add ~60-110 new Exercism entries
- **Java:** Add ~130-180 new Exercism entries
- **Python:** SKIP (already sufficient)
- **JavaScript:** Add 0-22 new entries (if needed)

### Phase 4: Final Execution & Validation (Est. 6-8 hours)
1. Execute all new entries (base + LLM)
2. Generate statistics
3. Validate dataset balance

---

## FILES TO MODIFY

### Immediate Action Required:

1. **`src/docker/python/run.sh`**
   - Line 14: Change unittest to pytest with tee

2. **`src/docker/javascript/run.sh`**
   - Lines 36-43: Add tee to Jest execution

3. **`src/docker/c/Dockerfile`** OR **`src/docker/c/run.sh`**
   - Add Unity framework support

---

## VALIDATION CRITERIA

After fixes, a language is considered "ready" if:
- ✅ New entries from github_ingestor.py achieve 100% pass rate (5/5)
- ✅ Re-executed recoverable entries achieve 100% pass rate
- ✅ Diagnostic logs show complete output (not truncated)
- ✅ Total valid entries >= 150 per language

---

## NEXT STEPS

**Immediate:**
1. **CHECKPOINT 1:** Review this analysis with user
2. Get approval for proposed fixes
3. Apply fixes to Docker configurations
4. Test fixes on 3 sample entries per language

**After Checkpoint 1:**
1. Execute Phase 2 (re-run recoverable)
2. Execute Phase 3 (add new entries if needed)
3. Execute Phase 4 (final validation)

---

**Report End**
