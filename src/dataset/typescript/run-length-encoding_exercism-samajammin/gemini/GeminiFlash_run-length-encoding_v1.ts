export default class RunLengthEncoding {
  static encode(str: string): string {
    if (!str) return "";

    let res = '';
    let count = 1;
    let prevChar = str[0];

    for (let i = 1; i < str.length; i++) {
      const curChar = str[i];
      if (curChar === prevChar) {
        count++;
      } else {
        res += (count > 1 ? count : "") + prevChar;
        count = 1;
        prevChar = curChar;
      }
    }
    res += (count > 1 ? count : "") + prevChar;
    return res;
  }

  static decode(str: string): string {
    let res = '';
    let num = '';
    for (let i = 0; i < str.length; i++) {
      const char = str[i];
      if (char >= '0' && char <= '9') {
        num += char;
      } else {
        const repeatCount = num ? parseInt(num, 10) : 1;
        res += char.repeat(repeatCount);
        num = '';
      }
    }
    return res;
  }
}