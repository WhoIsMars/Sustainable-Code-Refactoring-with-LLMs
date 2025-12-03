var Series = function(digits) {
	/* Mannipulates a series of digits */
	this.digits = [];
	for (var i = 0; i < digits.length; i++) {
		this.digits[i] = +digits[i];
	}
}

Series.prototype.slices = function(sliceSize) {
	/* Slices digits into arrays of a certain size */
	var num_slices = this.digits.length - sliceSize + 1;
	if(num_slices <= 0)
		throw new Error("Slice size is too big.");
	
	var result = new Array(num_slices);
	for (var i = 0; i < num_slices; i++) {
		result[i] = this.digits.slice(i, i + sliceSize);
	}
	return result;
};

module.exports = Series;