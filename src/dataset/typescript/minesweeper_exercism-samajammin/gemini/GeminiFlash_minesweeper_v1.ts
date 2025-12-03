export default class Minesweeper {
  annotate(board: string[]): string[] {
    const rows = board.length;
    if (rows === 0) {
      return [];
    }
    const cols = board[0].length;
    const mineCell = '*';
    const annotatedBoard: string[] = new Array(rows);

    for (let rowIdx = 0; rowIdx < rows; rowIdx++) {
      let annotatedRow = '';
      for (let colIdx = 0; colIdx < cols; colIdx++) {
        const cell = board[rowIdx][colIdx];
        if (cell === mineCell) {
          annotatedRow += mineCell;
        } else {
          let cellValue = 0;
          for (let r = Math.max(0, rowIdx - 1); r <= Math.min(rows - 1, rowIdx + 1); r++) {
            for (let c = Math.max(0, colIdx - 1); c <= Math.min(cols - 1, colIdx + 1); c++) {
              if (r === rowIdx && c === colIdx) {
                continue;
              }
              if (board[r][c] === mineCell) {
                cellValue++;
              }
            }
          }
          annotatedRow += cellValue === 0 ? ' ' : cellValue.toString();
        }
      }
      annotatedBoard[rowIdx] = annotatedRow;
    }

    return annotatedBoard;
  }
}