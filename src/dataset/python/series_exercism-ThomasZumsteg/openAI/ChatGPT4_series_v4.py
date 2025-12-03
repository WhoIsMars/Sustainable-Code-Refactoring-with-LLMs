"""Finds consecutive number sequences"""

def slices(digits, size):
    """Returns list of lists of consecutive digits"""
    if size <= 0 or size > len(digits):
        raise ValueError

    return [list(map(int, digits[i:i+size])) for i in range(len(digits) - size + 1)]