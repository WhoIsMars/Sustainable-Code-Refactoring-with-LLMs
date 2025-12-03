const dna = function (sequence) {
    const nucleotides = ['G', 'T', 'A', 'C'];
    const validDNA = new RegExp(`^[${nucleotides.join('')}]+$`);

    if (sequence && !validDNA.test(sequence)) {
        throw new Error("Not a valid DNA sequence");
    }

    const sequenceCounts = sequence
        ? nucleotides.reduce((acc, nucleotide) => {
              acc[nucleotide] = 0;
              return acc;
          }, {})
        : {};

    if (sequence) {
        for (const char of sequence) {
            if (sequenceCounts[char] !== undefined) {
                sequenceCounts[char]++;
            }
        }
    }

    const count = (letter) => sequenceCounts[letter] || 0;

    const histogram = () => ({ ...sequenceCounts });

    return {
        count,
        histogram,
    };
};

module.exports = dna;
exports.dna = dna;