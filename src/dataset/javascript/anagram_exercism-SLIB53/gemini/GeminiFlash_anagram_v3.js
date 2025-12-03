const hashWord = word => {
  const charCounts = new Array(26).fill(0);
  const aCode = 'a'.charCodeAt(0);
  const lowerWord = word.toLowerCase();

  for (let i = 0; i < lowerWord.length; i++) {
    const charCode = lowerWord.charCodeAt(i);
    if (charCode >= aCode && charCode < aCode + 26) {
      charCounts[charCode - aCode]++;
    } else {
      return null;
    }
  }

  return charCounts.join('');
};

export class Anagram {
  constructor(word) {
    this.word = word;
    this.wordLowerCase = word.toLowerCase();
    this.matchHash = hashWord(word);
  }

  matches(candidates) {
    if (this.matchHash === null) {
      return [];
    }

    return candidates.filter(candidate => {
      const candidateLowerCase = candidate.toLowerCase();
      if (this.wordLowerCase === candidateLowerCase) {
        return false;
      }

      const candidateHash = hashWord(candidate);
      return this.matchHash === candidateHash;
    });
  }
}