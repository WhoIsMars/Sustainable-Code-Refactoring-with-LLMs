class NucleotideCounts {
  constructor() {}

  static parse(dna) {
    const counts = { A: 0, C: 0, G: 0, T: 0 };

    if (!dna) {
      return '0 0 0 0';
    }

    for (let i = 0; i < dna.length; i++) {
      const nucleotide = dna[i];
      if (counts[nucleotide] !== undefined) {
        counts[nucleotide]++;
      } else {
        throw new Error('Invalid nucleotide in strand');
      }
    }

    return `${counts.A} ${counts.C} ${counts.G} ${counts.T}`;
  }
}

export default NucleotideCounts;