def verify(isbn):
    if len(isbn) != 10:
        return False
    
    total = 0
    for i, d in enumerate(isbn):
        weight = 10 - i
        if d == 'X':
            if i != 9:
                return False
            total += 10 * weight
        elif d.isdigit():
            total += int(d) * weight
        else:
            return False
    
    return total % 11 == 0