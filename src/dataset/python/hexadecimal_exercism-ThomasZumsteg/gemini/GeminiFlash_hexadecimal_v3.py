"""Converts hex string to decimal number"""

def hexa(hex_num):
    """Converts hex string to decimal number"""
    dec_num = 0
    for char in hex_num.lower():
        value = ord(char)
        if 48 <= value <= 57:  # '0' <= char <= '9'
            value -= 48
        elif 97 <= value <= 102:  # 'a' <= char <= 'f'
            value -= 87
        else:
            raise ValueError
        dec_num = (dec_num << 4) | value
    return dec_num