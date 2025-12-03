def is_valid(isbn):
    isbn = isbn.replace('-', '')
    if len(isbn) != 10:
        return False

    total = 0
    for i, digit in enumerate(isbn):
        if digit.isdigit():
            total += int(digit) * (10 - i)
        elif digit == 'X' and i == 9:
            total += 10
        else:
            return False

    return total % 11 == 0