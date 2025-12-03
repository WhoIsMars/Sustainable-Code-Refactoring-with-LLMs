var PhoneNumber = function(phoneNumber) { 
	/* Formats phone numbers */
	// Pre-compiled regex for better performance
	var digits = phoneNumber.replace(/\D/g, '');
	
	// Handle 10 or 11 digit numbers
	if (digits.length === 11 && digits[0] === '1') {
		digits = digits.slice(1);
	}
	
	if (digits.length === 10) {
		this.area = digits.slice(0, 3);
		this.first = digits.slice(3, 6);
		this.second = digits.slice(6, 10);
		this.num = digits;
	} else {
		// Should probably throw an error here
		this.num = '0000000000';
		this.area = '000';
		this.first = '000';
		this.second = '0000';
	}
}

PhoneNumber.prototype.number   = function() { return this.num }
PhoneNumber.prototype.areaCode = function() { return this.area }
PhoneNumber.prototype.toString = function() { return "(" + this.area + ") " + this.first + "-" + this.second }

module.exports = PhoneNumber;