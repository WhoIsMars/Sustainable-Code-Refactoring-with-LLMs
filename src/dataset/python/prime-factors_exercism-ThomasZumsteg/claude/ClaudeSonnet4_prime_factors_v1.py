"""Finds the prime factors of a number"""

def prime_factors(number):
    """Finds prime factors of a number"""
    if number <= 1:
        return []
    
    factors = []
    
    # Handle factor 2 separately to avoid checking even numbers later
    while number % 2 == 0:
        factors.append(2)
        number //= 2
    
    # Check odd factors only, starting from 3
    factor = 3
    while factor * factor <= number:
        while number % factor == 0:
            factors.append(factor)
            number //= factor
        factor += 2
    
    # If number is still greater than 1, it's a prime factor
    if number > 1:
        factors.append(int(number))
    
    return factors