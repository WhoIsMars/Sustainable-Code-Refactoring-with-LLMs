class NucleotideCount {
  static nucleotideCounts(dna: string) {
    const nucleotideCount = { A: 0, G: 0, T: 0, C: 0 };
    
    for (let i = 0; i < dna.length; i++) {
      const nucleotide = dna[i];
      switch (nucleotide) {
        case 'A':
          nucleotideCount.A++;
          break;
        case 'G':
          nucleotideCount.G++;
          break;
        case 'T':
          nucleotideCount.T++;
          break;
        case 'C':
          nucleotideCount.C++;
          break;
        default:
          throw new Error('Invalid nucleotide in strand');
      }
    }
    
    return nucleotideCount;
  }
}

export default NucleotideCount;