class Cipher {
	constructor(key) {
		if (key !== undefined && !/^[a-z]+$/.test(key)) {
			throw Error("Bad key");
		}
		this.key = key || "aaaaaaaaaa";
		this.keyCharCodes = Array.from(this.key, char => char.charCodeAt(0));
	}

	static #aAscii = 'a'.charCodeAt(0);
	static #zAscii = 'z'.charCodeAt(0);
	static #alphabetSize = Cipher.#zAscii - Cipher.#aAscii + 1;

	#shiftChar(charCode, keyCode, isEncoding) {
		let shift = isEncoding ? keyCode : -keyCode;
		return String.fromCharCode(
			((charCode - Cipher.#aAscii + shift + Cipher.#alphabetSize) % Cipher.#alphabetSize) + Cipher.#aAscii
		);
	}

	encode(plainText) {
		return Array.from(plainText, (char, index) =>
			this.#shiftChar(char.charCodeAt(0), this.keyCharCodes[index % this.keyCharCodes.length], true)
		).join('');
	}

	decode(cipherText) {
		return Array.from(cipherText, (char, index) =>
			this.#shiftChar(char.charCodeAt(0), this.keyCharCodes[index % this.keyCharCodes.length], false)
		).join('');
	}
}

module.exports = Cipher;