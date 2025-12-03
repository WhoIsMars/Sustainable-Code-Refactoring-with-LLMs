class Series {
  constructor(digits) {
    this.digits = Array.from(digits, Number);
  }

  slices(sliceSize) {
    if (sliceSize > this.digits.length) {
      throw new Error("Slice size is too big.");
    }
    const slices = [];
    for (let i = 0; i <= this.digits.length - sliceSize; i++) {
      slices.push(this.digits.slice(i, i + sliceSize));
    }
    return slices;
  }
}

module.exports = Series;