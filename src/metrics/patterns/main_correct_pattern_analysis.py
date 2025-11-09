#!/usr/bin/env python3
"""
Main Pattern Analysis Script with Case Studies Export
======================================================

Questo script esegue l'analisi corretta della correlazione tra pattern e metriche
di performance E genera i top 3 case studies per la presentazione della tesi.

Date: 2025-10-22
"""

import json
import logging
import sys
import os
from pathlib import Path
from typing import Dict, List, Optional, Set
from dataclasses import dataclass, field
from collections import defaultdict
import numpy as np
import ast
import re

# Add project root to path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "../.."))
from utility_dir import utility_paths, general_utils


# Configure logging
logging.basicConfig(
    level=logging.INFO, format="%(asctime)s - %(levelname)s - %(message)s"
)
logger = logging.getLogger(__name__)


# ============================================================================
# CONFIGURATION
# ============================================================================

SIMILARITY_THRESHOLD = 75.0  # Low similarity = significant changes
IMPROVEMENT_THRESHOLD = -15.0  # Minimum improvement to consider
MAX_IMPROVEMENT_CLAMP = 200.0
MIN_IMPROVEMENT_CLAMP = -200.0

METRICS = ["CPU_usage", "RAM_usage", "execution_time_ms"]


# ============================================================================
# DATA CLASSES (from original - unchanged)
# ============================================================================


@dataclass
class ASTMetrics:
    """AST-based code complexity metrics"""

    node_count: int = 0
    function_count: int = 0
    class_count: int = 0
    depth: int = 0
    cyclomatic: int = 0
    loop_count: int = 0
    condition_count: int = 0


@dataclass
class PatternMatch:
    """Represents a detected pattern"""

    name: str
    category: str
    language: str
    energy_impact: str
    present_in_base: bool
    present_in_llm: bool
    base_match_count: int = 0
    llm_match_count: int = 0

    @property
    def is_llm_introduced(self) -> bool:
        """
        Pattern introduced by LLM (not in base, or significantly increased).

        A pattern is considered "introduced" if:
        1. Present in LLM but not in base (new pattern), OR
        2. Present in both but LLM has significantly more instances
           (at least 2 more, or 1.5x more)
        """
        if self.present_in_llm and not self.present_in_base:
            # Pattern only in LLM - definitely introduced
            return True
        elif self.present_in_llm and self.present_in_base:
            # Pattern in both - only if significantly increased
            return (self.llm_match_count >= self.base_match_count + 2 or
                    self.llm_match_count >= self.base_match_count * 1.5)
        else:
            return False


# ============================================================================
# PATTERN DETECTION ENGINE (from original - unchanged)
# ============================================================================


class EnergyPatternDetector:
    """Energy-efficient pattern detector"""

    def __init__(self):
        self.patterns = self._initialize_patterns()

    def _initialize_patterns(self) -> Dict[str, Dict]:
        """
        Initialize pattern definitions from CHOSEN_PATTERNS.md

        Structure:
        - Generic patterns (G1-G6): Cross-language algorithmic and architectural patterns
        - Language-specific patterns: C, C++, Java, JavaScript/TypeScript, Python, Go
        """
        return {
            # ================================================================
            # GENERIC PATTERNS (Multi-language)
            # ================================================================
            "G1_lower_complexity_algorithm": {
                "regex": r"(\.find\(|\.indexOf\(|\.search\(|in\s+\w+|HashSet|HashMap|dict\(|set\()",
                "category": "algorithmic",
                "impact": "high",
                "description": "G1: Algorithm with lower asymptotic complexity (hash table, binary search)",
                "detection_method": "regex+ast",
                "evidence": "Changhee et al. ACM TOSEM 2022 - algorithmic changes show highest improvement",
            },
            "G1_nested_loops_o_n2": {
                "regex": r"for\s+[^{]+\{[^}]*for\s+[^{]+\{",
                "category": "algorithmic",
                "impact": "high",
                "description": "G1: Nested loops O(n²) pattern - candidate for optimization",
                "detection_method": "ast",
                "evidence": "O(n²) → O(n log n) or O(n) improvements documented",
            },
            "G2_reduced_allocations": {
                "regex": r"\b(new|malloc|calloc|make)\s*\(",
                "category": "memory",
                "impact": "high",
                "description": "G2: Reduced allocations / Object pooling / Buffer reuse",
                "detection_method": "ast",
                "evidence": "MDPI 2022: 87x energy reduction, 10-15% execution time on alloc/dealloc",
            },
            "G2_allocation_in_loop": {
                "regex": r"(for|while)\s*[^{]*\{[^}]*(new|malloc|\[\]|\barray\(|\blist\()",
                "category": "memory",
                "impact": "high",
                "description": "G2: Allocation inside loop - should be moved outside",
                "detection_method": "ast",
                "evidence": "Object pooling reduces GC pressure by 85%",
            },
            "G3_cache_locality": {
                "regex": r"(struct|class)\s+\w+\s*\{",
                "category": "memory",
                "impact": "high",
                "description": "G3: Memory access patterns optimization (AoS/SoA, cache blocking)",
                "detection_method": "ast",
                "evidence": "ScienceDirect: 59% average improvement with proper memory access",
            },
            "G4_memoization": {
                "regex": r"(@lru_cache|@cache|@memo|Cache|Memoize|\bcache\s*=)",
                "category": "algorithmic",
                "impact": "high",
                "description": "G4: Memoization / caching to eliminate recomputations",
                "detection_method": "regex",
                "evidence": "Standard compiler optimization, significant speedups on repeated calls",
            },
            "G4_loop_invariant_code_motion": {
                "regex": r"for\s+[^{]+\{",
                "category": "algorithmic",
                "impact": "medium",
                "description": "G4: Loop-invariant code motion candidate",
                "detection_method": "ast",
                "evidence": "MLB-LICM: 36.98% improvement on MRTC benchmarks",
            },
            "G5_fine_grained_locking": {
                "regex": r"(synchronized|lock\(|Lock|Mutex|RWMutex)",
                "category": "concurrency",
                "impact": "high",
                "description": "G5: Concurrency optimization - fine-grained locking vs coarse",
                "detection_method": "ast",
                "evidence": "ConcurrentHashMap shows 2-10x throughput vs synchronized",
            },
            "G6_branch_optimization": {
                "regex": r"(if|switch|case)\s*\(",
                "category": "control_flow",
                "impact": "medium",
                "description": "G6: Branch misprediction mitigation / predicate optimization",
                "detection_method": "ast",
                "evidence": "Cloudflare: 5.5x difference between good/bad branch patterns",
            },
            # ================================================================
            # PYTHON-SPECIFIC PATTERNS
            # ================================================================
            "PY1_builtin_functions": {
                "regex": r"\b(sum|min|max|any|all|map|filter|sorted|enumerate|zip)\s*\(",
                "category": "algorithmic",
                "impact": "high",
                "description": "PY1: Built-in C-native functions (sum, map, filter, etc.)",
                "detection_method": "regex",
                "evidence": "2-10x faster than Python loops due to C implementation",
            },
            "PY1_list_comprehension": {
                "regex": r"\[[^\]]+\s+for\s+[^\]]+\s+in\s+[^\]]+\]",
                "category": "algorithmic",
                "impact": "medium",
                "description": "PY1: List comprehension (C-speed loop)",
                "detection_method": "ast",
                "evidence": "2-3x faster than explicit Python loops",
            },
            "PY2_local_variable_cache": {
                "regex": r"^(\w+)\s*=\s*(\w+\.\w+|\w+)\s*$",
                "category": "algorithmic",
                "impact": "low",
                "description": "PY2: Cached local variables (minimize global lookups)",
                "detection_method": "ast",
                "evidence": "10-20% speedup in tight loops accessing globals",
            },
            "PY3_numpy_vectorization": {
                "regex": r"(import\s+numpy|from\s+numpy|np\.\w+)",
                "category": "algorithmic",
                "impact": "high",
                "description": "PY3: NumPy vectorization for numeric computation",
                "detection_method": "regex",
                "evidence": "9-100x faster than Python loops, Pandas: 82-460x improvements",
            },
            "PY4_string_join": {
                "regex": r"['\"]\.join\s*\(",
                "category": "algorithmic",
                "impact": "medium",
                "description": "PY4: str.join() vs repeated concatenation",
                "detection_method": "regex",
                "evidence": "10-100x faster than repeated + operator",
            },
            # ================================================================
            # JAVASCRIPT/TYPESCRIPT PATTERNS
            # ================================================================
            "JS1_monomorphic_objects": {
                "regex": r"(class\s+\w+|function\s+\w+\s*\(\)|new\s+\w+)",
                "category": "algorithmic",
                "impact": "high",
                "description": "JS1: Object shape stability - monomorphic inline caching",
                "detection_method": "ast",
                "evidence": "Monomorphic IC 10-100x faster than megamorphic",
            },
            "JS1_delete_property": {
                "regex": r"\bdelete\s+\w+\.",
                "category": "algorithmic",
                "impact": "high",
                "description": "JS1: Property deletion (breaks object shape) - ANTI-PATTERN",
                "detection_method": "regex",
                "evidence": "delete causes deoptimization in V8",
            },
            "JS2_temp_allocations_avoided": {
                "regex": r"(\.\.\.|\{[^}]*\}|\[[^\]]*\])\s*=",
                "category": "memory",
                "impact": "medium",
                "description": "JS2: Avoiding temporary allocations (spread, destructuring in loops)",
                "detection_method": "ast",
                "evidence": "Reducing allocations: 82x speedup in similar contexts",
            },
            "JS3_dom_batching": {
                "regex": r"(\.appendChild|\.innerHTML|\.style\.|\.classList)",
                "category": "algorithmic",
                "impact": "high",
                "description": "JS3: DOM manipulation batching to avoid layout thrashing",
                "detection_method": "ast",
                "evidence": "DOM batching reduces rendering from seconds to milliseconds",
            },
            "JS4_typed_arrays": {
                "regex": r"(Float32Array|Float64Array|Int8Array|Int16Array|Int32Array|Uint8Array|Uint16Array|Uint32Array|ArrayBuffer)",
                "category": "memory",
                "impact": "high",
                "description": "JS4: TypedArray for numeric computation",
                "detection_method": "regex",
                "evidence": "Three.js: 10% reduction, 9-100x faster on large datasets",
            },
            "JS5_monomorphic_calls": {
                "regex": r"function\s+\w+\s*\([^)]*\)",
                "category": "algorithmic",
                "impact": "medium",
                "description": "JS5: Monomorphic call sites (same type arguments)",
                "detection_method": "ast",
                "evidence": "Polymorphic functions prevent JIT optimization",
            },
            # ================================================================
            # JAVA PATTERNS
            # ================================================================
            "J1_collections": {
                "regex": r"\b(ArrayList|HashMap|HashSet|LinkedList)<[^>]+>|\.add\(|\.put\(|\.get\(|\.contains\(",
                "category": "memory",
                "impact": "high",
                "description": "J1: Java Collections Framework usage (ArrayList, HashMap, HashSet)",
                "detection_method": "regex",
                "evidence": "Proper collection choice and sizing: 2-5x improvement",
            },
            "J2_string_operations": {
                "regex": r"\bStringBuilder\b|\.append\(|String\.format\(|\+\s*=.*String|\.split\(|\.substring\(",
                "category": "memory",
                "impact": "high",
                "description": "J2: String operations (StringBuilder, concatenation, formatting)",
                "detection_method": "regex",
                "evidence": "StringBuilder 10-100x faster than + in loops",
            },
            "J3_loop_patterns": {
                "regex": r"for\s*\(\s*\w+\s+\w+\s*:\s*\w+\s*\)|for\s*\([^)]+\)|while\s*\([^)]+\)|\.iterator\(\)",
                "category": "algorithmic",
                "impact": "medium",
                "description": "J3: Java loop patterns (for-each, traditional for, while, iterator)",
                "detection_method": "regex",
                "evidence": "For-each often more efficient, no bound checking overhead",
            },
            "J4_stream_api": {
                "regex": r"\.stream\(\)|\.parallelStream\(\)|\.filter\(|\.map\(|\.collect\(|\b(IntStream|LongStream|DoubleStream)\b",
                "category": "algorithmic",
                "impact": "high",
                "description": "J4: Stream API usage (Java 8+, parallel streams, primitive streams)",
                "detection_method": "regex",
                "evidence": "Parallel streams show near-linear scaling for CPU-bound tasks",
            },
            "J5_array_operations": {
                "regex": r"\w+\[\]\s+\w+\s*=|new\s+\w+\[[^\]]*\]|Arrays\.(sort|copyOf|fill|equals)",
                "category": "memory",
                "impact": "high",
                "description": "J5: Array operations (declaration, initialization, Arrays utilities)",
                "detection_method": "regex",
                "evidence": "Primitive arrays 4-6x less memory overhead than boxed collections",
            },
            # ================================================================
            # C PATTERNS
            # ================================================================
            "C1_nested_loops": {
                "regex": r"for\s*\([^)]+\)\s*\{[^}]*for\s*\([^)]+\)",
                "category": "algorithmic",
                "impact": "high",
                "description": "C1: Nested loops / O(n²) operations",
                "detection_method": "regex",
                "evidence": "ACM TOSEM: 60-90% improvement from O(n²) to O(n log n) or O(n)",
            },
            "C2_memory_allocation": {
                "regex": r"\b(malloc|calloc|realloc|free)\s*\(",
                "category": "memory",
                "impact": "high",
                "description": "C2: Memory allocation patterns (malloc/calloc/realloc/free)",
                "detection_method": "regex",
                "evidence": "Preallocation reduces overhead by 10-30%, malloc/free have significant cost",
            },
            "C3_string_operations": {
                "regex": r"\b(strlen|strcpy|strcat|strcmp|strncpy|strncat|strncmp)\s*\(",
                "category": "algorithmic",
                "impact": "medium",
                "description": "C3: String operations (strlen, strcpy, strcat, strcmp)",
                "detection_method": "regex",
                "evidence": "strlen in loop = O(n²), optimized string functions 2-5x faster",
            },
            "C4_array_pointer": {
                "regex": r"\w+\[[^\]]+\]|(\*\s*\w+\+\+)|(\w+\s*\+\+)",
                "category": "algorithmic",
                "impact": "medium",
                "description": "C4: Array indexing and pointer arithmetic",
                "detection_method": "regex",
                "evidence": "Pointer arithmetic can be more efficient, sequential access improves cache",
            },
            "C5_function_in_loop": {
                "regex": r"(for|while)\s*\([^)]+\)\s*\{[^}]*\w+\s*\([^)]*\)",
                "category": "algorithmic",
                "impact": "medium",
                "description": "C5: Function calls in loops (loop-invariant code motion candidate)",
                "detection_method": "regex",
                "evidence": "LICM 15-40% improvement by hoisting invariant computations",
            },
            # ================================================================
            # C++ PATTERNS
            # ================================================================
            "CPP1_vector_operations": {
                "regex": r"std::vector<[^>]+>|\.push_back\(|\.emplace_back\(|\.reserve\(|\.resize\(",
                "category": "memory",
                "impact": "high",
                "description": "CPP1: std::vector and container operations",
                "detection_method": "regex",
                "evidence": "reserve() 2-10x speedup, emplace_back 20-40% faster than push_back",
            },
            "CPP2_string_operations": {
                "regex": r"std::string\s+\w+|\.append\(|\bstd::stringstream\b|\+\s*=.*string",
                "category": "memory",
                "impact": "medium",
                "description": "CPP2: std::string operations (concatenation, append, stringstream)",
                "detection_method": "regex",
                "evidence": "stringstream 5-10x faster than + operator in loops",
            },
            "CPP3_iterators_loops": {
                "regex": r"for\s*\(\s*(const\s+)?auto\s*[&]?\s*\w+\s*:\s*\w+\s*\)|\.begin\(\)|\.end\(\)",
                "category": "algorithmic",
                "impact": "medium",
                "description": "CPP3: Iterator and range-based loops",
                "detection_method": "regex",
                "evidence": "Range-based loops safer, clearer, enable better compiler optimizations",
            },
            "CPP4_memory_management": {
                "regex": r"\bnew\s+\w+|delete\s+\w+|std::(unique_ptr|shared_ptr|make_unique|make_shared)",
                "category": "memory",
                "impact": "high",
                "description": "CPP4: Memory management (new/delete, smart pointers)",
                "detection_method": "regex",
                "evidence": "Smart pointers provide safety with zero overhead (unique_ptr)",
            },
            "CPP5_stl_algorithms": {
                "regex": r"std::(sort|find|find_if|accumulate|transform|count|copy|fill|remove)\s*\(",
                "category": "algorithmic",
                "impact": "high",
                "description": "CPP5: STL algorithm library usage (sort, find, accumulate, transform)",
                "detection_method": "regex",
                "evidence": "STL algorithms 1.5-3x faster than naive implementations",
            },
            # ================================================================
            # GO PATTERNS
            # ================================================================
            "GO1_stack_allocation": {
                "regex": r"(&\w+|\breturn\s+&)",
                "category": "memory",
                "impact": "high",
                "description": "GO1: Escape analysis - stack vs heap allocation",
                "detection_method": "ast",
                "evidence": "85% GC pressure reduction, pause times from seconds to ms",
            },
            "GO2_sync_pool": {
                "regex": r"\bsync\.Pool\b",
                "category": "memory",
                "impact": "high",
                "description": "GO2: sync.Pool for object reuse",
                "detection_method": "regex",
                "evidence": "Drastically reduces allocation rate and GC overhead",
            },
            "GO3_interface_boxing_antipattern": {
                "regex": r"\binterface\{\}",
                "category": "memory",
                "impact": "medium",
                "description": "GO3: interface{} conversions - ANTI-PATTERN (causes heap allocation)",
                "detection_method": "regex",
                "evidence": "Boxing to interface{} triggers heap allocation",
            },
            "GO4_goroutine_pool": {
                "regex": r"\bgo\s+\w+\s*\(",
                "category": "concurrency",
                "impact": "medium",
                "description": "GO4: Goroutine management - worker pools vs unbounded spawn",
                "detection_method": "ast",
                "evidence": "Bounded goroutines prevent memory growth and scheduler overhead",
            },
            "GO5_preallocation": {
                "regex": r"\bmake\s*\(\s*\[\s*\]",
                "category": "memory",
                "impact": "medium",
                "description": "GO5: Slice/map preallocation with known capacity",
                "detection_method": "regex",
                "evidence": "2-10x speedup similar to C++ vector::reserve",
            },
            # ================================================================
            # CROSS-LANGUAGE SYNTAX PATTERNS
            # ================================================================
            "generic_early_return": {
                "regex": r"^\s*(if|when)\s*\([^)]+\)\s*\{?\s*return",
                "category": "control_flow",
                "impact": "medium",
                "description": "Early return/guard clause pattern",
                "detection_method": "regex",
                "evidence": "Reduces nesting and branch complexity",
            },
        }

    def _remove_comments(self, code: str, language: str) -> str:
        """
        Remove comments from code based on language.
        This prevents false positives from pattern matching in comments.
        """
        lang = language.lower()

        # Remove single-line comments
        if lang in ('python',):
            # Python: remove # comments
            code = re.sub(r'#.*$', '', code, flags=re.MULTILINE)
        elif lang in ('c', 'cpp', 'c++', 'java', 'javascript', 'js', 'typescript', 'ts', 'go', 'rust'):
            # C-style: remove // comments
            code = re.sub(r'//.*$', '', code, flags=re.MULTILINE)
            # Remove /* */ block comments
            code = re.sub(r'/\*.*?\*/', '', code, flags=re.DOTALL)

        return code

    def _count_pattern_matches(self, code: str, regex: str) -> int:
        """Count the number of actual matches for a pattern."""
        try:
            matches = re.findall(regex, code, re.MULTILINE | re.IGNORECASE)
            return len(matches)
        except re.error:
            return 0

    def detect_patterns(
        self, base_code: str, llm_code: str, language: str
    ) -> List[PatternMatch]:
        """
        Detect all patterns comparing base and LLM code.
        Returns only patterns introduced by LLM (not present in base).

        Detection methods:
        1. Remove comments from both code samples
        2. Regex-based detection with match counting
        3. AST-based detection for supported languages (Python, JavaScript, Java)

        Improvements:
        - Comments are removed to avoid false positives
        - Pattern presence requires at least one actual match
        - Match counts are compared (LLM should have MORE matches than base for introduction)
        """
        if not base_code or not llm_code:
            return []

        lang_lower = language.lower()
        detected = []

        # Remove comments to avoid false positives
        base_code_clean = self._remove_comments(base_code, lang_lower)
        llm_code_clean = self._remove_comments(llm_code, lang_lower)

        # ===== REGEX-BASED DETECTION =====
        for pattern_name, pattern_def in self.patterns.items():
            # Check language applicability
            if not self._is_pattern_applicable(pattern_name, lang_lower):
                continue

            regex = pattern_def["regex"]

            # Count matches instead of just checking presence
            base_matches = self._count_pattern_matches(base_code_clean, regex)
            llm_matches = self._count_pattern_matches(llm_code_clean, regex)

            # A pattern is "present" if it has at least one match
            present_in_base = base_matches > 0
            present_in_llm = llm_matches > 0

            # Create pattern match object with match counts
            # The is_llm_introduced property will handle the logic
            match = PatternMatch(
                name=pattern_name,
                category=pattern_def["category"],
                language=language,
                energy_impact=pattern_def["impact"],
                present_in_base=present_in_base,
                present_in_llm=present_in_llm,
                base_match_count=base_matches,
                llm_match_count=llm_matches,
            )

            detected.append(match)

        # ===== AST-BASED DETECTION =====
        # Add language-specific AST patterns
        if lang_lower == "python":
            ast_patterns = self.detect_ast_patterns_python(base_code, llm_code)
            detected.extend(ast_patterns)

        return detected

    def _is_pattern_applicable(self, pattern_name: str, language: str) -> bool:
        """
        Check if pattern applies to this language

        Pattern prefixes:
        - G1-G6: Generic patterns (apply to all languages)
        - PY: Python-specific
        - JS: JavaScript/TypeScript-specific
        - J: Java-specific
        - C: C-specific
        - CPP: C++-specific
        - GO: Go-specific
        - generic_: Cross-language syntax patterns
        """
        # Normalize language to lowercase for comparison
        lang = language.lower().strip()

        # Python patterns
        if pattern_name.startswith("PY") and lang != "python":
            return False

        # JavaScript/TypeScript patterns
        if pattern_name.startswith("JS") and lang not in (
            "javascript",
            "js",
            "typescript",
            "ts",
        ):
            return False

        # Java patterns (check for J but not JS, not GO, etc.)
        if pattern_name.startswith("J") and not pattern_name.startswith("JS"):
            # J1, J2, J3, J4, J5 patterns apply only to Java
            if lang not in ("java"):
                return False

        # C patterns (C1, C2, C3, C4, C5 - not CPP or GO patterns)
        if pattern_name.startswith("C") and not pattern_name.startswith("CPP"):
            # Must be exactly C language (not C++, not Go which has C in name somewhere)
            if lang not in ("c"):
                return False

        # C++ patterns
        if pattern_name.startswith("CPP"):
            if lang not in ("c++", "cpp"):
                return False

        # Go patterns
        if pattern_name.startswith("GO"):
            if lang not in ("go", "golang"):
                return False

        # Generic patterns (G1-G6, generic_*) apply to all languages
        return True

    def detect_ast_patterns_python(
        self, base_code: str, llm_code: str
    ) -> List[PatternMatch]:
        """
        Detect Python-specific AST patterns

        Includes:
        - Nested loops (O(n²) detection)
        - Allocations in loops
        - Loop-invariant code motion opportunities
        - Comprehensions vs explicit loops
        """
        if not base_code or not llm_code:
            return []

        patterns = []

        try:
            base_tree = ast.parse(base_code)
            llm_tree = ast.parse(llm_code)

            # Detect nested loops (O(n²) candidate)
            def count_nested_loops(tree):
                """Count nested for/while loops"""
                nested_count = 0
                for node in ast.walk(tree):
                    if isinstance(node, (ast.For, ast.While)):
                        # Check if this loop contains another loop
                        for child in ast.walk(node):
                            if child != node and isinstance(
                                child, (ast.For, ast.While)
                            ):
                                nested_count += 1
                                break
                return nested_count

            base_nested = count_nested_loops(base_tree)
            llm_nested = count_nested_loops(llm_tree)

            patterns.append(
                PatternMatch(
                    name="PY_AST_nested_loops",
                    category="algorithmic",
                    language="python",
                    energy_impact="high",
                    present_in_base=base_nested > 0,
                    present_in_llm=llm_nested > 0,
                )
            )

            # Detect allocations in loops (list/dict creation inside loops)
            def has_allocation_in_loop(tree):
                """Check for list/dict creation inside loops"""
                for node in ast.walk(tree):
                    if isinstance(node, (ast.For, ast.While)):
                        for child in ast.walk(node):
                            if isinstance(
                                child, (ast.List, ast.Dict, ast.ListComp, ast.Call)
                            ):
                                if isinstance(child, ast.Call) and hasattr(
                                    child.func, "id"
                                ):
                                    if child.func.id in ("list", "dict", "set"):
                                        return True
                                elif isinstance(child, (ast.List, ast.Dict)):
                                    return True
                return False

            base_alloc = has_allocation_in_loop(base_tree)
            llm_alloc = has_allocation_in_loop(llm_tree)

            patterns.append(
                PatternMatch(
                    name="PY_AST_allocation_in_loop",
                    category="memory",
                    language="python",
                    energy_impact="high",
                    present_in_base=base_alloc,
                    present_in_llm=llm_alloc,
                )
            )

            # Detect comprehensions
            base_comp = any(
                isinstance(
                    n, (ast.ListComp, ast.DictComp, ast.SetComp, ast.GeneratorExp)
                )
                for n in ast.walk(base_tree)
            )
            llm_comp = any(
                isinstance(
                    n, (ast.ListComp, ast.DictComp, ast.SetComp, ast.GeneratorExp)
                )
                for n in ast.walk(llm_tree)
            )

            patterns.append(
                PatternMatch(
                    name="PY_AST_comprehension",
                    category="algorithmic",
                    language="python",
                    energy_impact="medium",
                    present_in_base=base_comp,
                    present_in_llm=llm_comp,
                )
            )

        except SyntaxError:
            pass  # Invalid Python code

        return patterns


# ============================================================================
# DATA STRUCTURES (from original - unchanged)
# ============================================================================


@dataclass
class MetricImprovement:
    """Single metric improvement"""

    improvement_percentage: float
    label: str
    is_outlier: bool
    base_value: float
    llm_value: float

    def is_valid(self) -> bool:
        return (
            self.improvement_percentage != -999
            and self.label != "invalid"
            and not self.is_outlier
        )


@dataclass
class EntryAnalysis:
    """Complete analysis for one entry"""

    entry_id: str
    cluster_name: str
    language: str
    llm_type: str
    prompt_version: str
    cpu_improvement: MetricImprovement
    ram_improvement: MetricImprovement
    time_improvement: MetricImprovement
    similarity_index: Optional[float] = None
    patterns: List[PatternMatch] = field(default_factory=list)
    base_code_path: str = ""
    llm_code_path: str = ""


@dataclass
class ClusterStats:
    """Cluster statistics"""

    cluster_name: str
    total_entries: int
    languages: Set[str]
    avg_cpu_improvement: Optional[float] = None
    avg_ram_improvement: Optional[float] = None
    avg_time_improvement: Optional[float] = None
    avg_similarity: Optional[float] = None
    selected: bool = False


@dataclass
class PatternCorrelation:
    """Correlation between a pattern and performance metrics"""

    pattern_name: str
    frequency: int

    # SEPARATE correlations per metric
    cpu_avg_improvement: Optional[float] = None
    cpu_std: Optional[float] = None
    cpu_sample_size: int = 0

    ram_avg_improvement: Optional[float] = None
    ram_std: Optional[float] = None
    ram_sample_size: int = 0

    time_avg_improvement: Optional[float] = None
    time_std: Optional[float] = None
    time_sample_size: int = 0


# ============================================================================
# MAIN ANALYZER
# ============================================================================


class PatternPerformanceAnalyzer:
    """
    Analyzer che correttamente:
    1. Carica dati da clusters_improvements_data/
    2. Usa EnergyPatternDetector per individuare pattern
    3. Calcola correlazioni separate per CPU, RAM, Time
    4. Genera visualizzazioni e report
    """

    def __init__(self):
        self.improvements_dir = utility_paths.CLUSTERS_IMPROVEMENTS_DATA_FILEPATH
        self.clusters_dir = utility_paths.CLUSTERS_DIR_FILEPATH
        self.dataset_dir = utility_paths.DATASET_DIR
        self.output_dir = (
            utility_paths.METRICS_DIR_FILEPATH / "patterns" / "pattern_analysis"
        )
        self.output_dir.mkdir(parents=True, exist_ok=True)

        # Initialize pattern detector
        self.pattern_detector = EnergyPatternDetector()

        # Data storage
        self.entries: List[EntryAnalysis] = []
        self.cluster_stats: Dict[str, ClusterStats] = {}

        logger.info("=" * 80)
        logger.info("PATTERN-PERFORMANCE ANALYZER")
        logger.info("=" * 80)
        logger.info(f"Improvements source: {self.improvements_dir}")
        logger.info(f"Output directory: {self.output_dir}")
        logger.info("")

    # ... (All original methods: parse_metric, find_code_paths, process_cluster, etc. - UNCHANGED)

    def parse_metric(self, data: Dict) -> MetricImprovement:
        """Parse metric improvement from JSON"""
        return MetricImprovement(
            improvement_percentage=data.get("improvement_percentage", -999),
            label=data.get("label", "invalid"),
            is_outlier=data.get("is_outlier", False),
            base_value=data.get("base_value", 0),
            llm_value=data.get("llm_value", 0),
        )

    def find_code_paths(
        self,
        cluster_metadata: Dict,
        entry_id: str,
        language: str,
        llm_type: str,
        prompt_v: int,
    ) -> tuple:
        """Find base and LLM code file paths from cluster metadata"""
        
        lang_key = language.lower().strip()

        lang_entries = cluster_metadata.get(lang_key, [])

        for entry in lang_entries:
            if entry.get("id") != entry_id:
                continue

            # Base code path: relative to DATASET_DIR
            base_relative = entry.get("codeSnippetFilePath", "")

            # Find LLM path: absolute path in 'path' field
            llms = entry.get("LLMs", [])
            for llm in llms:
                if llm.get("type") == llm_type:
                    llm_absolute = llm.get("path", "")
                    # Check if this is the right prompt version
                    if f"_v{prompt_v}." in llm_absolute:
                        return base_relative, llm_absolute

        return None, None

    def find_similarity(
        self,
        cluster_metadata: Dict,
        entry_id: str,
        language: str,
        llm_type: str,
        prompt_v: int,
    ) -> Optional[float]:
        """Find similarity index"""
        lang_key = language.lower().strip()
        lang_entries = cluster_metadata.get(lang_key, [])

        for entry in lang_entries:
            if entry.get("id") != entry_id:
                continue

            llms = entry.get("LLMs", [])
            for llm in llms:
                if llm.get("type") == llm_type:
                    path = llm.get("path", "")
                    if f"_v{prompt_v}." in path:
                        return llm.get("similarity_index")
        return None

    def detect_patterns_for_entry(
        self, base_relative: str, llm_absolute: str, language: str
    ) -> List[PatternMatch]:
        """Detect patterns introduced by LLMs using EnergyPatternDetector"""
        # Build full paths
        # Base path: relative to DATASET_DIR
        full_base_path = utility_paths.DATASET_DIR / base_relative
        # LLM path: already absolute
        full_llm_path = Path(llm_absolute)

        # Read code files
        try:
            if not full_base_path.exists():
                logger.debug(f"Base path not found: {full_base_path}")
                return []

            if not full_llm_path.exists():
                logger.debug(f"LLM path not found: {full_llm_path}")
                return []

            # CRITICAL FIX: Handle directories for C/C++
            # For C/C++, the base path is often a directory, find the main source file
            if full_base_path.is_dir():
                lang_lower = language.lower()
                # Find the main source file
                source_files = []
                if lang_lower in ('c', 'cpp', 'c++'):
                    extensions = ['.c', '.cpp', '.cc', '.cxx'] if lang_lower in ('cpp', 'c++') else ['.c']
                    for ext in extensions:
                        source_files.extend(full_base_path.glob(f'*{ext}'))

                    if not source_files:
                        logger.debug(f"No source files found in directory: {full_base_path}")
                        return []

                    # Use the first non-test source file
                    for src in source_files:
                        if 'test' not in src.name.lower():
                            full_base_path = src
                            break
                    else:
                        full_base_path = source_files[0]

            with open(full_base_path, "r", encoding="utf-8") as f:
                base_code = f.read()
            with open(full_llm_path, "r", encoding="utf-8") as f:
                llm_code = f.read()

            if not base_code or not llm_code:
                return []

            # Use EnergyPatternDetector
            patterns = self.pattern_detector.detect_patterns(
                base_code, llm_code, language
            )

            # Return only LLM-introduced patterns
            return [p for p in patterns if p.is_llm_introduced]

        except Exception as e:
            logger.debug(f"Error detecting patterns for {base_relative}: {e}")
            return []

    def process_cluster(self, cluster_name: str) -> ClusterStats:
        """Process a single cluster (ORIGINAL LOGIC)"""
        imp_file = self.improvements_dir / f"improvements_cluster_{cluster_name}.json"
        if not imp_file.exists():
            return None

        improvements = general_utils.read_json(imp_file)
        if not improvements:
            return None

        meta_file = self.clusters_dir / f"cluster_{cluster_name}.json"
        metadata = general_utils.read_json(meta_file) if meta_file.exists() else {}

        stats = ClusterStats(
            cluster_name=cluster_name, total_entries=len(improvements), languages=set()
        )
        cpu_vals, ram_vals, time_vals, sim_vals = [], [], [], []

        for entry_id, entry_data in improvements.items():
            base_data = entry_data.get("base_5_exec_data", {})
            imp_data = entry_data.get("improvements_data", {})

            if not imp_data:
                continue

            language = base_data.get("language", "unknown")
            stats.languages.add(language)

            for llm_type in ["openAI", "claude", "gemini"]:
                llm_imp = imp_data.get(llm_type, {})
                for prompt_v in range(1, 5):
                    prompt_key = f"prompt_v{prompt_v}"
                    entry_imp = llm_imp.get(prompt_key, {})

                    if not entry_imp or entry_imp.get("language") == "":
                        continue

                    cpu_impr = self.parse_metric(entry_imp.get("CPU_usage", {}))
                    ram_impr = self.parse_metric(entry_imp.get("RAM_usage", {}))
                    time_impr = self.parse_metric(
                        entry_imp.get("execution_time_ms", {})
                    )

                    if not (
                        cpu_impr.is_valid()
                        and ram_impr.is_valid()
                        and time_impr.is_valid()
                    ):
                        continue

                    base_path, llm_path = self.find_code_paths(
                        metadata, entry_id, language, llm_type, prompt_v
                    )
                    similarity = self.find_similarity(
                        metadata, entry_id, language, llm_type, prompt_v
                    )
                    patterns = []
                    if base_path and llm_path:
                        patterns = self.detect_patterns_for_entry(
                            base_path, llm_path, language
                        )

                    entry_analysis = EntryAnalysis(
                        entry_id=entry_id,
                        cluster_name=cluster_name,
                        language=language,
                        llm_type=llm_type,
                        prompt_version=prompt_key,
                        cpu_improvement=cpu_impr,
                        ram_improvement=ram_impr,
                        time_improvement=time_impr,
                        similarity_index=similarity,
                        patterns=patterns,
                        base_code_path=base_path or "",
                        llm_code_path=llm_path or "",
                    )

                    self.entries.append(entry_analysis)

                    cpu_vals.append(cpu_impr.improvement_percentage)
                    ram_vals.append(ram_impr.improvement_percentage)
                    time_vals.append(time_impr.improvement_percentage)
                    if similarity is not None:
                        sim_vals.append(similarity)

        stats.avg_cpu_improvement = np.mean(cpu_vals) if cpu_vals else None
        stats.avg_ram_improvement = np.mean(ram_vals) if ram_vals else None
        stats.avg_time_improvement = np.mean(time_vals) if time_vals else None
        stats.avg_similarity = np.mean(sim_vals) if sim_vals else None

        return stats

    def process_all_clusters(self):
        """Process all clusters (ORIGINAL LOGIC)"""
        logger.info("STEP 1: Processing all clusters")
        logger.info("-" * 80)

        improvement_files = sorted(
            self.improvements_dir.glob("improvements_cluster_*.json")
        )
        total = len(improvement_files)

        for i, filepath in enumerate(improvement_files, 1):
            cluster_name = filepath.stem.replace("improvements_cluster_", "")
            try:
                stats = self.process_cluster(cluster_name)
                if stats:
                    self.cluster_stats[cluster_name] = stats
                    if i % 20 == 0:
                        logger.info(f"  Processed {i}/{total} clusters...")
            except Exception as e:
                logger.error(f"  Error processing {cluster_name}: {e}")

        logger.info(f"\n✓ Processed {len(self.cluster_stats)} clusters successfully")
        logger.info(f"✓ Total entries: {len(self.entries)}")

    def compute_pattern_correlations(self) -> List[PatternCorrelation]:
        """Compute correlations (ORIGINAL LOGIC)"""
        logger.info("\nSTEP 2: Computing pattern-metric correlations")
        logger.info("-" * 80)

        pattern_data = defaultdict(
            lambda: {
                "cpu_improvements": [],
                "ram_improvements": [],
                "time_improvements": [],
            }
        )

        for entry in self.entries:
            for pattern in entry.patterns:
                data = pattern_data[pattern.name]
                if entry.cpu_improvement.is_valid():
                    data["cpu_improvements"].append(
                        entry.cpu_improvement.improvement_percentage
                    )
                if entry.ram_improvement.is_valid():
                    data["ram_improvements"].append(
                        entry.ram_improvement.improvement_percentage
                    )
                if entry.time_improvement.is_valid():
                    data["time_improvements"].append(
                        entry.time_improvement.improvement_percentage
                    )

        correlations = []
        for pattern_name, data in pattern_data.items():
            # Frequency = number of entries where this pattern appears
            # (not 3x for each metric, just count unique entries)
            frequency = len(data["cpu_improvements"])  # Each entry contributes once per metric

            correlation = PatternCorrelation(
                pattern_name=pattern_name,
                frequency=frequency,
            )

            if data["cpu_improvements"]:
                correlation.cpu_avg_improvement = np.mean(data["cpu_improvements"])
                correlation.cpu_std = (
                    np.std(data["cpu_improvements"])
                    if len(data["cpu_improvements"]) > 1
                    else 0
                )
                correlation.cpu_sample_size = len(data["cpu_improvements"])

            if data["ram_improvements"]:
                correlation.ram_avg_improvement = np.mean(data["ram_improvements"])
                correlation.ram_std = (
                    np.std(data["ram_improvements"])
                    if len(data["ram_improvements"]) > 1
                    else 0
                )
                correlation.ram_sample_size = len(data["ram_improvements"])

            if data["time_improvements"]:
                correlation.time_avg_improvement = np.mean(data["time_improvements"])
                correlation.time_std = (
                    np.std(data["time_improvements"])
                    if len(data["time_improvements"]) > 1
                    else 0
                )
                correlation.time_sample_size = len(data["time_improvements"])

            correlations.append(correlation)

        correlations.sort(key=lambda x: x.frequency, reverse=True)
        logger.info(f"✓ Computed correlations for {len(correlations)} patterns")
        return correlations

    def select_best_clusters(
        self, similarity_threshold: float = 65.0, min_improvement: float = -10.0
    ) -> List[str]:
        """Select clusters (ORIGINAL LOGIC)"""
        logger.info("\nSTEP 3: Selecting best clusters for analysis")
        logger.info("-" * 80)

        selected = []
        for name, stats in self.cluster_stats.items():
            has_low_sim = (
                stats.avg_similarity is not None
                and stats.avg_similarity < similarity_threshold
            )
            has_good_impr = any(
                [
                    stats.avg_cpu_improvement is not None
                    and stats.avg_cpu_improvement < min_improvement,
                    stats.avg_ram_improvement is not None
                    and stats.avg_ram_improvement < min_improvement,
                    stats.avg_time_improvement is not None
                    and stats.avg_time_improvement < min_improvement,
                ]
            )

            if has_low_sim and has_good_impr:
                selected.append(name)
                stats.selected = True

        logger.info(f"✓ Selected {len(selected)}/{len(self.cluster_stats)} clusters")
        return selected

    def export_results(self, correlations: List[PatternCorrelation]):
        """Export results (ORIGINAL LOGIC)"""
        logger.info("\nSTEP 4: Exporting results")
        logger.info("-" * 80)

        # Pattern correlations
        corr_export = []
        for corr in correlations:
            corr_export.append(
                {
                    "pattern": corr.pattern_name,
                    "frequency": corr.frequency,
                    "cpu_avg_improvement": corr.cpu_avg_improvement,
                    "cpu_std": corr.cpu_std,
                    "cpu_sample_size": corr.cpu_sample_size,
                    "ram_avg_improvement": corr.ram_avg_improvement,
                    "ram_std": corr.ram_std,
                    "ram_sample_size": corr.ram_sample_size,
                    "time_avg_improvement": corr.time_avg_improvement,
                    "time_std": corr.time_std,
                    "time_sample_size": corr.time_sample_size,
                }
            )

        corr_file = self.output_dir / "pattern_metric_correlations.json"
        with open(corr_file, "w", encoding="utf-8") as f:
            json.dump(corr_export, f, indent=2, ensure_ascii=False)
        logger.info(f"✓ Pattern correlations: {corr_file}")

        # Cluster stats
        cluster_export = {}
        for name, stats in self.cluster_stats.items():
            cluster_export[name] = {
                "total_entries": stats.total_entries,
                "languages": list(stats.languages),
                "avg_cpu_improvement": stats.avg_cpu_improvement,
                "avg_ram_improvement": stats.avg_ram_improvement,
                "avg_time_improvement": stats.avg_time_improvement,
                "avg_similarity": stats.avg_similarity,
                "selected": stats.selected,
            }

        cluster_file = self.output_dir / "cluster_statistics.json"
        with open(cluster_file, "w", encoding="utf-8") as f:
            json.dump(cluster_export, f, indent=2, ensure_ascii=False)
        logger.info(f"✓ Cluster statistics: {cluster_file}")

        # Summary
        summary = {
            "total_clusters": len(self.cluster_stats),
            "selected_clusters": sum(
                1 for s in self.cluster_stats.values() if s.selected
            ),
            "total_entries": len(self.entries),
            "total_patterns_detected": sum(len(e.patterns) for e in self.entries),
            "unique_patterns": len(correlations),
            "entries_with_patterns": sum(1 for e in self.entries if e.patterns),
        }

        summary_file = self.output_dir / "analysis_summary.json"
        with open(summary_file, "w", encoding="utf-8") as f:
            json.dump(summary, f, indent=2, ensure_ascii=False)
        logger.info(f"✓ Analysis summary: {summary_file}")

    # ========================================================================
    # NEW: EXPORT TOP CASE STUDIES
    # ========================================================================

    def export_top_case_studies(self, top_n: int = 3):
        """
        Export the top N case studies for thesis presentation using strategic selection.

        STRATEGIC SELECTION LOGIC:
        Phase 1: Filter valid candidates (patterns, metrics, significant improvement)
        Phase 2: Find best "champion" per language
        Phase 3: Select top N languages with highest improvements
        Phase 4: Export the champions

        This ensures diversity (one per language) and impact (best improvements).
        """
        logger.info("\n" + "=" * 80)
        logger.info(f"EXPORTING TOP {top_n} CASE STUDIES (STRATEGIC SELECTION)")
        logger.info("=" * 80)

        # ===== PHASE 1: FILTER VALID CANDIDATES =====
        logger.info("\nPhase 1: Filtering valid candidates...")

        candidates = []
        for entry in self.entries:
            # Must have patterns introduced
            if not entry.patterns:
                continue

            # Must have valid metrics
            if not (
                entry.cpu_improvement.is_valid()
                and entry.ram_improvement.is_valid()
                and entry.time_improvement.is_valid()
            ):
                continue

            # Must show significant improvement in at least ONE metric
            # (>20% reduction in CPU, RAM, or Time)
            has_significant_improvement = (
                entry.cpu_improvement.improvement_percentage < -20.0
                or entry.ram_improvement.improvement_percentage < -20.0
                or entry.time_improvement.improvement_percentage < -20.0
            )

            if not has_significant_improvement:
                continue

            # Must have code paths
            if not entry.base_code_path or not entry.llm_code_path:
                continue

            candidates.append(entry)

        if not candidates:
            logger.warning("No valid candidates found for case studies!")
            return

        logger.info(f"  ✓ Found {len(candidates)} valid candidates with significant improvements")

        # ===== PHASE 2: FIND BEST CHAMPION PER LANGUAGE =====
        logger.info("\nPhase 2: Finding best champion per language...")

        # Group candidates by language
        by_language = defaultdict(list)
        for entry in candidates:
            by_language[entry.language].append(entry)

        logger.info(f"  Languages represented: {list(by_language.keys())}")

        # Find the champion for each language
        # Champion = entry with best (most negative) improvement across all metrics
        language_champions = {}

        for language, entries in by_language.items():
            # Calculate a composite "impact score" for each entry
            # Prioritize execution_time, then CPU, then RAM
            def calculate_impact_score(entry):
                """
                Calculate impact score - lower is better (more negative = more improvement)
                Priority: execution_time (weight=3) > CPU (weight=2) > RAM (weight=1)
                """
                time_imp = entry.time_improvement.improvement_percentage
                cpu_imp = entry.cpu_improvement.improvement_percentage
                ram_imp = entry.ram_improvement.improvement_percentage

                # Weighted average - lower (more negative) is better
                score = (3 * time_imp + 2 * cpu_imp + 1 * ram_imp) / 6
                return score

            # Find the entry with the lowest (best) impact score
            champion = min(entries, key=calculate_impact_score)
            language_champions[language] = champion

            score = calculate_impact_score(champion)
            logger.info(f"  {language}: Champion found with impact score {score:.2f}%")
            logger.info(f"    - Entry ID: {champion.entry_id}")
            logger.info(f"    - Time: {champion.time_improvement.improvement_percentage:.1f}%")
            logger.info(f"    - CPU: {champion.cpu_improvement.improvement_percentage:.1f}%")
            logger.info(f"    - RAM: {champion.ram_improvement.improvement_percentage:.1f}%")

        # ===== PHASE 3: SELECT TOP N LANGUAGES =====
        logger.info(f"\nPhase 3: Selecting top {top_n} languages by impact...")

        # Sort champions by their impact score
        sorted_champions = sorted(
            language_champions.items(),
            key=lambda x: (
                3 * x[1].time_improvement.improvement_percentage +
                2 * x[1].cpu_improvement.improvement_percentage +
                1 * x[1].ram_improvement.improvement_percentage
            ) / 6
        )

        # Select top N
        top_champions = sorted_champions[:top_n]

        logger.info(f"  ✓ Selected {len(top_champions)} language champions:")
        for rank, (language, champion) in enumerate(top_champions, 1):
            logger.info(f"    #{rank}: {language} - Entry {champion.entry_id}")

        # ===== PHASE 4: EXPORT =====
        logger.info("\nPhase 4: Exporting case studies...")

        top_candidates = [champion for _, champion in top_champions]

        logger.info(f"\nFinal selection: {len(top_candidates)} case studies\n")

        # Build case study JSON
        case_studies = []

        for rank, entry in enumerate(top_candidates, 1):
            logger.info(f"Processing Case Study #{rank}: {entry.entry_id}")
            logger.info(f"  Cluster: {entry.cluster_name}, Language: {entry.language}")
            logger.info(f"  LLM: {entry.llm_type}, Prompt: {entry.prompt_version}")
            logger.info(
                f"  Time improvement: {entry.time_improvement.improvement_percentage:.1f}%"
            )
            logger.info(f"  Patterns: {len(entry.patterns)}")

            # Read code files
            base_code_content = ""
            llm_code_content = ""

            try:
                # Base code
                full_base_path = utility_paths.DATASET_DIR / entry.base_code_path

                # Handle C/C++ directories
                if full_base_path.is_dir():
                    lang_lower = entry.language.lower()
                    if lang_lower in ("c", "cpp", "c++"):
                        extensions = (
                            [".c", ".cpp"] if lang_lower in ("cpp", "c++") else [".c"]
                        )
                        source_files = []
                        for ext in extensions:
                            source_files.extend(full_base_path.glob(f"*{ext}"))
                        if source_files:
                            for src in source_files:
                                if "test" not in src.name.lower():
                                    full_base_path = src
                                    break
                            else:
                                full_base_path = source_files[0]

                with open(full_base_path, "r", encoding="utf-8", errors="ignore") as f:
                    base_code_content = f.read()

                # LLM code
                full_llm_path = Path(entry.llm_code_path)
                with open(full_llm_path, "r", encoding="utf-8", errors="ignore") as f:
                    llm_code_content = f.read()

            except Exception as e:
                logger.error(f"  Error reading code files: {e}")
                continue

            # Format pattern names
            def format_pattern_name(name: str) -> str:
                """
                Format pattern name for display.
                Check longer prefixes BEFORE shorter ones (GO before G, JS before J, CPP before C)
                """
                # Check GO patterns first (before generic G)
                if name.startswith("GO"):
                    name = name[2:]
                    if name and name[0].isdigit():
                        name = name[1:]
                    if name.startswith("_"):
                        name = name[1:]
                    return f"(go) {name.replace('_', ' ')}"

                # Check generic patterns (G followed by digit)
                elif name.startswith("G") and len(name) > 1 and name[1].isdigit():
                    name = name[2:] if len(name) > 2 else ""
                    if name.startswith("_"):
                        name = name[1:]
                    return f"(generic) {name.replace('_', ' ')}"

                # Check Python patterns
                elif name.startswith("PY"):
                    name = name[2:] if len(name) > 2 else name
                    if name and name[0].isdigit():
                        name = name[1:]
                    if name.startswith("_"):
                        name = name[1:]
                    return f"(py) {name.replace('_', ' ')}"

                # Check JavaScript patterns (before Java)
                elif name.startswith("JS"):
                    name = name[2:]
                    if name and name[0].isdigit():
                        name = name[1:]
                    if name.startswith("_"):
                        name = name[1:]
                    return f"(js) {name.replace('_', ' ')}"

                # Check Java patterns
                elif name.startswith("J") and not name.startswith("JS"):
                    name = name[1:]
                    if name and name[0].isdigit():
                        name = name[1:]
                    if name.startswith("_"):
                        name = name[1:]
                    return f"(java) {name.replace('_', ' ')}"

                # Check C++ patterns (before C)
                elif name.startswith("CPP"):
                    name = name[3:]
                    if name and name[0].isdigit():
                        name = name[1:]
                    if name.startswith("_"):
                        name = name[1:]
                    return f"(c++) {name.replace('_', ' ')}"

                # Check C patterns
                elif name.startswith("C") and not name.startswith("CPP"):
                    name = name[1:]
                    if name and name[0].isdigit():
                        name = name[1:]
                    if name.startswith("_"):
                        name = name[1:]
                    return f"(c) {name.replace('_', ' ')}"

                # Unknown format
                else:
                    return name.replace("_", " ")

            # Build patterns list with regex
            patterns_introduced = []
            for pattern in entry.patterns:
                # Get regex from pattern detector
                regex_pattern = self.pattern_detector.patterns.get(
                    pattern.name, {}
                ).get("regex", "")

                patterns_introduced.append(
                    {
                        "name": pattern.name,
                        "formatted_name": format_pattern_name(pattern.name),
                        "regex_to_highlight": regex_pattern,
                    }
                )

            # Build case study object
            case_study = {
                "case_study_rank": rank,
                "entry_id": entry.entry_id,
                "cluster_name": entry.cluster_name,
                "language": entry.language,
                "llm_type": entry.llm_type,
                "prompt_version": entry.prompt_version,
                "patterns_introduced": patterns_introduced,
                "metrics": {
                    "CPU_usage": {
                        "base_avg_5_exec": entry.cpu_improvement.base_value,
                        "llm_avg_5_exec": entry.cpu_improvement.llm_value,
                        "improvement_perc": entry.cpu_improvement.improvement_percentage,
                    },
                    "RAM_usage": {
                        "base_avg_5_exec": entry.ram_improvement.base_value,
                        "llm_avg_5_exec": entry.ram_improvement.llm_value,
                        "improvement_perc": entry.ram_improvement.improvement_percentage,
                    },
                    "execution_time_ms": {
                        "base_avg_5_exec": entry.time_improvement.base_value,
                        "llm_avg_5_exec": entry.time_improvement.llm_value,
                        "improvement_perc": entry.time_improvement.improvement_percentage,
                    },
                },
                "code_base": base_code_content,
                "code_llm": llm_code_content,
                "base_code_path": str(full_base_path),
                "llm_code_path": str(full_llm_path),
            }

            case_studies.append(case_study)
            logger.info(f"  ✓ Case study #{rank} prepared\n")

        # Save to JSON
        output_file = self.output_dir / "top_3_case_studies.json"
        with open(output_file, "w", encoding="utf-8") as f:
            json.dump(case_studies, f, indent=2, ensure_ascii=False)

        logger.info("=" * 80)
        logger.info(f"✓ Exported {len(case_studies)} case studies to: {output_file}")
        logger.info("=" * 80 + "\n")

    def run_complete_analysis(self):
        """Run the complete analysis pipeline (MODIFIED)"""
        # Step 1: Process all clusters
        self.process_all_clusters()

        # Step 2: Compute pattern correlations
        correlations = self.compute_pattern_correlations()

        # Step 3: Select best clusters
        selected = self.select_best_clusters()

        # Step 4: Export results
        self.export_results(correlations)

        # Step 5: Export case studies (NEW)
        self.export_top_case_studies(top_n=3)

        # Step 6: Create visualizations
        try:
            from metrics.patterns.pattern_visualizer import PatternVisualizerV4

            visualizer = PatternVisualizerV4(self.output_dir)

            visualizer.set_statistics(
                total_clusters=len(self.cluster_stats),
                total_entries=len(self.entries),
                total_patterns=sum(len(e.patterns) for e in self.entries),
            )

            # Convert correlations
            corr_dicts = []
            for corr in correlations:
                corr_dicts.append(
                    {
                        "pattern": corr.pattern_name,
                        "frequency": corr.frequency,
                        "cpu_avg_improvement": corr.cpu_avg_improvement,
                        "cpu_std": corr.cpu_std,
                        "cpu_sample_size": corr.cpu_sample_size,
                        "ram_avg_improvement": corr.ram_avg_improvement,
                        "ram_std": corr.ram_std,
                        "ram_sample_size": corr.ram_sample_size,
                        "time_avg_improvement": corr.time_avg_improvement,
                        "time_std": corr.time_std,
                        "time_sample_size": corr.time_sample_size,
                    }
                )

            # Convert cluster stats
            cluster_dict = {}
            for name, stats in self.cluster_stats.items():
                cluster_dict[name] = {
                    "avg_similarity": stats.avg_similarity,
                    "avg_cpu_improvement": stats.avg_cpu_improvement,
                    "avg_ram_improvement": stats.avg_ram_improvement,
                    "avg_time_improvement": stats.avg_time_improvement,
                }

            # Create aggregate visualizations
            visualizer.create_all_visualizations(
                cluster_dict,
                corr_dicts,
                selected,
                similarity_threshold=SIMILARITY_THRESHOLD,
                improvement_threshold=IMPROVEMENT_THRESHOLD,
            )

            # NEW: Create case study visualizations
            case_studies_file = self.output_dir / "top_3_case_studies.json"
            if case_studies_file.exists():
                logger.info("\n" + "=" * 80)
                logger.info("GENERATING CASE STUDY VISUALIZATIONS")
                logger.info("=" * 80)

                with open(case_studies_file, "r", encoding="utf-8") as f:
                    case_studies_data = json.load(f)

                # Individual metrics comparison charts (one per case study)
                visualizer.plot_case_studies_metrics(case_studies_data)

                logger.info("=" * 80)
                logger.info("CASE STUDY VISUALIZATIONS COMPLETE")
                logger.info("=" * 80 + "\n")

        except Exception as e:
            logger.error(f"Error creating visualizations: {e}")
            import traceback

            traceback.print_exc()

        logger.info("\n" + "=" * 80)
        logger.info("ANALYSIS COMPLETE!")
        logger.info("=" * 80)
        logger.info(f"Results saved to: {self.output_dir}\n")


# ============================================================================
# MAIN
# ============================================================================


def main():
    """Main execution"""
    analyzer = PatternPerformanceAnalyzer()
    analyzer.run_complete_analysis()


if __name__ == "__main__":
    main()
