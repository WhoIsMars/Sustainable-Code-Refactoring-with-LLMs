export default class Squares {
  private _N: number;
  private _squareOfSum?: number;
  private _sumOfSquares?: number;

  constructor(N: number) {
    this._N = N;
  }

  get squareOfSum(): number {
    if (this._N < 0) {
      throw 'No negatives';
    }

    if (this._squareOfSum !== undefined) {
      return this._squareOfSum;
    }

    const n = this._N;
    this._squareOfSum = ((n * (n + 1)) / 2) ** 2;
    return this._squareOfSum;
  }

  get sumOfSquares(): number {
    if (this._sumOfSquares !== undefined) {
      return this._sumOfSquares;
    }

    const n = this._N;
    this._sumOfSquares = (n * (n + 1) * (2 * n + 1)) / 6;
    return this._sumOfSquares;
  }

  get difference(): number {
    return this.squareOfSum - this.sumOfSquares;
  }
}