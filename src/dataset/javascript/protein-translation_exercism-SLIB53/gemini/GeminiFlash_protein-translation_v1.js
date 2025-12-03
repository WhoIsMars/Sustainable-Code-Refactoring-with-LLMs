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

function translate(sequence) {
  if (!sequence) {
    return [];
  }

  const proteins = [];
  for (let i = 0; i < sequence.length; i += 3) {
    const codon = sequence.substring(i, i + 3);
    const protein = codonMap[codon];

    if (protein === undefined) {
      throw new Error('Invalid codon');
    }

    if (protein === null) {
      break;
    }

    proteins.push(protein);
  }

  return proteins;
}

export default translate;