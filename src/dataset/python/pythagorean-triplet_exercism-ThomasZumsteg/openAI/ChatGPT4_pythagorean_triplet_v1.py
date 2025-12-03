"""Finds Pythagorean triplets"""

def primitive_triplets(num):
    """Finds all primitive triplets that contain a certain number"""
    if num % 4 != 0:
        raise ValueError
    triplets = set()
    for m, n in factor_gen(num // 2):
        if (m - n) % 2 == 1 and gcd(m, n) == 1:  # Check coprime and one odd, one even
            triplet = tuple(sorted((m**2 - n**2, 2 * m * n, m**2 + n**2)))
            triplets.add(triplet)
    return triplets

def factor_gen(n):
    """Generates factor pairs of number n"""
    for i in range(1, int(n**0.5) + 1):
        if n % i == 0:
            yield n // i, i

def triplets_in_range(start, stop):
    """Generates all triplets with elements in a range"""
    triples = set()
    for c in range(start, stop + 1):
        c2 = c * c
        for a in range(start, min(c, int((c2 - start**2)**0.5) + 1)):
            b2 = c2 - a * a
            b = int(b2**0.5)
            if b >= a and b <= stop and b2 == b * b:
                triples.add((a, b, c))
    return triples

def is_triplet(nums):
    """Is true if nums is a primitive triplet"""
    a, b, c = sorted(nums)
    return a**2 + b**2 == c**2 and gcd(a, b) == 1 and gcd(b, c) == 1

def gcd(a, b):
    """Finds the greatest common factor using Euclid's algorithm."""
    while b:
        a, b = b, a % b
    return a