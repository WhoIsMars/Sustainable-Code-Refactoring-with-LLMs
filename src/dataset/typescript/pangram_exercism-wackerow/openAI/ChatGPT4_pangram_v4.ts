export default class {
  constructor(private sentence: string) {}

  isPangram(): boolean {
    const seen = new Set<string>();
    for (const char of this.sentence.toLowerCase()) {
      if (char >= 'a' && char <= 'z') {
        seen.add(char);
        if (seen.size === 26) return true;
      }
    }
    return false;
  }
}