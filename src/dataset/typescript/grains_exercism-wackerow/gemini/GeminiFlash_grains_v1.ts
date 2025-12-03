export default class Grains {
  public static square(digit: number): number {
    if (digit <= 0 || digit > 64 || !Number.isInteger(digit)) {
      throw 'Chessboard location must be integer from 1 to 64.';
    }
    return 2 ** (digit - 1);
  }

  public static total(): bigint {
    return 2n ** 64n - 1n;
  }
}