class Cipher {
  constructor(key) {
    if (key !== undefined && !/^[a-z]+$/.test(key)) throw Error("Bad key");
    this.key = key || "aaaaaaaaaa";
    this.keyCharCodes = Array.from(this.key, char => char.charCodeAt(0));
  }

  static aAscii = 'a'.charCodeAt(0);
  static zAscii = 'z'.charCodeAt(0);
  static range = Cipher.zAscii - Cipher.aAscii + 1;

  encode(plainText) {
    return Array.from(plainText, (char, index) => {
      const c = (char.charCodeAt(0) + this.keyCharCodes[index % this.keyCharCodes.length] - 2 * Cipher.aAscii) % Cipher.range + Cipher.aAscii;
      return String.fromCharCode(c);
    }).join('');
  }

  decode(cipherText) {
    return Array.from(cipherText, (char, index) => {
      const c = (char.charCodeAt(0) - this.keyCharCodes[index % this.keyCharCodes.length] + Cipher.range) % Cipher.range + Cipher.aAscii;
      return String.fromCharCode(c);
    }).join('');
  }
}

module.exports = Cipher;