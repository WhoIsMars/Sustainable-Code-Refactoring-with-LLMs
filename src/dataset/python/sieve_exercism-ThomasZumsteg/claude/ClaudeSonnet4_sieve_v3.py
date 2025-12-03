"""Finds primes numbers"""

def sieve(lim):
    """Implementation of sieve of Eratosthenes"""
    if lim < 2:
        return []
    if lim == 2:
        return [2]
    
    is_prime = [True] * (lim + 1)
    is_prime[0] = is_prime[1] = False
    
    for i in range(2, int(lim**0.5) + 1):
        if is_prime[i]:
            for j in range(i * i, lim + 1, i):
                is_prime[j] = False
    
    return [i for i in range(2, lim + 1) if is_prime[i]]