export default class Grains {
  private static readonly TOTAL_GRAINS = 18446744073709551615n; // 2^64 - 1 as BigInt

  public static square(digit: number): number {
    if (digit < 1 || digit > 64 || (digit | 0) !== digit) {
      throw 'Chessboard location must be integer from 1 to 64.';
    }
    return 1 << (digit - 1);
  }

  public static total(): number {
    return Number(Grains.TOTAL_GRAINS);
  }
}