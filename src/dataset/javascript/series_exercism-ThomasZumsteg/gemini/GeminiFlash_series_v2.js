var Series = function(digits) {
    this.digits = digits.split('').map(Number);
};

Series.prototype.slices = function(sliceSize) {
    const digitsLength = this.digits.length;
    const numSlices = digitsLength - sliceSize + 1;

    if (numSlices <= 0) {
        throw new Error("Slice size is too big.");
    }

    const result = [];
    for (let i = 0; i < numSlices; i++) {
        result.push(this.digits.slice(i, i + sliceSize));
    }
    return result;
};

module.exports = Series;