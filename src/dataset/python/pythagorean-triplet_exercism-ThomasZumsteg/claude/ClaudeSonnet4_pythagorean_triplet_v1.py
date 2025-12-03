"""Finds Pythagorean triplets"""

def primitive_triplets(num):
    """Finds all primative triplets that contain a certain number"""
    if num % 4 != 0:
        raise ValueError
    triplets = set()
    half_num = num >> 1  # Use bit shift for division by 2
    
    # Optimize factor generation inline to avoid function call overhead
    sqrt_half = int(half_num**0.5)
    for i in range(1, sqrt_half + 1):
        if half_num % i == 0:
            m, n = half_num // i, i
            if gcd(m, n) == 1:
                # Pre-calculate squares to avoid repeated computation
                m_sq, n_sq = m * m, n * n
                triplet = tuple(sorted((m_sq - n_sq, m * n << 1, m_sq + n_sq)))
                triplets.add(triplet)
    return triplets

def factor_gen(n):
    """Generates factor pairs of number n"""
    sqrt_n = int(n**0.5)
    for i in range(1, sqrt_n + 1):
        if n % i == 0:
            yield (n // i, i)

def triplets_in_range(start, stop):
    """Generates all triplets with elements in a range"""
    triples = set()
    # Optimize loop bounds and reduce redundant calculations
    for c in range(max(start, 3), stop + 1):  # c must be at least 3 for valid triplet
        c_sq = c * c
        for b in range(start, min(c, int(c_sq**0.5) + 1)):  # Limit b based on c²
            b_sq = b * b
            a_sq = c_sq - b_sq
            if a_sq > 0:
                a = int(a_sq**0.5)
                if a >= start and a < b and a * a == a_sq:
                    triples.add((a, b, c))
    return triples

def is_triplet(nums):
    """Is true if nums is a primative triplet"""
    a, b, c = sorted(nums)
    return a * a + b * b == c * c and gcd(gcd(a, b), c) == 1

def gcd(a, b):
    """Finds the greatest common factor using Euclid's algorithm.
    See http://en.wikipedia.org/wiki/Euclid%27s_algorithm"""
    while b:
        a, b = b, a % b
    return a