"""Finds consecutive number sequences"""

def slices(digits, size):
    """Returns list of lists of consecutive digits"""
    if size <= 0 or size > len(digits):
        raise ValueError
    
    digits_len = len(digits)
    return [[int(digits[i + j]) for j in range(size)] for i in range(digits_len - size + 1)]