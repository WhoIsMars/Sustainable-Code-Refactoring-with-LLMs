export default class ComplexNumber {
  private _abs: number | null = null;
  private _conj: ComplexNumber | null = null;
  private _exp: ComplexNumber | null = null;

  constructor(private _real: number, private _imag: number) {}

  get real(): number {
    return this._real;
  }

  get imag(): number {
    return this._imag;
  }

  get abs(): number {
    if (this._abs === null) {
      this._abs = Math.hypot(this._real, this._imag);
    }
    return this._abs;
  }

  get conj(): ComplexNumber {
    if (this._conj === null) {
      this._conj = new ComplexNumber(this._real, -this._imag);
    }
    return this._conj;
  }

  get exp(): ComplexNumber {
    if (this._exp === null) {
      const expReal = Math.exp(this._real);
      this._exp = new ComplexNumber(
        expReal * Math.cos(this._imag),
        expReal * Math.sin(this._imag)
      );
    }
    return this._exp;
  }

  public add(that: ComplexNumber): ComplexNumber {
    return new ComplexNumber(this._real + that._real, this._imag + that._imag);
  }

  public sub(that: ComplexNumber): ComplexNumber {
    return new ComplexNumber(this._real - that._real, this._imag - that._imag);
  }

  public mul(that: ComplexNumber): ComplexNumber {
    const real = this._real * that._real - this._imag * that._imag;
    const imag = this._imag * that._real + this._real * that._imag;
    return new ComplexNumber(real, imag);
  }

  public div(that: ComplexNumber): ComplexNumber {
    const denom = that._real ** 2 + that._imag ** 2;
    const real = (this._real * that._real + this._imag * that._imag) / denom;
    const imag = (this._imag * that._real - this._real * that._imag) / denom;
    return new ComplexNumber(real, imag);
  }
}