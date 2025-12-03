"""Finds the hamming distance between two DNA sequences"""

def distance(strand_a, strand_b):
    """Counts the differences in two sequences of DNA"""
    return sum(map(lambda pair: pair[0] != pair[1], zip(strand_a, strand_b)))