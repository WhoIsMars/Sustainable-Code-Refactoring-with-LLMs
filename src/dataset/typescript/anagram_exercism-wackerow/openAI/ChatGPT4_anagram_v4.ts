export default class Anagram {
  private readonly _anagram: string;
  private readonly _sortedAnagram: string;

  constructor(private anagram: string) {
    this._anagram = anagram.toLowerCase();
    this._sortedAnagram = Array.from(this._anagram).sort().join('');
  }

  public matches(...args: string[]): string[] {
    return args.filter(word => {
      const lowerWord = word.toLowerCase();
      return (
        lowerWord !== this._anagram &&
        lowerWord.length === this._anagram.length &&
        Array.from(lowerWord).sort().join('') === this._sortedAnagram
      );
    });
  }
}