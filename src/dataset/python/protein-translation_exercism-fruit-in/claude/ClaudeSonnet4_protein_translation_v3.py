CODONS = {
    "AUG": "Methionine", "UUU": "Phenylalanine", "UUC": "Phenylalanine",
    "UUA": "Leucine", "UUG": "Leucine", "UCU": "Serine", "UCC": "Serine",
    "UCA": "Serine", "UCG": "Serine", "UAU": "Tyrosine", "UAC": "Tyrosine",
    "UGU": "Cysteine", "UGC": "Cysteine", "UGG": "Tryptophan",
    "UAA": "STOP", "UAG": "STOP", "UGA": "STOP",
}

STOP_CODONS = {"UAA", "UAG", "UGA"}


def proteins(strand):
    result = []
    
    for i in range(0, len(strand), 3):
        if i + 3 > len(strand):
            break
        
        codon = strand[i:i + 3]
        
        if codon in STOP_CODONS:
            break
        
        protein = CODONS.get(codon)
        if protein:
            result.append(protein)
    
    return result


def chunks(s, n):
    for i in range(0, len(s), n):
        yield s[i:i + n]