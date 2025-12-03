export default class Grains {
  private static readonly TOTAL_GRAINS = 18446744073709551615n;

  public static square(digit: number): number {
    if (digit <= 0 || digit > 64 || !Number.isInteger(digit)) {
      throw 'Chessboard location must be integer from 1 to 64.';
    }
    return Math.pow(2, digit - 1);
  }

  public static total(): number {
    return Number(Grains.TOTAL_GRAINS);
  }
}