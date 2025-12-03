export default class Squares {
  constructor(private _N: number) {}

  get squareOfSum(): number {
    if (this._N < 0) { throw 'No negatives'}
    if (this._N <= 1) { return this._N }
    const sum = (this._N * (this._N + 1)) >> 1;
    return sum * sum;
  }

  get sumOfSquares(): number {
    if (this._N < 0) { return 0 }
    if (this._N <= 1) { return this._N }
    return (this._N * (this._N + 1) * ((this._N << 1) + 1)) / 6;
  }

  get difference(): number {
    return this.squareOfSum - this.sumOfSquares;
  }
}