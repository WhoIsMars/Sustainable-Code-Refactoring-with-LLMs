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
    let encryptedMessage = '';
    const keyLength = this.key.length;
    for (let i = 0; i < message.length; i++) {
      const char = message[i].toLowerCase();
      const adjustment = SimpleCipher.ABC.indexOf(char);
      if (adjustment === -1) {
        encryptedMessage += char;
        continue;
      }
      const keyAdjustment = SimpleCipher.ABC.indexOf(this.key[i % keyLength]);
      encryptedMessage += SimpleCipher.ABC[(adjustment + keyAdjustment) % SimpleCipher.ABC.length];
    }
    return encryptedMessage;
  }

  decode(encryptedMessage: string): string {
    let decryptedMessage = '';
    const keyLength = this.key.length;
    for (let i = 0; i < encryptedMessage.length; i++) {
      const char = encryptedMessage[i];
      const adjustment = SimpleCipher.ABC.indexOf(char);
      if (adjustment === -1) {
        decryptedMessage += char;
        continue;
      }
      const keyAdjustment = SimpleCipher.ABC.indexOf(this.key[i % keyLength]);
      decryptedMessage += SimpleCipher.ABC[((adjustment - keyAdjustment) + SimpleCipher.ABC.length) % SimpleCipher.ABC.length];
    }
    return decryptedMessage;
  }
}

export default SimpleCipher;