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
    const keyLength = this.key.length;
    const strLength = str.length;
    let result = '';

    for (let i = 0; i < strLength; i++) {
      const keyChar = this.key[i % keyLength];
      const strChar = str[i];
      const abcIndex = abc.indexOf(strChar);
      const defIndex = def.indexOf(keyChar);

      result += def.charAt((abcIndex + defIndex) % LENGTH);
    }

    return result;
  }


  decode(str) {
    const keyLength = this.key.length;
    const strLength = str.length;
    let result = '';

    for (let i = 0; i < strLength; i++) {
      const keyChar = this.key[i % keyLength];
      const strChar = str[i];
      const defIndexStr = def.indexOf(strChar);
      const abcIndexKey = abc.indexOf(keyChar);

      let tempValue = defIndexStr - abcIndexKey;
      if (tempValue < 0) {
        tempValue += LENGTH;
      }
      result += def.charAt(tempValue % LENGTH);
    }

    return result;
  }
}