export default class Grains {
  public static square(digit: number): number {
    if (digit <= 0 || digit > 64 || digit % 1 !== 0) {
      throw 'Chessboard location must be integer from 1 to 64.';
    }
    return Math.pow(2, digit - 1);
  }

  public static total(): number {
    return 18446744073709551615;
  }
}