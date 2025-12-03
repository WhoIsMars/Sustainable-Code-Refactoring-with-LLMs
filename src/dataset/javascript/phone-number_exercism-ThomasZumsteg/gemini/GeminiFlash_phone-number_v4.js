var PhoneNumber = function(phoneNumber) {
	let cleanedNumber = phoneNumber.replace(/\D/g, '');

	if (cleanedNumber.length === 11 && cleanedNumber[0] === '1') {
		cleanedNumber = cleanedNumber.slice(1);
	}

	if (cleanedNumber.length !== 10) {
		this.numberString = '0000000000';
		return;
	}

	this.numberString = cleanedNumber;
};

PhoneNumber.prototype.number = function() {
	return this.numberString;
};

PhoneNumber.prototype.areaCode = function() {
	return this.numberString.substring(0, 3);
};

PhoneNumber.prototype.toString = function() {
	const areaCode = this.numberString.substring(0, 3);
	const prefix = this.numberString.substring(3, 6);
	const lineNumber = this.numberString.substring(6, 10);
	return `(${areaCode}) ${prefix}-${lineNumber}`;
};

module.exports = PhoneNumber;