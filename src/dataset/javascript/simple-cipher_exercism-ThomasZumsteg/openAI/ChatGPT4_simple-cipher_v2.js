class Cipher {
  constructor(key) {
    if (key !== undefined && !/^[a-z]+$/.test(key)) {
      throw Error("Bad key");
    }
    this.key = key || "aaaaaaaaaa";
    this.keyCharCodes = Array.from(this.key, (char) => char.charCodeAt(0));
  }

  static a_ascii = 'a'.charCodeAt(0);
  static z_ascii = 'z'.charCodeAt(0);
  static range = Cipher.z_ascii - Cipher.a_ascii + 1;

  encode(plainText) {
    return this._transform(plainText, (charCode, keyCode) => {
      return (charCode + keyCode - 2 * Cipher.a_ascii) % Cipher.range + Cipher.a_ascii;
    });
  }

  decode(cipherText) {
    return this._transform(cipherText, (charCode, keyCode) => {
      return (charCode - keyCode + Cipher.range) % Cipher.range + Cipher.a_ascii;
    });
  }

  _transform(text, transformFn) {
    return Array.from(text, (char, index) => {
      const charCode = char.charCodeAt(0);
      const keyCode = this.keyCharCodes[index % this.keyCharCodes.length];
      return String.fromCharCode(transformFn(charCode, keyCode));
    }).join('');
  }
}

module.exports = Cipher;