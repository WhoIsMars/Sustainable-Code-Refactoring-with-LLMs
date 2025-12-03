export default class PerfectNumbers {
  static classify(num: number): string {
    if (num < 1 || num % 1 !== 0) { throw 'Classification is only possible for natural numbers.'}
    if (num === 1) { return 'deficient'; }

    let aliquotSum = 1;
    const limit = Math.sqrt(num);

    for (let i = 2; i <= limit; i++) {
      if (num % i === 0) {
        aliquotSum += i;
        if (i !== num / i) {
          aliquotSum += num / i;
        }
      }
    }

    if (aliquotSum === num) {
      return 'perfect';
    } else if (aliquotSum < num) {
      return 'deficient';
    } else {
      return 'abundant';
    }
  }
}