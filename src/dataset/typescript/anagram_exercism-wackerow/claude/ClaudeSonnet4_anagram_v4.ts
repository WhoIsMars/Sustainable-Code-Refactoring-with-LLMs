export default class Anagram {
  private _anagram: string;
  private _sortedAnagram: string;

  constructor(private anagram: string) {
    this._anagram = anagram.toLowerCase();
    this._sortedAnagram = this._anagram.split('').sort().join('');
  }

  public matches(...args: string[]): string[] {
    const matches: string[] = [];
    const targetLength = this._sortedAnagram.length;
    
    for (const word of args) {
      const lowerWord = word.toLowerCase();
      
      if (lowerWord === this._anagram || lowerWord.length !== targetLength) {
        continue;
      }
      
      const sortedWord = lowerWord.split('').sort().join('');
      if (sortedWord === this._sortedAnagram) {
        matches.push(word);
      }
    }
    
    return matches;
  }
}