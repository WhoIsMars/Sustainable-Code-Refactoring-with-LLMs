const dna = function (sequence = '') {
  const nucleotides = ['G', 'T', 'A', 'C'];
  const validDNA = new RegExp(`^[${nucleotides.join('')}]+$`);

  if (sequence && !validDNA.test(sequence)) {
    throw new Error('Not a valid DNA sequence');
  }

  const nucleotideCounts = nucleotides.reduce((acc, nucleotide) => {
    acc[nucleotide] = 0;
    return acc;
  }, {});

  for (const char of sequence) {
    if (nucleotideCounts[char] !== undefined) {
      nucleotideCounts[char]++;
    }
  }

  function count(letter) {
    return nucleotideCounts[letter] || 0;
  }

  function histogram() {
    return { ...nucleotideCounts };
  }

  return {
    count,
    histogram,
  };
};

module.exports = dna;