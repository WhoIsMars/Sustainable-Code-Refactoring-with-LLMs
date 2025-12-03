"""Finds primes numbers"""

def sieve(lim):
    """Implimentation of sieve of Eratosthenes"""
    if lim < 2:
        return []

    primes = []
    is_prime = [True] * (lim + 1)
    is_prime[0] = is_prime[1] = False

    for p in range(2, int(lim**0.5) + 1):
        if is_prime[p]:
            for i in range(p*p, lim + 1, p):
                is_prime[i] = False

    for p in range(2, lim + 1):
        if is_prime[p]:
            primes.append(p)
    return primes