class Encoding {
  constructor(char, runLength) {
    this.char = char;
    this.runLength = runLength;
  }
}

const shrinkToEncodings = str => {
  if (!str.length) return [];
  
  const buf = [];
  let char = str[0];
  let runLength = 1;

  for (let i = 1; i < str.length; i++) {
    if (str[i] === char) {
      runLength++;
    } else {
      buf.push(new Encoding(char, runLength));
      char = str[i];
      runLength = 1;
    }
  }
  
  buf.push(new Encoding(char, runLength));
  return buf;
};

const expandToEncodings = str => {
  const encodings = [];
  let i = 0;
  
  while (i < str.length) {
    let runLength = '';
    
    // Extract digits
    while (i < str.length && str[i] >= '0' && str[i] <= '9') {
      runLength += str[i];
      i++;
    }
    
    // Get character
    const char = str[i];
    i++;
    
    encodings.push(new Encoding(char, runLength ? parseInt(runLength) : 1));
  }
  
  return encodings;
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