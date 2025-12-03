export default class Triangle {
  constructor(number) {
    this.number = number;
    this.rows = this.getRows();
    this.lastRow = this.rows[number - 1];
  }

  getRows() {
    const rowsArray = [];

    for (let i = 0; i < this.number; i++) {
      const row = new Array(i + 1);
      row[0] = 1;
      row[i] = 1;

      if (i > 1) {
        const previousRow = rowsArray[i - 1];
        for (let j = 1; j < i; j++) {
          row[j] = previousRow[j - 1] + previousRow[j];
        }
      }

      rowsArray.push(row);
    }

    return rowsArray;
  }
}