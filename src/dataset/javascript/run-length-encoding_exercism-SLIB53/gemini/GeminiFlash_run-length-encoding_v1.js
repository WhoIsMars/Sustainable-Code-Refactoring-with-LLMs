class Encoding {
  constructor(char, runLength) {
    this.char = char;
    this.runLength = runLength;
  }
}

const shrinkToEncodings = str => {
  const buf = [];
  if (!str) return buf;

  let char = str[0];
  let runLength = 1;

  for (let i = 1; i < str.length; i++) {
    const cur = str[i];
    if (cur !== char) {
      buf.push(new Encoding(char, runLength));
      char = cur;
      runLength = 1;
    } else {
      runLength++;
    }
  }

  buf.push(new Encoding(char, runLength));
  return buf;
};

const expandToEncodings = str => {
  const buf = [];
  if (!str) return buf;

  let i = 0;
  while (i < str.length) {
    let runLengthStr = "";
    while (i < str.length && /\d/.test(str[i])) {
      runLengthStr += str[i];
      i++;
    }

    const char = str[i];
    i++;

    const runLength = runLengthStr ? parseInt(runLengthStr, 10) : 1;
    buf.push(new Encoding(char, runLength));
  }

  return buf;
};

const toEncodedString = encodings => {
  let result = "";
  for (const enc of encodings) {
    result += (enc.runLength > 1 ? enc.runLength : "") + enc.char;
  }
  return result;
};

const toDecodedString = encodings => {
  let result = "";
  for (const enc of encodings) {
    result += enc.char.repeat(enc.runLength);
  }
  return result;
};

export const encode = string => toEncodedString(shrinkToEncodings(string));

export const decode = string => toDecodedString(expandToEncodings(string));