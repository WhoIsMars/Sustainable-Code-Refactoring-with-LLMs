export default class PerfectNumbers {
  static classify(num: number): string {
    if (num <= 0 || !Number.isInteger(num)) {
      throw 'Classification is only possible for natural numbers.';
    }

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