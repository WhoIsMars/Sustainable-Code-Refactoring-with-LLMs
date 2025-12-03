const abc = 'abcdefghijklmnopqrstuvwxyz';
const LENGTH = abc.length;

export class Cipher {
  constructor(key) {
    if (typeof key === 'undefined') {
      this.key = Array.from({ length: 100 }, () => abc.charAt(Math.floor(Math.random() * LENGTH))).join('');
    } else if (!/^[a-z]+$/.test(key)) {
      throw new Error('Bad key');
    } else {
      this.key = key;
    }
  }

  encode(str) {
    const key = this._extendKey(str.length);
    return Array.from(str, (char, i) => 
      abc[(abc.indexOf(char) + abc.indexOf(key[i])) % LENGTH]
    ).join('');
  }

  decode(str) {
    const key = this._extendKey(str.length);
    return Array.from(str, (char, i) => 
      abc[(abc.indexOf(char) - abc.indexOf(key[i]) + LENGTH) % LENGTH]
    ).join('');
  }

  _extendKey(length) {
    if (this.key.length >= length) return this.key;
    const repeatCount = Math.ceil(length / this.key.length);
    return this.key.repeat(repeatCount).slice(0, length);
  }
}