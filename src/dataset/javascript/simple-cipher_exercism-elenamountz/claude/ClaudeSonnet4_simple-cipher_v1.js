const abc = 'abcdefghijklmnopqrstuvwxyz';
const def = 'defghijklmnopqrstuvwxyzabc';
const LENGTH = 26;

// Pre-compute lookup tables for O(1) character index access
const abcLookup = new Map();
const defLookup = new Map();
for (let i = 0; i < LENGTH; i++) {
  abcLookup.set(abc[i], i);
  defLookup.set(def[i], i);
}

export class Cipher {
  constructor(key) {
    if (typeof key === 'undefined') {
      const chars = new Array(100);
      for (let i = 0; i < 100; i++) {
        chars[i] = abc[Math.floor(Math.random() * LENGTH)];
      }
      this.key = chars.join('');
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
    let workingKey = this.key;
    if (strLen > keyLen) {
      const repeatCount = Math.ceil(strLen / keyLen);
      workingKey = this.key.repeat(repeatCount);
    }
    
    const result = new Array(strLen);
    for (let i = 0; i < strLen; i++) {
      const strIndex = abcLookup.get(str[i]);
      const keyIndex = defLookup.get(workingKey[i]);
      result[i] = def[(strIndex + keyIndex) % LENGTH];
    }
    return result.join('');
  }

  decode(str) {
    const strLen = str.length;
    const result = new Array(strLen);
    
    for (let i = 0; i < strLen; i++) {
      const strIndex = defLookup.get(str[i]);
      const keyIndex = abcLookup.get(this.key[i]);
      let tempValue = strIndex - keyIndex;
      if (tempValue < 0) {
        tempValue += LENGTH;
      }
      result[i] = def[tempValue];
    }
    return result.join('');
  }
}