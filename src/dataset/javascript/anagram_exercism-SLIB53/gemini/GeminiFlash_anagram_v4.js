export class Anagram {
  constructor(word) {
    this.word = word;
    this.wordLowerCase = word.toLowerCase();
    this.wordHash = this.hashWord(word);
  }

  hashWord(word) {
    return word
      .toLowerCase()
      .split("")
      .sort()
      .join("");
  }

  matches(candidates) {
    const { wordLowerCase, wordHash } = this;

    return candidates.filter(candidate => {
      const candidateLowerCase = candidate.toLowerCase();
      if (wordLowerCase === candidateLowerCase) {
        return false;
      }

      return wordHash === this.hashWord(candidate);
    });
  }
}