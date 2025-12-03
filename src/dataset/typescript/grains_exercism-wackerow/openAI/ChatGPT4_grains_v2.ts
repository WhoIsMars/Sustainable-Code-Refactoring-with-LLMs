export default class Grains {
  private static readonly MAX_SQUARES = 64;
  private static readonly TOTAL_GRAINS = BigInt(2 ** 64 - 1);

  public static square(digit: number): number {
    if (digit < 1 || digit > this.MAX_SQUARES) {
      throw new Error('Chessboard location must be an integer from 1 to 64.');
    }
    return 1 << (digit - 1);
  }

  public static total(): bigint {
    return this.TOTAL_GRAINS;
  }
}