export class Matrix {
  constructor(str){
    this.str = str;
    this.rows = this.getRows();
    this.columns = this.getColumns();
  }

  getRows(){
    const lines = this.str.split('\n');
    const rows = new Array(lines.length);
    
    for (let i = 0; i < lines.length; i++) {
      const elements = lines[i].split(' ');
      const row = new Array(elements.length);
      for (let j = 0; j < elements.length; j++) {
        row[j] = parseInt(elements[j], 10);
      }
      rows[i] = row;
    }
    
    return rows;
  }
  
  getColumns() {
    if (this.rows.length === 0) return [];
    
    const numCols = this.rows[0].length;
    const columns = new Array(numCols);
    
    for (let col = 0; col < numCols; col++) {
      const column = new Array(this.rows.length);
      for (let row = 0; row < this.rows.length; row++) {
        column[row] = this.rows[row][col];
      }
      columns[col] = column;
    }
    
    return columns;
  }
}