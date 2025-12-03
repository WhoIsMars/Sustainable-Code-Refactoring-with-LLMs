def verify(isbn):
    total = 0
    for i, d in enumerate(reversed(isbn)):
        if d == 'X':
            if i != 0:
                return False
            d = 10
        elif d.isdigit():
            d = int(d)
        else:
            return False
        total += d * (10 - i)
    return len(isbn) == 10 and total % 11 == 0