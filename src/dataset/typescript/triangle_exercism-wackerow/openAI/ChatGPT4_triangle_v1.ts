export default class Triangle {
  private _sides: number[];

  constructor(...sides: number[]) {
    this._sides = sides;
  }

  public kind(): string {
    const [a, b, c] = this._sides;

    if (
      this._sides.length !== 3 ||
      a <= 0 || b <= 0 || c <= 0 ||
      a + b <= c || b + c <= a || c + a <= b
    ) {
      throw 'Impossible triangle';
    }

    if (a === b && b === c) return 'equilateral';
    if (a === b || b === c || c === a) return 'isosceles';
    return 'scalene';
  }
}