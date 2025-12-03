function translate(phrase) {
	return phrase.split(' ').map(pigize).join(' ');
}

function pigize(word) {
	const regex = /^([^aeioy]*qu)(.*)$|^(.*?)([aeiouy].*)$/;
	const matches = word.match(regex);
	return matches ? (matches[2] || matches[4]) + (matches[1] || matches[3]) + "ay" : word;
}

module.exports = { translate };