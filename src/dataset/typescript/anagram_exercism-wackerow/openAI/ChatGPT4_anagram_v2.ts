export default class Anagram {
  private readonly _anagram: string;
  private readonly _sortedAnagram: string;

  constructor(anagram: string) {
    this._anagram = anagram.toLowerCase();
    this._sortedAnagram = Anagram.sortString(this._anagram);
  }

  public matches(...args: string[]): string[] {
    return args.filter(word => {
      const lowerWord = word.toLowerCase();
      return (
        lowerWord !== this._anagram &&
        Anagram.sortString(lowerWord) === this._sortedAnagram
      );
    });
  }

  private static sortString(str: string): string {
    return str.split('').sort().join('');
  }
}