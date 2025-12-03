class NucleotideCount {
  static nucleotideCounts(dna: string) {
    const nucleotideCount: { [key: string]: number } = {
      A: 0,
      C: 0,
      G: 0,
      T: 0,
    };

    for (let i = 0; i < dna.length; i++) {
      const nucleotide = dna[i];
      if (nucleotideCount[nucleotide] === undefined) {
        throw new Error('Invalid nucleotide in strand');
      }
      nucleotideCount[nucleotide]++;
    }

    return nucleotideCount;
  }
}

export default NucleotideCount;