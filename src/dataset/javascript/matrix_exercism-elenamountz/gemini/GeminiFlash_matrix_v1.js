export class Matrix {
  constructor(str) {
    this.str = str;
    const rows = str.split('\n');
    this.rows = rows.map(row => row.split(' ').map(Number));
    this.columns = this.getColumns(this.rows);
  }


  getColumns(rows) {
    if (!rows || rows.length === 0) {
      return [];
    }

    const numCols = rows[0].length;
    const columns = [];

    for (let j = 0; j < numCols; j++) {
      const column = [];
      for (let i = 0; i < rows.length; i++) {
        column.push(rows[i][j]);
      }
      columns.push(column);
    }

    return columns;
  }
}