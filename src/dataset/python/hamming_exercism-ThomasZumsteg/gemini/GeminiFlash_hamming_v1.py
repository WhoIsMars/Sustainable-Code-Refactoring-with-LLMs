"""Finds the hamming distance between two DNA sequences"""

def distance(strand_a, strand_b):
    """Counts the differences in two sequences of DNA"""
    if len(strand_a) != len(strand_b):
        raise ValueError("Strands must be of equal length")
    return sum(a != b for a, b in zip(strand_a, strand_b))