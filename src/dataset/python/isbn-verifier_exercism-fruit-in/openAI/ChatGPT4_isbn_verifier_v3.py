def is_valid(isbn):
    digits = []
    for ch in isbn:
        if ch == 'X' and len(digits) == 9:
            digits.append(10)
        elif ch.isdigit():
            digits.append(int(ch))
    
    if len(digits) != 10:
        return False

    return sum(d * (10 - i) for i, d in enumerate(digits)) % 11 == 0