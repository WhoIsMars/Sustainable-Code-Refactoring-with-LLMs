export default class PerfectNumbers {
  static classify(num: number): string {
    if (num < 1 || num % 1 !== 0) {
      throw 'Classification is only possible for natural numbers.';
    }

    let aliquotSum = 1;

    if (num > 1) {
      const limit = Math.sqrt(num);
      for (let i = 2; i <= limit; i++) {
        if (num % i === 0) {
          aliquotSum += i;
          if (i !== num / i) {
            aliquotSum += num / i;
          }
        }
      }
    }

    if (aliquotSum === num) {
      return 'perfect';
    }

    return aliquotSum < num ? 'deficient' : 'abundant';
  }
}