export default class Squares {
  constructor(private _N: number) {}

  get squareOfSum(): number {
    if (this._N < 0) throw 'No negatives';
    const sum = (this._N * (this._N + 1)) / 2;
    return sum ** 2;
  }

  get sumOfSquares(): number {
    if (this._N < 0) throw 'No negatives';
    return (this._N * (this._N + 1) * (2 * this._N + 1)) / 6;
  }

  get difference(): number {
    return this.squareOfSum - this.sumOfSquares;
  }
}