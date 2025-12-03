"""Finds consecutive number sequences"""

def slices(digits, size):
    """Returns list of lists of consecutive digits"""
    if size <= 0 or size > len(digits):
        raise ValueError

    slice_list = []
    digits_len = len(digits)
    for i in range(digits_len - size + 1):
        slice_list.append(list(map(int, digits[i:i+size])))
    return slice_list