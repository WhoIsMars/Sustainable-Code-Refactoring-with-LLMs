def verify(isbn):
    counter = 1
    total = 0
    for d in reversed(isbn):
        if d == 'X':
            if counter != 1:
                return False
            total += 10
        elif d.isdigit():
            total += int(d) * counter
        else:
            continue
        counter += 1
    return counter == 11 and total % 11 == 0