export default class PerfectNumbers {
  public static readonly PERFECT = 'perfect';
  public static readonly ABUNDANT = 'abundant';
  public static readonly DEFICIENT = 'deficient';

  public static getSumOfFactors(int: number): number {
    if (int === 1) return 0;
    let sum = 1;
    const sqrt = Math.sqrt(int);
    for (let i = 2; i <= sqrt; i++) {
      if (int % i === 0) {
        sum += i;
        const pair = int / i;
        if (i !== pair) sum += pair;
      }
    }
    return sum;
  }

  public static classify(int: number): string {
    if (int < 1) {
      throw new Error('Classification is only possible for natural numbers.');
    }
    const sum = PerfectNumbers.getSumOfFactors(int);
    return sum === int
      ? PerfectNumbers.PERFECT
      : sum > int
      ? PerfectNumbers.ABUNDANT
      : PerfectNumbers.DEFICIENT;
  }
}