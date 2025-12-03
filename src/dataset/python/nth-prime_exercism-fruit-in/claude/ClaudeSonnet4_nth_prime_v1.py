def prime(number):
    if number < 1:
        raise(ValueError(r".+"))

    if number == 1:
        return 2
    
    # Use sieve for better performance when finding multiple primes
    if number <= 1000:
        return _sieve_prime(number)
    
    # For larger numbers, use optimized sequential search
    ret = 2
    count = 1
    
    while count < number:
        ret += 1 if ret == 2 else 2  # Skip even numbers after 2
        if isprime(ret):
            count += 1
    
    return ret


def _sieve_prime(n):
    # Estimate upper bound for nth prime using approximation
    if n < 6:
        return [2, 3, 5, 7, 11][n-1]
    
    limit = max(20, int(n * (1.25 * n.bit_length())))
    sieve = [True] * (limit + 1)
    sieve[0] = sieve[1] = False
    
    for i in range(2, int(limit**0.5) + 1):
        if sieve[i]:
            for j in range(i*i, limit + 1, i):
                sieve[j] = False
    
    primes = [i for i in range(2, limit + 1) if sieve[i]]
    return primes[n-1] if n <= len(primes) else prime(n)


def isprime(number):
    if number < 2:
        return False
    if number == 2:
        return True
    if number % 2 == 0:
        return False
    
    i = 3
    while i * i <= number:
        if number % i == 0:
            return False
        i += 2
    
    return True