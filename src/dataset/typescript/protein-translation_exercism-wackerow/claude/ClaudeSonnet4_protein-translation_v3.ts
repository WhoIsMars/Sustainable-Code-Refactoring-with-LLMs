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
    const length = rna.length;
    
    for (let i = 0; i < length - 2; i += 3) {
      const codon = rna.slice(i, i + 3);
      const protein = this._codons.get(codon);
      
      if (protein === 'STOP') {
        break;
      }
      
      if (protein) {
        aminoAcids.push(protein);
      }
    }
    
    return aminoAcids;
  }
}

export default ProteinTranslation