class Squares {
  constructor(num) {
    const numPlus1 = num + 1;
    const numPlus1Squared = numPlus1 * numPlus1;
    this.squareOfSums = (num * numPlus1Squared) / 4;
    this.sumOfSquares = (num * numPlus1 * (2 * num + 1)) / 6;
    this.difference = this.squareOfSums - this.sumOfSquares;
  }
}

module.exports = Squares;