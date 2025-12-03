export class Matrix {
  constructor(str) {
    this.str = str;
    const rows = str.split('\n').map(row => row.split(' ').map(Number));
    this.rows = rows;
    this.columns = this.transpose(rows);
  }

  transpose(matrix) {
    if (!matrix || matrix.length === 0) {
      return [];
    }

    const numRows = matrix.length;
    const numCols = matrix[0].length;
    const transposedMatrix = Array(numCols).fill(null).map(() => Array(numRows));

    for (let i = 0; i < numRows; i++) {
      for (let j = 0; j < numCols; j++) {
        transposedMatrix[j][i] = matrix[i][j];
      }
    }

    return transposedMatrix;
  }

  getRows() {
    return this.rows;
  }

  getColumns() {
    return this.columns;
  }
}