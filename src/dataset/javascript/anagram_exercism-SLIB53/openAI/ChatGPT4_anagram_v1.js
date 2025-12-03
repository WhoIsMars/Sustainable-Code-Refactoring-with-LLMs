const hashWord = (() => {
  const cache = new Map();
  return word => {
    if (cache.has(word)) return cache.get(word);
    const hashed = [...word.toLowerCase()].sort().join("");
    cache.set(word, hashed);
    return hashed;
  };
})();

export class Anagram {
  constructor(word) {
    this.word = word.toLowerCase();
    this.wordHash = hashWord(this.word);
  }

  matches(candidates) {
    return candidates.filter(candidate => {
      const candidateLower = candidate.toLowerCase();
      return this.word !== candidateLower && this.wordHash === hashWord(candidateLower);
    });
  }
}