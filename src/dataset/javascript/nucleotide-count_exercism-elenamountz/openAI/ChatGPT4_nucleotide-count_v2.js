class NucleotideCounts {
  static parse(dna) {
    if (dna === '') return '0 0 0 0';

    const counts = { A: 0, C: 0, G: 0, T: 0 };

    for (const n of dna) {
      if (counts[n] === undefined) {
        throw new Error('Invalid nucleotide in strand');
      }
      counts[n]++;
    }

    return `${counts.A} ${counts.C} ${counts.G} ${counts.T}`;
  }
}

export default NucleotideCounts;