export default class WordSearch {
  constructor(grid) {
    this.grid = grid;
    this.rows = grid.length;
    this.cols = grid[0]?.length || 0;
  }

  find(words) {
    const result = {};
    const foundWords = new Set();
    
    // Pre-initialize result object
    for (const word of words) {
      result[word] = undefined;
    }
    
    for (let r = 0; r < this.rows && foundWords.size < words.length; r++) {
      for (let c = 0; c < this.cols && foundWords.size < words.length; c++) {
        const char = this.grid[r][c];
        
        // Only check words that start with current character and haven't been found
        for (const word of words) {
          if (!foundWords.has(word) && word[0] === char) {
            const end = this.search(word, r, c);
            if (end !== undefined) {
              result[word] = {"start": [r+1, c+1], "end": end};
              foundWords.add(word);
            }
          }
        }
      }
    }
    return result;
  }

  search(word, row, col) {
    const directions = [
      [1, 1], [1, 0], [1, -1],
      [0, 1], [0, -1],
      [-1, 1], [-1, 0], [-1, -1]
    ];
    
    const wordLength = word.length;
    
    for (const [rowDir, colDir] of directions) {
      let isValid = true;
      
      // Check bounds first
      const endRow = row + rowDir * (wordLength - 1);
      const endCol = col + colDir * (wordLength - 1);
      
      if (endRow < 0 || endRow >= this.rows || endCol < 0 || endCol >= this.cols) {
        continue;
      }
      
      // Check each character
      for (let pos = 0; pos < wordLength; pos++) {
        const currentRow = row + rowDir * pos;
        const currentCol = col + colDir * pos;
        
        if (this.grid[currentRow][currentCol] !== word[pos]) {
          isValid = false;
          break;
        }
      }
      
      if (isValid) {
        return [endRow + 1, endCol + 1];
      }
    }
    
    return undefined;
  }
}