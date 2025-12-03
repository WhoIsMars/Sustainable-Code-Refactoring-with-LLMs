export default class ComplexNumber {
  private readonly _abs: number;
  private readonly _conj: ComplexNumber;
  private readonly _exp: ComplexNumber;

  constructor(private readonly _real: number, private readonly _imag: number) {
    this._abs = Math.hypot(_real, _imag);
    this._conj = new ComplexNumber(_real, -_imag);
    const expReal = Math.exp(_real);
    this._exp = new ComplexNumber(expReal * Math.cos(_imag), expReal * Math.sin(_imag));
  }

  get real(): number {
    return this._real;
  }

  get imag(): number {
    return this._imag;
  }

  get abs(): number {
    return this._abs;
  }

  get conj(): ComplexNumber {
    return this._conj;
  }

  get exp(): ComplexNumber {
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
    const denom = that._real * that._real + that._imag * that._imag;
    const real = (this._real * that._real + this._imag * that._imag) / denom;
    const imag = (this._imag * that._real - this._real * that._imag) / denom;
    return new ComplexNumber(real, imag);
  }
}