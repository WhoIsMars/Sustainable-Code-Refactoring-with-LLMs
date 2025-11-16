#!/usr/bin/env python3
"""
Convert DIRECT format result files to AGGREGATED format
========================================================

This script converts old DIRECT format result files (single entry per file)
to the new AGGREGATED format ({"results": {"language": [entries]}}).

Usage:
    python convert_direct_to_aggregated.py [--dry-run]
"""

import argparse
import json
import sys
from pathlib import Path
from typing import Dict, Any

# Add parent directory to path
sys.path.insert(0, str(Path(__file__).parent.parent))

from utility_dir.utility_paths import OUTPUT_DIR_FILEPATH
from utility_dir.general_utils import read_json, write_json


def is_direct_format(data: Dict[str, Any]) -> bool:
    """Check if data is in DIRECT format"""
    if not isinstance(data, dict):
        return False

    # DIRECT format has 'id' and 'filename' but NOT 'results'
    return ('id' in data and 'filename' in data and 'results' not in data)


def is_aggregated_format(data: Dict[str, Any]) -> bool:
    """Check if data is in AGGREGATED format"""
    if not isinstance(data, dict):
        return False

    # AGGREGATED format has 'results' key
    return 'results' in data


def convert_to_aggregated(direct_data: Dict[str, Any]) -> Dict[str, Any]:
    """
    Convert DIRECT format to AGGREGATED format

    Args:
        direct_data: Single entry in DIRECT format

    Returns:
        Data in AGGREGATED format
    """
    # Extract language from the entry
    language = direct_data.get('language', 'unknown')

    # Create AGGREGATED structure
    aggregated_data = {
        "results": {
            language: [direct_data]
        }
    }

    return aggregated_data


def merge_with_existing(
    new_entry: Dict[str, Any],
    existing_aggregated: Dict[str, Any]
) -> Dict[str, Any]:
    """
    Merge a new entry into existing AGGREGATED data

    Args:
        new_entry: New entry to add
        existing_aggregated: Existing AGGREGATED format data

    Returns:
        Merged AGGREGATED data
    """
    language = new_entry.get('language', 'unknown')
    entry_id = new_entry.get('id')

    # Ensure results structure exists
    if 'results' not in existing_aggregated:
        existing_aggregated['results'] = {}

    # Ensure language list exists
    if language not in existing_aggregated['results']:
        existing_aggregated['results'][language] = []

    # Check if entry already exists (by ID)
    entry_exists = False
    for idx, existing_entry in enumerate(existing_aggregated['results'][language]):
        if existing_entry.get('id') == entry_id:
            # Update existing entry
            existing_aggregated['results'][language][idx] = new_entry
            entry_exists = True
            break

    if not entry_exists:
        # Add new entry
        existing_aggregated['results'][language].append(new_entry)

    return existing_aggregated


def convert_file(file_path: Path, dry_run: bool = False) -> bool:
    """
    Convert a single file from DIRECT to AGGREGATED format

    Args:
        file_path: Path to the file to convert
        dry_run: If True, only report what would be done

    Returns:
        True if conversion was successful or needed
    """
    try:
        data = read_json(file_path)

        if not data:
            print(f"  ⚠️  Empty or corrupted: {file_path.name}")
            return False

        if is_aggregated_format(data):
            # Already in correct format
            return True

        if is_direct_format(data):
            print(f"  🔄 Converting: {file_path.name}")

            if not dry_run:
                # Convert to AGGREGATED format
                aggregated_data = convert_to_aggregated(data)
                write_json(file_path, aggregated_data)
                print(f"      ✓ Converted to AGGREGATED format")
            else:
                print(f"      [DRY RUN] Would convert to AGGREGATED format")

            return True
        else:
            print(f"  ⚠️  Unknown format: {file_path.name}")
            return False

    except Exception as e:
        print(f"  ❌ Error processing {file_path.name}: {e}")
        return False


def main():
    """Main conversion script"""
    parser = argparse.ArgumentParser(
        description="Convert DIRECT format result files to AGGREGATED format"
    )
    parser.add_argument(
        '--dry-run',
        action='store_true',
        help='Show what would be done without modifying files'
    )

    args = parser.parse_args()

    print("="*80)
    print("DIRECT → AGGREGATED Format Conversion")
    print("="*80)
    print(f"Dry run: {args.dry_run}")
    print(f"Directory: {OUTPUT_DIR_FILEPATH}")
    print()

    # Find all result files
    result_files = sorted(OUTPUT_DIR_FILEPATH.glob("*_results_*.json"))

    if not result_files:
        print("No result files found!")
        return

    print(f"Found {len(result_files)} result files")
    print()

    # Categorize files
    direct_files = []
    aggregated_files = []
    other_files = []

    print("Analyzing files...")
    for file_path in result_files:
        data = read_json(file_path)

        if not data:
            other_files.append(file_path)
        elif is_aggregated_format(data):
            aggregated_files.append(file_path)
        elif is_direct_format(data):
            direct_files.append(file_path)
        else:
            other_files.append(file_path)

    print(f"\nFile categories:")
    print(f"  AGGREGATED (correct): {len(aggregated_files)}")
    print(f"  DIRECT (to convert):  {len(direct_files)}")
    print(f"  Other/corrupted:      {len(other_files)}")
    print()

    if not direct_files:
        print("✅ No files need conversion!")
        return

    # Convert DIRECT files
    print(f"Converting {len(direct_files)} DIRECT format files...")
    print()

    converted_count = 0
    failed_count = 0

    for file_path in direct_files:
        if convert_file(file_path, dry_run=args.dry_run):
            converted_count += 1
        else:
            failed_count += 1

    # Summary
    print()
    print("="*80)
    print("CONVERSION SUMMARY")
    print("="*80)
    print(f"Files processed:  {len(direct_files)}")
    print(f"Successfully converted: {converted_count}")
    print(f"Failed: {failed_count}")

    if args.dry_run:
        print()
        print("⚠️  This was a DRY RUN - no files were modified")
        print("    Run without --dry-run to apply changes")
    else:
        print()
        print("✅ Conversion complete!")


if __name__ == '__main__':
    main()
