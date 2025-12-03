class SimpleCipher {
  private static readonly ABC: string = 'abcdefghijklmnopqrstuvwxyz';
  public key: string;

  constructor(_key?: string) {
    this.key = _key || this.generateKey();
  }

  private generateKey(): string {
    let key = '';
    const abcLength = SimpleCipher.ABC.length;
    for (let i = 0; i < 128; i++) {
      key += SimpleCipher.ABC[Math.floor(Math.random() * abcLength)];
    }
    return key;
  }

  encode(message: string): string {
    return this.processMessage(message, true);
  }

  decode(encryptedMessage: string): string {
    return this.processMessage(encryptedMessage, false);
  }

  private processMessage(message: string, encode: boolean): string {
    let result = '';
    const keyLength = this.key.length;
    const abcLength = SimpleCipher.ABC.length;

    for (let i = 0; i < message.length; i++) {
      const char = message[i];
      const keyChar = this.key[i % keyLength];

      const charIndex = SimpleCipher.ABC.indexOf(char);
      const keyIndex = SimpleCipher.ABC.indexOf(keyChar);

      if (charIndex === -1) {
        continue; // Skip characters not in the alphabet
      }

      let shiftedIndex: number;
      if (encode) {
        shiftedIndex = (charIndex + keyIndex) % abcLength;
      } else {
        shiftedIndex = ((charIndex - keyIndex) % abcLength + abcLength) % abcLength;
      }

      result += SimpleCipher.ABC[shiftedIndex];
    }

    return result;
  }
}

export default SimpleCipher;