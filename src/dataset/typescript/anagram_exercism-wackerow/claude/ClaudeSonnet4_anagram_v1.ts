export default class Anagram {
  private _anagram: string;
  private _sortedAnagram: string;

  constructor(private anagram: string) {
    this._anagram = anagram.toLowerCase();
    this._sortedAnagram = this._anagram.split('').sort().join('');
  }

  public matches(...args: string[]): string[] {
    const matches: string[] = [];
    const anagramLength = this._anagram.length;
    
    for (const word of args) {
      // Early exit if lengths don't match
      if (word.length !== anagramLength) {
        continue;
      }
      
      const lowerWord = word.toLowerCase();
      
      // Early exit if words are identical
      if (lowerWord === this._anagram) {
        continue;
      }
      
      // Only sort if previous checks pass
      const sortedWord = lowerWord.split('').sort().join('');
      
      if (sortedWord === this._sortedAnagram) {
        matches.push(word);
      }
    }
    
    return matches;
  }
}