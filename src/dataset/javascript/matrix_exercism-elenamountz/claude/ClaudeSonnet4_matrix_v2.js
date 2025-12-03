export class Matrix {
  constructor(str){
    this.str = str;
    this.rows = this.getRows();
    this.columns = this.getColumns();
  }

  getRows(){
    return this.str.split('\n').map(row => 
      row.split(' ').map(num => parseInt(num, 10))
    );
  }

  getColumns() {
    if (!this.rows.length) return [];
    
    const numCols = this.rows[0].length;
    const columns = new Array(numCols);
    
    for (let col = 0; col < numCols; col++) {
      columns[col] = new Array(this.rows.length);
      for (let row = 0; row < this.rows.length; row++) {
        columns[col][row] = this.rows[row][col];
      }
    }
    
    return columns;
  }
}