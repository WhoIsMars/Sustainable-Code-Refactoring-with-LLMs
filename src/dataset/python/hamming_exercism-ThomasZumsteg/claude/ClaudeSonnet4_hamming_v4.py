"""Finds the hamming distance between two DNA sequences"""

def distance(strand_a, strand_b):
    """Counts the differences in two sequences of DNA"""
    count = 0
    for i in range(len(strand_a)):
        if strand_a[i] != strand_b[i]:
            count += 1
    return count