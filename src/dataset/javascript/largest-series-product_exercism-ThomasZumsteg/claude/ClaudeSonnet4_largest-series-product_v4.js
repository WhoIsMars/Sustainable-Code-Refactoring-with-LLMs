var Series = function(digits) {
	this.digits = digits.split('').map(function(e) {return parseInt(e, 10)});
}

Series.prototype.slices = function(size) {
	if(this.digits.length < size)
		throw new Error("Slice size is too big.");
	var slices = [];
	var length = this.digits.length;
	for(var i = 0; i <= length - size; i++ ) {
		slices.push(this.digits.slice(i, i + size));
	}
	return slices;
};

Series.prototype.largestProduct = function(size) {
	if(this.digits.length < size)
		throw new Error("Slice size is too big.");
	
	var maxProduct = 0;
	var length = this.digits.length;
	
	for(var i = 0; i <= length - size; i++) {
		var product = 1;
		for(var j = 0; j < size; j++) {
			product *= this.digits[i + j];
		}
		if(product > maxProduct) {
			maxProduct = product;
		}
	}
	
	return maxProduct;
};

function multiply(numbers) {
	var result = 1;
	var length = numbers.length;
	for(var i = 0; i < length; i++) {
		result *= numbers[i];
	}
	return result;
}

module.exports = Series;