var Cipher = function(key) {
    if (key !== undefined && !/^[a-z]+$/.test(key)) {
        throw new Error("Bad key");
    }
    this.key = key || "aaaaaaaaaa";
    this.keyLength = this.key.length;
};

var a_ascii = 'a'.charCodeAt(0);
var z_ascii = 'z'.charCodeAt(0);
var alphabetLength = z_ascii - a_ascii + 1;

Cipher.prototype.encode = function(plainText) {
    var key = this.key;
    var keyLength = this.keyLength;
    var result = "";
    for (var i = 0; i < plainText.length; i++) {
        var letter = plainText[i];
        var keyChar = key[i % keyLength];
        var c = letter.charCodeAt(0) + keyChar.charCodeAt(0);
        c -= 2 * a_ascii;
        c %= alphabetLength;
        c += a_ascii;
        result += String.fromCharCode(c);
    }
    return result;
};

Cipher.prototype.decode = function(cipherText) {
    var key = this.key;
    var keyLength = this.keyLength;
    var result = "";
    for (var i = 0; i < cipherText.length; i++) {
        var letter = cipherText[i];
        var keyChar = key[i % keyLength];
        var c = letter.charCodeAt(0) - keyChar.charCodeAt(0);
        c %= alphabetLength;
        c += a_ascii;
        result += String.fromCharCode(c);
    }
    return result;
};

module.exports = Cipher;