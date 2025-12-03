def to_rna(dna_strand):
    trans = {'G': 'C', 'C': 'G', 'T': 'A', 'A': 'U'}
    return ''.join(trans[c] for c in dna_strand)