export default class Matrix {
  constructor(str) {
    this.matrixString = str.replace(/\n /g, '\n');
    this.rows = this.getRows();
    this.columns = this.getColumns();
    this.saddlePoints = this.getSaddlePoints();
  }

  getRows() {
    return this.matrixString.split('\n').map(row => row.split(' ').map(Number));
  }

  getColumns() {
    const numRows = this.rows.length;
    const numCols = this.rows[0].length;
    const columns = Array(numCols).fill(null).map(() => Array(numRows));

    for (let i = 0; i < numRows; i++) {
      for (let j = 0; j < numCols; j++) {
        columns[j][i] = this.rows[i][j];
      }
    }

    return columns;
  }

  getSaddlePoints() {
    const saddlePoints = [];
    const numRows = this.rows.length;
    const numCols = this.columns.length;

    for (let i = 0; i < numRows; i++) {
      const rowMax = Math.max(...this.rows[i]);

      for (let j = 0; j < numCols; j++) {
        const colMin = Math.min(...this.columns[j]);

        if (rowMax === colMin && this.rows[i][j] === rowMax) {
          saddlePoints.push([i, j]);
        }
      }
    }

    return saddlePoints;
  }
}