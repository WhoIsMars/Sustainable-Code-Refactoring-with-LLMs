"""Finds the prime factors of a number"""

def prime_factors(number):
    """Finds prime factors of a number"""
    factors = []
    while number % 2 == 0:
        factors.append(2)
        number //= 2
    for factor in range(3, int(number**0.5) + 1, 2):
        while number % factor == 0:
            factors.append(factor)
            number //= factor
    if number > 2:
        factors.append(number)
    return factors