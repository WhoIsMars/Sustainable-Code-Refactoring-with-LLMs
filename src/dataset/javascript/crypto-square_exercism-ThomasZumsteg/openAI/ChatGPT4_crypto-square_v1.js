class Crypto {
	constructor(plainText) {
		this.plainText = plainText;
		this.normalizedText = this._normalizePlaintext();
		this.squareSize = Math.ceil(Math.sqrt(this.normalizedText.length));
		this.segments = this._plaintextSegments();
	}

	_normalizePlaintext() {
		return this.plainText.toLowerCase().replace(/[^a-z0-9]/g, '');
	}

	normalizePlaintext() {
		return this.normalizedText;
	}

	size() {
		return this.squareSize;
	}

	_plaintextSegments() {
		const size = this.squareSize;
		const segments = [];
		for (let i = 0; i < this.normalizedText.length; i += size) {
			segments.push(this.normalizedText.slice(i, i + size));
		}
		return segments;
	}

	plaintextSegments() {
		return this.segments;
	}

	ciphertext() {
		const size = this.squareSize;
		const segments = this.segments;
		let cipherText = '';
		for (let i = 0; i < size; i++) {
			for (const segment of segments) {
				if (segment[i]) cipherText += segment[i];
			}
		}
		return cipherText;
	}

	normalizeCiphertext() {
		const cipherText = this.ciphertext();
		const size = this.squareSize;
		const normalized = [];
		for (let i = 0; i < cipherText.length; i += size) {
			normalized.push(cipherText.slice(i, i + size));
		}
		return normalized.join(' ');
	}
}

module.exports = Crypto;