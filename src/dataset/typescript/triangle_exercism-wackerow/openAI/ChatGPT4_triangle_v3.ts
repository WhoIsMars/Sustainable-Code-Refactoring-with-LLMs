export default class Triangle {
  private _sides: number[];

  constructor(...sides: number[]) {
    this._sides = sides;
    if (
      sides.length !== 3 ||
      sides.some(side => side <= 0) ||
      sides[0] + sides[1] <= sides[2] ||
      sides[1] + sides[2] <= sides[0] ||
      sides[2] + sides[0] <= sides[1]
    ) {
      throw 'Impossible triangle';
    }
  }

  public kind(): string {
    const [a, b, c] = this._sides;
    if (a === b && b === c) return 'equilateral';
    if (a === b || b === c || c === a) return 'isosceles';
    return 'scalene';
  }
}