def transform(old_structure):
    """Swaps key and value in old data structure"""
    return {item.lower(): key for key, items in old_structure.items() for item in items}