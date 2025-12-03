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
    ['UGA', 'STOP']
]);

module.exports = function(rna) {
    if (!rna) return [];
    
    const result = [];
    const length = rna.length;
    
    for (let i = 0; i < length; i += 3) {
        const codon = rna.substr(i, 3);
        if (codon.length < 3) break;
        
        const protein = translate.get(codon);
        if (protein === 'STOP') break;
        if (protein === undefined) throw new Error('Invalid codon');
        
        result.push(protein);
    }
    
    return result;
};