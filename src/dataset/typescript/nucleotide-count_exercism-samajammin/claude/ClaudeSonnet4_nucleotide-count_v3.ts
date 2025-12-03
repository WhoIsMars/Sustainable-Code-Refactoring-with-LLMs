class NucleotideCount {
  private static readonly VALID_NUCLEOTIDES = new Set(['A', 'G', 'T', 'C']);
  
  static nucleotideCounts(dna: string) {
    const nucleotideCount = { A: 0, G: 0, T: 0, C: 0 };
    
    for (let i = 0; i < dna.length; i++) {
      const nucleotide = dna[i];
      if (!this.VALID_NUCLEOTIDES.has(nucleotide)) {
        throw new Error('Invalid nucleotide in strand');
      }
      nucleotideCount[nucleotide as keyof typeof nucleotideCount]++;
    }
    
    return nucleotideCount;
  }
}

export default NucleotideCount;