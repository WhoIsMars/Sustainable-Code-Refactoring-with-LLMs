export default class ComplexNumber {
  private readonly realValue: number;
  private readonly imagValue: number;

  constructor(real: number, imag: number) {
    this.realValue = real;
    this.imagValue = imag;
  }

  get real(): number {
    return this.realValue;
  }

  get imag(): number {
    return this.imagValue;
  }

  get abs(): number {
    const real = this.realValue;
    const imag = this.imagValue;
    return Math.hypot(real, imag);
  }

  get conj(): ComplexNumber {
    return new ComplexNumber(this.realValue, -this.imagValue);
  }

  get exp(): ComplexNumber {
    const expReal = Math.exp(this.realValue);
    const cosImag = Math.cos(this.imagValue);
    const sinImag = Math.sin(this.imagValue);

    return new ComplexNumber(
      expReal * cosImag,
      expReal * sinImag
    );
  }

  public add(that: ComplexNumber): ComplexNumber {
    return new ComplexNumber(
      this.realValue + that.realValue,
      this.imagValue + that.imagValue
    );
  }

  public sub(that: ComplexNumber): ComplexNumber {
    return new ComplexNumber(
      this.realValue - that.realValue,
      this.imagValue - that.imagValue
    );
  }

  public mul(that: ComplexNumber): ComplexNumber {
    const real1 = this.realValue;
    const imag1 = this.imagValue;
    const real2 = that.realValue;
    const imag2 = that.imagValue;

    return new ComplexNumber(
      real1 * real2 - imag1 * imag2,
      imag1 * real2 + real1 * imag2
    );
  }

  public div(that: ComplexNumber): ComplexNumber {
    const real1 = this.realValue;
    const imag1 = this.imagValue;
    const real2 = that.realValue;
    const imag2 = that.imagValue;

    const denominator = real2 * real2 + imag2 * imag2;

    return new ComplexNumber(
      (real1 * real2 + imag1 * imag2) / denominator,
      (imag1 * real2 - real1 * imag2) / denominator
    );
  }
}