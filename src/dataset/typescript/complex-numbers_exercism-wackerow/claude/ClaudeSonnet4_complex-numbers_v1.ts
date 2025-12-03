export default class ComplexNumber {
  constructor(private _real: number, private _imag: number) {}

  get real(): number {
    return this._real;
  }

  get imag(): number {
    return this._imag;
  }
  
  get abs(): number {
    return Math.sqrt(this._real * this._real + this._imag * this._imag);
  }

  get conj(): ComplexNumber {
    return new ComplexNumber(this._real, -this._imag);
  }

  get exp(): ComplexNumber {
    const expReal = Math.exp(this._real);
    return new ComplexNumber(
      expReal * Math.cos(this._imag),
      expReal * Math.sin(this._imag)
    );
  }

  public add(that: ComplexNumber): ComplexNumber {
    return new ComplexNumber(
      this._real + that._real,
      this._imag + that._imag
    );
  }

  public sub(that: ComplexNumber): ComplexNumber {
    return new ComplexNumber(
      this._real - that._real,
      this._imag - that._imag
    );
  }

  public mul(that: ComplexNumber): ComplexNumber {
    return new ComplexNumber(
      this._real * that._real - this._imag * that._imag,
      this._imag * that._real + this._real * that._imag
    );
  }

  public div(that: ComplexNumber): ComplexNumber {
    const denominator = that._real * that._real + that._imag * that._imag;
    return new ComplexNumber(
      (this._real * that._real + this._imag * that._imag) / denominator,
      (this._imag * that._real - this._real * that._imag) / denominator
    );
  }
}