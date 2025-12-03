const abc = 'abcdefghijklmnopqrstuvwxyz';
const def = 'defghijklmnopqrstuvwxyzabc';
const LENGTH = 26;

const abcMap = new Map();
const defMap = new Map();
for (let i = 0; i < LENGTH; i++) {
  abcMap.set(abc[i], i);
  defMap.set(def[i], i);
}

export class Cipher {
  constructor(key) {
    if (typeof key === 'undefined') {
      this.key = this._generateRandomKey();
    } else if (!/^[a-z]+$/.test(key)) {
      throw new Error('Bad key');
    } else {
      this.key = key;
    }
  }

  _generateRandomKey() {
    let result = '';
    for (let i = 0; i < 100; i++) {
      result += abc[Math.floor(Math.random() * LENGTH)];
    }
    return result;
  }

  toMatch(regex) {
    return regex.test(this.key);
  }
  
  encode(str) {
    const keyLength = this.key.length;
    let result = '';
    
    for (let i = 0; i < str.length; i++) {
      const keyIndex = i % keyLength;
      const charIndex = abcMap.get(str[i]);
      const keyCharIndex = defMap.get(this.key[keyIndex]);
      result += def[(charIndex + keyCharIndex) % LENGTH];
    }
    return result;
  }

  decode(str) {
    const keyLength = this.key.length;
    let result = '';
    
    for (let i = 0; i < str.length; i++) {
      const keyIndex = i % keyLength;
      const charIndex = defMap.get(str[i]);
      const keyCharIndex = abcMap.get(this.key[keyIndex]);
      let tempValue = charIndex - keyCharIndex;
      if (tempValue < 0) {
        tempValue += LENGTH;
      }
      result += def[tempValue];
    }
    return result;
  }
}