#!/bin/bash

# RESTORE ALL RESULTS FROM MOST RECENT BACKUP
# This script restores all non-JavaScript results that were overwritten

echo "========================================================================="
echo "EMERGENCY RESTORE - Recovering overwritten results"
echo "========================================================================="
echo ""
echo "This will restore all non-JavaScript results from the most recent backup"
echo "Timestamp: $(date)"
echo ""

cd /Users/piccoletto/Desktop/Everything/pisa/tesi/Sustainable-Code-Refactoring-with-LLMs/src/execution_outputs

# Count files to restore
echo "Analyzing backup files..."
TOTAL_BACKUPS=$(ls *_backup_*.json 2>/dev/null | wc -l | tr -d ' ')
echo "Found $TOTAL_BACKUPS backup files"
echo ""

# For each unique cluster_results file, find the MOST RECENT backup
# and restore it ONLY if the current file was modified recently (in last 3 hours)

RESTORED=0
SKIPPED=0

# Get list of all unique result file patterns
for backup_file in *_backup_*.json; do
    # Extract base name (cluster_results_N.json)
    base_name=$(echo "$backup_file" | sed 's/_backup_[0-9]*\.json$/.json/')

    # Check if current file was modified in last 3 hours (180 minutes)
    if [ -f "$base_name" ]; then
        modified_minutes=$(( ($(date +%s) - $(stat -f%m "$base_name")) / 60 ))

        if [ $modified_minutes -lt 180 ]; then
            # File was recently modified - need to restore from backup

            # Find the MOST RECENT backup for this file
            most_recent_backup=$(ls -t ${base_name%.json}_backup_*.json 2>/dev/null | head -1)

            if [ -n "$most_recent_backup" ]; then
                # Check if backup contains non-JavaScript data
                has_non_js=$(python3 -c "
import json, sys
try:
    with open('$most_recent_backup') as f:
        data = json.load(f)

    # Check if has results for other languages
    if 'results' in data:
        langs = list(data['results'].keys())
        non_js_langs = [l for l in langs if l != 'javascript']
        print('yes' if non_js_langs else 'no')
    else:
        # Old format - check for non-JS entry IDs
        entries = list(data.keys())
        non_js = [e for e in entries if not e.startswith('javascript_') and e not in ['execution_date', 'execution_metadata']]
        print('yes' if non_js else 'no')
except:
    print('no')
" 2>/dev/null)

                if [ "$has_non_js" = "yes" ]; then
                    echo "Restoring: $base_name from $most_recent_backup"
                    cp "$most_recent_backup" "$base_name"
                    RESTORED=$((RESTORED + 1))
                else
                    SKIPPED=$((SKIPPED + 1))
                fi
            fi
        fi
    fi
done

echo ""
echo "========================================================================="
echo "RESTORE COMPLETE"
echo "========================================================================="
echo "Files restored:    $RESTORED"
echo "Files skipped:     $SKIPPED (JavaScript-only or not modified)"
echo ""
echo "Timestamp: $(date)"
echo "========================================================================="
