export default class {
  constructor(private sentence: string) {}

  isPangram(): boolean {
    const seen = new Set<string>();
    
    for (let i = 0; i < this.sentence.length; i++) {
      const char = this.sentence[i].toLowerCase();
      if (char >= 'a' && char <= 'z') {
        seen.add(char);
        if (seen.size === 26) {
          return true;
        }
      }
    }
    
    return false;
  }
}