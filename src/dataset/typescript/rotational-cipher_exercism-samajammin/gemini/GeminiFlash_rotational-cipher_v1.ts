export default class RotationalCipher {
  static readonly alphabet: string = 'abcdefghijklmnopqrstuvwxyz';
  static readonly alphabetLength: number = RotationalCipher.alphabet.length;

  static rotate(message: string, key: number): string {
    const rotatedChars: string[] = [];
    const normalizedKey = key % RotationalCipher.alphabetLength;

    for (let i = 0; i < message.length; i++) {
      const char = message[i];
      const charCode = char.charCodeAt(0);

      if (charCode >= 65 && charCode <= 90) { // A-Z
        const rotatedCharCode = ((charCode - 65 + normalizedKey) % RotationalCipher.alphabetLength) + 65;
        rotatedChars.push(String.fromCharCode(rotatedCharCode));
      } else if (charCode >= 97 && charCode <= 122) { // a-z
        const rotatedCharCode = ((charCode - 97 + normalizedKey) % RotationalCipher.alphabetLength) + 97;
        rotatedChars.push(String.fromCharCode(rotatedCharCode));
      } else {
        rotatedChars.push(char);
      }
    }

    return rotatedChars.join('');
  }
}