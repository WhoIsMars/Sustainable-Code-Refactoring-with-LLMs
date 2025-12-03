var Crypto = function(plainText) {
	/* Encrypts  message using the crypto-square algorithm */
	this.palinText = plainText;
	this._normalizedText = null;
	this._size = null;
	this._segments = null;
	this._ciphertext = null;
}

Crypto.prototype.normalizePlaintext = function() {
	/* Removes all characters except letters and numbers */
	if (this._normalizedText === null) {
		this._normalizedText = this.palinText
			.toLowerCase()
			.replace(/[^a-z0-9]/g, '');
	}
	return this._normalizedText;
};

Crypto.prototype.size = function() {
	/* Size of the square */
	if (this._size === null) {
		this._size = Math.ceil(Math.sqrt(this.normalizePlaintext().length));
	}
	return this._size;
};

Crypto.prototype.plaintextSegments = function() {
	/* Splits clear text into groups array*/
	if (this._segments === null) {
		var text = this.normalizePlaintext();
		var size = this.size();
		this._segments = [];
		for (var i = 0; i < text.length; i += size) {
			this._segments.push(text.slice(i, i + size));
		}
	}
	return this._segments;
};

Crypto.prototype.ciphertext = function() {
	/* Encrypts the text by selecting from column then row */
	if (this._ciphertext === null) {
		var text_blocks = this.plaintextSegments();
		var size = this.size();
		var cipher_chars = [];
		
		for (var i = 0; i < size; i++) {
			for (var j = 0; j < text_blocks.length; j++) {
				if (i < text_blocks[j].length) {
					cipher_chars.push(text_blocks[j][i]);
				}
			}
		}
		this._ciphertext = cipher_chars.join('');
	}
	return this._ciphertext;
};

Crypto.prototype.normalizeCiphertext = function() {
	/* Splits cipher text into groups */
	var cipher = this.ciphertext();
	var size = this.size();
	var result = [];
	
	for (var i = 0; i < cipher.length; i += size) {
		result.push(cipher.slice(i, i + size));
	}
	return result.join(' ');
};

module.exports = Crypto;