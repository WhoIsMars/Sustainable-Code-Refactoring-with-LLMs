export default class Matrix{
  constructor(str){
    this.str = str.replace(/\n /g, '\n');
    this.rows = this.getRows();
    this.columns = this.getColumns();
    this.saddlePoints = this.getSaddlePoints();
  }
  
  getRows(){
    return this.str.split('\n').map(row => 
      row.split(' ').map(num => parseInt(num, 10))
    );
  }
  
  getColumns() {
    const numCols = this.rows[0].length;
    const columns = new Array(numCols);
    
    for(let col = 0; col < numCols; col++){
      columns[col] = new Array(this.rows.length);
      for(let row = 0; row < this.rows.length; row++){
        columns[col][row] = this.rows[row][col];
      }
    }
    return columns;
  }
  
  getSaddlePoints(){
    const saddlePoints = [];
    const rowMaxes = this.rows.map(row => Math.max(...row));
    const colMins = this.columns.map(col => Math.min(...col));
    
    for(let i = 0; i < this.rows.length; i++){
      const rowMax = rowMaxes[i];
      for(let j = 0; j < this.rows[i].length; j++){
        if(this.rows[i][j] === rowMax && this.rows[i][j] === colMins[j]){
          saddlePoints.push([i, j]);
        }
      }
    }
    return saddlePoints;
  }
}