"""
GitHub Ingestor for Exercism Solutions

This module automates the ingestion of code-test pairs from GitHub repositories
containing Exercism solutions. It validates completeness (source, tests, headers, build files),
avoids duplicates, and integrates entries into the project's dataset and cluster structure.

"""

import requests
import logging
import time
import base64
import shutil
from pathlib import Path
from typing import List, Dict, Optional, Set, Tuple
from dataclasses import dataclass
from datetime import datetime
from concurrent.futures import ThreadPoolExecutor, as_completed
from threading import Lock
import sys
import os

# Add parent directory to path for imports
sys.path.append(str(Path(__file__).parent.parent))

from utility_dir.utility_paths import (
    DATASET_DIR,
    CLUSTERS_DIR_FILEPATH,
)
from utility_dir.general_utils import (
    read_json,
    write_json,
    load_github_token,
    RateLimiter,
    LANGUAGES,
    get_ext_by_lang,
)


# Import test execution components
try:
    from run_tests_on_clusters.run_tests_on_cluster import (
        TestExecutor,
        ContainerManager,
    )

    TEST_VALIDATION_AVAILABLE = True
except ImportError as _e:
    TEST_VALIDATION_AVAILABLE = False


# Configure logging
logging.basicConfig(
    level=logging.INFO, format="%(asctime)s - %(name)s - %(levelname)s - %(message)s"
)
logger = logging.getLogger(__name__)


@dataclass
class ExercismEntry:
    """Represents a validated Exercism exercise entry"""

    repo_name: str
    repo_owner: str
    exercise_name: str
    language: str
    source_files: List[Dict]  # List of source file metadata from GitHub API
    test_files: List[Dict]  # List of test file metadata
    header_files: List[Dict]  # List of header files (.h)
    build_files: List[Dict]  # list of files like Makefile or CMakeLists.txt
    license_type: str = "Unknown"

    def get_unique_id(self) -> str:
        """Generate unique ID for this entry"""
        return f"{self.language}_{self.exercise_name}_{self.repo_owner}"


class GitHubAPIClient:
    """Handles GitHub API interactions with rate limiting and authentication"""

    def __init__(self, token: Optional[str] = None):
        if not token:
            from dotenv import load_dotenv

            # Load from src/.env (parent directory of this file's parent)
            env_path = Path(__file__).parent.parent / ".env"
            load_dotenv(env_path)
            token = os.getenv("GITHUB_TOKEN")
            if not token:
                logger.warning("GitHub token not found in .env file")

        self.token = token
        self.session = requests.Session()
        self.rate_limiter = RateLimiter(max_requests=50, time_window=60)

        # Set up headers
        self.headers = {
            "Accept": "application/vnd.github.v3+json",
            "User-Agent": "Sustainable-Code-Refactoring-LLM-Research",
        }
        if self.token:
            self.headers["Authorization"] = f"token {self.token}"
            logger.info("GitHub API client initialized with authentication token")
        else:
            logger.warning(
                "GitHub API client initialized WITHOUT token - rate limits will be strict"
            )

    def search_repositories(
        self, query: str, language: str, per_page: int = 30
    ) -> List[Dict]:
        """
        Search GitHub repositories

        Args:
            query: Search query string
            language: Programming language filter
            per_page: Results per page (max 100)

        Returns:
            List of repository metadata dictionaries
        """
        self.rate_limiter.wait_if_needed()

        url = "https://api.github.com/search/repositories"
        params = {
            "q": f"{query} language:{language}",
            "sort": "stars",
            "order": "desc",
            "per_page": min(per_page, 100),
        }

        try:
            response = self.session.get(url, headers=self.headers, params=params)
            response.raise_for_status()
            data = response.json()
            logger.info(
                f"Found {data.get('total_count', 0)} repositories matching query"
            )
            return data.get("items", [])
        except requests.RequestException as e:
            logger.error(f"Error searching repositories: {e}")
            return []

    def get_repo_contents(self, owner: str, repo: str, path: str = "") -> List[Dict]:
        """
        Get contents of a repository directory

        Args:
            owner: Repository owner
            repo: Repository name
            path: Path within repository

        Returns:
            List of file/directory metadata
        """
        self.rate_limiter.wait_if_needed()

        url = f"https://api.github.com/repos/{owner}/{repo}/contents/{path}"

        try:
            response = self.session.get(url, headers=self.headers)
            if response.status_code == 404:
                logger.debug(f"Path not found: {path} in {owner}/{repo}")
                return []
            response.raise_for_status()
            return response.json() if isinstance(response.json(), list) else []
        except requests.RequestException as e:
            logger.error(f"Error getting repo contents: {e}")
            return []

    def get_file_content(self, owner: str, repo: str, file_path: str) -> Optional[str]:
        """
        Download file content from GitHub

        Args:
            owner: Repository owner
            repo: Repository name
            file_path: Path to file in repository

        Returns:
            File content as string, or None if error
        """
        self.rate_limiter.wait_if_needed()

        url = f"https://api.github.com/repos/{owner}/{repo}/contents/{file_path}"

        try:
            response = self.session.get(url, headers=self.headers)
            if response.status_code == 404:
                return None
            response.raise_for_status()

            data = response.json()
            if data.get("encoding") == "base64":
                content = base64.b64decode(data["content"]).decode(
                    "utf-8", errors="ignore"
                )
                return content
            return data.get("content", "")
        except Exception as e:
            logger.error(f"Error getting file content {file_path}: {e}")
            return None


class ExercismValidator:
    """Validates Exercism entries for completeness"""

    @staticmethod
    def is_source_file(filename: str, language: str) -> bool:
        """Check if file is a source code file"""
        fn_lower = filename.lower()
        match language:
            case "c":
                return filename.endswith(".c") and "test" not in fn_lower
            case "cpp":
                return filename.endswith(".cpp") and "test" not in fn_lower
            case "python":
                # Exclude test files: *_test.py, test_*.py, *test*.py
                return filename.endswith(".py") and "test" not in fn_lower
            case "go":
                return filename.endswith(".go") and "test" not in fn_lower
            case "typescript":
                # Exclude .spec.ts, .test.ts
                return filename.endswith(".ts") and "test" not in fn_lower and ".spec." not in fn_lower
            case "javascript":
                # Exclude .spec.js, .test.js - Exercism uses .spec.js for tests
                return filename.endswith(".js") and "test" not in fn_lower and ".spec." not in fn_lower
            case "java":
                # Exclude Test*.java, *Test.java
                return filename.endswith(".java") and "test" not in fn_lower
            case _:
                return False

    @staticmethod
    def is_test_file(filename: str, language: str) -> bool:
        """Check if file is a test file"""
        fn_lower = filename.lower()
        match language:
            case "c":
                return filename.endswith(".c") and "test" in fn_lower
            case "cpp":
                return (
                    filename.endswith(".cpp") or filename.endswith(".cc")
                ) and "test" in fn_lower
            case "go":
                # Go uses _test.go suffix
                return filename.endswith("_test.go")
            case "python":
                # Python uses *_test.py or test_*.py
                return filename.endswith(".py") and ("test" in fn_lower)
            case "java":
                # Java uses *Test.java or Test*.java
                return filename.endswith(".java") and "test" in fn_lower
            case "javascript":
                # Exercism JavaScript uses .spec.js for tests
                return filename.endswith(".spec.js") or (filename.endswith(".js") and "test" in fn_lower)
            case "typescript":
                # TypeScript uses .spec.ts or .test.ts
                return filename.endswith(".spec.ts") or filename.endswith(".test.ts") or (
                    filename.endswith(".ts") and "test" in fn_lower
                )
            case _:
                return False

    @staticmethod
    def is_header_file(filename: str) -> bool:
        """Check if file is a header file"""
        return filename.endswith(".h") or filename.endswith(".hpp")

    @staticmethod
    def is_build_file(filename: str) -> bool:
        """Check if file is a build configuration file"""
        return filename.lower() in [
            "makefile",
            "cmakelists.txt",
            "package.json",
            "package-lock.json",
            "tsconfig.json",
        ]  # "jest.config.js"

    @staticmethod
    def validate_entry(files: List[Dict], language: str) -> Tuple[bool, Dict]:
        """
        Validate that an exercise directory has all required files

        Args:
            files: List of file metadata from GitHub API
            language

        Returns:
            (is_valid, categorized_files) where categorized_files contains:
                - source_files: list
                - test_files: list
                - header_files: list
                - build_files: list
        """
        categorized = {
            "source_files": [],
            "test_files": [],
            "header_files": [],
            "build_files": [],
        }

        for file_meta in files:
            if file_meta.get("type") != "file":
                continue

            filename = file_meta.get("name", "")

            if ExercismValidator.is_source_file(filename, language):
                categorized["source_files"].append(file_meta)
            elif ExercismValidator.is_test_file(filename, language):
                categorized["test_files"].append(file_meta)
            elif ExercismValidator.is_header_file(filename):
                categorized["header_files"].append(file_meta)
            elif ExercismValidator.is_build_file(filename):
                categorized["build_files"].append(file_meta)

        # Validation rules
        has_source = len(categorized["source_files"]) > 0
        has_tests = len(categorized["test_files"]) > 0

        if language in ["c", "cpp", "c++"]:
            has_build = len(categorized["build_files"]) > 0
        else:
            has_build = True

        is_valid = has_source and has_tests and has_build

        if not is_valid:
            missing = []
            if not has_source:
                missing.append("source files")
            if not has_tests:
                missing.append("test files")
            if not has_build:
                missing.append("build files (Makefile/CMakeLists.txt)")
            logger.debug(f"Entry invalid - missing: {', '.join(missing)}")

        return is_valid, categorized


class DuplicateChecker:
    """Checks for duplicate entries in existing clusters"""

    def __init__(self, clusters_dir: Path):
        self.clusters_dir = clusters_dir
        self.existing_entries: Set[str] = set()
        self._load_existing_entries()

    def _load_existing_entries(self):
        """Load all existing entries from cluster files"""
        cluster_files = list(self.clusters_dir.glob("cluster_*.json"))
        logger.info(
            f"Loading existing entries from {len(cluster_files)} cluster files..."
        )

        for cluster_file in cluster_files:
            if "debug" in cluster_file.name or "bad_entries" in cluster_file.name:
                continue

            try:
                cluster_data = read_json(cluster_file)
                for language, entries in cluster_data.items():
                    if language in ["c", "cpp"]:
                        for entry in entries:
                            # Create entry identifier
                            entry_id = entry.get("id", "")
                            source = entry.get("source", "")
                            exercise_name = (
                                entry.get("filename", "")
                                .replace(".c", "")
                                .replace(".cpp", "")
                            )

                            # Add multiple identifiers to catch duplicates
                            self.existing_entries.add(entry_id)
                            self.existing_entries.add(
                                f"{language}_{exercise_name}_{source}"
                            )
            except Exception as e:
                logger.warning(f"Error reading cluster file {cluster_file}: {e}")

        logger.info(f"Loaded {len(self.existing_entries)} existing C/C++ entries")

    def is_duplicate(self, entry: ExercismEntry) -> bool:
        """Check if entry already exists"""
        entry_id = entry.get_unique_id()
        return entry_id in self.existing_entries


class GitHubIngestor:
    """Main ingestor class - orchestrates the entire process"""

    def __init__(
        self, dataset_dir: Path, clusters_dir: Path, github_token: Optional[str] = None
    ):
        self.dataset_dir = dataset_dir
        self.clusters_dir = clusters_dir
        self.api_client = GitHubAPIClient(github_token)
        self.validator = ExercismValidator()
        self.duplicate_checker = DuplicateChecker(clusters_dir)
        self.ingested_count = {"c": 0, "cpp": 0}
        self.cluster_write_lock = Lock()  # For thread-safe cluster JSON updates

    def generate_fallback_makefile(self, entry_dir: Path, language: str) -> bool:
        """
        Generate a standard Makefile for C/C++ when the original is incompatible

        Args:
            entry_dir: Directory containing src/ and test/ subdirectories
            language: 'c' or 'cpp'

        Returns:
            True if Makefile created successfully, False otherwise
        """
        try:
            if language == "c":
                makefile_content = """# Auto-generated Makefile for C
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
LDFLAGS = -lm

SRC_DIR = src
TEST_DIR = test
BUILD_DIR = .

# Find all .c files in src and test directories
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
TEST_FILES = $(wildcard $(TEST_DIR)/*.c)
ALL_FILES = $(SRC_FILES) $(TEST_FILES)

# Default target: compile and run tests
test: $(ALL_FILES)
\t$(CC) $(CFLAGS) -o tests.out $(ALL_FILES) $(LDFLAGS)
\t./tests.out

# Clean build artifacts
clean:
\trm -f tests.out $(SRC_DIR)/*.o $(TEST_DIR)/*.o

.PHONY: test clean
"""
            else:  # cpp
                makefile_content = """# Auto-generated Makefile for C++
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g
LDFLAGS = -lm

SRC_DIR = src
TEST_DIR = test
BUILD_DIR = .

# Find all .cpp files in src and test directories
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)
ALL_FILES = $(SRC_FILES) $(TEST_FILES)

# Default target: compile and run tests
test: $(ALL_FILES)
\t$(CXX) $(CXXFLAGS) -o tests.out $(ALL_FILES) $(LDFLAGS)
\t./tests.out

# Clean build artifacts
clean:
\trm -f tests.out $(SRC_DIR)/*.o $(TEST_DIR)/*.o

.PHONY: test clean
"""

            makefile_path = entry_dir / "Makefile"
            makefile_path.write_text(makefile_content, encoding="utf-8")
            logger.info(f"  ✓ Generated fallback Makefile for {language}")
            return True

        except Exception as e:
            logger.error(f"  ✗ Failed to generate fallback Makefile: {e}")
            return False

    def cleanup_failed_entry(self, entry_dir_name: str, language: str) -> bool:
        """
        Remove entry directory after validation failure

        Args:
            entry_dir_name: Name of entry directory to remove
            language:

        Returns:
            True if cleanup successful, False otherwise
        """
        entry_path = self.dataset_dir / language / entry_dir_name

        try:
            if entry_path.exists():
                shutil.rmtree(entry_path)
                logger.info(f"  ✓ Cleaned up failed entry: {entry_dir_name}")
                return True
            else:
                logger.warning(f"  ⚠️  Entry directory does not exist: {entry_path}")
                return False

        except Exception as e:
            logger.error(f"  ✗ Failed to cleanup entry {entry_dir_name}: {e}")
            return False

    def search_exercism_repos(self, language: str, max_repos: int = 20) -> List[Dict]:
        """
        Search for Exercism repositories for a specific language

        Args:
            language
            max_repos: Maximum repositories to search

        Returns:
            List of repository metadata
        """
        if language == "cpp":
            language = "c++"
        query = f"exercism {language}"

        logger.info(f"Searching for Exercism {language.upper()} repositories...")
        repos = self.api_client.search_repositories(query, language, per_page=max_repos)

        # Filter for repos that likely contain exercism solutions (not official exercism repos)
        filtered_repos = []
        for repo in repos:
            repo_name = repo.get("name", "").lower()
            repo_desc = (
                repo.get("description", "").lower() if repo.get("description") else ""
            )
            repo_owner = repo.get("owner", {}).get("login", "").lower()

            # Skip official exercism repos - they contain only templates, not solutions
            if repo_owner == "exercism":
                logger.debug(f"Skipping official Exercism repo: {repo_owner}/{repo_name}")
                continue

            if "exercism" in repo_name or "exercism" in repo_desc:
                filtered_repos.append(repo)

        logger.info(f"Found {len(filtered_repos)} relevant Exercism repositories (excluding official)")
        return filtered_repos

    def _explore_java_maven_structure(
        self, owner: str, repo_name: str, base_path: str
    ) -> List[Dict]:
        """
        Explore Java Maven/Gradle standard structure (src/main/java, src/test/java)

        Args:
            owner: Repository owner
            repo_name: Repository name
            base_path: Base path to explore (e.g., "java/exercise-name")

        Returns:
            List of file metadata from both src/main and src/test
        """
        all_files = []

        # Try Maven/Gradle structure
        maven_paths = [
            f"{base_path}/src/main/java" if base_path else "src/main/java",
            f"{base_path}/src/test/java" if base_path else "src/test/java",
            f"{base_path}/src" if base_path else "src",
        ]

        for maven_path in maven_paths:
            files = self._get_files_recursive(owner, repo_name, maven_path, max_depth=3)
            all_files.extend(files)

        return all_files

    def _get_files_recursive(
        self, owner: str, repo_name: str, path: str, max_depth: int = 2, current_depth: int = 0
    ) -> List[Dict]:
        """
        Recursively get all files in a directory up to max_depth

        Args:
            owner: Repository owner
            repo_name: Repository name
            path: Path to explore
            max_depth: Maximum recursion depth
            current_depth: Current recursion depth

        Returns:
            List of file metadata dictionaries
        """
        if current_depth >= max_depth:
            return []

        files = []
        contents = self.api_client.get_repo_contents(owner, repo_name, path)

        if not contents:
            return []

        for item in contents:
            if item.get("type") == "file":
                files.append(item)
            elif item.get("type") == "dir":
                # Recurse into subdirectories
                subdir_files = self._get_files_recursive(
                    owner, repo_name, item["path"], max_depth, current_depth + 1
                )
                files.extend(subdir_files)

        return files

    def explore_repo_for_exercises(
        self, repo: Dict, language: str
    ) -> List[ExercismEntry]:
        """
        Explore repository structure to find valid Exercism exercises

        Args:
            repo: Repository metadata from GitHub API
            language

        Returns:
            List of validated ExercismEntry objects
        """
        owner = repo["owner"]["login"]
        repo_name = repo["name"]
        valid_entries = []

        logger.info(
            f"Exploring {owner}/{repo_name} for {language.upper()} exercises..."
        )

        # Common Exercism repo structures
        possible_paths = [
            f"{language}",
            f"exercism/{language}",
            f"{language}/exercises",
            "",  # Root level
        ]

        for base_path in possible_paths:
            contents = self.api_client.get_repo_contents(owner, repo_name, base_path)

            if not contents:
                continue

            # Look for exercise directories
            for item in contents:
                if item.get("type") != "dir":
                    continue

                exercise_name = item["name"]
                exercise_path = item["path"]

                # Skip non-exercise directories
                if exercise_name.startswith(".") or exercise_name in [
                    "build",
                    "bin",
                    "obj",
                    "test",
                    "tests",
                ]:
                    continue

                logger.debug(f"  Checking exercise: {exercise_name}")

                # Get exercise directory contents
                exercise_files = self.api_client.get_repo_contents(
                    owner, repo_name, exercise_path
                )

                # For Java, also try Maven/Gradle structure
                if language == "java":
                    maven_files = self._explore_java_maven_structure(
                        owner, repo_name, exercise_path
                    )
                    if maven_files:
                        exercise_files.extend(maven_files)
                        logger.debug(f"    Found {len(maven_files)} files in Maven structure")

                # Validate exercise
                is_valid, categorized = self.validator.validate_entry(
                    exercise_files, language
                )

                if is_valid:
                    entry = ExercismEntry(
                        repo_name=repo_name,
                        repo_owner=owner,
                        exercise_name=exercise_name,
                        language=language,
                        source_files=categorized["source_files"],
                        test_files=categorized["test_files"],
                        header_files=categorized["header_files"],
                        build_files=categorized["build_files"],
                        license_type=repo.get("license", {}).get("name", "Unknown")
                        if repo.get("license")
                        else "Unknown",
                    )

                    # Check for duplicates
                    if not self.duplicate_checker.is_duplicate(entry):
                        valid_entries.append(entry)
                        logger.info(f"    ✓ Valid entry found: {exercise_name}")
                    else:
                        logger.debug(f"    ✗ Duplicate skipped: {exercise_name}")

        return valid_entries

    def validate_entry_with_tests(
        self,
        entry: ExercismEntry,
        entry_dir_name: str,
        num_executions: int = 5,
        code_file_name="",
        test_file_name="",
    ) -> Tuple[bool, List]:
        """
        Validate entry by running tests multiple times (default: 5)

        This function executes the test suite for an entry N times and verifies
        that ALL executions pass with 100% success rate.

        Args:
            entry: ExercismEntry object containing metadata
            entry_dir_name: Directory name where files were saved
            num_executions: Number of test executions (default: 5)

        Returns:
            Tuple of (success: bool, results: List[BaseEntryResult])
            - success: True if all tests pass in all executions (100% pass rate)
            - results: List of BaseEntryResult objects from test executions
        """
        if not TEST_VALIDATION_AVAILABLE:
            logger.warning("Test validation not available - skipping validation")
            return False, []  # Fallback: assume invalid if validation unavailable

        logger.info(
            f"🧪 Validating {entry.exercise_name} with {num_executions} test executions..."
        )

        try:
            is_c_or_cpp = False
            if entry.language in ["c", "cpp", "c++"]:
                is_c_or_cpp = True

            if code_file_name == "" or test_file_name == "":
                raise Exception(
                    f"invalid :\ncode file name ={code_file_name}\ntest_file_name = {test_file_name}"
                )

            # Setup test executor
            container_manager = ContainerManager()
            test_executor = TestExecutor(container_manager)

            # Build entry metadata dict as expected by execute_test
            main_source_file = entry.source_files[0] if entry.source_files else None
            if not main_source_file:
                logger.error(f"  ✗ No source file found for {entry.exercise_name}")
                return False, []

            codeSnippetFilePath = f"{entry.language}/{entry_dir_name}"
            if not is_c_or_cpp:
                codeSnippetFilePath += f"/{code_file_name}"
            else:
                codeSnippetFilePath += "/src"

            testUnitFilePath = f"{entry.language}/{entry_dir_name}"
            if not is_c_or_cpp:
                testUnitFilePath += f"/{test_file_name}"
            else:
                testUnitFilePath += "/test"

            entry_dict = {
                "id": entry.get_unique_id(),
                "filename": main_source_file["name"],
                "language": entry.language,
                "codeSnippetFilePath": codeSnippetFilePath,
                "testUnitFilePath": testUnitFilePath,
            }

            # Verify directories exist
            entry_base_dir = self.dataset_dir / entry.language / entry_dir_name
            src_path = self.dataset_dir / entry_dict["codeSnippetFilePath"]
            test_path = self.dataset_dir / entry_dict["testUnitFilePath"]

            if not src_path.exists() or not test_path.exists():
                logger.error(f"  ✗ Source/test directories not found: {entry_dir_name}")
                return False, []

            if is_c_or_cpp :
                # Check if Makefile exists, generate fallback if needed
                makefile_path = entry_base_dir / "Makefile"
                cmakelists_path = entry_base_dir / "CMakeLists.txt"

                if not makefile_path.exists() and not cmakelists_path.exists():
                    logger.warning(
                        "  ⚠️  No build file found, generating fallback Makefile..."
                    )
                    if not self.generate_fallback_makefile(entry_base_dir, entry.language):
                        logger.error("  ✗ Failed to generate fallback Makefile")
                        return False, []

            # Execute tests multiple times
            passed_count = 0
            failed_count = 0
            results = []

            for i in range(num_executions):
                logger.info(f"  Execution {i + 1}/{num_executions}...")

                try:
                    #execute test and get metrics (results) (not save result in .json file)
                    result = test_executor.execute_test(
                        entry=entry_dict,
                        language=entry.language,
                        test_type="base",
                        llm_info=None,
                        use_cache=True,
                        debug_mode=False,
                    )

                    results.append(result)

                    # Check if test passed AND metrics are valid
                    if result.regressionTestPassed and result.success:
                        passed_count += 1
                        logger.debug(
                            f"    ✓ Execution {i + 1}: PASS "
                            f"(CPU: {result.CPU_usage:.2f}%, RAM: {result.RAM_usage} bytes, "
                            f"Time: {result.execution_time_ms}ms)"
                        )
                    else:
                        failed_count += 1
                        logger.warning(
                            f"    ✗ Execution {i + 1}: FAIL "
                            f"(passed={result.regressionTestPassed}, success={result.success}, "
                            f"error={result.error_message})"
                        )
                        # Early exit on first failure (100% pass rate required)
                        break

                except Exception as e:
                    logger.error(f"    ✗ Execution {i + 1} threw exception: {e}")
                    failed_count += 1
                    break

            # Calculate pass rate
            pass_rate = (
                (passed_count / num_executions) * 100 if num_executions > 0 else 0
            )

            # Log summary
            if passed_count == num_executions:
                # Calculate average metrics
                avg_cpu = sum(r.CPU_usage for r in results if r.CPU_usage) / len(
                    results
                )
                avg_ram = sum(r.RAM_usage for r in results if r.RAM_usage) / len(
                    results
                )
                avg_time = sum(
                    r.execution_time_ms for r in results if r.execution_time_ms
                ) / len(results)

                logger.info(
                    f"  ✅ All tests passed ({passed_count}/{num_executions} = {pass_rate:.1f}%)\n"
                    f"     Avg metrics - CPU: {avg_cpu:.2f}%, RAM: {avg_ram:.0f} bytes, Time: {avg_time:.2f}ms"
                )
                return True, results
            else:
                logger.warning(
                    f"  ❌ Tests failed ({passed_count}/{num_executions} = {pass_rate:.1f}%) - "
                    f"Required: 100% pass rate"
                )
                return False, results  # Return partial results even on failure

        except Exception as e:
            logger.error(f"  ✗ Validation error for {entry.exercise_name}: {e}")
            return False, []

    def download_and_save_entry(self, entry: ExercismEntry) -> object:
        """
        Download entry files and save to dataset structure

        Args:
            entry: ExercismEntry object

        Returns:
            True if successful, False otherwise
        """
        # Create directory structure: src/dataset/{language}/{exercise}_{source}/
        source_clean = (
            entry.repo_owner.replace(" ", "_").replace("(", "").replace(")", "")
        )
        entry_dir_name = f"{entry.exercise_name}_exercism-{source_clean}"
        entry_base_dir = self.dataset_dir / entry.language / entry_dir_name

        is_c_or_cpp = False

        test_file_name = ""
        code_file_name = ""

        if entry.language in ["c", "cpp", "c++"]:
            src_dir = entry_base_dir / "src"
            test_dir = entry_base_dir / "test"
            is_c_or_cpp = True
        else:
            src_dir = entry_base_dir
            test_dir = entry_base_dir

        try:
            ext = get_ext_by_lang(entry.language)

            # Create directories for all languages
            entry_base_dir.mkdir(parents=True, exist_ok=True)
            if is_c_or_cpp:
                src_dir.mkdir(parents=True, exist_ok=True)
                test_dir.mkdir(parents=True, exist_ok=True)

            logger.info(f"Downloading files for {entry.exercise_name}...")

            # Download source files and their headers to src/
            for file_meta in entry.source_files + entry.header_files:
                content = self.api_client.get_file_content(
                    entry.repo_owner, entry.repo_name, file_meta["path"]
                )
                if content is None:
                    logger.error(f"  Failed to download {file_meta['name']}")
                    return {"is_valid": False, "code_file_name": "", "test_file_name": ""}

                name = str(file_meta["name"])
                # Case-insensitive check for exercise name in filename
                # (handles CamelCase naming in Java, e.g., "Acronym.java" for "acronym")
                exercise_normalized = entry.exercise_name.replace("-", "").lower()
                name_normalized = name.replace("-", "").replace("_", "").lower()
                if name.endswith(ext) and exercise_normalized in name_normalized:
                    code_file_name = name

                file_path = src_dir / file_meta["name"]
                file_path.write_text(content, encoding="utf-8")
                logger.debug(f"  ✓ {file_meta['name']} → src/")

            # Download test files to test/
            for file_meta in entry.test_files:
                content = self.api_client.get_file_content(
                    entry.repo_owner, entry.repo_name, file_meta["path"]
                )
                if content is None:
                    logger.error(f"  Failed to download {file_meta['name']}")
                    return {"is_valid": False, "code_file_name": code_file_name, "test_file_name": ""}

                t_file_name: str = file_meta["name"]
                if not is_c_or_cpp and "suite" not in t_file_name.lower():
                    t_file_name = t_file_name.replace("test", "testSuite")

                if ext in t_file_name:
                    test_file_name = t_file_name

                file_path = test_dir / t_file_name
                file_path.write_text(content, encoding="utf-8")
                logger.debug(f"  ✓ {file_meta['name']} → test/")

            if is_c_or_cpp:
                # Check if test directory needs header files (unity.h, catch.hpp, etc.)
                # These are often in the test directory on Exercism
                test_headers = [
                    f
                    for f in entry.header_files
                    if "test" in f.get("path", "").lower()
                    or "unity" in f.get("name", "").lower()
                    or "catch" in f.get("name", "").lower()
                ]

                for file_meta in test_headers:
                    content = self.api_client.get_file_content(
                        entry.repo_owner, entry.repo_name, file_meta["path"]
                    )
                    if content:
                        file_path = test_dir / file_meta["name"]
                        file_path.write_text(content, encoding="utf-8")
                        logger.debug(f"  ✓ {file_meta['name']} → test/")

            # Download build files to root of entry directory
            for file_meta in entry.build_files:
                content = self.api_client.get_file_content(
                    entry.repo_owner, entry.repo_name, file_meta["path"]
                )
                if content is None:
                    logger.error(f"  Failed to download {file_meta['name']}")
                    return {"is_valid": False, "code_file_name": code_file_name, "test_file_name": test_file_name}

                file_path = entry_base_dir / file_meta["name"]
                file_path.write_text(content, encoding="utf-8")
                logger.debug(f"  ✓ {file_meta['name']} → ./")

            logger.info(f"✓ Successfully saved all files for {entry.exercise_name}")
            is_valid = code_file_name != "" and test_file_name != ""
            return {
                "is_valid": is_valid,
                "code_file_name": code_file_name,
                "test_file_name": test_file_name,
            }

        except Exception as e:
            logger.error(f"Error saving entry {entry.exercise_name}: {e}")
            # Cleanup on failure
            if entry_base_dir.exists():
                import shutil

                shutil.rmtree(entry_base_dir, ignore_errors=True)
            return {
                "is_valid": False,
                "code_file_name": code_file_name,
                "test_file_name": test_file_name,
            }

    def update_cluster_json(self, entry: ExercismEntry, entry_dir_name: str) -> bool:
        """
        Update or create cluster JSON file for the exercise (thread-safe)

        Args:
            entry: ExercismEntry object
            entry_dir_name: Name of the directory where files were saved

        Returns:
            True if successful, False otherwise
        """
        cluster_name = entry.exercise_name.lower().replace("-", "_").replace(" ", "_")
        cluster_file = self.clusters_dir / f"cluster_{cluster_name}.json"

        # Use lock for thread-safe cluster file updates
        with self.cluster_write_lock:
            try:
                # Load existing cluster or create new
                if cluster_file.exists():
                    cluster_data = read_json(cluster_file)
                else:
                    cluster_data = {}

                # Ensure language key exists
                if entry.language not in cluster_data:
                    cluster_data[entry.language] = []

                # Create new entry metadata
                source_clean = (
                    entry.repo_owner.replace(" ", "_").replace("(", "").replace(")", "")
                )

                # Find main source file
                main_source_file = entry.source_files[0] if entry.source_files else None
                main_test_file = entry.test_files[0] if entry.test_files else None

                if not main_source_file or not main_test_file:
                    logger.error(
                        f"Missing source or test file for {entry.exercise_name}"
                    )
                    return False

                # Count characters and words
                content = self.api_client.get_file_content(
                    entry.repo_owner, entry.repo_name, main_source_file["path"]
                )
                char_count = len(content) if content else 0
                word_count = len(content.split()) if content else 0

                # Reject entries with empty source files
                if char_count == 0:
                    logger.error(
                        f"Source file is empty for {entry.exercise_name}. Skipping."
                    )
                    return False

                new_entry = {
                    "id": entry.get_unique_id(),
                    "filename": main_source_file["name"],
                    "language": entry.language,
                    "source": f"exercism-{source_clean}",
                    "codeSnippetFilePath": f"{entry.language}/{entry_dir_name}/src",
                    "testUnitFilePath": f"{entry.language}/{entry_dir_name}/test",
                    "downloadDate": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
                    "characterQuantity": char_count,
                    "wordQuantity": word_count,
                    "licenseType": entry.license_type,
                    "LLMs": [],
                }

                # Add to cluster
                cluster_data[entry.language].append(new_entry)

                # Save cluster file
                write_json(cluster_file, cluster_data)
                logger.info(f"✓ Updated cluster file: {cluster_file.name}")

                return True

            except Exception as e:
                logger.error(
                    f"Error updating cluster JSON for {entry.exercise_name}: {e}"
                )
                return False

    def save_base_test_results(
        self,
        entry: ExercismEntry,
        entry_dir_name: str,  # noqa: ARG002
        test_results: List,
    ) -> bool:
        """
        Save base test execution results to execution_outputs directory

        This method saves the 5 test execution results from validation to JSON files
        in the format expected by the metrics analysis pipeline.

        Args:
            entry: ExercismEntry object
            entry_dir_name: Directory name where files were saved
            test_results: List of BaseEntryResult objects from validate entry with tests

        Returns:
            True if all results saved successfully, False otherwise
        """
        if not test_results:
            logger.warning(f"No test results to save for {entry.exercise_name}")
            return False

        try:
            # Get execution_outputs directory from project structure
            execution_outputs_dir = self.dataset_dir.parent / "execution_outputs"
            execution_outputs_dir.mkdir(parents=True, exist_ok=True)

            # Determine cluster name from exercise name
            cluster_name = (
                entry.exercise_name.lower().replace("-", "_").replace(" ", "_")
            )

            # Save each execution result in AGGREGATED format
            saved_count = 0
            for i, result in enumerate(test_results, start=1):
                # Create result filename: {cluster}_results_{1-5}.json
                result_filename = f"{cluster_name}_results_{i}.json"
                result_path = execution_outputs_dir / result_filename

                # Convert BaseEntryResult to dict format
                result_entry = {
                    "id": result.id,
                    "filename": result.filename,
                    "language": result.language,
                    "base_log": result.base_log,
                    "execution_time_ms": result.execution_time_ms,
                    "CPU_usage": result.CPU_usage,
                    "RAM_usage": result.RAM_usage,
                    "regressionTestPassed": result.regressionTestPassed,
                    "success": result.success,
                    "error_message": result.error_message,
                }

                # Load existing data if file exists and merge intelligently
                if result_path.exists():
                    existing_data = read_json(result_path)

                    # Initialize AGGREGATED format if needed
                    if not existing_data or "results" not in existing_data:
                        # File exists but wrong format or corrupted - create AGGREGATED structure
                        output_data = {"results": {}}
                        logger.debug(
                            f"  Converting {result_filename} to AGGREGATED format"
                        )
                    else:
                        # Already in AGGREGATED format
                        output_data = existing_data

                    # Ensure language key exists
                    lang = result.language
                    if lang not in output_data["results"]:
                        output_data["results"][lang] = []

                    # Check if this entry already exists (by ID)
                    entry_exists = False
                    for idx, existing_entry in enumerate(output_data["results"][lang]):
                        if existing_entry.get("id") == result.id:
                            # Update existing entry
                            output_data["results"][lang][idx] = result_entry
                            entry_exists = True
                            logger.debug(f"  ✓ Updated existing entry: {result.id}")
                            break

                    if not entry_exists:
                        # Add new entry to the language's result list
                        output_data["results"][lang].append(result_entry)
                        logger.debug(f"  ✓ Added new entry: {result.id}")

                else:
                    # New file - create AGGREGATED format structure
                    output_data = {"results": {result.language: [result_entry]}}
                    logger.debug(f"  ✓ Created new file: {result_filename}")

                # Write to JSON file in AGGREGATED format
                write_json(result_path, output_data)
                saved_count += 1

            logger.info(
                f"💾 Saved {saved_count}/{len(test_results)} base test results to execution_outputs/"
            )
            return True

        except Exception as e:
            logger.error(
                f"Error saving base test results for {entry.exercise_name}: {e}"
            )
            return False

    def save_ingestion_manifest(
        self,
        language: str,
        ingested_clusters: List[str],
        ingested_count: int,
        validated_count: int,
        failed_count: int,
    ) -> bool:
        """
        Save ingestion manifest for pipeline tracking

        Creates a JSON manifest file with metadata about the ingestion session,
        including which clusters were modified and statistics.

        Args:
            language
            ingested_clusters: List of cluster names that were modified
            ingested_count: Number of entries successfully ingested
            validated_count: Number of entries that passed validation
            failed_count: Number of entries that failed validation

        Returns:
            True if manifest saved successfully, False otherwise
        """
        try:
            # Create logs directory if it doesn't exist
            logs_dir = self.dataset_dir.parent / "logs"
            logs_dir.mkdir(parents=True, exist_ok=True)

            # Generate timestamp for unique filename
            timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
            manifest_filename = f"ingestion_manifest_{language}_{timestamp}.json"
            manifest_path = logs_dir / manifest_filename

            # Create manifest data
            manifest = {
                "timestamp": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
                "language": language,
                "clusters": ingested_clusters,
                "entry_count": ingested_count,
                "validated_count": validated_count,
                "failed_count": failed_count,
                "success_rate": f"{(ingested_count / validated_count * 100):.1f}%"
                if validated_count > 0
                else "0%",
            }

            # Save manifest
            write_json(manifest_path, manifest)
            logger.info(f"📝 Saved ingestion manifest: {manifest_filename}")
            logger.info(f"   Clusters modified: {len(ingested_clusters)}")
            logger.info(f"   Entries ingested: {ingested_count}")

            return True

        except Exception as e:
            logger.error(f"Error saving ingestion manifest: {e}")
            return False

    def _process_single_entry(
        self, entry: ExercismEntry, language: str
    ) -> Tuple[bool, str, Dict]:
        """
        Process a single entry: download, validate, and update cluster

        Args:
            entry: ExercismEntry object
            language

        Returns:
            Tuple of (success, entry_dir_name, stats_dict)
        """
        source_clean = (
            entry.repo_owner.replace(" ", "_").replace("(", "").replace(")", "")
        )
        entry_dir_name = f"{entry.exercise_name}_exercism-{source_clean}"

        stats = {
            "entry_name": entry.exercise_name,
            "downloaded": False,
            "validated": False,
            "ingested": False,
            "error": None,
        }

        try:
            # Step 1: Download files
            logger.info(f"Downloading: {entry.exercise_name}")
            res = self.download_and_save_entry(entry)
            valid = res["is_valid"]
            test_file_name = res["test_file_name"]
            code_file_name = res["code_file_name"]
            if not valid:
                stats["error"] = "Download failed"
                logger.error(f"  ❌ Download failed: {entry.exercise_name}")
                return False, entry_dir_name, stats

            stats["downloaded"] = True

            # Step 2: Validate with tests (5 executions)
            logger.info(f"🧪 Validating: {entry.exercise_name}")
            validation_success, test_results = self.validate_entry_with_tests(
                entry,
                entry_dir_name,
                num_executions=5,
                code_file_name=code_file_name,
                test_file_name=test_file_name,
            )

            if not validation_success:
                stats["error"] = "Test validation failed"
                logger.warning(f"  ⚠️  Validation failed: {entry.exercise_name}")

                # Cleanup failed entry
                self.cleanup_failed_entry(entry_dir_name, language)
                return False, entry_dir_name, stats

            stats["validated"] = True

            # Step 3: Update cluster JSON (only if validation passed)
            logger.info(f"💾 Saving to cluster: {entry.exercise_name}")
            if not self.update_cluster_json(entry, entry_dir_name):
                stats["error"] = "Cluster update failed"
                logger.warning(f"  ⚠️  Cluster update failed: {entry.exercise_name}")

                # Cleanup since it won't be in cluster
                self.cleanup_failed_entry(entry_dir_name, language)
                return False, entry_dir_name, stats

            stats["ingested"] = True

            # Step 4: Save base test results to execution_outputs (NEW!)
            logger.info(f"💾 Saving base test results: {entry.exercise_name}")
            if not self.save_base_test_results(entry, entry_dir_name, test_results):
                logger.warning("  ⚠️  Failed to save test results (entry still valid)")
                # Don't fail the entire process if saving results fails
                stats["test_results_saved"] = False
            else:
                stats["test_results_saved"] = True

            logger.info(
                f"  ✅ Successfully ingested and validated: {entry.exercise_name}"
            )
            return True, entry_dir_name, stats

        except Exception as e:
            stats["error"] = str(e)
            logger.error(f"  ✗ Exception processing {entry.exercise_name}: {e}")

            # Cleanup on exception
            try:
                self.cleanup_failed_entry(entry_dir_name, language)
            except Exception:  # noqa: S110
                pass

            return False, entry_dir_name, stats

    def ingest_entries(
        self, language: str, max_repos: int = 10, max_entries_per_lang: int = 20
    ) -> int:
        """
        Main ingestion workflow with test validation and parallelization

        Args:
            language
            max_repos: Maximum repositories to search
            max_entries_per_lang: Maximum entries to ingest per language

        Returns:
            Number of entries successfully ingested
        """
        logger.info(f"\n{'=' * 60}")
        logger.info(f"Starting ingestion for {language.upper()} with test validation")
        logger.info(f"{'=' * 60}\n")

        # Search repositories
        repos = self.search_exercism_repos(language, max_repos)

        if not repos:
            logger.warning(f"No repositories found for {language}")
            return 0

        # Collect all valid entries from all repos
        all_valid_entries = []
        for repo in repos:
            valid_entries = self.explore_repo_for_exercises(repo, language)
            all_valid_entries.extend(valid_entries)

            # Stop if we have enough candidates
            if len(all_valid_entries) >= max_entries_per_lang * 2:
                logger.info(
                    f"Collected {len(all_valid_entries)} candidates (enough for processing)"
                )
                break

        logger.info(f"Found {len(all_valid_entries)} total candidate entries")

        if not all_valid_entries:
            logger.warning(f"No valid entries found for {language}")
            return 0

        # Limit to max_entries to process
        entries_to_process = all_valid_entries[
            : max_entries_per_lang * 2
        ]  # Process 2x to account for failures

        # Statistics tracking
        ingested = 0
        downloaded_count = 0
        validated_count = 0
        failed_validation_count = 0
        failed_download_count = 0
        ingested_clusters = set()  # Track unique cluster names

        # Process entries in parallel using ThreadPoolExecutor
        logger.info(
            f"\n🚀 Processing {len(entries_to_process)} entries in parallel (max 3 workers)...\n"
        )

        with ThreadPoolExecutor(max_workers=3) as executor:
            # Submit all tasks
            future_to_entry = {
                executor.submit(self._process_single_entry, entry, language): entry
                for entry in entries_to_process
            }

            # Process results as they complete
            for future in as_completed(future_to_entry):
                entry = future_to_entry[future]

                # Check if we've reached the limit
                if ingested >= max_entries_per_lang:
                    logger.info(
                        f"✓ Reached target: {ingested}/{max_entries_per_lang} entries ingested"
                    )
                    break

                try:
                    success, _entry_dir_name, stats = future.result()

                    # Update statistics
                    if stats["downloaded"]:
                        downloaded_count += 1
                    if stats["validated"]:
                        validated_count += 1
                    if stats["ingested"]:
                        ingested += 1
                        self.ingested_count[language] += 1

                        # Track cluster name for manifest
                        cluster_name = (
                            entry.exercise_name.lower()
                            .replace("-", "_")
                            .replace(" ", "_")
                        )
                        ingested_clusters.add(cluster_name)
                    elif stats["validated"] and not stats["ingested"]:
                        failed_validation_count += 1
                    elif not stats["downloaded"]:
                        failed_download_count += 1

                    # Log progress
                    if success:
                        logger.info(
                            f"📊 Progress: {ingested}/{max_entries_per_lang} ingested | "
                            f"{validated_count} validated | {failed_validation_count} failed validation"
                        )

                except Exception as e:
                    logger.error(f"Error processing entry {entry.exercise_name}: {e}")
                    failed_download_count += 1

                # Small delay to avoid overwhelming the system
                time.sleep(0.5)

        # Final summary
        logger.info(f"\n{'=' * 60}")
        logger.info(f"INGESTION COMPLETE FOR {language.upper()}")
        logger.info(f"{'=' * 60}")
        logger.info(f"✅ Successfully ingested:      {ingested}/{max_entries_per_lang}")
        logger.info(f"📥 Downloaded:                 {downloaded_count}")
        logger.info(f"✓  Validated (passed tests):   {validated_count}")
        logger.info(f"✗  Failed validation:          {failed_validation_count}")
        logger.info(f"✗  Failed download:            {failed_download_count}")
        logger.info(f"{'=' * 60}\n")

        # Save ingestion manifest for pipeline tracking
        if ingested > 0:
            self.save_ingestion_manifest(
                language=language,
                ingested_clusters=sorted(list(ingested_clusters)),
                ingested_count=ingested,
                validated_count=validated_count,
                failed_count=failed_validation_count + failed_download_count,
            )

        return ingested

    def run(
        self,
        languages: List[str] = [],
        max_repos: int = 10,
        max_entries: int = 20,
    ):
        """
        Run the complete ingestion process

        Args:
            languages: List of languages to process
            max_repos: Maximum repositories per language
            max_entries: Maximum entries per language
        """

        if len(languages) == 0:
            raise Exception("Please choose at least one language")

        logger.info("=" * 60)
        logger.info("GitHub Ingestor for Exercism Solutions")
        logger.info("=" * 60)

        total_ingested = 0

        for lang in languages:
            if lang not in LANGUAGES:
                logger.warning(f"Unsupported language: {lang}. Skipping.")
                continue

            count = self.ingest_entries(lang, max_repos, max_entries)
            total_ingested += count

        # Final summary
        logger.info("\n" + "=" * 60)
        logger.info("INGESTION SUMMARY")
        logger.info("=" * 60)
        logger.info(f"Total new entries ingested: {total_ingested}")
        for lang in LANGUAGES:
            logger.info(f"  - {lang}:   {self.ingested_count.get(lang, 0)}")
        logger.info("=" * 60)


def main():
    """Main entry point"""
    import argparse

    parser = argparse.ArgumentParser(
        description="GitHub Ingestor for Exercism Solutions"
    )
    parser.add_argument(
        "--languages",
        nargs="+",
        choices=LANGUAGES,
        default=LANGUAGES,
        help="Languages to process (default: all 7 languages)",
    )
    parser.add_argument(
        "--max-repos",
        type=int,
        default=100,
        help="Maximum repositories to search per language (default: 100)",
    )
    parser.add_argument(
        "--max-entries",
        type=int,
        default=42,
        help="Maximum entries to ingest per language (default: 42)",
    )
    parser.add_argument(
        "--token",
        type=str,
        help="GitHub API token (optional, will try to load from .github_token if not provided)",
    )
    parser.add_argument(
        "--no-interactive",
        action="store_true",
        help="Run without interactive prompts (for automation/scripts)",
    )

    args = parser.parse_args()

    # Get GitHub token (GitHubAPIClient will auto-load from .env if not provided)
    token = args.token
    if not token:
        token = load_github_token()

    # Initialize ingestor
    ingestor = GitHubIngestor(
        dataset_dir=DATASET_DIR, clusters_dir=CLUSTERS_DIR_FILEPATH, github_token=token
    )

    print(f"languages = {args.languages}")

    # Run ingestion
    ingestor.run(
        languages=args.languages, max_repos=args.max_repos, max_entries=args.max_entries
    )


if __name__ == "__main__":
    main()
