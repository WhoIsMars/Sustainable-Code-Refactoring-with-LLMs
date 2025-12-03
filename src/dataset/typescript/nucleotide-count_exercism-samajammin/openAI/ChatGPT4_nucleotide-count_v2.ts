class NucleotideCount {
  static nucleotideCounts(dna: string) {
    const nucleotideCount = { A: 0, G: 0, T: 0, C: 0 } as const;

    for (let i = 0; i < dna.length; i++) {
      const nucleotide = dna[i];
      if (!(nucleotide in nucleotideCount)) {
        throw new Error('Invalid nucleotide in strand');
      }
      nucleotideCount[nucleotide as keyof typeof nucleotideCount]++;
    }

    return nucleotideCount;
  }
}

export default NucleotideCount;