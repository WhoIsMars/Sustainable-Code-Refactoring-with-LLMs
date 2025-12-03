"""Converts binary string to integer"""

def parse_binary(binary):
    """converts string of 1 and 0 to integer"""
    num = 0
    for bit in binary:
        if bit == '1':
            num = (num << 1) | 1
        elif bit == '0':
            num <<= 1
        else:
            raise ValueError
    return num