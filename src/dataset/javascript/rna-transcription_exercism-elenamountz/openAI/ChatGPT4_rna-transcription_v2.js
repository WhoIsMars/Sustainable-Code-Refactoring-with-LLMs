export const toRna = (dna) => {
  if (dna === '') return '';
  
  const transcriptionMap = {
    G: 'C',
    C: 'G',
    T: 'A',
    A: 'U'
  };

  return [...dna].map(nucleotide => {
    if (!transcriptionMap[nucleotide]) throw new Error("Invalid input DNA.");
    return transcriptionMap[nucleotide];
  }).join('');
};