export class Anagram {
  constructor(word) {
    this.word = word;
    this.wordLower = word.toLowerCase();
    this.wordHash = this.hashWord(word);
  }

  hashWord(word) {
    return word.toLowerCase().split("").sort().join("");
  }

  matches(candidates) {
    const { wordLower, wordHash } = this;

    return candidates.filter(candidate => {
      const candidateLower = candidate.toLowerCase();
      return (
        wordLower !== candidateLower && wordHash === this.hashWord(candidate)
      );
    });
  }
}