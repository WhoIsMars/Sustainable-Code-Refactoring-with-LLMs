var dna = function(sequence) {
	/* Analyzes DNA sequences */
	dna.sequence = sequence || '';
	dna.nucleotides = "GTAC";

	// Validates DNA sequence
	if (sequence && !isValidDNA(sequence, dna.nucleotides))
		throw new Error("Not a valid DNA sequence");

	return {
		count: count,
		histogram: histogram,
	};
};

function isValidDNA(sequence, nucleotides) {
    for (let i = 0; i < sequence.length; i++) {
        if (nucleotides.indexOf(sequence[i]) === -1) {
            return false;
        }
    }
    return true;
}

function count(letter) {
	/* Counts the occurences of a single dna sequence */
	let count = 0;
    for (let i = 0; i < dna.sequence.length; i++) {
        if (dna.sequence[i] === letter) {
            count++;
        }
    }
    return count;
};

function histogram() {
	/* Counts the occurences of all dna sequences */
	var counts = {};
	for (let i = 0; i < dna.nucleotides.length; i++) {
        const nucleotide = dna.nucleotides[i];
        counts[nucleotide] = count(nucleotide);
    }
	return counts;
};

module.exports = dna;

exports.dna = dna;