def distance(strand_a, strand_b):
    """Counts the differences in two sequences of DNA"""
    return sum(a != b for a, b in zip(strand_a, strand_b))