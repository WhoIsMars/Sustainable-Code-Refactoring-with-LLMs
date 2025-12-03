var Series = function(digits) {
    this.digits = digits.split('').map(Number);
};

Series.prototype.slices = function(size) {
    const digitsLength = this.digits.length;
    if (size > digitsLength) {
        throw new Error("Slice size is too big.");
    }

    const numberOfSlices = digitsLength - size + 1;
    const slices = new Array(numberOfSlices);

    for (let i = 0; i < numberOfSlices; i++) {
        slices[i] = this.digits.slice(i, i + size);
    }

    return slices;
};

Series.prototype.largestProduct = function(size) {
    const slices = this.slices(size);
    let maxProduct = 0;

    for (let i = 0; i < slices.length; i++) {
        let product = 1;
        const slice = slices[i];
        for (let j = 0; j < slice.length; j++) {
            product *= slice[j];
        }
        if (product > maxProduct) {
            maxProduct = product;
        }
    }

    return maxProduct;
};

module.exports = Series;