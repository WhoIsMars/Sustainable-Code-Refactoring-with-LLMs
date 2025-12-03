export default class Triangle {
  constructor(number) {
    this.number = number;
    this.rows = this.generateRows();
    this.lastRow = this.rows[this.number - 1];
  }

  generateRows() {
    const rows = [];
    for (let i = 0; i < this.number; i++) {
      const row = Array(i + 1).fill(1);
      for (let j = 1; j < i; j++) {
        row[j] = rows[i - 1][j - 1] + rows[i - 1][j];
      }
      rows.push(row);
    }
    return rows;
  }
}