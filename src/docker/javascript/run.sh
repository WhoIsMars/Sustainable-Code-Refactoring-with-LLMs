#!/bin/bash
set -e

echo "🕵️  Analisi file JS per determinare se usare ESM o CommonJS..."

# Cerca tutti i file JS nel progetto
all_js_files=$(find . -name "*.js" -type f 2>/dev/null)

# Default mode
mode="commonjs"

# Prima controlla se ci sono require() - indica CommonJS
if echo "$all_js_files" | xargs grep -lE 'require\s*\(' 2>/dev/null | head -1 | grep -q .; then
  echo "🔍 Trovato require() → CommonJS"
  mode="commonjs"
# Poi controlla se ci sono ES Modules pattern (import from, export default/const/function)
elif echo "$all_js_files" | xargs grep -lE '^\s*(import\s+.*\s+from|export\s+(default|const|function|class|let|var))' 2>/dev/null | head -1 | grep -q .; then
  echo "🔍 Trovato ESM pattern → ESM"
  mode="esm"
fi

# Backup del package.json
cp package.json package.json.bak

# Modifica il type nel package.json se serve
if [ "$mode" = "esm" ]; then
  echo "⚙️  Rilevato codice con import/export → ESM"
  # Aggiungi `"type": "module"` nel package.json
  jq '. + {type: "module"}' package.json.bak > package.json
else
  echo "⚙️  Nessun import/export → CommonJS"
  # Rimuovi il campo "type" se presente
  jq 'del(.type)' package.json.bak > package.json
fi

# Installa le dipendenze
npm install

# Avvia Jest con output visibile tramite tee
if [ "$mode" = "esm" ]; then
  echo "▶️  Avvio Jest in modalità ESM"
  /usr/bin/time -v node --experimental-vm-modules ./node_modules/.bin/jest \
    --config=jest.config.js \
    --silent=false 2>&1 | tee output.log
else
  echo "▶️  Avvio Jest in modalità CommonJS"
  # Usa jest.config.cjs per CommonJS (module.exports invece di export default)
  /usr/bin/time -v ./node_modules/.bin/jest \
    --config=jest.config.cjs \
    --silent=false 2>&1 | tee output.log
fi

echo ""
echo "==> Jest execution completed"
echo "==> Output log summary (last 50 lines):"
tail -50 output.log 2>/dev/null || echo "(output.log not found or empty)"

# Ripristina il package.json originale
mv package.json.bak package.json
