export default class Triangle {
  constructor(s1, s2, s3) {
    this.sides = [s1, s2, s3].sort((a, b) => a - b);
    if (this.sides.some(side => side <= 0) || this.sides[0] + this.sides[1] <= this.sides[2]) {
      throw new Error();
    }
  }

  kind() {
    const [a, b, c] = this.sides;
    if (a === c) return 'equilateral';
    if (a === b || b === c) return 'isosceles';
    return 'scalene';
  }
}