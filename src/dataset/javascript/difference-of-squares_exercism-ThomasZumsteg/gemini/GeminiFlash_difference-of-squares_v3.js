var Squares = function(num) {
	this.squareOfSums = Math.pow(num * (num + 1) / 2, 2);
	this.sumOfSquares = num * (num + 1) * (2 * num + 1) / 6;
	this.difference = this.squareOfSums - this.sumOfSquares;
}

module.exports = Squares;