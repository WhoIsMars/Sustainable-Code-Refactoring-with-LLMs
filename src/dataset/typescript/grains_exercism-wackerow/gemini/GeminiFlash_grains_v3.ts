export default class Grains {
  public static square(digit: number): bigint {
    if (digit <= 0 || digit > 64 || digit % 1 !== 0) {
      throw 'Chessboard location must be integer from 1 to 64.';
    }
    return 1n << (BigInt(digit) - 1n);
  }

  public static total(): bigint {
    return (1n << 64n) - 1n;
  }
}