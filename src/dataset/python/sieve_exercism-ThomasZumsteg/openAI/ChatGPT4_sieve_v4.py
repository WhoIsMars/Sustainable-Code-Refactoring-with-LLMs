"""Finds prime numbers"""

def sieve(lim):
    """Implementation of sieve of Eratosthenes"""
    if lim < 2:
        return []
    sieve = [True] * (lim + 1)
    sieve[0] = sieve[1] = False
    for start in range(2, int(lim**0.5) + 1):
        if sieve[start]:
            sieve[start*start:lim+1:start] = [False] * len(range(start*start, lim+1, start))
    return [num for num, is_prime in enumerate(sieve) if is_prime]