export default class RunLengthEncoding {
  static encode(str: string): string {
    if (!str) {
      return "";
    }

    let res = '';
    let count = 1;

    for (let i = 0; i < str.length; i++) {
      if (i + 1 < str.length && str[i] === str[i + 1]) {
        count++;
      } else {
        res += (count > 1 ? count : "") + str[i];
        count = 1;
      }
    }

    return res;
  }

  static decode(str: string): string {
    let res = '';
    let num = '';

    for (let i = 0; i < str.length; i++) {
      const char = str[i];
      if (/[0-9]/.test(char)) {
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