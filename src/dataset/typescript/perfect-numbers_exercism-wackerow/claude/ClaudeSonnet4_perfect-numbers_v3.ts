export default class PerfectNumbers {
  static classify(num: number): string {
    if (num < 1 || num % 1 !== 0) { throw 'Classification is only possible for natural numbers.'}
    
    let aliquotSum = 1;
    const sqrtNum = Math.sqrt(num);
    
    for (let i = 2; i <= sqrtNum; i++) {
      if (num % i === 0) {
        aliquotSum += i;
        if (i !== sqrtNum) {
          aliquotSum += num / i;
        }
      }
    }
    
    if (num === 1) aliquotSum = 0;
    
    if (aliquotSum === num) return 'perfect';
    return aliquotSum < num ? 'deficient' : 'abundant';
  }
}