"""Finds Pythagorean triplets"""

from math import gcd, sqrt

def primitive_triplets(num):
    """Finds all primative triplets that contain a certain number"""
    if num % 4 != 0:
        raise ValueError
    triplets = set()
    half_num = num // 2
    for m in range(1, int(sqrt(half_num)) + 1):
        if half_num % m == 0:
            n = half_num // m
            if (m + n) % 2 == 1 and gcd(m, n) == 1:
                a = abs(m**2 - n**2)
                b = 2 * m * n
                c = m**2 + n**2
                triplet = tuple(sorted((a, b, c)))
                triplets.add(triplet)
    return triplets

def triplets_in_range(start, stop):
    """Generates all triplets with elements in a range"""
    triples = set()
    for m in range(1, int(sqrt(stop)) + 1):
        for n in range(m % 2 + 1, m, 2):
            a = m**2 - n**2
            b = 2 * m * n
            c = m**2 + n**2
            if c > stop:
                break
            if a >= start and b >= start and a < b:
                triples.add(tuple(sorted((a, b, c))))
            elif b >= start and a >= start and b < a:
                triples.add(tuple(sorted((b, a, c))))
    return triples

def is_triplet(nums):
    """Is true if nums is a primative triplet"""
    a, b, c = sorted(nums)
    return a**2 + b**2 == c**2 and gcd(gcd(a, b), c) == 1