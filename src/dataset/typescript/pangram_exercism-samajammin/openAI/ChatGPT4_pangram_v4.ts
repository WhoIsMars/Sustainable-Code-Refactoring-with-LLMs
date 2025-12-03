export default class Pangram {
  readonly phrase: string;

  constructor(phrase: string) {
    this.phrase = phrase.toLowerCase();
  }

  isPangram(): boolean {
    let alphabetMask = 0;
    for (const char of this.phrase) {
      const code = char.charCodeAt(0) - 97;
      if (code >= 0 && code < 26) {
        alphabetMask |= 1 << code;
        if (alphabetMask === 0b11111111111111111111111111) return true;
      }
    }
    return false;
  }
}