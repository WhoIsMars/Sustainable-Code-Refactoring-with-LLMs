class SimpleCipher {
  private static readonly abc: string = 'abcdefghijklmnopqrstuvwxyz';
  public key: string;

  constructor(_key?: string) {
    this.key = _key || this.generateKey();
  }

  private generateKey(): string {
    let key = '';
    const abcLength = SimpleCipher.abc.length;
    for (let i = 0; i < 128; i++) {
      key += SimpleCipher.abc[Math.floor(Math.random() * abcLength)];
    }
    return key;
  }

  encode(message: string): string {
    let encryptedMessage = '';
    const keyLength = this.key.length;
    for (let i = 0; i < message.length; i++) {
      const char = message[i];
      if (SimpleCipher.abc.indexOf(char) === -1) {
          continue;
      }
      const adjustment = SimpleCipher.abc.indexOf(char);
      const keyAdjustment = SimpleCipher.abc.indexOf(this.key[i % keyLength]);
      encryptedMessage += SimpleCipher.abc[(adjustment + keyAdjustment) % SimpleCipher.abc.length];
    }
    return encryptedMessage;
  }

  decode(encryptedMessage: string): string {
    let decryptedMessage = '';
    const keyLength = this.key.length;
    for (let i = 0; i < encryptedMessage.length; i++) {
      const char = encryptedMessage[i];
      if (SimpleCipher.abc.indexOf(char) === -1) {
          continue;
      }
      const adjustment = SimpleCipher.abc.indexOf(char);
      const keyAdjustment = SimpleCipher.abc.indexOf(this.key[i % keyLength]);
      decryptedMessage += SimpleCipher.abc[((adjustment - keyAdjustment) + SimpleCipher.abc.length) % SimpleCipher.abc.length];
    }
    return decryptedMessage;
  }
}

export default SimpleCipher;