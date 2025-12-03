export const toRna = (dna) => {
  if (dna === '') return '';
  const mapping = { G: 'C', C: 'G', T: 'A', A: 'U' };
  return [...dna].map(nucleotide => {
    if (!mapping[nucleotide]) throw new Error("Invalid input DNA.");
    return mapping[nucleotide];
  }).join('');
};