export default class Matrix {
  constructor(str) {
    this.str = str.split('\n ').join('\n');
    this.rows = this.getRows();
    this.columns = this.getColumns();
    this.saddlePoints = this.getSaddlePoints();
  }

  getRows() {
    return this.str.split('\n').map(row => row.split(' ').map(Number));
  }

  getColumns() {
    const numRows = this.rows.length;
    const numCols = numRows > 0 ? this.rows[0].length : 0;
    const columns = [];

    for (let j = 0; j < numCols; j++) {
      const column = [];
      for (let i = 0; i < numRows; i++) {
        column.push(this.rows[i][j]);
      }
      columns.push(column);
    }
    return columns;
  }

  getSaddlePoints() {
    const saddlePoints = [];
    const numRows = this.rows.length;
    const numCols = this.columns.length;

    for (let i = 0; i < numRows; i++) {
      const row = this.rows[i];
      const maxInRow = Math.max(...row);

      for (let j = 0; j < numCols; j++) {
        const col = this.columns[j];
        const minInCol = Math.min(...col);

        if (maxInRow === minInCol && row[j] === maxInRow) {
          saddlePoints.push([i, j]);
        }
      }
    }

    return saddlePoints;
  }
}