def verify(isbn):
    if len(isbn) != 10:
        return False
    
    total = 0
    for i, d in enumerate(isbn):
        if d == 'X':
            if i != 9:
                return False
            total += 10 * (10 - i)
        elif d.isdigit():
            total += int(d) * (10 - i)
        else:
            return False
    
    return total % 11 == 0