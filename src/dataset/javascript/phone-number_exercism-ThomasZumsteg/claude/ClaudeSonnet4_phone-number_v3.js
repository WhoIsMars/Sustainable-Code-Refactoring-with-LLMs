const PhoneNumber = function(phoneNumber) {
    const digits = phoneNumber.replace(/\D/g, '');
    
    if (digits.length === 10 || (digits.length === 11 && digits[0] === '1')) {
        const start = digits.length === 11 ? 1 : 0;
        this.area = digits.slice(start, start + 3);
        this.first = digits.slice(start + 3, start + 6);
        this.second = digits.slice(start + 6, start + 10);
        this.num = this.area + this.first + this.second;
    } else {
        this.num = '0000000000';
        this.area = '000';
        this.first = '000';
        this.second = '0000';
    }
};

PhoneNumber.prototype.number = function() { 
    return this.num;
};

PhoneNumber.prototype.areaCode = function() { 
    return this.area;
};

PhoneNumber.prototype.toString = function() { 
    return `(${this.area}) ${this.first}-${this.second}`;
};

module.exports = PhoneNumber;