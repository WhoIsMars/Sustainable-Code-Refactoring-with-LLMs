"""Converts hex string to decimal number"""

def hexa(hex_num):
    """Converts hex string to decimal number"""
    dec_num = 0
    for char in hex_num.lower():
        value = ord(char)
        if 48 <= value <= 57:  # '0' <= char <= '9'
            digit = value - 48
        elif 97 <= value <= 102:  # 'a' <= char <= 'f'
            digit = value - 87
        else:
            raise ValueError
        dec_num = (dec_num << 4) | digit
    return dec_num