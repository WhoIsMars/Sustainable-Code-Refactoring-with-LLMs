const dna = function (sequence = '') {
    const nucleotides = ['G', 'T', 'A', 'C'];
    const validDNA = /^[GTAC]+$/;

    if (sequence && !validDNA.test(sequence)) {
        throw new Error("Not a valid DNA sequence");
    }

    const count = (letter) => {
        if (!nucleotides.includes(letter)) return 0;
        return [...sequence].filter((nuc) => nuc === letter).length;
    };

    const histogram = () => {
        return nucleotides.reduce((counts, nuc) => {
            counts[nuc] = count(nuc);
            return counts;
        }, {});
    };

    return {
        count,
        histogram,
    };
};

module.exports = dna;