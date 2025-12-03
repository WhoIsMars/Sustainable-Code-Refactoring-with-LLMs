export default class Pangram {
  readonly phrase: string;

  constructor(phrase: string) {
    this.phrase = phrase.toLowerCase();
  }

  isPangram() {
    let alphabetCount = 0;
    const seen = new Set<string>();

    for (const char of this.phrase) {
      if (char >= 'a' && char <= 'z' && !seen.has(char)) {
        seen.add(char);
        alphabetCount++;
        if (alphabetCount === 26) return true;
      }
    }

    return false;
  }
}