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
  return str.match(/\d*\D/g).map(encStr => {
    const match = encStr.match(/(\d*)(\D)/);
    const runLength = match[1] ? Number(match[1]) : 1;
    return new Encoding(match[2], runLength);
  });
};

const toEncodedString = encodings => 
  encodings.map(enc => (enc.runLength > 1 ? enc.runLength : "") + enc.char).join("");

const toDecodedString = encodings => 
  encodings.map(enc => enc.char.repeat(enc.runLength)).join("");

export const encode = string => toEncodedString(shrinkToEncodings(string));

export const decode = string => toDecodedString(expandToEncodings(string));