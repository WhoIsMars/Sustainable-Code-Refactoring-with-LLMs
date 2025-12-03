export default class RotationalCipher {
  static readonly alphabet: string = 'abcdefghijklmnopqrstuvwxyz';
  static readonly alphabetLength: number = RotationalCipher.alphabet.length;

  static rotate(message: string, key: number): string {
    if (key === 0) {
      return message;
    }

    const rotatedAlphabet = RotationalCipher.alphabet;
    const rotatedAlphabetLength = RotationalCipher.alphabetLength;
    const normalizedKey = key % rotatedAlphabetLength;

    let result = '';
    for (let i = 0; i < message.length; i++) {
      const char = message[i];
      const charCode = char.charCodeAt(0);

      if (charCode >= 65 && charCode <= 90) {
        const baseCharCode = 65;
        const charIndex = charCode - baseCharCode;
        const newCharIndex = (charIndex + normalizedKey) % rotatedAlphabetLength;
        result += String.fromCharCode(baseCharCode + newCharIndex);
      } else if (charCode >= 97 && charCode <= 122) {
        const baseCharCode = 97;
        const charIndex = charCode - baseCharCode;
        const newCharIndex = (charIndex + normalizedKey) % rotatedAlphabetLength;
        result += String.fromCharCode(baseCharCode + newCharIndex);
      } else {
        result += char;
      }
    }

    return result;
  }
}