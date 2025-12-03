export class Matrix {
  constructor(str) {
    this.str = str;
    this._parseMatrix();
  }

  _parseMatrix() {
    const lines = this.str.split('\n');
    const numRows = lines.length;
    const numCols = lines[0] ? lines[0].split(' ').length : 0;
    
    this.rows = new Array(numRows);
    this.columns = new Array(numCols);
    
    for (let i = 0; i < numCols; i++) {
      this.columns[i] = new Array(numRows);
    }
    
    for (let i = 0; i < numRows; i++) {
      const values = lines[i].split(' ');
      this.rows[i] = new Array(numCols);
      
      for (let j = 0; j < numCols; j++) {
        const value = parseInt(values[j], 10);
        this.rows[i][j] = value;
        this.columns[j][i] = value;
      }
    }
  }

  getRows() {
    return this.rows;
  }

  getColumns() {
    return this.columns;
  }
}