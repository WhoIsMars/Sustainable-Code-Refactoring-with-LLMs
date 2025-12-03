"""Finds prime numbers"""

def sieve(lim):
    """Implementation of sieve of Eratosthenes"""
    if lim < 2:
        return []
    sieve = [True] * (lim + 1)
    sieve[0] = sieve[1] = False
    primes = []
    for num in range(2, int(lim**0.5) + 1):
        if sieve[num]:
            primes.append(num)
            for multiple in range(num * num, lim + 1, num):
                sieve[multiple] = False
    primes.extend(num for num in range(int(lim**0.5) + 1, lim + 1) if sieve[num])
    return primes