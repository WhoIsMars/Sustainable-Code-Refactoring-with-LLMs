export default class Triangle {
  private _sides: number[];

  constructor(...sides: number[]) {
    this._sides = sides;
  }

  public kind(): string {
    const [a, b, c] = this._sides;

    if (this._sides.length !== 3 || a <= 0 || b <= 0 || c <= 0 || a + b <= c || a + c <= b || b + c <= a) {
      throw 'Impossible triangle';
    }

    if (a === b) {
      if (b === c) {
        return 'equilateral';
      } else {
        return 'isosceles';
      }
    } else if (b === c || a === c) {
      return 'isosceles';
    } else {
      return 'scalene';
    }
  }
}