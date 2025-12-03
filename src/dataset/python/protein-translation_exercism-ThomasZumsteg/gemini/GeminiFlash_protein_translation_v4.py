CODON_MAP = (
    (('AUG',),'Methionine'),
    (('UUU', 'UUC'),'Phenylalanine'),
    (('UUA', 'UUG'),'Leucine'),
    (('UCU', 'UCC', 'UCA', 'UCG'),'Serine'),
    (('UAU', 'UAC'),'Tyrosine'),
    (('UGU', 'UGC'),'Cysteine'),
    (('UGG',),'Tryptophan'),
    (('UAA', 'UAG', 'UGA'),'STOP'))

PROTEINS = { codon: name for codons, name in CODON_MAP for codon in codons }

def proteins(strand):
    result = []
    for i in range(0, len(strand), 3):
        codon = strand[i:i+3]
        if len(codon) < 3:
            break
        protein = PROTEINS.get(codon)
        if protein == 'STOP':
            break
        result.append(protein)
    return result