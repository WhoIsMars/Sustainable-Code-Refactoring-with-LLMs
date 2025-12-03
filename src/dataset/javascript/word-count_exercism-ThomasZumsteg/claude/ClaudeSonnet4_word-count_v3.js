var Words = function() {}

Words.prototype.count = function( wordString ) {
	var wordCount = {};
	var trimmed = wordString.trim();
	
	if (!trimmed) return wordCount;
	
	var words = trimmed.split(/\s+/);
	var length = words.length;
	
	for (var i = 0; i < length; i++) {
		var word = words[i];
		wordCount[word] = (wordCount[word] || 0) + 1;
	}
	
	return wordCount;
};

module.exports = Words;