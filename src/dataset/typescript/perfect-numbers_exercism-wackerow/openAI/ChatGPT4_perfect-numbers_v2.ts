export default class PerfectNumbers {
  static classify(num: number): string {
    if (num < 1 || num % 1 !== 0) {
      throw 'Classification is only possible for natural numbers.';
    }
    let aliquotSum = 1;
    const sqrt = Math.sqrt(num);
    for (let i = 2; i <= sqrt; i++) {
      if (num % i === 0) {
        aliquotSum += i + (i !== num / i ? num / i : 0);
      }
    }
    if (aliquotSum === num) return 'perfect';
    return aliquotSum < num ? 'deficient' : 'abundant';
  }
}