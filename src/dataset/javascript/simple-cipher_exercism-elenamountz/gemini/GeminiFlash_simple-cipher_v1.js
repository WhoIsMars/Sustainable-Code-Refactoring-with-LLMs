const abc = 'abcdefghijklmnopqrstuvwxyz';
const def = 'defghijklmnopqrstuvwxyzabc';
const LENGTH = abc.length;

export class Cipher {
  constructor(key) {
    if (typeof key === 'undefined') {
      this.key = this.generateRandomKey(100);
    } else if (!/^[a-z]+$/.test(key)) {
      throw new Error('Bad key');
    } else {
      this.key = key;
    }
  }

  generateRandomKey(length) {
    let result = '';
    for (let i = 0; i < length; i++) {
      result += abc.charAt(Math.floor(Math.random() * LENGTH));
    }
    return result;
  }

  encode(str) {
    let encoded = '';
    const keyLength = this.key.length;
    for (let i = 0; i < str.length; i++) {
      const charIndex = abc.indexOf(str[i]);
      const keyCharIndex = abc.indexOf(this.key[i % keyLength]);
      encoded += def.charAt((charIndex + keyCharIndex) % LENGTH);
    }
    return encoded;
  }

  decode(str) {
    let decoded = '';
    const keyLength = this.key.length;
    for (let i = 0; i < str.length; i++) {
      let tempValue = def.indexOf(str[i]) - abc.indexOf(this.key[i % keyLength]);
      if (tempValue < 0) {
        tempValue += LENGTH;
      }
      decoded += abc.charAt(tempValue % LENGTH);
    }
    return decoded;
  }
}