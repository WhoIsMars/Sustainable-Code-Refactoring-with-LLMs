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

  const codon = sequence.substring(0, 3);
  const protein = codonMap[codon];

  if (protein === undefined) {
    throw new Error('Invalid codon');
  }

  if (protein === null) {
    return acc;
  }

  return translate(sequence.substring(3), acc.concat([protein]));
}

export default translate;