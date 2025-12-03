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
    
    for (let i = 0; i < dna.length; i++) {
      const nucleotide = dna[i];
      if (nucleotide === 'A') {
        counts.A++;
      } else if (nucleotide === 'C') {
        counts.C++;
      } else if (nucleotide === 'T') {
        counts.T++;
      } else if (nucleotide === 'G') {
        counts.G++;
      } else {
        throw 'Invalid nucleotide in strand';
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

  private static countLetter(_letter: string, _word: string): number {
    let count = 0;
    for (let i = 0; i < _word.length; i++) {
      if (_word[i] === _letter) {
        count++;
      }
    }
    return count;
  }
}

export default NucleotideCount