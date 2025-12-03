export default class RunLengthEncoding {
  static encode(str: string): string {
    if (!str) return '';
    let res = '';
    let curCount = 1;
    let prevChar = str[0];

    for (let i = 1; i < str.length; i++) {
      if (str[i] === prevChar) {
        curCount++;
      } else {
        res += (curCount > 1 ? curCount : '') + prevChar;
        prevChar = str[i];
        curCount = 1;
      }
    }
    return res + (curCount > 1 ? curCount : '') + prevChar;
  }

  static decode(str: string): string {
    let res = '';
    let num = 0;

    for (const char of str) {
      const digit = char.charCodeAt(0) - 48;
      if (digit >= 0 && digit <= 9) {
        num = num * 10 + digit;
      } else {
        res += char.repeat(num || 1);
        num = 0;
      }
    }
    return res;
  }
}