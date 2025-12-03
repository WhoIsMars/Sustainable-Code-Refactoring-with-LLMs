class ComplexNumber {
    constructor(real, imag) {
        this.real = real;
        this.imag = imag;
    }

    add(other) {
        return new ComplexNumber(this.real + other.real, this.imag + other.imag);
    }

    sub(other) {
        return new ComplexNumber(this.real - other.real, this.imag - other.imag);
    }

    mul(other) {
        const real = this.real * other.real - this.imag * other.imag;
        const imag = this.real * other.imag + this.imag * other.real;
        return new ComplexNumber(real, imag);
    }

    div(other) {
        const otherReal = other.real;
        const otherImag = other.imag;
        const denom = otherReal * otherReal + otherImag * otherImag;

        if (denom === 0) {
            return new ComplexNumber(NaN, NaN);
        }

        const realNum = this.real * otherReal + this.imag * otherImag;
        const imagNum = otherReal * this.imag - otherImag * this.real;
        return new ComplexNumber(realNum / denom, imagNum / denom);
    }

    get abs() {
        const real = this.real;
        const imag = this.imag;
        return Math.sqrt(real * real + imag * imag);
    }

    get conj() {
        return new ComplexNumber(this.real, -this.imag);
    }

    get exp() {
        const expReal = Math.exp(this.real);
        return new ComplexNumber(
            expReal * Math.cos(this.imag),
            expReal * Math.sin(this.imag)
        );
    }
}

module.exports = ComplexNumber;