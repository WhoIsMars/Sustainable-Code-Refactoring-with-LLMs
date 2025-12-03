export default class Triangle {
  constructor(s1, s2, s3) {
    this.s1 = s1;
    this.s2 = s2;
    this.s3 = s3;
  }
  
  kind() {
    const { s1, s2, s3 } = this;
    
    if (s1 <= 0 || s2 <= 0 || s3 <= 0) {
      throw new Error();
    }
    
    if (s1 + s2 <= s3 || s2 + s3 <= s1 || s3 + s1 <= s2) {
      throw new Error();
    }
    
    const equalSides = (s1 === s2) + (s1 === s3) + (s2 === s3);
    
    if (equalSides === 3) return 'equilateral';
    if (equalSides === 1) return 'isosceles';
    return 'scalene';
  }
}