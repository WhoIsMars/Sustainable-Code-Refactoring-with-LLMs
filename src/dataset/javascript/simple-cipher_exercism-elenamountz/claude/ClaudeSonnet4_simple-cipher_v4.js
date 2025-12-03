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
      const keyChars = new Array(100);
      for (let i = 0; i < 100; i++) {
        keyChars[i] = abc[Math.floor(Math.random() * LENGTH)];
      }
      this.key = keyChars.join('');
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
    
    if (strLen > keyLen) {
      const repeats = Math.ceil(strLen / keyLen);
      this.key = this.key.repeat(repeats);
    }
    
    const result = new Array(strLen);
    for (let i = 0; i < strLen; i++) {
      const strIndex = abcMap.get(str[i]);
      const keyIndex = defMap.get(this.key[i]);
      result[i] = def[(strIndex + keyIndex) % LENGTH];
    }
    return result.join('');
  }

  decode(str) {
    const strLen = str.length;
    const result = new Array(strLen);
    
    for (let i = 0; i < strLen; i++) {
      const strIndex = defMap.get(str[i]);
      const keyIndex = abcMap.get(this.key[i]);
      let tempValue = strIndex - keyIndex;
      if (tempValue < 0) {
        tempValue += LENGTH;
      }
      result[i] = def[tempValue];
    }
    return result.join('');
  }
}