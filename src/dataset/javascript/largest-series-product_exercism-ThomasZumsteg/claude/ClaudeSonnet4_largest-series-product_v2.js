var Series = function(digits) {
	/* A series of digits */
	this.digits = digits;
	this.length = digits.length;
}

Series.prototype.slices = function(size) {
	/* Slices digits into groups */
	if(this.length < size)
		throw new Error("Slice size is too big.");
	var slices = [];
	for(var i = 0; i + size <= this.length; i++ ) {
		var slice = [];
		for(var j = 0; j < size; j++) {
			slice.push(parseInt(this.digits[i + j]));
		}
		slices.push(slice);
	}
	return slices;
};

Series.prototype.largestProduct = function(size) {
	/* The largest group when digits of slices are multipled together */
	if(this.length < size)
		throw new Error("Slice size is too big.");
	
	var maxProduct = 0;
	for(var i = 0; i + size <= this.length; i++) {
		var product = 1;
		for(var j = 0; j < size; j++) {
			product *= parseInt(this.digits[i + j]);
		}
		if(product > maxProduct) {
			maxProduct = product;
		}
	}
	return maxProduct;
};

function multiply(numbers) {
	/* Multiples all elements of an array together */
	var result = 1;
	for(var i = 0; i < numbers.length; i++) {
		result *= numbers[i];
	}
	return result;
}

module.exports = Series;