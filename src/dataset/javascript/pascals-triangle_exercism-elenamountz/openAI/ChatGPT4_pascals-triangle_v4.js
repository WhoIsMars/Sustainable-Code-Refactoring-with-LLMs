export default class Triangle {
  constructor(number) {
    this.number = number;
    this.rows = this.generateRows(number);
    this.lastRow = this.rows[number - 1];
  }

  generateRows(number) {
    const rows = [];
    for (let i = 0; i < number; i++) {
      const row = new Array(i + 1).fill(1);
      for (let j = 1; j < i; j++) {
        row[j] = rows[i - 1][j - 1] + rows[i - 1][j];
      }
      rows.push(row);
    }
    return rows;
  }

  getRows() {
    return this.rows;
  }

  getLastRow() {
    return this.lastRow;
  }
}