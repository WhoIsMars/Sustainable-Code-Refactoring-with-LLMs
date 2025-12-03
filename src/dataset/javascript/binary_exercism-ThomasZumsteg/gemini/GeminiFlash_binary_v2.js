var Binary = function(binString) { this.binString = binString; };

Binary.prototype.toDecimal = function() {
    // Validate string
    if (/[^01]/.test(this.binString)) {
        return 0;
    }

    let decimal = 0;
    let powerOf2 = 1;

    for (let i = this.binString.length - 1; i >= 0; i--) {
        decimal += (this.binString[i] - '0') * powerOf2;
        powerOf2 *= 2;
    }

    return decimal;
};

module.exports = Binary;