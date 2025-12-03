def is_valid(isbn):
    digits = []
    for ch in isbn:
        if ch == '-':
            continue
        if ch == 'X':
            digits.append(10)
        elif ch.isdigit():
            digits.append(int(ch))
        else:
            return False

    if len(digits) != 10 or digits[-1] == 10 and any(d == 10 for d in digits[:-1]):
        return False

    return sum(d * i for d, i in zip(digits, range(10, 0, -1))) % 11 == 0