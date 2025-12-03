export default class PerfectNumbers {
  public static readonly PERFECT = 'perfect';
  public static readonly ABUNDANT = 'abundant';
  public static readonly DEFICIENT = 'deficient';

  private static getSumOfFactors(int: number): number {
    if (int === 1) return 0;
    let sum = 1; // 1 is always a factor
    const sqrt = Math.sqrt(int);
    for (let i = 2; i <= sqrt; i++) {
      if (int % i === 0) {
        sum += i;
        const complement = int / i;
        if (complement !== i) {
          sum += complement;
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
    if (sum === int) return PerfectNumbers.PERFECT;
    if (sum > int) return PerfectNumbers.ABUNDANT;
    return PerfectNumbers.DEFICIENT;
  }
}