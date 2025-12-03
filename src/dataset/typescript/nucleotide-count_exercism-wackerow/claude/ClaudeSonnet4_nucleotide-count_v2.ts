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
}

export default NucleotideCount