class Matrix {
  constructor(matrix) {
    this.rows = matrix.split("\n").map(row =>
      row.trim().split(/\s+/).map(Number)
    );

    this.columns = this.rows[0].map((_, colIndex) =>
      this.rows.map(row => row[colIndex])
    );

    this.saddlePoints = this.findSaddlePoints();
  }

  findSaddlePoints() {
    const rowMax = this.rows.map(row => Math.max(...row));
    const colMin = this.columns.map(col => Math.min(...col));
    const saddlePoints = [];

    for (let r = 0; r < this.rows.length; r++) {
      for (let c = 0; c < this.columns.length; c++) {
        if (this.rows[r][c] === rowMax[r] && this.rows[r][c] === colMin[c]) {
          saddlePoints.push([r, c]);
        }
      }
    }

    return saddlePoints;
  }
}

module.exports = Matrix;