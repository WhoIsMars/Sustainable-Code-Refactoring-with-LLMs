#!/usr/bin/env python3
"""
Automatic LLM Test Launcher
Monitors base code execution and automatically launches LLM tests when complete.
"""

import time
import subprocess
import sys
from pathlib import Path
from datetime import datetime

def wait_for_base_completion(pid_file='js_rerun.pid', log_file='full_js_base_rerun.log', check_interval=30):
    """Wait for base code execution to complete"""
    print("="*80)
    print("AUTOMATIC LLM TEST LAUNCHER")
    print("="*80)
    print(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print(f"Monitoring PID file: {pid_file}")
    print(f"Checking every {check_interval} seconds")
    print()

    while True:
        # Check if process is still running
        try:
            with open(pid_file) as f:
                pid = int(f.read().strip())

            # Check if process exists
            result = subprocess.run(['ps', '-p', str(pid)], capture_output=True)
            if result.returncode != 0:
                print(f"\n✓ Base code execution completed (PID {pid} no longer running)")
                break

        except (FileNotFoundError, ValueError):
            print(f"\n⚠️  PID file not found or invalid, checking log file...")

        # Also check log file for completion message
        if Path(log_file).exists():
            with open(log_file) as f:
                content = f.read()
                if 'EXECUTION COMPLETED' in content:
                    print(f"\n✓ Found completion message in log file")
                    break

        # Show progress
        try:
            success_count = subprocess.run(
                ['grep', '-c', '✓ Success', log_file],
                capture_output=True,
                text=True
            )
            count = int(success_count.stdout.strip()) if success_count.returncode == 0 else 0
            print(f"\r[{datetime.now().strftime('%H:%M:%S')}] Base execution in progress... ({count}/103 clusters completed)", end='', flush=True)
        except:
            pass

        time.sleep(check_interval)

    # Wait a bit to ensure all writes are complete
    print("\nWaiting 10 seconds for file writes to complete...")
    time.sleep(10)
    return True

def run_llm_tests():
    """Run LLM tests for all prompt versions using Python script"""
    print("\n" + "="*80)
    print("STARTING LLM CODE EXECUTION (ALL PROMPT VERSIONS)")
    print("="*80)
    print(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print()

    log_file = 'full_js_llm_all_rerun.log'

    # Run Python script for all LLM tests
    cmd = ['python3', '-u', 'run_all_js_llm.py']

    print(f"Command: {' '.join(cmd)}")
    print(f"Log file: {log_file}")
    print()

    try:
        # Run with unbuffered output
        with open(log_file, 'w') as f:
            result = subprocess.run(
                cmd,
                stdout=f,
                stderr=subprocess.STDOUT,
                text=True
            )

        if result.returncode == 0:
            print(f"✓ All LLM tests completed successfully")
        else:
            print(f"⚠️  LLM tests completed with exit code {result.returncode}")

        # Show log tail
        print("\n" + "-"*80)
        print("Last 30 lines of execution log:")
        print("-"*80)
        try:
            with open(log_file) as f:
                lines = f.readlines()
                for line in lines[-30:]:
                    print(line.rstrip())
        except:
            pass

    except Exception as e:
        print(f"✗ Error executing LLM tests: {e}")

    print("\n" + "="*80)
    print("✅ ALL LLM EXECUTIONS COMPLETED")
    print("="*80)
    print(f"Completed: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print("="*80)

def main():
    try:
        # Step 1: Wait for base code completion
        if wait_for_base_completion():
            print("\n✅ Base code execution completed!")

            # Show final stats
            try:
                with open('full_js_base_rerun.log') as f:
                    content = f.read()
                    if 'Success:' in content:
                        # Extract summary from log
                        for line in content.split('\n'):
                            if 'Success:' in line or 'Failed:' in line or 'Total clusters:' in line:
                                print(f"  {line.strip()}")
            except:
                pass

            # Step 2: Launch LLM tests
            user_confirm = input("\nProceed with LLM execution for all prompt versions (v1-v4)? (y/n): ")
            if user_confirm.lower() == 'y':
                run_llm_tests()
                print("\n" + "="*80)
                print("🎉 ALL TESTS COMPLETED (BASE + LLM)")
                print("="*80)
                return 0
            else:
                print("\nLLM execution skipped by user")
                return 0
        else:
            print("\n❌ Base code execution did not complete properly")
            return 1

    except KeyboardInterrupt:
        print("\n\n⚠️  Monitoring interrupted by user")
        return 1
    except Exception as e:
        print(f"\n\n❌ Error: {e}")
        import traceback
        traceback.print_exc()
        return 1

if __name__ == '__main__':
    sys.exit(main())
