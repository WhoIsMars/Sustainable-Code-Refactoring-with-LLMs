export default class Pangram {
  readonly phrase: string;

  constructor(phrase: string) {
    this.phrase = phrase.toLowerCase();
  }

  isPangram(): boolean {
    let alphabetMask = 0;
    for (const char of this.phrase) {
      const charCode = char.charCodeAt(0) - 97;
      if (charCode >= 0 && charCode < 26) {
        alphabetMask |= 1 << charCode;
        if (alphabetMask === (1 << 26) - 1) return true;
      }
    }
    return false;
  }
}