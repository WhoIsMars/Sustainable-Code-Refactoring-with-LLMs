export default class Triangle {
  private _sides: number[];

  constructor(...sides: number[]) {
    this._sides = sides.sort((a, b) => a - b);
  }

  public kind(): string {
    const [a, b, c] = this._sides;

    if (this._sides.length !== 3 || a <= 0 || a + b <= c) {
      throw 'Impossible triangle';
    }

    if (a === c) {
      return 'equilateral';
    }

    if (a === b || b === c) {
      return 'isosceles';
    }

    return 'scalene';
  }
}