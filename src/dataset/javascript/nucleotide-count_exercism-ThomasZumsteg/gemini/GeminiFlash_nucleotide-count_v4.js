var dna = function(sequence) {
	var sprintf = require('util').format;
	dna.sequence = sequence || '';
	dna.nucleotides = "GTAC".split('');

	var validDNA = new RegExp(sprintf("^[%s]+$", dna.nucleotides.join('')));
	if (sequence && !validDNA.test(sequence)) {
		throw new Error("Not a valid DNA sequence");
	}

	return {
		count: count,
		histogram: histogram,
	};
};

function count(letter) {
	let count = 0;
	for (let i = 0; i < dna.sequence.length; i++) {
		if (dna.sequence[i] === letter) {
			count++;
		}
	}
	return count;
}

function histogram() {
	const counts = {};
	for (let i = 0; i < dna.nucleotides.length; i++) {
		counts[dna.nucleotides[i]] = count(dna.nucleotides[i]);
	}
	return counts;
}

module.exports = dna;

exports.dna = dna;