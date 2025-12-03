export default class RotationalCipher {
  static readonly alphabet: string = 'abcdefghijklmnopqrstuvwxyz';
  static readonly alphabetLength: number = RotationalCipher.alphabet.length;

  static rotate(message: string, key: number): string {
    if (key === 0) {
      return message;
    }

    const rotatedAlphabetLower = RotationalCipher.alphabet.slice(key) + RotationalCipher.alphabet.slice(0, key);
    const rotatedAlphabetUpper = rotatedAlphabetLower.toUpperCase();

    let result = '';
    for (let i = 0; i < message.length; i++) {
      const char = message[i];

      if (char >= 'a' && char <= 'z') {
        result += rotatedAlphabetLower[char.charCodeAt(0) - 'a'.charCodeAt(0)];
      } else if (char >= 'A' && char <= 'Z') {
        result += rotatedAlphabetUpper[char.charCodeAt(0) - 'A'.charCodeAt(0)];
      } else {
        result += char;
      }
    }

    return result;
  }
}