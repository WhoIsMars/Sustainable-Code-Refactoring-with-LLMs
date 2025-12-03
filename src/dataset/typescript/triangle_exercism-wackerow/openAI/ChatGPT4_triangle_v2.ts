export default class Triangle {
  private _sides: number[];

  constructor(...sides: number[]) {
    this._sides = sides.sort((a, b) => a - b);
    if (
      this._sides.length !== 3 ||
      this._sides[0] <= 0 ||
      this._sides[0] + this._sides[1] <= this._sides[2]
    ) {
      throw 'Impossible triangle';
    }
  }

  public kind(): string {
    const [a, b, c] = this._sides;
    if (a === c) return 'equilateral';
    if (a === b || b === c) return 'isosceles';
    return 'scalene';
  }
}