class Squares {
  constructor(num) {
    const n = num;
    const nPlus1 = n + 1;
    const nPlus1Squared = nPlus1 * nPlus1;
    this.squareOfSums = (n * n * nPlus1Squared) / 4;
    this.sumOfSquares = (n * nPlus1 * (2 * n + 1)) / 6;
    this.difference = this.squareOfSums - this.sumOfSquares;
  }
}

module.exports = Squares;