export class Matrix {
  constructor(str) {
    this.str = str;
    this._rows = null;
    this._columns = null;
  }

  getRows() {
    if (this._rows === null) {
      this._rows = this.str.split('\n').map(row => 
        row.split(' ').map(num => parseInt(num, 10))
      );
    }
    return this._rows;
  }

  getColumns() {
    if (this._columns === null) {
      const rows = this.getRows();
      const colCount = rows[0]?.length || 0;
      this._columns = Array(colCount);
      
      for (let col = 0; col < colCount; col++) {
        this._columns[col] = Array(rows.length);
        for (let row = 0; row < rows.length; row++) {
          this._columns[col][row] = rows[row][col];
        }
      }
    }
    return this._columns;
  }

  get rows() {
    return this.getRows();
  }

  get columns() {
    return this.getColumns();
  }
}