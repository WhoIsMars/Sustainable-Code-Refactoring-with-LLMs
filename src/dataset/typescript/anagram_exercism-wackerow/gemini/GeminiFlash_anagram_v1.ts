export default class Anagram {
  private _anagramLower: string;
  private _sortedAnagram: string;

  constructor(private anagram: string) {
    this._anagramLower = anagram.toLowerCase();
    this._sortedAnagram = this._anagramLower.split('').sort().join('');
  }

  public matches(...args: string[]): string[] {
    const anagramLower = this._anagramLower;
    const sortedAnagram = this._sortedAnagram;
    const matches: string[] = [];

    for (const word of args) {
      const wordLower = word.toLowerCase();

      if (wordLower === anagramLower) {
        continue;
      }

      if (word.length !== this.anagram.length) {
          continue;
      }
      
      const sortedWord = wordLower.split('').sort().join('');

      if (sortedWord === sortedAnagram) {
        matches.push(word);
      }
    }

    return matches;
  }
}