import math

def prime(number):
    if number < 1:
        raise ValueError(".+")

    if number == 1:
        return 2

    count = 1
    candidate = 3
    while count < number:
        if isprime(candidate):
            count += 1
        if count < number:
            candidate += 2
        else:
            break

    return candidate


def isprime(number):
    if number <= 1:
        return False
    if number <= 3:
        return True
    if number % 2 == 0 or number % 3 == 0:
        return False
    for i in range(5, int(math.sqrt(number)) + 1, 6):
        if number % i == 0 or number % (i + 2) == 0:
            return False
    return True