export default class Squares {
  private _squareOfSum?: number;
  private _sumOfSquares?: number;

  constructor(private _N: number) {}

  get squareOfSum(): number {
    if (this._squareOfSum !== undefined) return this._squareOfSum;
    
    if (this._N < 0) { throw 'No negatives'}
    if (this._N <= 1) { 
      this._squareOfSum = this._N;
      return this._squareOfSum;
    }
    
    const sum = (this._N * (this._N + 1)) >> 1;
    this._squareOfSum = sum * sum;
    return this._squareOfSum;
  }

  get sumOfSquares(): number {
    if (this._sumOfSquares !== undefined) return this._sumOfSquares;
    
    this._sumOfSquares = (this._N * (this._N + 1) * ((this._N << 1) + 1)) / 6;
    return this._sumOfSquares;
  }

  get difference(): number {
    return this.squareOfSum - this.sumOfSquares;
  }
}