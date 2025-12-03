"""Converts binary string to integer"""

def parse_binary(binary):
    """converts string of 1 and 0 to integer"""
    if not all(bit in "01" for bit in binary):
        raise ValueError
    return int(binary, 2)