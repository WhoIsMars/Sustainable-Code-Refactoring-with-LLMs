class Encoding {
  constructor(char, runLength) {
    this.char = char;
    this.runLength = runLength;
  }
}

const shrinkToEncodings = str => {
  if (!str) return [];
  const buf = [];
  let char = str[0], runLength = 1;

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
  const matchEncodingRegex = /(\d+)?(\D)/g;
  const buf = [];
  let match;

  while ((match = matchEncodingRegex.exec(str)) !== null) {
    const runLength = match[1] ? parseInt(match[1], 10) : 1;
    buf.push(new Encoding(match[2], runLength));
  }

  return buf;
};

const toEncodedString = encodings => 
  encodings.map(enc => (enc.runLength > 1 ? enc.runLength : "") + enc.char).join("");

const toDecodedString = encodings => 
  encodings.map(enc => enc.char.repeat(enc.runLength)).join("");

export const encode = string => toEncodedString(shrinkToEncodings(string));

export const decode = string => toDecodedString(expandToEncodings(string));