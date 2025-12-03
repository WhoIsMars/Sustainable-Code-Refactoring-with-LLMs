"""Converts hex string to decimal number"""

def hexa(hex_num):
    """Converts hex string to decimal number"""
    dec_num = 0
    for char in hex_num.lower():
        value = ord(char)
        if '0' <= char <= '9':
            digit = value - ord('0')
        elif 'a' <= char <= 'f':
            digit = value - ord('a') + 10
        else:
            raise ValueError
        dec_num = (dec_num << 4) | digit
    return dec_num