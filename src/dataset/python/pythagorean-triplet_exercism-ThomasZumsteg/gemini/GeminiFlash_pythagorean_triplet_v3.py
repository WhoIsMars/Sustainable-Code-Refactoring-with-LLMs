"""Finds Pythagorean triplets"""

def primitive_triplets(num):
    """Finds all primative triplets that contain a certain number"""
    if num % 4 != 0:
        raise ValueError
    triplets = set()
    half_num = num // 2
    for m, n in factor_gen(half_num):
        if gcd(m, n) == 1 and m > n:
            triplet = tuple(sorted((m**2 - n**2, 2*m*n, m**2 + n**2)))
            triplets.add(triplet)
    return triplets

def factor_gen(n):
    """Generates factor pairs of number n, optimized for m > n"""
    i = 1
    while i * i <= n:
        if n % i == 0:
            j = n // i
            if j >= i:
                yield (j, i)
        i += 1

def triplets_in_range(start, stop):
    """Generates all triplets with elements in a range"""
    triples = set()
    for a in range(start, stop + 1):
        for b in range(a + 1, stop + 1):
            c_squared = a**2 + b**2
            c = int(c_squared**0.5)
            if c > stop:
                break
            if c**2 == c_squared:
                triples.add((a, b, c))
    return triples

def is_triplet(nums):
    """Is true if nums is a primative triplet"""
    a, b, c = sorted(nums)
    return a**2 + b**2 == c**2 and gcd(gcd(a, b), c) == 1

def gcd(a, b):
    """Finds the greatest common factor using Euclid's algorithm.
    See http://en.wikipedia.org/wiki/Euclid's_algorithm"""
    while b:
        a, b = b, a % b
    return a