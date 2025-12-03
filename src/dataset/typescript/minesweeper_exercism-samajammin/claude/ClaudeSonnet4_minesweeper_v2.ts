export default class Minesweeper {
  annotate(board: string[]): string[] {
    const mineCell = '*';
    const rows = board.length;
    const result: string[] = new Array(rows);
    
    for (let rowIdx = 0; rowIdx < rows; rowIdx++) {
      const row = board[rowIdx];
      const cols = row.length;
      let newRow = '';
      
      for (let colIdx = 0; colIdx < cols; colIdx++) {
        if (row[colIdx] === mineCell) {
          newRow += mineCell;
          continue;
        }
        
        let cellValue = 0;
        const minR = Math.max(0, rowIdx - 1);
        const maxR = Math.min(rows - 1, rowIdx + 1);
        const minC = Math.max(0, colIdx - 1);
        const maxC = Math.min(cols - 1, colIdx + 1);
        
        for (let r = minR; r <= maxR; r++) {
          const boardRow = board[r];
          for (let c = minC; c <= maxC; c++) {
            if (boardRow[c] === mineCell) {
              cellValue++;
            }
          }
        }
        
        newRow += cellValue === 0 ? ' ' : cellValue;
      }
      
      result[rowIdx] = newRow;
    }
    
    return result;
  }
}