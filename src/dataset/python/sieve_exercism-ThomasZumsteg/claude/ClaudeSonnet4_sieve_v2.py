"""Finds primes numbers"""

def sieve(lim):
    """Implimentation of sieve of Eratosthenes"""
    if lim < 2:
        return []
    if lim == 2:
        return [2]
    
    # Use boolean array instead of set for better memory efficiency
    is_prime = [True] * (lim + 1)
    is_prime[0] = is_prime[1] = False
    
    # Only check up to sqrt(lim)
    for num in range(2, int(lim**0.5) + 1):
        if is_prime[num]:
            # Mark multiples starting from num*num with step num
            for multiple in range(num * num, lim + 1, num):
                is_prime[multiple] = False
    
    # Collect primes in one pass
    return [num for num in range(2, lim + 1) if is_prime[num]]