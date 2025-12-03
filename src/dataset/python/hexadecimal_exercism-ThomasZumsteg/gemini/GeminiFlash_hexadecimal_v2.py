"""Converts hex string to decimal number"""

def hexa(hex_num):
    """Converts hex string to decimal number"""
    dec_num = 0
    for char in hex_num.lower():
        if '0' <= char <= '9':
            digit = ord(char) - ord('0')
        elif 'a' <= char <= 'f':
            digit = ord(char) - ord('a') + 10
        else:
            raise ValueError
        dec_num = (dec_num << 4) | digit
    return dec_num