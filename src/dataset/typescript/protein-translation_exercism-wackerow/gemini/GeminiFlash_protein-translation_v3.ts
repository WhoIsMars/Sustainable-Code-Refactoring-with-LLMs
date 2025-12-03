class ProteinTranslation {
  private static readonly _codons: Readonly<{[s: string]: string}> = {
    'AUG': 'Methionine',
    'UUU': 'Phenylalanine',
    'UUC': 'Phenylalanine',
    'UUA': 'Leucine',
    'UUG': 'Leucine',
    'UCU': 'Serine',
    'UCC': 'Serine',
    'UCA': 'Serine',
    'UCG': 'Serine',
    'UAU': 'Tyrosine',
    'UAC': 'Tyrosine',
    'UGU': 'Cysteine',
    'UGC': 'Cysteine',
    'UGG': 'Tryptophan',
    'UAA': 'STOP',
    'UAG': 'STOP',
    'UGA': 'STOP'
  };

  static proteins(rna: string): string[] {
    const aminoAcids: string[] = [];
    for (let i = 0; i < rna.length; i += 3) {
      const codon = rna.substring(i, i + 3);
      const protein = this._codons[codon];

      if (protein === 'STOP') {
        return aminoAcids;
      }

      if (protein) {
        aminoAcids.push(protein);
      } else {
        break;
      }
    }
    return aminoAcids;
  }
}

export default ProteinTranslation