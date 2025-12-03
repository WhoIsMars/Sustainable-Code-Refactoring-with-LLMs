export default class RotationalCipher {
  private static readonly _abc = 'abcdefghijklmnopqrstuvwxyz';
  private static readonly _ABC = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
  private static readonly _abcMap = new Map(
    Array.from(RotationalCipher._abc, (char, i) => [char, i])
  );
  private static readonly _ABCMap = new Map(
    Array.from(RotationalCipher._ABC, (char, i) => [char, i])
  );

  public static rotate(message: string, key: number): string {
    const abcLength = this._abc.length;
    const ABCLength = this._ABC.length;
    return Array.from(message, (letter) => {
      if (this._abcMap.has(letter)) {
        return this._abc[(this._abcMap.get(letter)! + key) % abcLength];
      }
      if (this._ABCMap.has(letter)) {
        return this._ABC[(this._ABCMap.get(letter)! + key) % ABCLength];
      }
      return letter;
    }).join('');
  }
}