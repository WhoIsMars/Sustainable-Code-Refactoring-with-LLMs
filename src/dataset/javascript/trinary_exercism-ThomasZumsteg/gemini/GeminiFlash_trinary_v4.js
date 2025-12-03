var Trinary = function(digits) {
	this.digits = digits;
};

Trinary.prototype.toDecimal = function() {
	let decimal = 0;
	const digits = this.digits;
	const len = digits.length;

	for (let i = 0; i < len; i++) {
		const digit = digits[len - 1 - i];
		if (digit >= '0' && digit <= '2') {
			decimal += digit * (3 ** i);
		} else {
			return 0;
		}
	}

	return decimal;
};

module.exports = Trinary;