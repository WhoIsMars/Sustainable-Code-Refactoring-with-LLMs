class Octal {
    constructor(oct) {
        this.oct = oct;
    }

    toDecimal() {
        if (/[^0-7]/.test(this.oct)) return 0;
        return [...this.oct].reduce((total, elem, i) => 
            total * 8 + Number(elem), 0);
    }
}

module.exports = Octal;