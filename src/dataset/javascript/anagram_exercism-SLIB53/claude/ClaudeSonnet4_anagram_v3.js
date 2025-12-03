const hashWord = word => {
  const chars = [];
  for (let i = 0; i < word.length; i++) {
    chars.push(word.charCodeAt(i) | 32);
  }
  chars.sort((a, b) => a - b);
  return String.fromCharCode(...chars);
};

export class Anagram {
  constructor(word) {
    this.word = word;
    this.wordLowerCase = word.toLowerCase();
    this.matchHash = hashWord(word);
  }

  matches(candidates) {
    const results = [];
    for (let i = 0; i < candidates.length; i++) {
      const candidate = candidates[i];
      const candidateLower = candidate.toLowerCase();
      if (this.wordLowerCase !== candidateLower && 
          this.matchHash === hashWord(candidate)) {
        results.push(candidate);
      }
    }
    return results;
  }
}