def verify(isbn):
    isbn = isbn.replace('-', '')
    if not (9 <= len(isbn) <= 10):
        return False

    total = 0
    for i, digit in enumerate(isbn):
        if digit == 'X' and i == 9:
            total += 10 * (10 - i)
        elif digit.isdigit():
            total += int(digit) * (10 - i)
        else:
            return False

    return len(isbn) == 10 and total % 11 == 0