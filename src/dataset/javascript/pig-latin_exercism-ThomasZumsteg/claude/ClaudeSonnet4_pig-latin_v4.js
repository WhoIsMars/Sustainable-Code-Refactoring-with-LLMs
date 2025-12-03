function translate(phrase) {
	const words = phrase.split(' ');
	const result = new Array(words.length);
	
	for (let i = 0; i < words.length; i++) {
		result[i] = pigize(words[i]);
	}
	
	return result.join(' ');
}

function pigize(word) {
	const len = word.length;
	if (len === 0) return word;
	
	let consonantEnd = 0;
	
	if (word.charCodeAt(0) === 113 && len > 1 && word.charCodeAt(1) === 117) {
		consonantEnd = 2;
	} else {
		const firstChar = word.charCodeAt(0);
		if (firstChar === 97 || firstChar === 101 || firstChar === 105 || 
			firstChar === 111 || firstChar === 117 || firstChar === 121) {
			consonantEnd = 0;
		} else {
			for (let i = 1; i < len; i++) {
				const char = word.charCodeAt(i);
				if (char === 97 || char === 101 || char === 105 || 
					char === 111 || char === 117 || char === 121) {
					consonantEnd = i;
					break;
				}
				if (char === 113 && i + 1 < len && word.charCodeAt(i + 1) === 117) {
					consonantEnd = i + 2;
					break;
				}
			}
		}
	}
	
	if (consonantEnd === 0) {
		return word + 'ay';
	}
	
	return word.slice(consonantEnd) + word.slice(0, consonantEnd) + 'ay';
}

module.exports = { translate: translate };