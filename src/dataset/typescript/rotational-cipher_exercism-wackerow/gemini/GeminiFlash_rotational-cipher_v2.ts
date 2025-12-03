export default class RotationalCipher {
  private static readonly LOWERCASE = 'abcdefghijklmnopqrstuvwxyz';
  private static readonly UPPERCASE = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
  private static readonly LOWERCASE_LENGTH = RotationalCipher.LOWERCASE.length;
  private static readonly UPPERCASE_LENGTH = RotationalCipher.UPPERCASE.length;

  public static rotate(message: string, key: number): string {
    let encrypted = '';
    for (let i = 0; i < message.length; i++) {
      const char = message[i];
      const charCode = char.charCodeAt(0);

      if (charCode >= 97 && charCode <= 122) { // lowercase
        encrypted += RotationalCipher.LOWERCASE[(charCode - 97 + key) % RotationalCipher.LOWERCASE_LENGTH];
      } else if (charCode >= 65 && charCode <= 90) { // uppercase
        encrypted += RotationalCipher.UPPERCASE[(charCode - 65 + key) % RotationalCipher.UPPERCASE_LENGTH];
      } else {
        encrypted += char;
      }
    }
    return encrypted;
  }
}