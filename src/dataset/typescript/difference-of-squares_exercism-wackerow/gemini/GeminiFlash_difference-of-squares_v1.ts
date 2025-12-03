export default class Squares {
  private readonly _N: number;

  constructor(N: number) {
    this._N = N;
  }

  get squareOfSum(): number {
    if (this._N < 0) {
      throw 'No negatives';
    }
    const n = this._N;
    return ((n * (n + 1)) / 2) ** 2;
  }

  get sumOfSquares(): number {
    const n = this._N;
    return (n * (n + 1) * (2 * n + 1)) / 6;
  }

  get difference(): number {
    return this.squareOfSum - this.sumOfSquares;
  }
}