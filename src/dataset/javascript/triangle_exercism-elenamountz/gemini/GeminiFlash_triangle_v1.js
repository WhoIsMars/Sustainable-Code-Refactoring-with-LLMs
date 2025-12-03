export default class Triangle {
  constructor(s1, s2, s3) {
    this.s1 = s1;
    this.s2 = s2;
    this.s3 = s3;
  }

  kind() {
    const { s1, s2, s3 } = this;

    if (s1 <= 0 || s2 <= 0 || s3 <= 0) {
      throw new Error("Sides must be positive.");
    }

    if (s1 + s2 <= s3 || s2 + s3 <= s1 || s3 + s1 <= s2) {
      throw new Error("Invalid triangle.");
    }

    if (s1 === s2) {
      if (s1 === s3) {
        return 'equilateral';
      } else {
        return 'isosceles';
      }
    } else if (s1 === s3 || s2 === s3) {
      return 'isosceles';
    } else {
      return 'scalene';
    }
  }
}