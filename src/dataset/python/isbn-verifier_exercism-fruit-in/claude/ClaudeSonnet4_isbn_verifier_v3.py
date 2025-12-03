def is_valid(isbn):
    digits = []
    for ch in isbn:
        if ch == '-':
            continue
        elif ch == 'X':
            digits.append(10)
        elif ch.isdigit():
            digits.append(int(ch))
        else:
            return False
    
    if len(digits) != 10 or digits[9] != 10 and any(d == 10 for d in digits[:9]):
        return False
    
    checksum = 0
    for i, digit in enumerate(digits):
        checksum += digit * (10 - i)
    
    return checksum % 11 == 0