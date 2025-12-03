export class Matrix {
  constructor(str) {
    this.str = str;
    const parsedRows = this.parseRows(str);
    this.rows = parsedRows;
    this.columns = this.transpose(parsedRows);
  }

  parseRows(str) {
    return str.split('\n').map(row => {
      const numStrings = row.split(' ');
      const nums = new Array(numStrings.length);
      for (let i = 0; i < numStrings.length; i++) {
        nums[i] = parseInt(numStrings[i], 10);
      }
      return nums;
    });
  }

  transpose(matrix) {
    if (!matrix || matrix.length === 0) {
      return [];
    }

    const numRows = matrix.length;
    const numCols = matrix[0].length;
    const transposedMatrix = Array.from({ length: numCols }, () => new Array(numRows));

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