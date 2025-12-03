export default class RotationalCipher {
  static readonly alphabet = 'abcdefghijklmnopqrstuvwxyz';
  static readonly alphabetLength = RotationalCipher.alphabet.length;
  static readonly charCodeA = 'a'.charCodeAt(0);
  static readonly charCodeZ = 'z'.charCodeAt(0);
  static readonly charCodeUpperA = 'A'.charCodeAt(0);
  static readonly charCodeUpperZ = 'Z'.charCodeAt(0);

  static rotate(message: string, key: number): string {
    const shift = key % this.alphabetLength;

    return Array.from(message, char => {
      const charCode = char.charCodeAt(0);

      if (charCode >= this.charCodeA && charCode <= this.charCodeZ) {
        return String.fromCharCode(
          ((charCode - this.charCodeA + shift) % this.alphabetLength) + this.charCodeA
        );
      }

      if (charCode >= this.charCodeUpperA && charCode <= this.charCodeUpperZ) {
        return String.fromCharCode(
          ((charCode - this.charCodeUpperA + shift) % this.alphabetLength) + this.charCodeUpperA
        );
      }

      return char;
    }).join('');
  }
}