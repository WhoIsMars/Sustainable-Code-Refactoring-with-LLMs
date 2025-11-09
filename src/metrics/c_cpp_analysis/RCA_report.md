# Root Cause Analysis: C vs C++ Pass Rate Discrepancy

**Generated for Thesis - Section 5.3 (Threats to Validity)**

---

## Executive Summary

- **C Mean Pass Rate**: 91.35%
- **C++ Mean Pass Rate**: 90.76%
- **Gap**: +0.59% (C++ performs worse)

## 1. Global Statistics

### Pass Rate Comparison

| Metric | C | C++ | Gap |
|--------|---|-----|-----|
| Mean | 91.35% | 90.76% | +0.59% |
| Median | 100.00% | 100.00% | +0.00% |
| Std | 27.98% | 27.91% | +0.07% |
| Min | 0.00% | 0.00% | +0.00% |
| Max | 100.00% | 100.00% | +0.00% |

### Distribution Analysis

- **0% Pass Rate**: C = 20, C++ = 17
- **100% Pass Rate**: C = 216, C++ = 197

### By Model Breakdown

| Model | C Mean | C++ Mean | Gap |
|-------|--------|----------|-----|
| openAI | 95.90% | 88.37% | +7.53% |
| claude | 83.33% | 88.06% | -4.73% |
| gemini | 92.50% | 97.50% | -5.00% |

## 2. Error Classification

### Total Error Count

- **C Total Errors**: 886
- **C++ Total Errors**: 805
- **Difference**: -81 more errors in C++

### Root Cause Distribution

#### C Root Causes:


#### C++ Root Causes:


## 3. Build Configuration Differences

### Key Differences:

**Base Docker Image:**
- C: `FROM ubuntu:22.04`
- C++: `FROM gcc:latest`

**Compiler:**
- C: `gcc`
- C++: `g++`

- C++ uses Boost libraries, C does not

- C++ uses Catch2 test framework

## 4. Code Analysis

### Analyzed Clusters (Top 3):

- `bob.with_metrics`
- `collatz_conjecture`
- `hello_world`

### Sample Code Differences

#### Cluster: `bob.with_metrics`

**Base C Vs Base Cpp:**

```diff
Error generating diff: [Errno 2] No such file or directory: 'c/bob_Exercism_ThomasZumsteg/src'
```

**Llm C Vs Llm Cpp:**

```diff
Error generating diff: [Errno 2] No such file or directory: 'c/bob_Exercism_ThomasZumsteg/openAI/ChatGPT4_bob_v4.c'
```

**Base C Vs Llm C:**

```diff
Error generating diff: [Errno 2] No such file or directory: 'c/bob_Exercism_ThomasZumsteg/src'
```

**Base Cpp Vs Llm Cpp:**

```diff
Error generating diff: [Errno 2] No such file or directory: 'cpp/bob_Exercism_johnngugi/src'
```

#### Cluster: `collatz_conjecture`

**Base C Vs Base Cpp:**

```diff
Error generating diff: [Errno 2] No such file or directory: 'c/collatz_conjecture_Exercism_ThomasZumsteg/src'
```

**Llm C Vs Llm Cpp:**

```diff
--- LLM C (openAI v4)
+++ LLM C++ (openAI v4)
@@ -1,12 +1,14 @@
-#define ERROR_VALUE -1

+#include "collatz_conjecture.h"

 

-int steps(int start) {

-    if (start <= 0)

-        return ERROR_VALUE;

-    int step = 0;

-    while (start != 1) {

-        start = (start & 1) ? start * 3 + 1 : start >> 1;

-        step++;

-    }

-    return step;

-}
+namespace collatz_conjecture {

+	int steps(int n) {

+		if (n <= 0)

+			throw std::domain_error("less or equals 0");

+		int res = 0;

+		while (n != 1) {

+			n = (n % 2 == 0) ? (n / 2) : (n * 3 + 1);

+			++res;

+		}

+		return res;

+	}

+}  // namespace collatz_conjecture
```

**Base C Vs Llm C:**

```diff
Error generating diff: [Errno 2] No such file or directory: 'c/collatz_conjecture_Exercism_ThomasZumsteg/src'
```

**Base Cpp Vs Llm Cpp:**

```diff
Error generating diff: [Errno 2] No such file or directory: 'cpp/collatz_conjecture_Exercism_thefullarcticfox/src'
```

#### Cluster: `hello_world`

**Base C Vs Base Cpp:**

```diff
Error generating diff: [Errno 2] No such file or directory: 'c/hello_world_Exercism_HeitorMP/src'
```

**Llm C Vs Llm Cpp:**

```diff
--- LLM C (openAI v4)
+++ LLM C++ (openAI v4)
@@ -1,6 +1,11 @@
 #include "hello_world.h"

+#include <string>

 

-const char *hello(void)

-{

-    return "Hello, World!";

+namespace hello_world {

+

+const std::string& hello() {

+    static const std::string message = "Hello, World!";

+    return message;

+}

+

 }
```

**Base C Vs Llm C:**

```diff
Error generating diff: [Errno 2] No such file or directory: 'c/hello_world_Exercism_HeitorMP/src'
```

**Base Cpp Vs Llm Cpp:**

```diff
Error generating diff: [Errno 2] No such file or directory: 'cpp/hello_world_Exercism_johnngugi/src'
```

## 5. Hypotheses and Root Causes

## 6. Recommendations

1. **Manual Code Review**: Examine compilation logs for C++ failures
2. **Prompt Engineering**: Improve prompts with C++-specific constraints
3. **Build Validation**: Add pre-execution compilation checks
4. **Error Logging**: Enhanced error reporting for C++ builds
5. **Header Analysis**: Automated detection of header/implementation mismatches

---

*This report was generated automatically for thesis analysis.*
