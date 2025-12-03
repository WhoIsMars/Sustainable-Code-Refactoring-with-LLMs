class SimpleCipher {
  private static readonly _abc: string = 'abcdefghijklmnopqrstuvwxyz';
  public key: string;

  constructor(_key?: string) {
    if (_key) {
      this.key = _key;
    } else {
      let key = '';
      const abcLength = SimpleCipher._abc.length;
      for (let i = 0; i < 128; i++) {
        key += SimpleCipher._abc[Math.floor(Math.random() * abcLength) % abcLength];
      }
      this.key = key;
    }
  }

  encode(message: string): string {
    let encryptedMessage = '';
    const keyLength = this.key.length;
    for (let i = 0; i < message.length; i++) {
      const char = message[i].toLowerCase();
      const adjustment = SimpleCipher._abc.indexOf(char);
      if (adjustment === -1) {
        encryptedMessage += char;
        continue;
      }
      const keyAdjustment = SimpleCipher._abc.indexOf(this.key[i % keyLength]);
      encryptedMessage += SimpleCipher._abc[(adjustment + keyAdjustment) % SimpleCipher._abc.length];
    }
    return encryptedMessage;
  }

  decode(encryptedMessage: string): string {
    let decryptedMessage = '';
    const keyLength = this.key.length;
    for (let i = 0; i < encryptedMessage.length; i++) {
      const char = encryptedMessage[i];
      const adjustment = SimpleCipher._abc.indexOf(char);
      if (adjustment === -1) {
        decryptedMessage += char;
        continue;
      }
      const keyAdjustment = SimpleCipher._abc.indexOf(this.key[i % keyLength]);
      decryptedMessage += SimpleCipher._abc[((adjustment - keyAdjustment) + SimpleCipher._abc.length) % SimpleCipher._abc.length];
    }
    return decryptedMessage;
  }
}

export default SimpleCipher;