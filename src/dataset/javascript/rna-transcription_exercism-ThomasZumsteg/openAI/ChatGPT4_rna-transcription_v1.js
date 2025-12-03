var DnaTranscriber = function() {};

DnaTranscriber.prototype.toRna = function(dna) {
	/* Translates dna to RNA */
	const dnaToRna = { G: 'C', C: 'G', T: 'A', A: 'U' };
	return [...dna].map(e => dnaToRna[e]).join('');
};

module.exports = DnaTranscriber;