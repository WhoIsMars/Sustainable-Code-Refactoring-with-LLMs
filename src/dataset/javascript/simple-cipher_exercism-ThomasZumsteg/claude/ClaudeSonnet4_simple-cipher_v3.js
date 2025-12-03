const Cipher = function(key) {
	if (key !== undefined && !key.match(/^[a-z]+$/)) {
		throw new Error("Bad key");
	}
	this.key = key || "aaaaaaaaaa";
	this.keyLength = this.key.length;
	this.keyCharCodes = [];
	for (let i = 0; i < this.keyLength; i++) {
		this.keyCharCodes[i] = this.key.charCodeAt(i);
	}
};

const A_ASCII = 97;
const ALPHABET_SIZE = 26;

Cipher.prototype.encode = function(plainText) {
	let result = '';
	const textLength = plainText.length;
	
	for (let i = 0; i < textLength; i++) {
		const letterCode = plainText.charCodeAt(i);
		const keyCode = this.keyCharCodes[i % this.keyLength];
		let c = letterCode + keyCode - 2 * A_ASCII;
		c = ((c % ALPHABET_SIZE) + ALPHABET_SIZE) % ALPHABET_SIZE + A_ASCII;
		result += String.fromCharCode(c);
	}
	
	return result;
};

Cipher.prototype.decode = function(cipherText) {
	let result = '';
	const textLength = cipherText.length;
	
	for (let i = 0; i < textLength; i++) {
		const letterCode = cipherText.charCodeAt(i);
		const keyCode = this.keyCharCodes[i % this.keyLength];
		let c = letterCode - keyCode;
		c = ((c % ALPHABET_SIZE) + ALPHABET_SIZE) % ALPHABET_SIZE + A_ASCII;
		result += String.fromCharCode(c);
	}
	
	return result;
};

module.exports = Cipher;