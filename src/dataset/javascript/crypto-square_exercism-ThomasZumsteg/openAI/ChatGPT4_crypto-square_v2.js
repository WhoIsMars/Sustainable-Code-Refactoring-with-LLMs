class Crypto {
	constructor(plainText) {
		this.plainText = plainText;
	}

	normalizePlaintext() {
		return this.plainText.toLowerCase().replace(/[^a-z0-9]/g, '');
	}

	size() {
		return Math.ceil(Math.sqrt(this.normalizePlaintext().length));
	}

	plaintextSegments() {
		const text = this.normalizePlaintext();
		const size = this.size();
		const segments = [];
		for (let i = 0; i < text.length; i += size) {
			segments.push(text.slice(i, i + size));
		}
		return segments;
	}

	ciphertext() {
		const segments = this.plaintextSegments();
		const size = this.size();
		const cipherArray = Array(size).fill('');
		for (const segment of segments) {
			for (let i = 0; i < segment.length; i++) {
				cipherArray[i] += segment[i];
			}
		}
		return cipherArray.join('');
	}

	normalizeCiphertext() {
		const cipherText = this.ciphertext();
		const size = this.size();
		const result = [];
		for (let i = 0; i < cipherText.length; i += size) {
			result.push(cipherText.slice(i, i + size));
		}
		return result.join(' ');
	}
}

module.exports = Crypto;