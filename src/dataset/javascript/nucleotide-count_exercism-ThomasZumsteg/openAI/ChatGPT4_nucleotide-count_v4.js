const dna = function (sequence = '') {
    const nucleotides = ['G', 'T', 'A', 'C'];
    const validDNA = new RegExp(`^[${nucleotides.join('')}]+$`);

    if (sequence && !validDNA.test(sequence)) {
        throw new Error('Not a valid DNA sequence');
    }

    const count = (letter) => {
        if (!nucleotides.includes(letter)) return 0;
        return [...sequence].filter((char) => char === letter).length;
    };

    const histogram = () => {
        return nucleotides.reduce((counts, nucleotide) => {
            counts[nucleotide] = count(nucleotide);
            return counts;
        }, {});
    };

    return {
        count,
        histogram,
    };
};

module.exports = dna;