export default class PerfectNumbers {
  public static readonly PERFECT = 'perfect';
  public static readonly ABUNDANT = 'abundant';
  public static readonly DEFICIENT = 'deficient';

  public static getSumOfFactors(int: number): number {
    let sum = 1;
    if (int <= 1) return 0;

    for (let i = 2; i <= Math.sqrt(int); i++) {
      if (int % i === 0) {
        sum += i;
        if (i * i !== int) {
          sum += int / i;
        }
      }
    }
    return sum;
  }

  public static classify(int: number): string {
    if (int < 1) {
      throw new Error('Classification is only possible for natural numbers.');
    }

    const sum = PerfectNumbers.getSumOfFactors(int);

    if (sum === int) {
      return PerfectNumbers.PERFECT;
    } else if (sum > int) {
      return PerfectNumbers.ABUNDANT;
    } else {
      return PerfectNumbers.DEFICIENT;
    }
  }
}