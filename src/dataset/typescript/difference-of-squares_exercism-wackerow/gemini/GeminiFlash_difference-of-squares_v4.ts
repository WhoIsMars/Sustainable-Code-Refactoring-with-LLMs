export default class Squares {
  constructor(private _N: number) {}

  get squareOfSum(): number {
    if (this._N < 0) { throw 'No negatives'}
    const n = this._N;
    const sum = n * (n + 1) / 2;
    return sum * sum;
  }

  get sumOfSquares(): number {
    const n = this._N;
    return n * (n + 1) * (2 * n + 1) / 6;
  }

  get difference(): number {
    return this.squareOfSum - this.sumOfSquares;
  }
}