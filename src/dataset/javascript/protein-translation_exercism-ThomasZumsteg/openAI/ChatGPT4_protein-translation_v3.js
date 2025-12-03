const translate = new Map([
    ['AUG', 'Methionine'],
    ['UCA', 'Serine'],
    ['UCC', 'Serine'],
    ['UCG', 'Serine'],
    ['UCU', 'Serine'],
    ['UUA', 'Leucine'],
    ['UUC', 'Phenylalanine'],
    ['UUG', 'Leucine'],
    ['UUU', 'Phenylalanine'],
    ['UAU', 'Tyrosine'],
    ['UAC', 'Tyrosine'],
    ['UGC', 'Cysteine'],
    ['UGU', 'Cysteine'],
    ['UGG', 'Tryptophan'],
    ['UAA', 'STOP'],
    ['UAG', 'STOP'],
    ['UGA', 'STOP'],
]);

module.exports = function (rna) {
    if (!rna || rna.length % 3 !== 0) throw new Error('Invalid RNA sequence');
    const result = [];
    for (let i = 0; i < rna.length; i += 3) {
        const codon = rna.substring(i, i + 3);
        const protein = translate.get(codon);
        if (!protein) throw new Error('Invalid codon');
        if (protein === 'STOP') break;
        result.push(protein);
    }
    return result;
};