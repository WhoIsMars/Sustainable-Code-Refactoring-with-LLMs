const abc = 'abcdefghijklmnopqrstuvwxyz';
const def = 'defghijklmnopqrstuvwxyzabc';
const LENGTH = 26;

// Pre-compute lookup tables for O(1) character to index mapping
const abcMap = new Map();
const defMap = new Map();
for (let i = 0; i < LENGTH; i++) {
  abcMap.set(abc[i], i);
  defMap.set(def[i], i);
}

export class Cipher {
  constructor(key) {
    if (typeof key === 'undefined') {
      this.key = Array.from({length: 100}, () => abc[Math.floor(Math.random() * LENGTH)]).join('');
    } else if (!/^[a-z]+$/.test(key)) {
      throw new Error('Bad key');
    } else {
      this.key = key;
    }
  }

  toMatch(regex) {
    return regex.test(this.key);
  }
  
  encode(str) {
    const strLen = str.length;
    const keyLen = this.key.length;
    
    // Extend key only if necessary
    if (strLen > keyLen) {
      const repeats = Math.ceil(strLen / keyLen);
      this.key = this.key.repeat(repeats);
    }
    
    let result = '';
    for (let i = 0; i < strLen; i++) {
      const strIndex = abcMap.get(str[i]);
      const keyIndex = defMap.get(this.key[i]);
      result += def[(strIndex + keyIndex) % LENGTH];
    }
    return result;
  }

  decode(str) {
    let result = '';
    for (let i = 0; i < str.length; i++) {
      const strIndex = defMap.get(str[i]);
      const keyIndex = abcMap.get(this.key[i]);
      let tempValue = strIndex - keyIndex;
      if (tempValue < 0) {
        tempValue += LENGTH;
      }
      result += def[tempValue];
    }
    return result;
  }
}