export default class Triangle {
  private readonly _a: number;
  private readonly _b: number;
  private readonly _c: number;

  constructor(...sides: number[]) {
    if (sides.length !== 3) {
      throw 'Impossible triangle';
    }
    this._a = sides[0];
    this._b = sides[1];
    this._c = sides[2];
  }

  public kind(): string {
    const a = this._a;
    const b = this._b;
    const c = this._c;

    if (a <= 0 || b <= 0 || c <= 0 || 
        a + b <= c || b + c <= a || c + a <= b) {
      throw 'Impossible triangle';
    }

    if (a === b && b === c) {
      return 'equilateral';
    }

    if (a === b || b === c || c === a) {
      return 'isosceles';
    }

    return 'scalene';
  }
}