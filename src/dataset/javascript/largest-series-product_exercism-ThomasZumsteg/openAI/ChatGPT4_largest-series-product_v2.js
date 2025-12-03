class Series {
  constructor(digits) {
    this.digits = Array.from(digits, Number);
  }

  slices(size) {
    if (this.digits.length < size) {
      throw new Error("Slice size is too big.");
    }
    const slices = [];
    for (let i = 0; i <= this.digits.length - size; i++) {
      slices.push(this.digits.slice(i, i + size));
    }
    return slices;
  }

  largestProduct(size) {
    if (size === 0) return 1;
    if (this.digits.length < size) {
      throw new Error("Slice size is too big.");
    }
    let maxProduct = 0;
    for (let i = 0; i <= this.digits.length - size; i++) {
      let product = 1;
      for (let j = 0; j < size; j++) {
        product *= this.digits[i + j];
        if (product === 0) break; // Early exit if product is zero
      }
      maxProduct = Math.max(maxProduct, product);
    }
    return maxProduct;
  }
}

module.exports = Series;