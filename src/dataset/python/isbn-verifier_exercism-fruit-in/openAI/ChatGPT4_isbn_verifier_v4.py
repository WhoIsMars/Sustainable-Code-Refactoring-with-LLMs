def is_valid(isbn):
    digits = []
    for ch in isbn:
        if ch == 'X' and len(digits) == 9:
            digits.append(10)
        elif ch.isdigit():
            digits.append(int(ch))
    
    if len(digits) != 10:
        return False

    return sum(d * i for d, i in zip(digits, range(10, 0, -1))) % 11 == 0