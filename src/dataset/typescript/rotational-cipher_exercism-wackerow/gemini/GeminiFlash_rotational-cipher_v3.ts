export default class RotationalCipher {
  private static readonly _abc = 'abcdefghijklmnopqrstuvwxyz';
  private static readonly _ABC = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
  private static readonly _abcLength = RotationalCipher._abc.length;
  private static readonly _ABCLength = RotationalCipher._ABC.length;

  public static rotate(message: string, key: number): string {
    let encrypted = '';
    for (let i = 0; i < message.length; i++) {
      const char = message[i];
      const abcIndex = this._abc.indexOf(char);
      if (abcIndex >= 0) {
        encrypted += this._abc[(abcIndex + key) % this._abcLength];
        continue;
      }
      const ABCIndex = this._ABC.indexOf(char);
      if (ABCIndex >= 0) {
        encrypted += this._ABC[(ABCIndex + key) % this._ABCLength];
        continue;
      }
      encrypted += char;
    }
    return encrypted;
  }
}