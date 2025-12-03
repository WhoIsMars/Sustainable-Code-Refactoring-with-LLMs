export default class Matrix {
  constructor(str) {
    this.str = str.replace(/\n\s+/g, '\n');
    this.rows = this.getRows();
    this.columns = this.getColumns();
    this.saddlePoints = this.getSaddlePoints();
  }

  getRows() {
    return this.str.split('\n').map(row => row.split(' ').map(Number));
  }

  getColumns() {
    return this.rows[0].map((_, colIndex) => this.rows.map(row => row[colIndex]));
  }

  getSaddlePoints() {
    const saddlePoints = [];
    const rowMax = this.rows.map(row => Math.max(...row));
    const colMin = this.columns.map(col => Math.min(...col));

    for (let i = 0; i < this.rows.length; i++) {
      for (let j = 0; j < this.columns.length; j++) {
        if (this.rows[i][j] === rowMax[i] && this.rows[i][j] === colMin[j]) {
          saddlePoints.push([i, j]);
        }
      }
    }

    return saddlePoints;
  }
}