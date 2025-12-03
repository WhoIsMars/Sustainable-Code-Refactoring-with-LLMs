class NucleotideCount {
  static nucleotideCounts(dna: string) {
    const nucleotideCount: { [key: string]: number } = {
      A: 0,
      G: 0,
      T: 0,
      C: 0,
    };

    for (let i = 0; i < dna.length; i++) {
      const nucleotide = dna[i];
      if (nucleotideCount.hasOwnProperty(nucleotide)) {
        nucleotideCount[nucleotide]++;
      } else {
        throw new Error('Invalid nucleotide in strand');
      }
    }

    return nucleotideCount;
  }
}

export default NucleotideCount;