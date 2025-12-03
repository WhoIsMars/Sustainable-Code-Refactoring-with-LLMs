var Series = function(digits) {
	this.digits = Array.from(digits, Number);
};

Series.prototype.slices = function(sliceSize) {
	var digitsLength = this.digits.length;
	var num_slices = digitsLength - sliceSize + 1;

	if (num_slices <= 0) {
		throw new Error("Slice size is too big.");
	}

	const result = [];
	for (let i = 0; i < num_slices; i++) {
		result.push(this.digits.slice(i, i + sliceSize));
	}
	return result;
};

module.exports = Series;