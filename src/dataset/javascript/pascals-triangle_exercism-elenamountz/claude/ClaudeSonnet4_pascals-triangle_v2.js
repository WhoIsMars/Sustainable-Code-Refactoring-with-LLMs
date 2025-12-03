export default class Triangle{
  constructor(number){
    this.number = number;
    this.rows = this.getRows();
    this.lastRow = this.rows[number - 1];
  }
  
  getRows(){
    if(this.number <= 0) return [];
    
    const rowsArray = new Array(this.number);
    rowsArray[0] = [1];
    
    if(this.number === 1) return rowsArray;
    
    rowsArray[1] = [1, 1];
    
    for(let i = 2; i < this.number; i++){
      const currentRow = new Array(i + 1);
      currentRow[0] = 1;
      currentRow[i] = 1;
      
      const prevRow = rowsArray[i - 1];
      for(let j = 1; j < i; j++){
        currentRow[j] = prevRow[j - 1] + prevRow[j];
      }
      
      rowsArray[i] = currentRow;
    }
    
    return rowsArray;
  }
}