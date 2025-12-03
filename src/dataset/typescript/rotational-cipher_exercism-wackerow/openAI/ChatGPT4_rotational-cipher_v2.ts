export default class RotationalCipher {
  private static readonly _abc = 'abcdefghijklmnopqrstuvwxyz';
  private static readonly _ABC = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
  private static readonly _abcLength = RotationalCipher._abc.length;
  private static readonly _ABCLength = RotationalCipher._ABC.length;

  public static rotate(message: string, key: number): string {
    const keyModABC = key % this._abcLength;
    const keyModABCUpper = key % this._ABCLength;

    return Array.from(message, (char) => {
      const lowerIndex = this._abc.indexOf(char);
      if (lowerIndex !== -1) {
        return this._abc[(lowerIndex + keyModABC) % this._abcLength];
      }

      const upperIndex = this._ABC.indexOf(char);
      if (upperIndex !== -1) {
        return this._ABC[(upperIndex + keyModABCUpper) % this._ABCLength];
      }

      return char;
    }).join('');
  }
}