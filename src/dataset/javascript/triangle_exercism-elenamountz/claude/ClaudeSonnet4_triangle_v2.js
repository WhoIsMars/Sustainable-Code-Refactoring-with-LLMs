export default class Triangle{
  constructor(s1, s2, s3){
      this.s1 = s1;
      this.s2 = s2;
      this.s3 = s3;
  }
  kind(){
    const s1 = this.s1;
    const s2 = this.s2;
    const s3 = this.s3;
    
    if(s1 <= 0 || s2 <= 0 || s3 <= 0){
      throw new Error;
    }
    if(s1 + s2 <= s3 || s2 + s3 <= s1 || s3 + s1 <= s2){
      throw new Error;
    }
    
    const s1EqS2 = s1 === s2;
    const s1EqS3 = s1 === s3;
    const s2EqS3 = s2 === s3;
    
    if(s1EqS2 && s1EqS3){
      return 'equilateral';
    } else if(s1EqS2 || s1EqS3 || s2EqS3){
      return 'isosceles';
    } else {
      return 'scalene';
    }
  }
};