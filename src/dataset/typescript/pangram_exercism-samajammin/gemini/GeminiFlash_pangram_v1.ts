export default class Pangram {
  private readonly phrase: string;

  constructor(phrase: string) {
    this.phrase = phrase.toLowerCase();
  }

  isPangram(): boolean {
    const seen = new Array(26).fill(false);
    let count = 0;

    for (let i = 0; i < this.phrase.length; i++) {
      const charCode = this.phrase.charCodeAt(i);
      if (charCode >= 97 && charCode <= 122) {
        const index = charCode - 97;
        if (!seen[index]) {
          seen[index] = true;
          count++;
          if (count === 26) {
            return true;
          }
        }
      }
    }

    return false;
  }
}