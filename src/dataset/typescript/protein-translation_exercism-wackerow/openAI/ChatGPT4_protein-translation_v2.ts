class ProteinTranslation {
  private static readonly _codons = new Map<string, string>([
    ['AUG', 'Methionine'],
    ['UUU', 'Phenylalanine'],
    ['UUC', 'Phenylalanine'],
    ['UUA', 'Leucine'],
    ['UUG', 'Leucine'],
    ['UCU', 'Serine'],
    ['UCC', 'Serine'],
    ['UCA', 'Serine'],
    ['UCG', 'Serine'],
    ['UAU', 'Tyrosine'],
    ['UAC', 'Tyrosine'],
    ['UGU', 'Cysteine'],
    ['UGC', 'Cysteine'],
    ['UGG', 'Tryptophan'],
    ['UAA', 'STOP'],
    ['UAG', 'STOP'],
    ['UGA', 'STOP']
  ]);

  static proteins(rna: string): string[] {
    const aminoAcids: string[] = [];
    for (let i = 0, len = rna.length; i <= len - 3; i += 3) {
      const codon = rna.slice(i, i + 3);
      const protein = this._codons.get(codon);
      if (!protein || protein === 'STOP') break;
      aminoAcids.push(protein);
    }
    return aminoAcids;
  }
}

export default ProteinTranslation;