var DnaTranscriber = function() {};

// Pre-computed mapping to avoid recreation on each call
var DNA_TO_RNA_MAP = {
	'G': 'C',
	'C': 'G',
	'T': 'A',
	'A': 'U'
};

DnaTranscriber.prototype.toRna = function(dna) {
	/* Translates dna to RNA */
	var result = '';
	for (var i = 0; i < dna.length; i++) {
		result += DNA_TO_RNA_MAP[dna[i]];
	}
	return result;
}

module.exports = DnaTranscriber;