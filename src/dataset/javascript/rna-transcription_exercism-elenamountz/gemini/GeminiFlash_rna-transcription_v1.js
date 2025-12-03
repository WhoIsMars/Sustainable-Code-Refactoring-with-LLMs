const dnaToRnaMap = {
  'G': 'C',
  'C': 'G',
  'T': 'A',
  'A': 'U'
};

export const toRna = (dna) => {
  if (!dna) {
    return '';
  }

  let rna = '';
  for (let i = 0; i < dna.length; i++) {
    const nucleotide = dna[i];
    const rnaNucleotide = dnaToRnaMap[nucleotide];

    if (rnaNucleotide) {
      rna += rnaNucleotide;
    } else {
      throw new Error("Invalid input DNA.");
    }
  }
  return rna;
};