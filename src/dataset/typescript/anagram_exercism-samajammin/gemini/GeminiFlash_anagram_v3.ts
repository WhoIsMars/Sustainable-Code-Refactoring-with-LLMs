export default class Anagram {
  private readonly anagram: string;
  private readonly sortedAnagram: string;

  constructor(anagram: string) {
    this.anagram = anagram.toLowerCase();
    this.sortedAnagram = [...this.anagram].sort().join('');
  }

  private isAnagram(word: string): boolean {
    const lowerCaseWord = word.toLowerCase();
    if (this.anagram === lowerCaseWord) {
      return false;
    }

    if (this.anagram.length !== lowerCaseWord.length) {
      return false;
    }

    return this.sortedAnagram === [...lowerCaseWord].sort().join('');
  }

  public matches(...words: string[]): string[] {
    return words.filter((word) => this.isAnagram(word));
  }
}