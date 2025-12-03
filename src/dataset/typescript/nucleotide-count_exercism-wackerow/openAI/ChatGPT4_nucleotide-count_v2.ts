type Count = {
  A: number,
  C: number,
  T: number,
  G: number,
}

class NucleotideCount {
  static nucleotideCounts(dna: string): Count {
    const counts: Count = { A: 0, C: 0, T: 0, G: 0 };

    for (const nucleotide of dna.toUpperCase()) {
      if (!(nucleotide in counts)) {
        throw 'Invalid nucleotide in strand';
      }
      counts[nucleotide as keyof Count]++;
    }

    return counts;
  }
}

export default NucleotideCount;