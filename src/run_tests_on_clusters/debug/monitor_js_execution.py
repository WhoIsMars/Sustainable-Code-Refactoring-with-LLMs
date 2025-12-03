#!/usr/bin/env python3
"""
Monitor JavaScript execution progress in real-time
"""

import time
import json
from pathlib import Path
from collections import defaultdict
from datetime import datetime

EXEC_OUTPUTS = Path(__file__).parent.parent / "execution_outputs"
LOGS_DIR = Path(__file__).parent / "js_full_execution_logs"

def analyze_progress():
    """Analyze current execution progress"""
    
    # Count result files with recent modifications
    recent_files = []
    cutoff_time = time.time() - (60 * 60)  # Last hour
    
    for result_file in EXEC_OUTPUTS.glob("*_results_*.json"):
        if result_file.stat().st_mtime >= cutoff_time:
            recent_files.append(result_file)
    
    # Analyze JavaScript entries
    js_stats = {
        'total_clusters': 0,
        'js_entries_found': 0,
        'js_passed': 0,
        'js_failed': 0,
        'js_timeout': 0,
        'clusters_with_js': set()
    }
    
    for result_file in sorted(EXEC_OUTPUTS.glob("*_results_*.json")):
        try:
            with open(result_file) as f:
                data = json.load(f)
            
            js_stats['total_clusters'] += 1
            
            js_entries = data.get('results', {}).get('javascript', [])
            if js_entries:
                cluster_name = result_file.stem.rsplit('_results_', 1)[0]
                js_stats['clusters_with_js'].add(cluster_name)
                
                for entry in js_entries:
                    js_stats['js_entries_found'] += 1
                    if entry.get('regressionTestPassed'):
                        js_stats['js_passed'] += 1
                    else:
                        js_stats['js_failed'] += 1
                    
                    if entry.get('timeout') or (entry.get('error_message', '') and 'TIMEOUT' in entry.get('error_message', '')):
                        js_stats['js_timeout'] += 1
        
        except Exception:
            continue
    
    return js_stats, recent_files

def print_status():
    """Print current status"""
    stats, recent_files = analyze_progress()
    
    now = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    
    print("\n" + "=" * 80)
    print(f"JAVASCRIPT EXECUTION MONITOR - {now}")
    print("=" * 80)
    
    print(f"\nClusters with JavaScript: {len(stats['clusters_with_js'])}")
    print(f"Total result files: {stats['total_clusters']}")
    print(f"Files modified in last hour: {len(recent_files)}")
    
    print(f"\nJavaScript Entries:")
    print(f"  Total:   {stats['js_entries_found']}")
    print(f"  Passed:  {stats['js_passed']} ({stats['js_passed']/max(1,stats['js_entries_found'])*100:.1f}%)")
    print(f"  Failed:  {stats['js_failed']} ({stats['js_failed']/max(1,stats['js_entries_found'])*100:.1f}%)")
    print(f"  Timeout: {stats['js_timeout']}")
    
    # Check log files
    if LOGS_DIR.exists():
        log_files = list(LOGS_DIR.glob("*.log"))
        if log_files:
            latest_log = max(log_files, key=lambda p: p.stat().st_mtime)
            print(f"\nLatest log: {latest_log.name}")
            print(f"  Size: {latest_log.stat().st_size / 1024:.1f} KB")
            print(f"  Modified: {datetime.fromtimestamp(latest_log.stat().st_mtime).strftime('%H:%M:%S')}")
    
    print("\n" + "=" * 80)

if __name__ == "__main__":
    print("JavaScript Execution Monitor")
    print("Press Ctrl+C to stop\n")
    
    try:
        while True:
            print_status()
            print("Refreshing in 30 seconds...")
            time.sleep(30)
    except KeyboardInterrupt:
        print("\n\nMonitor stopped.")
