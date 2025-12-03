export default class RotationalCipher {
  private static _abc = 'abcdefghijklmnopqrstuvwxyz';
  private static _ABC = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
  private static _abcMap = new Map([...RotationalCipher._abc].map((c, i) => [c, i]));
  private static _ABCMap = new Map([...RotationalCipher._ABC].map((c, i) => [c, i]));

  public static rotate(message: string, key: number): string {
    const abcLength = this._abc.length;
    const ABCLength = this._ABC.length;

    return [...message].map((letter) => {
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