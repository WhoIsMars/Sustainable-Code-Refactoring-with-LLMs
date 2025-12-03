function translate(phrase) {
	/* Translates a phrase into piglatin */
	return phrase.split(' ').map(pigize).join(' ');
}

function pigize(word) {
	/* Turns a word into piglatin */
	// Check for consonant clusters ending with 'qu' first
	let i = 0;
	const len = word.length;
	
	if (len === 0) return word;
	
	// Find first vowel or 'y' (not at start)
	while (i < len) {
		const char = word[i];
		if (char === 'a' || char === 'e' || char === 'i' || char === 'o' || char === 'u' || (char === 'y' && i > 0)) {
			break;
		}
		// Handle 'qu' as a unit
		if (char === 'q' && i + 1 < len && word[i + 1] === 'u') {
			i += 2;
			break;
		}
		i++;
	}
	
	// If no vowel found or starts with vowel/y, return as is or handle edge case
	if (i === 0 || i >= len) return word;
	
	return word.slice(i) + word.slice(0, i) + "ay";
}

module.exports = { translate: translate }