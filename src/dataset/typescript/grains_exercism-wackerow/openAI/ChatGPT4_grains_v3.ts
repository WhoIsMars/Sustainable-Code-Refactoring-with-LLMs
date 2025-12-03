export default class Grains {
  private static readonly MAX_SQUARES = 64;
  private static readonly TOTAL_GRAINS = BigInt(2 ** Grains.MAX_SQUARES - 1);

  public static square(digit: number): number {
    if (!Number.isInteger(digit) || digit <= 0 || digit > Grains.MAX_SQUARES) {
      throw 'Chessboard location must be integer from 1 to 64.';
    }
    return 1 << (digit - 1);
  }

  public static total(): bigint {
    return Grains.TOTAL_GRAINS;
  }
}