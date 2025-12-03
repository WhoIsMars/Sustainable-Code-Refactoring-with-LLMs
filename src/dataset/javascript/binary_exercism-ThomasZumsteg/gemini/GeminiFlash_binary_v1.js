var Binary = function(binString) { this.binString = binString; };

Binary.prototype.toDecimal = function() {
    let decimal = 0;
    const binString = this.binString;
    const len = binString.length;

    for (let i = 0; i < len; i++) {
        const bit = binString[i];

        if (bit !== '0' && bit !== '1') {
            return 0;
        }

        if (bit === '1') {
            decimal = (decimal * 2) + 1;
        } else {
            decimal = decimal * 2;
        }
    }

    return decimal;
};

module.exports = Binary;