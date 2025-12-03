def hexa(hex_num):
    """Converts hex string to decimal number"""
    try:
        return int(hex_num, 16)
    except ValueError:
        raise ValueError("Invalid hexadecimal input")