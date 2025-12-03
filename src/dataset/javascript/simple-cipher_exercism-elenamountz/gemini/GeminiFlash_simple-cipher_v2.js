const abc = 'abcdefghijklmnopqrstuvwxyz';
const def = 'defghijklmnopqrstuvwxyzabc';
const LENGTH = abc.length;

export class Cipher {
  constructor(key) {
    if (typeof key === 'undefined') {
      this.key = Array.from({ length: 100 }, () => abc[Math.floor(Math.random() * LENGTH)]).join('');
    } else if (!/^[a-z]+$/.test(key)) {
      throw new Error('Bad key');
    } else {
      this.key = key;
    }
    this.keyLength = this.key.length;
  }

  encode(str) {
    let result = '';
    const key = this.key;
    const keyLength = this.keyLength;
    const strLength = str.length;

    for (let i = 0; i < strLength; i++) {
      const keyChar = key[i % keyLength];
      const strChar = str[i];
      const abcIndex = abc.indexOf(strChar);
      const defIndex = def.indexOf(keyChar);

      result += def[ (abcIndex + defIndex) % LENGTH];
    }

    return result;
  }

  decode(str) {
    let result = '';
    const key = this.key;
    const keyLength = this.keyLength;
    const strLength = str.length;

    for (let i = 0; i < strLength; i++) {
      const keyChar = key[i % keyLength];
      const strChar = str[i];
      const defIndex = def.indexOf(strChar);
      const abcIndex = abc.indexOf(keyChar);

      let tempValue = defIndex - abcIndex;
      if (tempValue < 0) {
        tempValue += LENGTH;
      }
      result += abc[tempValue % LENGTH];
    }
    return result;
  }
}