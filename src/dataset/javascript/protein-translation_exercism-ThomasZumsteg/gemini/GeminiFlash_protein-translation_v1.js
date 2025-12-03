const translate = {
    'AUG': 'Methionine',
    'UCA': 'Serine',
    'UCC': 'Serine',
    'UCG': 'Serine',
    'UCU': 'Serine',
    'UUA': 'Leucine',
    'UUC': 'Phenylalanine',
    'UUG': 'Leucine',
    'UUU': 'Phenylalanine',
    'UAU': 'Tyrosine',
    'UAC': 'Tyrosine',
    'UGC': 'Cysteine',
    'UGU': 'Cysteine',
    'UGG': 'Tryptophan',
    'UAA': 'STOP',
    'UAG': 'STOP',
    'UGA': 'STOP',
};

module.exports = function(rna) {
    if (!rna) {
        return [];
    }

    const result = [];
    for (let i = 0; i < rna.length; i += 3) {
        const codon = rna.slice(i, i + 3);
        const protein = translate[codon];

        if (protein === 'STOP') {
            break;
        }

        if (!protein) {
            throw new Error('Invalid codon');
        }

        result.push(protein);
    }

    return result;
};