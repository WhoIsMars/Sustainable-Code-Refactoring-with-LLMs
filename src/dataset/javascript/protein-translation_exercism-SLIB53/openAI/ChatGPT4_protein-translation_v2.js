function translate(sequence, acc = []) {
  const codonMap = {
    AUG: 'Methionine',
    UUU: 'Phenylalanine', UUC: 'Phenylalanine',
    UUA: 'Leucine', UUG: 'Leucine',
    UCU: 'Serine', UCC: 'Serine', UCA: 'Serine', UCG: 'Serine',
    UAU: 'Tyrosine', UAC: 'Tyrosine',
    UGU: 'Cysteine', UGC: 'Cysteine',
    UGG: 'Tryptophan',
    UAA: null, UAG: null, UGA: null
  };

  while (sequence) {
    const codon = sequence.slice(0, 3);
    const protein = codonMap[codon];

    if (protein === undefined) throw new Error('Invalid codon');
    if (protein === null) break;

    acc.push(protein);
    sequence = sequence.slice(3);
  }

  return acc;
}

export default translate;