def is_valid(isbn):
    isbn = isbn.replace('-', '')
    if len(isbn) != 10:
        return False

    total = 0
    for i, char in enumerate(isbn):
        if char.isdigit():
            digit = int(char)
        elif char == 'X' and i == 9:
            digit = 10
        else:
            return False

        total += digit * (10 - i)

    return total % 11 == 0