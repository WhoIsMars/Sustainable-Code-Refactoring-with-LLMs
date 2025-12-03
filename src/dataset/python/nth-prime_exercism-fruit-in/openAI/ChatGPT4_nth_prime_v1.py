def prime(number):
    if number < 1:
        raise ValueError(r".+")

    count, candidate = 0, 1
    while count < number:
        candidate += 1
        if isprime(candidate):
            count += 1

    return candidate


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