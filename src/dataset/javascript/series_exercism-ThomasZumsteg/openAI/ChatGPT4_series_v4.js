class Series {
    constructor(digits) {
        this.digits = Array.from(digits, Number);
    }

    slices(sliceSize) {
        if (sliceSize > this.digits.length) {
            throw new Error("Slice size is too big.");
        }
        const result = [];
        for (let i = 0; i <= this.digits.length - sliceSize; i++) {
            result.push(this.digits.slice(i, i + sliceSize));
        }
        return result;
    }
}

module.exports = Series;