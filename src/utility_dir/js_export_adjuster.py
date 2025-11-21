import re
import sys
from pathlib import Path


def detect_exports_in_tests(test_code):
    """
    Detect which identifiers test code is trying to import/require.
    Supports: JS import, JS require, Python import.
    """
    exports = set()

    # JS import { foo } from "./mod.js"
    m = re.findall(r'import\s*{([^}]+)}', test_code)
    for group in m:
        exports.update([x.strip() for x in group.split(",")])

    # JS default import: import foo from "./mod.js"
    m = re.findall(r'import\s+([A-Za-z_]\w*)\s+from', test_code)
    exports.update(m)

    # CommonJS require("x").foo
    m = re.findall(r'require\([\'"][^\'"]+[\'"]\)\.([A-Za-z_]\w*)', test_code)
    exports.update(m)

    # Python: from mod import foo
    m = re.findall(r'from\s+\S+\s+import\s+([A-Za-z_][\w]*)', test_code)
    exports.update(m)

    # Python: import mod; mod.foo
    m = re.findall(r'\b([A-Za-z_]\w*)\s*\.', test_code)
    exports.update(m)

    return exports


def detect_js_module_type(code):
    if "module.exports" in code or "exports." in code:
        return "commonjs"
    if "export " in code:
        return "esm"
    return "none"


def fix_js_esm(code, exports_needed):
    # Trova gli export esistenti
    existing_named = set()
    m = re.findall(r'export\s*{\s*([^}]+)}', code)
    for group in m:
        existing_named.update([x.strip() for x in group.split(",")])

    default_export = re.search(r'export\s+default\s+([A-Za-z_]\w*)', code)

    for fn in exports_needed:
        # 🔒 Patch 1: già esportato come named o default?
        if default_export and default_export.group(1) == fn:
            continue
        if fn in existing_named:
            continue
        if re.search(r'\bexport\b[^{]*\b' + re.escape(fn) + r'\b', code):
            continue

        # 🔒 Patch 2: esiste nel codice?
        if not re.search(r'(class|function|const|let|var)\s+' + re.escape(fn), code):
            print(f"⚠️ Warning: '{fn}' richiesto dai test, ma non esiste nel codice.")
            continue

        # 🔒 Patch 3: non creare default se non richiesto dai test
        # → qui aggiungiamo solo named export
        code += f"\nexport {{ {fn} }};\n"

    return code


def fix_js_commonjs(code, exports_needed):
    for fn in exports_needed:
        # già esportato?
        if re.search(r'module\.exports\s*=\s*{[^}]*' + re.escape(fn), code):
            continue
        if re.search(r'exports\.' + re.escape(fn), code):
            continue

        # esiste nel codice?
        if not re.search(r'(class|function|const|let|var)\s+' + re.escape(fn), code):
            print(f"⚠️ Warning: '{fn}' richiesto dai test, ma non esiste nel codice.")
            continue

        code += f"\nexports.{fn} = {fn};\n"

    return code


def process(source_path, test_path):
    source = Path(source_path).read_text()
    tests = Path(test_path).read_text()

    exports_needed = detect_exports_in_tests(tests)
    if not exports_needed:
        print("⚠️  Nessun export identificato nei test.")
        return

    print("Export richiesti dai test:", exports_needed)

    # JavaScript?
    if source_path.endswith(".js") or source_path.endswith(".mjs"):
        module_type = detect_js_module_type(source)
        print(f"🔧 File JavaScript ({module_type})")

        if module_type == "esm":
            fixed = fix_js_esm(source, exports_needed)
        elif module_type == "commonjs":
            fixed = fix_js_commonjs(source, exports_needed)
        else:
            # No module system detected → assume ESM
            fixed = fix_js_esm(source, exports_needed)

    else:
        raise ValueError("Formato file sorgente non supportato")

    Path(source_path).write_text(fixed)
    print("✅ File sistemato:", source_path)


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Uso: python3 fix_exports.py <source_file> <test_file>")
        sys.exit(1)

    process(sys.argv[1], sys.argv[2])
