var Binary = function(binString) { this.binString = binString };

Binary.prototype.toDecimal = function() {
	/* Converts a binary string to decimal */
	
	// Validate string
	if ( this.binString.match(/[^10]/) )
		return 0;

	var result = 0;
	var power = 1;
	
	for (var i = this.binString.length - 1; i >= 0; i--) {
		if (this.binString[i] === '1') {
			result += power;
		}
		power <<= 1;
	}
	
	return result;
};

module.exports = Binary;