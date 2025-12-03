function translate(phrase) {
	/* Translates a phrase into piglatin */
	const words = phrase.split(' ');
	const result = new Array(words.length);
	
	for (let i = 0; i < words.length; i++) {
		result[i] = pigize(words[i]);
	}
	
	return result.join(' ');
}

function pigize(word) {
	/* Turns a word into piglatin */
	// Handle consonant clusters starting with 'qu'
	let i = 0;
	if (word.length > 1 && word[0] !== 'a' && word[0] !== 'e' && word[0] !== 'i' && word[0] !== 'o' && word[0] !== 'u' && word[0] !== 'y') {
		while (i < word.length && word[i] !== 'a' && word[i] !== 'e' && word[i] !== 'i' && word[i] !== 'o' && word[i] !== 'u' && word[i] !== 'y') {
			i++;
			if (i >= 2 && word.substring(i-2, i) === 'qu') break;
		}
	}
	
	return i === 0 ? word : word.substring(i) + word.substring(0, i) + "ay";
}

module.exports = { translate: translate }