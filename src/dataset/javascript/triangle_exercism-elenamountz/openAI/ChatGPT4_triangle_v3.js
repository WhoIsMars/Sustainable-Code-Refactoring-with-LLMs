export default class Triangle {
  constructor(s1, s2, s3) {
    if (s1 <= 0 || s2 <= 0 || s3 <= 0 || s1 + s2 <= s3 || s2 + s3 <= s1 || s3 + s1 <= s2) {
      throw new Error();
    }
    this.sides = [s1, s2, s3];
  }

  kind() {
    const [s1, s2, s3] = this.sides;
    if (s1 === s2 && s2 === s3) return 'equilateral';
    if (s1 === s2 || s2 === s3 || s1 === s3) return 'isosceles';
    return 'scalene';
  }
}