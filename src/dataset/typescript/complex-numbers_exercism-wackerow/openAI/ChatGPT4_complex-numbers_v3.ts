export default class ComplexNumber {
  constructor(private _real: number, private _imag: number) {}

  get real(): number {
    return this._real;
  }

  get imag(): number {
    return this._imag;
  }

  get abs(): number {
    return Math.hypot(this._real, this._imag);
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

  public add({ _real, _imag }: ComplexNumber): ComplexNumber {
    return new ComplexNumber(this._real + _real, this._imag + _imag);
  }

  public sub({ _real, _imag }: ComplexNumber): ComplexNumber {
    return new ComplexNumber(this._real - _real, this._imag - _imag);
  }

  public mul({ _real, _imag }: ComplexNumber): ComplexNumber {
    return new ComplexNumber(
      this._real * _real - this._imag * _imag,
      this._imag * _real + this._real * _imag
    );
  }

  public div({ _real, _imag }: ComplexNumber): ComplexNumber {
    const denominator = _real * _real + _imag * _imag;
    return new ComplexNumber(
      (this._real * _real + this._imag * _imag) / denominator,
      (this._imag * _real - this._real * _imag) / denominator
    );
  }
}