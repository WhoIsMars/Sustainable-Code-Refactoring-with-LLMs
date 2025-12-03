var Squares = function(num) {
	/* Calculates sums of difference functions */
	// Based on triangle numbers and square pyramid numbers
	var numPlus1 = num + 1;
	var numSquared = num * num;
	this.squareOfSums = (numSquared * numPlus1 * numPlus1) >> 2;
	this.sumOfSquares = num * numPlus1 * (num + num + 1) / 6;
	this.difference = this.squareOfSums - this.sumOfSquares;
}

module.exports = Squares;