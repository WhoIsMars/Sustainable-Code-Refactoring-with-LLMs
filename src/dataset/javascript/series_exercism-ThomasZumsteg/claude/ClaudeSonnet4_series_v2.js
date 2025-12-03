var Series = function(digits) {
	/* Mannipulates a series of digits */
	this.digits = digits;
	this.length = digits.length;
}

Series.prototype.slices = function(sliceSize) {
	/* Slices digits into arrays of a certain size */
	var num_slices = this.length - sliceSize + 1;
	if(num_slices <= 0)
		throw new Error("Slice size is too big.");
	
	var result = new Array(num_slices);
	for(var i = 0; i < num_slices; i++) {
		var slice = new Array(sliceSize);
		for(var j = 0; j < sliceSize; j++) {
			slice[j] = parseInt(this.digits[i + j]);
		}
		result[i] = slice;
	}
	return result;
};

module.exports = Series;