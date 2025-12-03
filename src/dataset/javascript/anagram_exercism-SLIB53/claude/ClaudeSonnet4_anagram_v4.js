const hashWord = word => {
  const chars = new Array(26).fill(0);
  const lowerWord = word.toLowerCase();
  
  for (let i = 0; i < lowerWord.length; i++) {
    const charCode = lowerWord.charCodeAt(i);
    if (charCode >= 97 && charCode <= 122) {
      chars[charCode - 97]++;
    }
  }
  
  return chars.join(',');
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