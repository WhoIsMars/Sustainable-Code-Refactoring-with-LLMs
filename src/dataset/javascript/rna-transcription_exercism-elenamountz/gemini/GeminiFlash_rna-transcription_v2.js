export const toRna = (dna) => {
  if (!dna) {
    return '';
  }

  const dnaToRnaMap = {
    'G': 'C',
    'C': 'G',
    'T': 'A',
    'A': 'U'
  };

  let rna = '';
  for (let i = 0; i < dna.length; i++) {
    const nucleotide = dna[i];
    if (dnaToRnaMap.hasOwnProperty(nucleotide)) {
      rna += dnaToRnaMap[nucleotide];
    } else {
      throw new Error("Invalid input DNA.");
    }
  }

  return rna;
};