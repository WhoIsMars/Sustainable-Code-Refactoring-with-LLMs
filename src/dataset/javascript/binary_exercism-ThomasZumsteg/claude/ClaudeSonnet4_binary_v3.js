var Binary = function(binString) { 
    this.binString = binString;
};

Binary.prototype.toDecimal = function() {
    if (!/^[01]*$/.test(this.binString)) {
        return 0;
    }
    
    let result = 0;
    let power = 1;
    
    for (let i = this.binString.length - 1; i >= 0; i--) {
        if (this.binString[i] === '1') {
            result += power;
        }
        power <<= 1;
    }
    
    return result;
};

module.exports = Binary;