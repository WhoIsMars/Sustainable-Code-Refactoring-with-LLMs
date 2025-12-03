type Count = {
  A: number,
  C: number,
  T: number,
  G: number,
}

class NucleotideCount {
  static nucleotideCounts(_dna: string): Count {
    const dna = _dna.toUpperCase();
    const counts: Count = { A: 0, C: 0, T: 0, G: 0 };

    for (const letter of dna) {
      if (!(letter in counts)) throw 'Invalid nucleotide in strand';
      counts[letter as keyof Count]++;
    }

    return counts;
  }
}

export default NucleotideCount;