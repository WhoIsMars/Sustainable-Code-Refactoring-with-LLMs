export default class WordSearch {
  constructor(grid) {
    this.grid = grid;
  }

  find(words) {
    const result = {};
    for (const word of words) {
      result[word] = undefined;
    }

    for (let r = 0; r < this.grid.length; r++) {
      for (let c = 0; c < this.grid[r].length; c++) {
        for (const word of words) {
          if (this.grid[r][c] === word[0] && result[word] === undefined) {
            const end = this.search(word, r, c);
            if (end) {
              result[word] = { "start": [r + 1, c + 1], "end": end };
            }
          }
        }
      }
    }
    return result;
  }

  search(word, row, col) {
    const diffs = [
      { "row": 1, "col": 1 },
      { "row": 1, "col": 0 },
      { "row": 1, "col": -1 },
      { "row": 0, "col": 1 },
      { "row": 0, "col": -1 },
      { "row": -1, "col": 1 },
      { "row": -1, "col": 0 },
      { "row": -1, "col": -1 },
    ];

    for (const diff of diffs) {
      let valid = true;
      for (let pos = 0; pos < word.length; pos++) {
        const newRow = row + diff.row * pos;
        const newCol = col + diff.col * pos;

        if (newRow < 0 || newRow >= this.grid.length ||
          newCol < 0 || newCol >= this.grid[0].length ||
          this.grid[newRow][newCol] !== word[pos]) {
          valid = false;
          break;
        }
      }

      if (valid) {
        const endRow = row + diff.row * (word.length - 1);
        const endCol = col + diff.col * (word.length - 1);
        return [endRow + 1, endCol + 1];
      }
    }

    return undefined;
  }
}