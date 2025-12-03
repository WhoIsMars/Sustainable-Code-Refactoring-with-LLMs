type Count = {
  A: number;
  C: number;
  T: number;
  G: number;
};

class NucleotideCount {
  static nucleotideCounts(_dna: string): Count {
    const dna = _dna.toUpperCase();
    if (this.isInvalid(dna)) {
      throw 'Invalid nucleotide in strand';
    }

    let aCount = 0;
    let cCount = 0;
    let tCount = 0;
    let gCount = 0;

    for (let i = 0; i < dna.length; i++) {
      const char = dna[i];
      switch (char) {
        case 'A':
          aCount++;
          break;
        case 'C':
          cCount++;
          break;
        case 'T':
          tCount++;
          break;
        case 'G':
          gCount++;
          break;
      }
    }

    return {
      A: aCount,
      C: cCount,
      T: tCount,
      G: gCount,
    };
  }

  private static isInvalid(_word: string): boolean {
    for (let i = 0; i < _word.length; i++) {
      const letter = _word[i];
      if (letter !== 'A' && letter !== 'C' && letter !== 'T' && letter !== 'G') {
        return true;
      }
    }
    return false;
  }
}

export default NucleotideCount;