var Squares = function(num) {
  this.squareOfSums = (() => {
    const sum = (num * (num + 1)) / 2;
    return sum * sum;
  })();

  this.sumOfSquares = (num * (num + 1) * (2 * num + 1)) / 6;
  this.difference = this.squareOfSums - this.sumOfSquares;
};

module.exports = Squares;