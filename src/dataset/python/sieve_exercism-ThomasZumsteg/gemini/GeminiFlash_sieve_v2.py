"""Finds primes numbers"""

def sieve(lim):
    """Implimentation of sieve of Eratosthenes"""
    if lim < 2:
        return []
    primes = []
    is_prime = [True] * (lim + 1)
    is_prime[0] = is_prime[1] = False

    for num in range(2, int(lim**0.5) + 1):
        if is_prime[num]:
            for multiple in range(num*num, lim + 1, num):
                is_prime[multiple] = False

    for num in range(2, lim + 1):
        if is_prime[num]:
            primes.append(num)
    return primes