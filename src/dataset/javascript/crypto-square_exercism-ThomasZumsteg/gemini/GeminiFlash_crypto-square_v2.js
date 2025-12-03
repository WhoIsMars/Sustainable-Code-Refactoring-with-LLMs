var Crypto = function(plainText) {
    this.plainText = plainText;
};

Crypto.prototype.normalizePlaintext = function() {
    const text = this.plainText.toLowerCase();
    let result = '';
    for (let i = 0; i < text.length; i++) {
        const char = text[i];
        if (/[a-z0-9]/.test(char)) {
            result += char;
        }
    }
    return result;
};

Crypto.prototype.size = function() {
    const normalized = this.normalizePlaintext();
    return Math.ceil(Math.sqrt(normalized.length));
};

Crypto.prototype.plaintextSegments = function() {
    const normalized = this.normalizePlaintext();
    const size = this.size();
    const segments = [];
    for (let i = 0; i < normalized.length; i += size) {
        segments.push(normalized.substring(i, i + size));
    }
    return segments;
};

Crypto.prototype.ciphertext = function() {
    const text_blocks = this.plaintextSegments();
    const size = this.size();
    let cipher_text = '';
    for (let i = 0; i < size; i++) {
        for (let j = 0; j < text_blocks.length; j++) {
            cipher_text += text_blocks[j][i] || '';
        }
    }
    return cipher_text;
};

Crypto.prototype.normalizeCiphertext = function() {
    const cipher = this.ciphertext();
    const size = this.size();
    const result = [];
    for (let i = 0; i < cipher.length; i += size) {
        result.push(cipher.substring(i, i + size));
    }
    return result.join(' ');
};

module.exports = Crypto;