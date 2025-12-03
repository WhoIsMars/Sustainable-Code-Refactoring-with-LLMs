export default class Anagram {
  private readonly _anagramLower: string;
  private readonly _sortedAnagram: string;

  constructor(private anagram: string) {
    this._anagramLower = anagram.toLowerCase();
    this._sortedAnagram = this._anagramLower.split('').sort().join('');
  }

  public matches(...args: string[]): string[] {
    const matches: string[] = [];
    for (const word of args) {
      const lowerWord = word.toLowerCase();
      if (lowerWord === this._anagramLower) continue;

      if (word.length !== this.anagram.length) continue;

      const sortedWord = lowerWord.split('').sort().join('');

      if (sortedWord === this._sortedAnagram) {
        matches.push(word);
      }
    }
    return matches;
  }
}