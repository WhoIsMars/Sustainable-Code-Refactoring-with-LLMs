"""Converts binary string to integer"""

def parse_binary(binary):
    """converts string of 1 and 0 to integer"""
    if not binary:
        return 0
    
    # Validate all characters at once
    if not all(bit in '01' for bit in binary):
        raise ValueError
    
    # Use built-in int() with base 2 for optimal performance
    return int(binary, 2)