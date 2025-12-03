"""Converts hex string to decimal number"""

def hexa(hex_num):
    """Converts hex string to decimal number"""
    dec_num = 0
    for char in hex_num.lower():
        dec_num <<= 4
        if '0' <= char <= '9':
            dec_num |= ord(char) - ord('0')
        elif 'a' <= char <= 'f':
            dec_num |= ord(char) - ord('a') + 10
        else:
            raise ValueError
    return dec_num