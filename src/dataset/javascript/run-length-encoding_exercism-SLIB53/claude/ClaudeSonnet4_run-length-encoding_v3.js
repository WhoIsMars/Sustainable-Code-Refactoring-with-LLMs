class Encoding {
  constructor(char, runLength) {
    this.char = char;
    this.runLength = runLength;
  }
}

const shrinkToEncodings = str => {
  if (!str) return [];
  
  const result = [];
  let currentChar = str[0];
  let runLength = 1;
  
  for (let i = 1; i < str.length; i++) {
    if (str[i] === currentChar) {
      runLength++;
    } else {
      result.push(new Encoding(currentChar, runLength));
      currentChar = str[i];
      runLength = 1;
    }
  }
  
  result.push(new Encoding(currentChar, runLength));
  return result;
};

const expandToEncodings = str => {
  if (!str) return [];
  
  const result = [];
  let i = 0;
  
  while (i < str.length) {
    let runLength = 1;
    let numStr = '';
    
    while (i < str.length && str[i] >= '0' && str[i] <= '9') {
      numStr += str[i];
      i++;
    }
    
    if (numStr) {
      runLength = parseInt(numStr, 10);
    }
    
    if (i < str.length) {
      result.push(new Encoding(str[i], runLength));
      i++;
    }
  }
  
  return result;
};

const toEncodedString = encodings => {
  let result = '';
  for (const enc of encodings) {
    result += (enc.runLength > 1 ? enc.runLength : '') + enc.char;
  }
  return result;
};

const toDecodedString = encodings => {
  let result = '';
  for (const enc of encodings) {
    result += enc.char.repeat(enc.runLength);
  }
  return result;
};

export const encode = string => toEncodedString(shrinkToEncodings(string));

export const decode = string => toDecodedString(expandToEncodings(string));