class Squares {
  constructor(num) {
    const n = BigInt(num);
    this.squareOfSums = (n * (n + 1n) / 2n) ** 2n;
    this.sumOfSquares = n * (n + 1n) * (2n * n + 1n) / 6n;
    this.difference = this.squareOfSums - this.sumOfSquares;
  }
}

module.exports = Squares;