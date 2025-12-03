def to_rna(dna_strand):
    trans = str.maketrans({'G': 'C', 'C': 'G', 'T': 'A', 'A': 'U'})
    return dna_strand.translate(trans)