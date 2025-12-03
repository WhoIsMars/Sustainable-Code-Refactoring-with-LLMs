class Series {
    constructor(digits) {
        // Manipulates a series of digits
        this.digits = Array.from(digits, Number);
    }

    slices(sliceSize) {
        // Slices digits into arrays of a certain size
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