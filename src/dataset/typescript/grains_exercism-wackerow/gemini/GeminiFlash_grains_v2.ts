export default class Grains {
  private static readonly TWO_POW_64 = BigInt("18446744073709551615");

  public static square(digit: number): bigint {
    if (digit <= 0 || digit > 64 || digit % 1 !== 0) {
      throw 'Chessboard location must be integer from 1 to 64.';
    }
    return BigInt(1) << BigInt(digit - 1);
  }

  public static total(): bigint {
    return Grains.TWO_POW_64;
  }
}