const Squares = function(num) {
    const numPlusOne = num + 1;
    const numSquared = num * num;
    
    this.squareOfSums = (numSquared * numPlusOne * numPlusOne) >> 2;
    this.sumOfSquares = (num * numPlusOne * ((num << 1) + 1)) / 6;
    this.difference = this.squareOfSums - this.sumOfSquares;
};

module.exports = Squares;