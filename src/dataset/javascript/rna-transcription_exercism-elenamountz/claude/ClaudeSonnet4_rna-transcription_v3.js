export const toRna = (dna) => {
  if (!dna) return '';
  
  const mapping = { 'G': 'C', 'C': 'G', 'T': 'A', 'A': 'U' };
  let rna = '';
  
  for (let i = 0; i < dna.length; i++) {
    const nucleotide = mapping[dna[i]];
    if (nucleotide === undefined) {
      throw new Error("Invalid input DNA.");
    }
    rna += nucleotide;
  }
  
  return rna;
};