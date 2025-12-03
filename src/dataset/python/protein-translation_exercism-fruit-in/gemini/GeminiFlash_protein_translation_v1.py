CODONS = {
    "AUG": "Methionine", "UUU": "Phenylalanine", "UUC": "Phenylalanine",
    "UUA": "Leucine", "UUG": "Leucine", "UCU": "Serine", "UCC": "Serine",
    "UCA": "Serine", "UCG": "Serine", "UAU": "Tyrosine", "UAC": "Tyrosine",
    "UGU": "Cysteine", "UGC": "Cysteine", "UGG": "Tryptophan",
    "UAA": "STOP", "UAG": "STOP", "UGA": "STOP",
}


def proteins(strand):
    proteins_list = []
    for i in range(0, len(strand), 3):
        codon = strand[i:i + 3]
        protein = CODONS.get(codon)
        if protein == "STOP":
            break
        if protein:
            proteins_list.append(protein)
    return proteins_list