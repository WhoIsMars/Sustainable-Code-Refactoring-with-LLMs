export class Matrix {
  constructor(str) {
    this.str = str;
    this.rows = this.getRows();
    this.columns = this.getColumns();
  }

  getRows() {
    return this.str.split('\n').map(row => row.split(' ').map(Number));
  }

  getColumns() {
    const rows = this.rows;
    const columns = Array.from({ length: rows[0].length }, () => []);
    for (let i = 0; i < rows.length; i++) {
      for (let j = 0; j < rows[i].length; j++) {
        columns[j].push(rows[i][j]);
      }
    }
    return columns;
  }
}