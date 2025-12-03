class Series {
	constructor(digits) {
		this.digits = Array.from(digits, Number);
	}

	slices(size) {
		if (this.digits.length < size) throw new Error("Slice size is too big.");
		const slices = [];
		for (let i = 0; i <= this.digits.length - size; i++) {
			slices.push(this.digits.slice(i, i + size));
		}
		return slices;
	}

	largestProduct(size) {
		if (size === 0) return 1;
		return this.slices(size).reduce((max, slice) => {
			const product = slice.reduce((total, num) => total * num, 1);
			return Math.max(max, product);
		}, 0);
	}
}

module.exports = Series;