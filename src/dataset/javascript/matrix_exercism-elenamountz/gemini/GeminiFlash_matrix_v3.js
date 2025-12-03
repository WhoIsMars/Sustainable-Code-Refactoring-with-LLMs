export class Matrix {
  constructor(str){
    this.str = str;
    const rows = str.split('\n');
    this.rows = rows.map(row => row.split(' ').map(Number));
    this.columns = this.getColumns();
  }

  getColumns() {
    const numRows = this.rows.length;
    if (numRows === 0) {
      return [];
    }
    const numCols = this.rows[0].length;
    const columns = Array(numCols).fill(null).map(() => []);

    for (let i = 0; i < numRows; i++) {
      for (let j = 0; j < numCols; j++) {
        columns[j].push(this.rows[i][j]);
      }
    }
    return columns;
  }
}