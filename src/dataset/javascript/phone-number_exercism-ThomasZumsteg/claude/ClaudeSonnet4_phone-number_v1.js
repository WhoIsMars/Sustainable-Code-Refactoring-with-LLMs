var PhoneNumber = function(phoneNumber) { 
	/* Formats phone numbers */
	// Pre-compiled regex for better performance
	var reNumber = /^1?\D*(\d{3})\D*(\d{3})\D*(\d{4})\D*$/;
	var match = phoneNumber.match(reNumber); 
	if(match) {
		this.area = match[1];
		this.first = match[2];
		this.second = match[3];
		this.num = match[1] + match[2] + match[3];
	}
	else {
		// Should probably throw an error here
		this.num = '00000000000';
	}
}

PhoneNumber.prototype.number   = function() { return this.num }
PhoneNumber.prototype.areaCode = function() { return this.area }
PhoneNumber.prototype.toString = function() { return "(" + this.area + ") " + this.first + "-" + this.second }

module.exports = PhoneNumber;