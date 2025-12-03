"""Transforms an old data structure into a new one"""

def transform(old_structure):
    """Swaps key and value in old data structure"""
    new_structure = {}
    for key, items in old_structure.items():
        new_structure.update({item.lower(): key for item in items})
    return new_structure