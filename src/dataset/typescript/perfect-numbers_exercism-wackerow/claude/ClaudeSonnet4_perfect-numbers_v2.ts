export default class PerfectNumbers {
  static classify(num: number): string {
    if (num < 1 || num % 1 !== 0) { throw 'Classification is only possible for natural numbers.'}
    
    if (num === 1) return 'deficient';
    
    let aliquotSum = 1; // 1 is always a divisor
    const sqrt = Math.sqrt(num);
    
    for (let i = 2; i <= sqrt; i++) {
      if (num % i === 0) {
        aliquotSum += i;
        if (i !== sqrt) {
          aliquotSum += num / i;
        }
      }
    }
    
    if (aliquotSum === num) return 'perfect';
    return aliquotSum < num ? 'deficient' : 'abundant';
  }
}