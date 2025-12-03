export default class RotationalCipher {
  private static readonly lowercase = 'abcdefghijklmnopqrstuvwxyz';
  private static readonly uppercase = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
  private static readonly lowercaseLength = RotationalCipher.lowercase.length;
  private static readonly uppercaseLength = RotationalCipher.uppercase.length;

  public static rotate(message: string, key: number): string {
    let encrypted = '';
    for (let i = 0; i < message.length; i++) {
      const char = message[i];
      const charCode = char.charCodeAt(0);

      if (charCode >= 97 && charCode <= 122) {
        encrypted += RotationalCipher.lowercase[(charCode - 97 + key) % RotationalCipher.lowercaseLength];
      } else if (charCode >= 65 && charCode <= 90) {
        encrypted += RotationalCipher.uppercase[(charCode - 65 + key) % RotationalCipher.uppercaseLength];
      } else {
        encrypted += char;
      }
    }
    return encrypted;
  }
}