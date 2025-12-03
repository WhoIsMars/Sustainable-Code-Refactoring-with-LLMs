var Squares = function(num) {
	var numPlusOne = num + 1;
	var numSquared = num * num;
	var numPlusOneSquared = numPlusOne * numPlusOne;
	
	this.squareOfSums = (numSquared * numPlusOneSquared) >> 2;
	this.sumOfSquares = (num * numPlusOne * ((num << 1) + 1)) / 6;
	this.difference = this.squareOfSums - this.sumOfSquares;
}

module.exports = Squares;