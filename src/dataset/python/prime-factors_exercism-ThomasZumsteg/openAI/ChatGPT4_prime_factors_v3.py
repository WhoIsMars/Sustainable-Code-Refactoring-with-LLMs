"""Finds the prime factors of a number"""

def prime_factors(number):
    """Finds prime factors of a number"""
    factors = []
    factor = 2
    while factor * factor <= number:
        while number % factor == 0:
            factors.append(factor)
            number //= factor
        factor += 1
    if number > 1:
        factors.append(number)
    return factors