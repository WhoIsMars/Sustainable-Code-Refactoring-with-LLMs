export const toRna = (dna) => {
  if (dna === '') {
    return '';
  }
  
  const mapping = { 'G': 'C', 'C': 'G', 'T': 'A', 'A': 'U' };
  const result = [];
  
  for (let i = 0; i < dna.length; i++) {
    const nucleotide = dna[i];
    const rnaBase = mapping[nucleotide];
    if (rnaBase === undefined) {
      throw new Error("Invalid input DNA.");
    }
    result[i] = rnaBase;
  }
  
  return result.join('');
};