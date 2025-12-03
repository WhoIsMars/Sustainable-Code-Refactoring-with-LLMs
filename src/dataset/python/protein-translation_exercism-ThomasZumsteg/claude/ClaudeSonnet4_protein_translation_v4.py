from itertools import count

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
    strand_len = len(strand)
    
    for i in range(0, strand_len, 3):
        if i + 3 > strand_len:
            break
        
        codon = strand[i:i+3]
        protein = PROTEINS.get(codon)
        
        if protein == 'STOP':
            break
        elif protein is not None:
            result.append(protein)
    
    return result