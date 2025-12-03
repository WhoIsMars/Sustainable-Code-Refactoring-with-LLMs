var dna = function(sequence) {
	dna.sequence = sequence || '';
	dna.nucleotides = ['G', 'T', 'A', 'C'];

	if (sequence && !/^[GTAC]+$/.test(sequence)) {
		throw new Error("Not a valid DNA sequence");
	}

	return {
		count: count,
		histogram: histogram,
	};
};

function count(letter) {
	var count = 0;
	var seq = dna.sequence;
	for (var i = 0; i < seq.length; i++) {
		if (seq[i] === letter) count++;
	}
	return count;
}

function histogram() {
	var counts = { G: 0, T: 0, A: 0, C: 0 };
	var seq = dna.sequence;
	for (var i = 0; i < seq.length; i++) {
		var nucleotide = seq[i];
		if (counts.hasOwnProperty(nucleotide)) {
			counts[nucleotide]++;
		}
	}
	return counts;
}

module.exports = dna;

exports.dna = dna;