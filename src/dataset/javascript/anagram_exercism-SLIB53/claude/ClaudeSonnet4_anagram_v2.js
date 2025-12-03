const hashWord = word => {
  const chars = new Array(26).fill(0);
  const lowerWord = word.toLowerCase();
  
  for (let i = 0; i < lowerWord.length; i++) {
    const charCode = lowerWord.charCodeAt(i) - 97;
    if (charCode >= 0 && charCode < 26) {
      chars[charCode]++;
    }
  }
  
  return chars.join('');
};

export class Anagram {
  constructor(word) {
    this.word = word;
    this.wordLowerCase = word.toLowerCase();
    this.matchHash = hashWord(word);
  }

  matches(candidates) {
    return candidates.filter(
      candidate => {
        const candidateLower = candidate.toLowerCase();
        return this.wordLowerCase !== candidateLower &&
               this.matchHash === hashWord(candidate);
      }
    );
  }
}