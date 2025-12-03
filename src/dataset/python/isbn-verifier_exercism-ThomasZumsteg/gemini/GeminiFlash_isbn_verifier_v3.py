def verify(isbn):
    isbn = isbn.replace('-', '')
    if not (9 <= len(isbn) <= 10):
        return False

    total = 0
    for i, digit in enumerate(reversed(isbn)):
        if digit == 'X' and i == 0:
            total += 10 * (i + 1)
        elif digit.isdigit():
            total += int(digit) * (i + 1)
        else:
            return False

    return len(isbn) == 10 and total % 11 == 0