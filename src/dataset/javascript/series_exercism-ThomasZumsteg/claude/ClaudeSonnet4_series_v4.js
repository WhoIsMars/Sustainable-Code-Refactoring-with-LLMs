var Series = function(digits) {
	this.digits = digits.split('').map(function(e) { return parseInt(e, 10); });
}

Series.prototype.slices = function(sliceSize) {
	var num_slices = this.digits.length - sliceSize + 1;
	if (num_slices <= 0) {
		throw new Error("Slice size is too big.");
	}
	
	var result = new Array(num_slices);
	for (var i = 0; i < num_slices; i++) {
		result[i] = this.digits.slice(i, i + sliceSize);
	}
	return result;
};

module.exports = Series;