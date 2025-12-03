var Crypto = function(plainText) {
	/* Encrypts  message using the crypto-square algorithm */
	this.plainText = plainText;
	this.normalizedText = this.normalizePlaintext();
	this.squareSize = this.size();
};

Crypto.prototype.normalizePlaintext = function() {
	/* Removes all characters except letters and numbers */
	let normalized = "";
	const text = this.plainText.toLowerCase();
	for (let i = 0; i < text.length; i++) {
		const char = text[i];
		if (/[a-z0-9]/.test(char)) {
			normalized += char;
		}
	}
	return normalized;
};

Crypto.prototype.size = function() {
	/* Size of the square */
	return Math.ceil(Math.sqrt(this.normalizedText.length));
};

Crypto.prototype.plaintextSegments = function() {
	/* Splits clear text into groups array*/
	const textSize = this.squareSize;
	const text = this.normalizedText;
	const segments = [];
	for (let i = 0; i < text.length; i += textSize) {
		segments.push(text.substring(i, i + textSize));
	}
	return segments;
};

Crypto.prototype.ciphertext = function() {
	/* Encrypts the text by selecting from column then row */
	const text_blocks = this.plaintextSegments();
	let cipher_text = '';
	const size = this.squareSize;
	for (let i = 0; i < size; i++) {
		for (let j = 0; j < text_blocks.length; j++) {
			cipher_text += text_blocks[j].charAt(i);
		}
	}
	return cipher_text;
};

Crypto.prototype.normalizeCiphertext = function() {
	/* Splits cipher text into groups */
	const cipher = this.ciphertext();
	const size = this.squareSize;
	const result = [];
	for (let i = 0; i < cipher.length; i += size) {
		result.push(cipher.substring(i, i + size));
	}
	return result.join(' ');
};

module.exports = Crypto;