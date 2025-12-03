export default class Anagram {
  private readonly anagramCharCount: Map<string, number>;

  constructor(anagram: string) {
    this.anagramCharCount = this.getCharCount(anagram.toLowerCase());
  }

  private getCharCount(word: string): Map<string, number> {
    const charCount = new Map<string, number>();
    for (const char of word) {
      charCount.set(char, (charCount.get(char) || 0) + 1);
    }
    return charCount;
  }

  private isAnagram(word: string): boolean {
    if (this.anagramCharCount.size !== word.length) {
      return false;
    }
    const wordCharCount = this.getCharCount(word);
    if (this.anagramCharCount.size !== wordCharCount.size) {
      return false;
    }
    for (const [char, count] of this.anagramCharCount) {
      if (wordCharCount.get(char) !== count) {
        return false;
      }
    }
    return true;
  }

  public matches(...words: string[]): string[] {
    return words.filter((word) => {
      const lowerWord = word.toLowerCase();
      return lowerWord !== [...this.anagramCharCount.keys()].join('') && this.isAnagram(lowerWord);
    });
  }
}