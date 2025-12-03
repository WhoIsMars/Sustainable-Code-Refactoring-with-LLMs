export default class RotationalCipher {
  private static readonly alphabet = 'abcdefghijklmnopqrstuvwxyz';
  private static readonly alphabetLength = RotationalCipher.alphabet.length;

  static rotate(message: string, key: number): string {
    const adjustedKey = key % this.alphabetLength;

    return Array.from(message, char => {
      const charCode = char.charCodeAt(0);

      if (char >= 'a' && char <= 'z') {
        return this.alphabet[(charCode - 97 + adjustedKey) % this.alphabetLength];
      } else if (char >= 'A' && char <= 'Z') {
        return this.alphabet[(charCode - 65 + adjustedKey) % this.alphabetLength].toUpperCase();
      }

      return char;
    }).join('');
  }
}