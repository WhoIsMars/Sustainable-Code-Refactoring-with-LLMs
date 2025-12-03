def is_valid(isbn):
    isbn = isbn.replace('-', '')
    if len(isbn) != 10:
        return False

    total = 0
    for i, digit in enumerate(isbn):
        if i < 9 and not digit.isdigit():
            return False
        if i == 9 and digit == 'X':
            digit = 10
        elif not digit.isdigit():
            return False
        total += int(digit) * (10 - i)

    return total % 11 == 0