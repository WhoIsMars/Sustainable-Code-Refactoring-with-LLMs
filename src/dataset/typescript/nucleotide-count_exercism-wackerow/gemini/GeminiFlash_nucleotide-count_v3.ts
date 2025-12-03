type Count = {
  A: number,
  C: number,
  T: number,
  G: number,
}

class NucleotideCount {
  static nucleotideCounts(_dna: string): Count {
    const dna = _dna.toUpperCase();
    if (this.isInvalid(dna)) { throw 'Invalid nucleotide in strand'}
    const counts: Count = { A: 0, C: 0, T: 0, G: 0 };
    for (let i = 0; i < dna.length; i++) {
      const char = dna[i];
      switch (char) {
        case 'A': counts.A++; break;
        case 'C': counts.C++; break;
        case 'T': counts.T++; break;
        case 'G': counts.G++; break;
      }
    }
    return counts;
  }

  private static isInvalid(_word: string): boolean {
    for (let i = 0; i < _word.length; i++) {
      const char = _word[i];
      if (char !== "A" && char !== "C" && char !== "T" && char !== "G") {
        return true;
      }
    }
    return false;
  }

}

export default NucleotideCount