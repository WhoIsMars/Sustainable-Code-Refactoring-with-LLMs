var dna = function(sequence) {
	/* Analyzes DNA sequences */
	dna.sequence = sequence || '';
	dna.nucleotides = ['G', 'T', 'A', 'C'];

	// Validates DNA sequence
	if (sequence) {
		for (let i = 0; i < sequence.length; i++) {
			if (dna.nucleotides.indexOf(sequence[i]) === -1) {
				throw new Error("Not a valid DNA sequence");
			}
		}
	}
	
	return {
		count: count,
		histogram: histogram,
	};
};

function count(letter) {
	/* Counts the occurences of a single dna sequence */
	var count = 0;
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
	var sequence = dna.sequence;
	
	// Initialize counts
	for (let i = 0; i < dna.nucleotides.length; i++) {
		counts[dna.nucleotides[i]] = 0;
	}
	
	// Single pass through sequence
	for (let i = 0; i < sequence.length; i++) {
		counts[sequence[i]]++;
	}
	
	return counts;
};

module.exports = dna;

exports.dna = dna;