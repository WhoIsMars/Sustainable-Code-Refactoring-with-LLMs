var Cipher = function(key) {
	if( key !== undefined && !key.match(/^[a-z]+$/) )
		throw Error("Bad key");
	this.key = key || "aaaaaaaaaa";
	this.keyLength = this.key.length;
	this.keyOffsets = new Array(this.keyLength);
	for (var i = 0; i < this.keyLength; i++) {
		this.keyOffsets[i] = this.key.charCodeAt(i) - 97;
	}
}

var a_ascii = 97;
var alphabet_size = 26;

Cipher.prototype.encode = function(plainText) {
	var result = '';
	var textLength = plainText.length;
	for (var i = 0; i < textLength; i++) {
		var charCode = plainText.charCodeAt(i);
		var keyOffset = this.keyOffsets[i % this.keyLength];
		var shifted = ((charCode - a_ascii + keyOffset) % alphabet_size) + a_ascii;
		result += String.fromCharCode(shifted);
	}
	return result;
};

Cipher.prototype.decode = function(cipherText) {
	var result = '';
	var textLength = cipherText.length;
	for (var i = 0; i < textLength; i++) {
		var charCode = cipherText.charCodeAt(i);
		var keyOffset = this.keyOffsets[i % this.keyLength];
		var shifted = ((charCode - a_ascii - keyOffset + alphabet_size) % alphabet_size) + a_ascii;
		result += String.fromCharCode(shifted);
	}
	return result;
};

module.exports = Cipher;