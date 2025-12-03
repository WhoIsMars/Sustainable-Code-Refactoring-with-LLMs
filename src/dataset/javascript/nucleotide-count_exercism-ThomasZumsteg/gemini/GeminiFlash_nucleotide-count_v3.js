var dna = function(sequence) {
	/* Analyzes DNA sequences */
	dna.sequence = sequence || '';
	dna.nucleotides = "GTAC".split('');

	// Validates DNA sequence
	if (sequence && !/^[GTAC]+$/.test(sequence)) {
		throw new Error("Not a valid DNA sequence");
	}

	return {
		count: count,
		histogram: histogram,
	};
};

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
	const counts = {};
	for (const nucleotide of dna.nucleotides) {
		counts[nucleotide] = count(nucleotide);
	}
	return counts;
};

module.exports = dna;

exports.dna = dna;