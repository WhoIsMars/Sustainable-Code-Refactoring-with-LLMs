"""Finds Pythagorean triplets"""

import math

def primitive_triplets(num):
    """Finds all primative triplets that contain a certain number"""
    if num % 4 != 0:
        raise ValueError
    triplets = set()
    half_num = num >> 1
    sqrt_half = int(math.sqrt(half_num))
    
    for i in range(1, sqrt_half + 1):
        if half_num % i == 0:
            m, n = half_num // i, i
            if math.gcd(m, n) == 1:
                a = m * m - n * n
                b = 2 * m * n
                c = m * m + n * n
                triplet = tuple(sorted((a, b, c)))
                triplets.add(triplet)
    return triplets

def factor_gen(n):
    """Generates factor pairs of number n"""
    sqrt_n = int(math.sqrt(n))
    for i in range(1, sqrt_n + 1):
        if n % i == 0:
            yield (n // i, i)

def triplets_in_range(start, stop):
    """Generates all triplets with elements in a range"""
    triples = set()
    start_sq = start * start
    
    for c in range(start, stop + 1):
        c_sq = c * c
        for b in range(start, c):
            b_sq = b * b
            a_sq = c_sq - b_sq
            if a_sq < start_sq:
                continue
            a = int(math.sqrt(a_sq))
            if a >= start and a < b and a * a == a_sq:
                triples.add((a, b, c))
    return triples

def is_triplet(nums):
    """Is true if nums is a primative triplet"""
    a, b, c = sorted(nums)
    return a * a + b * b == c * c and math.gcd(math.gcd(a, b), c) == 1

def gcd(a, b):
    """Finds the greatest common factor using Euclid's algorithm.
    See http://en.wikipedia.org/wiki/Euclid%27s_algorithm"""
    return math.gcd(a, b)