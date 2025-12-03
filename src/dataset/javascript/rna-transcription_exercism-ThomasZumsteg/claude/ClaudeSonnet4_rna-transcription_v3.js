var DnaTranscriber = function() {};

DnaTranscriber.prototype.toRna = function(dna) {
	var dnaToRna = {
		'G': 'C',
		'C': 'G',
		'T': 'A',
		'A': 'U'
	};
	
	var result = '';
	for (var i = 0; i < dna.length; i++) {
		result += dnaToRna[dna[i]];
	}
	return result;
};

function makeHash(keys, values) {
	var hash = {};
	for (var i = 0; i < keys.length; i++) {
		hash[keys[i]] = values[i];
	}
	return hash;
}

module.exports = DnaTranscriber;