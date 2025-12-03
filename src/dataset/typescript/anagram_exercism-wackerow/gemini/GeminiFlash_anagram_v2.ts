export default class Anagram {
  private readonly _anagramLower: string;
  private readonly _sortedAnagram: string;

  constructor(anagram: string) {
    this._anagramLower = anagram.toLowerCase();
    this._sortedAnagram = this._anagramLower.split('').sort().join('');
  }

  public matches(...words: string[]): string[] {
    const matches: string[] = [];
    for (const word of words) {
      const lowerWord = word.toLowerCase();
      if (lowerWord === this._anagramLower) continue;

      if (lowerWord.length !== this._anagramLower.length) continue;

      let sortedWord: string;
      if (word.length <= 10) {
        sortedWord = lowerWord.split('').sort().join('');
      } else {
        const charCounts = new Array(26).fill(0);
        for (let i = 0; i < lowerWord.length; i++) {
          charCounts[lowerWord.charCodeAt(i) - 97]++;
        }
        sortedWord = charCounts.join('');
        const anagramCharCounts = new Array(26).fill(0);
        for (let i = 0; i < this._anagramLower.length; i++) {
          anagramCharCounts[this._anagramLower.charCodeAt(i) - 97]++;
        }
        if (sortedWord !== anagramCharCounts.join('')) continue;
        matches.push(word);
        continue;
      }

      if (sortedWord === this._sortedAnagram) {
        matches.push(word);
      }
    }
    return matches;
  }
}