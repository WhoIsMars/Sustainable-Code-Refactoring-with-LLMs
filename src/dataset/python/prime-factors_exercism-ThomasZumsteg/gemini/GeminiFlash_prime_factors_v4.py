"""Finds the prime factors of a number"""

def prime_factors(number):
    """Finds prime factors of a number"""
    factors = []
    d = 2
    while d * d <= number:
        while number % d == 0:
            factors.append(d)
            number //= d
        d += 1
    if number > 1:
        factors.append(number)
    return factors