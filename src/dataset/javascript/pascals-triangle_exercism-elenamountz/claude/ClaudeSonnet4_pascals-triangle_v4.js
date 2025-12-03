export default class Triangle{
  constructor(number){
    this.number = number;
    this.rows = this.getRows();
    this.lastRow = this.getLastRow();
  }
  getRows(){
    if (this.number <= 0) return [];
    
    const rowsArray = new Array(this.number);
    
    for(let i = 0; i < this.number; i++){
      const row = new Array(i + 1);
      row[0] = 1;
      row[i] = 1;
      
      for(let j = 1; j < i; j++){
        row[j] = rowsArray[i-1][j-1] + rowsArray[i-1][j];
      }
      
      rowsArray[i] = row;
    }
    return rowsArray;
  }
  getLastRow(){
    return this.rows[this.number - 1];
  }
}