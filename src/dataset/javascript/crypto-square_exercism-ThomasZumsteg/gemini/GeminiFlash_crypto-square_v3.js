var Crypto = function(plainText) {
	this.plainText = plainText;
};

Crypto.prototype.normalizePlaintext = function() {
	let normalized = "";
	for (let i = 0; i < this.plainText.length; i++) {
		const char = this.plainText[i].toLowerCase();
		if (/[a-z0-9]/.test(char)) {
			normalized += char;
		}
	}
	return normalized;
};

Crypto.prototype.size = function() {
	const normalizedPlaintextLength = this.normalizePlaintext().length;
	return Math.ceil(Math.sqrt(normalizedPlaintextLength));
};

Crypto.prototype.plaintextSegments = function() {
	const normalizedText = this.normalizePlaintext();
	const segmentSize = this.size();
	const segments = [];
	for (let i = 0; i < normalizedText.length; i += segmentSize) {
		segments.push(normalizedText.substring(i, i + segmentSize));
	}
	return segments;
};

Crypto.prototype.ciphertext = function() {
	const textBlocks = this.plaintextSegments();
	const segmentSize = this.size();
	let cipherText = '';

	for (let i = 0; i < segmentSize; i++) {
		for (let j = 0; j < textBlocks.length; j++) {
			cipherText += textBlocks[j][i] || '';
		}
	}
	return cipherText;
};

Crypto.prototype.normalizeCiphertext = function() {
	const cipherText = this.ciphertext();
	const segmentSize = this.size();
	const segments = [];
	for (let i = 0; i < cipherText.length; i += segmentSize) {
		segments.push(cipherText.substring(i, i + segmentSize));
	}
	return segments.join(' ');
};

module.exports = Crypto;