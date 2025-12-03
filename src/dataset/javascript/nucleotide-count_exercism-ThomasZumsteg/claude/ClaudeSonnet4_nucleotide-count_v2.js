var dna = function(sequence) {
	/* Analyzes DNA sequences */
	dna.sequence = sequence || '';
	dna.nucleotides = ['G', 'T', 'A', 'C'];

	// Validates DNA sequence
	if (sequence && !/^[GTAC]+$/.test(sequence))
		throw new Error("Not a valid DNA sequence");
	
	return {
		count: count,
		histogram: histogram,
	};
};

function count(letter) {
	/* Counts the occurences of a single dna sequence */
	var count = 0;
	var seq = dna.sequence;
	for (var i = 0; i < seq.length; i++) {
		if (seq[i] === letter) count++;
	}
	return count;
};

function histogram() {
	/* Counts the occurences of all dna sequences */
	var counts = {G: 0, T: 0, A: 0, C: 0};
	var seq = dna.sequence;
	for (var i = 0; i < seq.length; i++) {
		var nucleotide = seq[i];
		if (counts.hasOwnProperty(nucleotide)) {
			counts[nucleotide]++;
		}
	}
	return counts;
};

module.exports = dna;