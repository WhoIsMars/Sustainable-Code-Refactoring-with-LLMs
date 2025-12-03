type Count = {
  A: number,
  C: number,
  T: number,
  G: number,
}

class NucleotideCount {
  static nucleotideCounts(_dna: string): Count {
    const dna = _dna.toUpperCase();
    
    const counts = { A: 0, C: 0, T: 0, G: 0 };
    
    for (let i = 0; i < dna.length; i++) {
      const nucleotide = dna[i];
      if (nucleotide === 'A' || nucleotide === 'C' || nucleotide === 'T' || nucleotide === 'G') {
        counts[nucleotide as keyof Count]++;
      } else {
        throw 'Invalid nucleotide in strand';
      }
    }
    
    return counts;
  }

  private static isInvalid(_word: string): boolean {
    return _word.split('').filter(
      letter => letter !== "A" && letter !== "C" && letter !== "T" && letter !== "G"
    ).length !== 0; 
  }

  private static countLetter(_letter: string, _word: string): number {
   return _word.split('').filter(letter => letter === _letter).length; 
  }
}

export default NucleotideCount