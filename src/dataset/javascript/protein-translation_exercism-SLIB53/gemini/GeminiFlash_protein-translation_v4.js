function translate(sequence, acc = []) {
  if (!sequence) {
    return acc;
  }

  const codonMap = {
    'AUG': 'Methionine',
    'UUU': 'Phenylalanine',
    'UUC': 'Phenylalanine',
    'UUA': 'Leucine',
    'UUG': 'Leucine',
    'UCU': 'Serine',
    'UCC': 'Serine',
    'UCA': 'Serine',
    'UCG': 'Serine',
    'UAU': 'Tyrosine',
    'UAC': 'Tyrosine',
    'UGU': 'Cysteine',
    'UGC': 'Cysteine',
    'UGG': 'Tryptophan',
    'UAA': null,
    'UAG': null,
    'UGA': null,
  };

  for (let i = 0; i < sequence.length; i += 3) {
    const codon = sequence.substring(i, i + 3);
    const protein = codonMap[codon];

    if (protein) {
      acc.push(protein);
    } else if (protein === null) {
      return acc;
    } else {
      throw new Error('Invalid codon');
    }
  }

  return acc;
}

export default translate;