export default class {
  private readonly lowerCaseSentence: string;

  constructor(sentence: string) {
    this.lowerCaseSentence = sentence.toLowerCase();
  }

  isPangram(): boolean {
    if (this.lowerCaseSentence.length < 26) {
      return false;
    }

    const seen = new Set<string>();
    for (let i = 0; i < this.lowerCaseSentence.length; i++) {
      const char = this.lowerCaseSentence[i];
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