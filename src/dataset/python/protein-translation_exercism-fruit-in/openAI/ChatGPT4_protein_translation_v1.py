CODONS = {
    "AUG": "Methionine", "UUU": "Phenylalanine", "UUC": "Phenylalanine",
    "UUA": "Leucine", "UUG": "Leucine", "UCU": "Serine", "UCC": "Serine",
    "UCA": "Serine", "UCG": "Serine", "UAU": "Tyrosine", "UAC": "Tyrosine",
    "UGU": "Cysteine", "UGC": "Cysteine", "UGG": "Tryptophan",
    "UAA": "STOP", "UAG": "STOP", "UGA": "STOP",
}


def proteins(strand):
    return [
        CODONS[codon] for codon in (strand[i:i + 3] for i in range(0, len(strand), 3))
        if CODONS[codon] != "STOP"
    ][:next((i for i, codon in enumerate((strand[j:j + 3] for j in range(0, len(strand), 3))) if CODONS[codon] == "STOP"), len(strand) // 3)]