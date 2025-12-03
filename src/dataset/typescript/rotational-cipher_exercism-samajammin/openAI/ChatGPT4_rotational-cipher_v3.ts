export default class RotationalCipher {
  static readonly alphabet: string = 'abcdefghijklmnopqrstuvwxyz';
  static readonly alphabetLength: number = RotationalCipher.alphabet.length;

  static rotate(message: string, key: number): string {
    const adjustedKey = key % this.alphabetLength;

    return Array.from(message, char => {
      const charCode = char.charCodeAt(0);

      if (char >= 'A' && char <= 'Z') {
        return String.fromCharCode(((charCode - 65 + adjustedKey) % 26) + 65);
      } else if (char >= 'a' && char <= 'z') {
        return String.fromCharCode(((charCode - 97 + adjustedKey) % 26) + 97);
      }

      return char;
    }).join('');
  }
}