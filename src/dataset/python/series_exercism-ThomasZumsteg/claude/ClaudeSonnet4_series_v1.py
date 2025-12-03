"""Finds consecutive number sequences"""

def slices(digits, size):
    """Returns list of lists of consecutive digits"""
    if size <= 0 or size > len(digits):
        raise ValueError

    digits_len = len(digits)
    slice_list = []
    slice_list_append = slice_list.append
    
    for i in range(digits_len - size + 1):
        slice_list_append([int(digits[j]) for j in range(i, i + size)])
    
    return slice_list