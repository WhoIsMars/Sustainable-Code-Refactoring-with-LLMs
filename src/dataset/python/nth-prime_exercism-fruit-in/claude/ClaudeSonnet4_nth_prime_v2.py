def prime(number):
    if number < 1:
        raise(ValueError(r".+"))
    
    if number == 1:
        return 2
    
    primes = [2]
    candidate = 3
    
    while len(primes) < number:
        is_prime = True
        sqrt_candidate = int(candidate ** 0.5) + 1
        
        for p in primes:
            if p >= sqrt_candidate:
                break
            if candidate % p == 0:
                is_prime = False
                break
        
        if is_prime:
            primes.append(candidate)
        
        candidate += 2
    
    return primes[number - 1]


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