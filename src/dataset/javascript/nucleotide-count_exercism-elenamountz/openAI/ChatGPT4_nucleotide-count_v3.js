class NucleotideCounts {
  static parse(dna) {
    if (dna === '') return '0 0 0 0';

    const resultArr = [0, 0, 0, 0];
    const nucleotideMap = { A: 0, C: 1, G: 2, T: 3 };

    for (const n of dna) {
      const index = nucleotideMap[n];
      if (index === undefined) throw new Error('Invalid nucleotide in strand');
      resultArr[index]++;
    }

    return resultArr.join(' ');
  }
}

export default NucleotideCounts;