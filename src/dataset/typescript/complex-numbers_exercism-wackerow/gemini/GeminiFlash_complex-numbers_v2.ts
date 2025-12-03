export default class ComplexNumber {
  constructor(private _real: number, private _imag: number) {}

  get real(): number {
    return this._real;
  }

  get imag(): number {
    return this._imag;
  }

  get abs(): number {
    const real = this._real;
    const imag = this._imag;
    return Math.sqrt(real * real + imag * imag);
  }

  get conj(): ComplexNumber {
    return new ComplexNumber(this._real, -this._imag);
  }

  get exp(): ComplexNumber {
    const realExp = Math.exp(this._real);
    const cosImag = Math.cos(this._imag);
    const sinImag = Math.sin(this._imag);
    return new ComplexNumber(realExp * cosImag, realExp * sinImag);
  }

  public add(that: ComplexNumber): ComplexNumber {
    return new ComplexNumber(this._real + that._real, this._imag + that._imag);
  }

  public sub(that: ComplexNumber): ComplexNumber {
    return new ComplexNumber(this._real - that._real, this._imag - that._imag);
  }

  public mul(that: ComplexNumber): ComplexNumber {
    const real1 = this._real;
    const imag1 = this._imag;
    const real2 = that._real;
    const imag2 = that._imag;
    return new ComplexNumber(
      real1 * real2 - imag1 * imag2,
      imag1 * real2 + real1 * imag2
    );
  }

  public div(that: ComplexNumber): ComplexNumber {
    const real1 = this._real;
    const imag1 = this._imag;
    const real2 = that._real;
    const imag2 = that._imag;
    const denominator = real2 * real2 + imag2 * imag2;

    return new ComplexNumber(
      (real1 * real2 + imag1 * imag2) / denominator,
      (imag1 * real2 - real1 * imag2) / denominator
    );
  }
}