const abc = 'abcdefghijklmnopqrstuvwxyz';
const def = 'defghijklmnopqrstuvwxyzabc';
const LENGTH = abc.length;

export class Cipher{
  constructor(key){
    if(typeof key === 'undefined'){
      let randomKey = '';
      for (let i = 0; i < 100; i++) {
        randomKey += abc[Math.floor(Math.random() * LENGTH)];
      }
      this.key = randomKey;
    } else if(!/^[a-z]+$/.test(key)){
      throw new Error('Bad key');
    } else {
      this.key = key;
    }
  }

  toMatch(regex){
    return regex.test(this.key);
  }
  
  encode(str){
    const keyLength = this.key.length;
    const strLength = str.length;
    let result = '';

    let extendedKey = this.key;
    if (strLength > keyLength) {
        const numRepeats = Math.ceil(strLength / keyLength);
        extendedKey = this.key.repeat(numRepeats);
    }

    for(let i = 0; i < strLength; i++){
      result += def[(abc.indexOf(str[i]) + abc.indexOf(extendedKey[i])) % LENGTH];
    }
    return result;
  }

  decode(str){
    const keyLength = this.key.length;
    const strLength = str.length;
    let result = '';

    let extendedKey = this.key;
    if (strLength > keyLength) {
        const numRepeats = Math.ceil(strLength / keyLength);
        extendedKey = this.key.repeat(numRepeats);
    }

    for(let i = 0; i < strLength; i++){
      let tempValue = (def.indexOf(str[i]) - abc.indexOf(extendedKey[i]));
      if(tempValue < 0){
        tempValue += LENGTH;
      }
      result += abc[tempValue % LENGTH];
    }
    return result;
  }
}