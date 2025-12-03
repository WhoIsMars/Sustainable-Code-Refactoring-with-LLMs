const hashWord = word => {
  const charCount = Array(26).fill(0);
  for (const char of word.toLowerCase()) {
    const code = char.charCodeAt(0) - 97;
    if (code >= 0 && code < 26) charCount[code]++;
  }
  return charCount.join(",");
};

export class Anagram {
  constructor(word) {
    this.wordLowerCase = word.toLowerCase();
    this.matchHash = hashWord(word);
  }

  matches(candidates) {
    return candidates.filter(candidate => {
      const candidateLowerCase = candidate.toLowerCase();
      return (
        this.wordLowerCase !== candidateLowerCase &&
        this.matchHash === hashWord(candidate)
      );
    });
  }
}