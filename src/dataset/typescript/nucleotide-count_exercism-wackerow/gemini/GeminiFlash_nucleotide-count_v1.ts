type Count = {
  A: number;
  C: number;
  T: number;
  G: number;
};

class NucleotideCount {
  static nucleotideCounts(dna: string): Count {
    const upperDNA = dna.toUpperCase();
    if (this.isInvalid(upperDNA)) {
      throw 'Invalid nucleotide in strand';
    }

    const counts: Count = { A: 0, C: 0, T: 0, G: 0 };
    for (let i = 0; i < upperDNA.length; i++) {
      const nucleotide = upperDNA[i];
      counts[nucleotide as keyof Count]++;
    }

    return counts;
  }

  private static isInvalid(word: string): boolean {
    for (let i = 0; i < word.length; i++) {
      const letter = word[i];
      if (letter !== 'A' && letter !== 'C' && letter !== 'T' && letter !== 'G') {
        return true;
      }
    }
    return false;
  }
}

export default NucleotideCount;