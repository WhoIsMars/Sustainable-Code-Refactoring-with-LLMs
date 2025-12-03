export default class WordSearch {
  constructor(grid) {
    this.grid = grid;
    this.directions = [
      [1, 1], [1, 0], [1, -1], [0, 1],
      [0, -1], [-1, 1], [-1, 0], [-1, -1]
    ];
  }

  find(words) {
    const result = {};
    const rows = this.grid.length;
    const cols = this.grid[0].length;

    for (const word of words) {
      result[word] = undefined;
      outer: for (let r = 0; r < rows; r++) {
        for (let c = 0; c < cols; c++) {
          const end = this.search(word, r, c);
          if (end) {
            result[word] = { start: [r + 1, c + 1], end };
            break outer;
          }
        }
      }
    }
    return result;
  }

  search(word, row, col) {
    const wordLen = word.length;
    const rows = this.grid.length;
    const cols = this.grid[0].length;

    for (const [dRow, dCol] of this.directions) {
      let r = row, c = col, pos = 0;

      while (
        pos < wordLen &&
        r >= 0 && r < rows &&
        c >= 0 && c < cols &&
        this.grid[r][c] === word[pos]
      ) {
        r += dRow;
        c += dCol;
        pos++;
      }

      if (pos === wordLen) {
        return [row + dRow * (wordLen - 1) + 1, col + dCol * (wordLen - 1) + 1];
      }
    }
  }
}