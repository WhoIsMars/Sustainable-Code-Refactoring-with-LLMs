const hashWord = word => {
  const lowerCaseWord = word.toLowerCase();
  const charArray = Array(26).fill(0); // Assuming only lowercase English letters

  for (let i = 0; i < lowerCaseWord.length; i++) {
    const charCode = lowerCaseWord.charCodeAt(i) - 'a'.charCodeAt(0);
    if (charCode >= 0 && charCode < 26) {
      charArray[charCode]++;
    }
  }

  return charArray.join('');
};


export class Anagram {
  constructor(word) {
    this.word = word;
    this.wordLowerCase = word.toLowerCase();
    this.matchHash = hashWord(word);
  }

  matches(candidates) {
    const { wordLowerCase, matchHash } = this;

    return candidates.filter(candidate => {
      const candidateLowerCase = candidate.toLowerCase();
      return wordLowerCase !== candidateLowerCase && matchHash === hashWord(candidate);
    });
  }
}