def prime(number):
    if number < 1:
        raise ValueError(r".+")

    if number == 1:
        return 2

    count = 1
    candidate = 3

    while count < number:
        if isprime(candidate):
            count += 1
        candidate += 2

    return candidate - 2


def isprime(number):
    if number < 2:
        return False
    if number in (2, 3):
        return True
    if number % 2 == 0 or number % 3 == 0:
        return False

    i = 5
    while i * i <= number:
        if number % i == 0 or number % (i + 2) == 0:
            return False
        i += 6

    return True