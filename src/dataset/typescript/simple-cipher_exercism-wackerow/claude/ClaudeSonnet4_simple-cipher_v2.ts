class SimpleCipher {
  private static readonly ALPHABET = 'abcdefghijklmnopqrstuvwxyz';
  private static readonly ALPHABET_LENGTH = 26;
  public key: string;

  constructor(_key?: string) {
    if (_key) {
      this.key = _key;
    } else {
      let key = '';
      for (let i = 0; i < 128; i++) {
        key += SimpleCipher.ALPHABET[Math.floor(Math.random() * SimpleCipher.ALPHABET_LENGTH)];
      }
      this.key = key;
    }
  }

  encode(message: string): string {
    let encryptedMessage = '';
    const keyLength = this.key.length;
    
    for (let i = 0; i < message.length; i++) {
      const charCode = message.charCodeAt(i);
      const adjustment = charCode >= 97 ? charCode - 97 : charCode - 65 + 32;
      const keyAdjustment = this.key.charCodeAt(i % keyLength) - 97;
      encryptedMessage += SimpleCipher.ALPHABET[(adjustment + keyAdjustment) % SimpleCipher.ALPHABET_LENGTH];
    }
    return encryptedMessage;
  }

  decode(encryptedMessage: string): string {
    let decryptedMessage = '';
    const keyLength = this.key.length;
    
    for (let i = 0; i < encryptedMessage.length; i++) {
      const adjustment = encryptedMessage.charCodeAt(i) - 97;
      const keyAdjustment = this.key.charCodeAt(i % keyLength) - 97;
      decryptedMessage += SimpleCipher.ALPHABET[((adjustment - keyAdjustment) + SimpleCipher.ALPHABET_LENGTH) % SimpleCipher.ALPHABET_LENGTH];
    }
    return decryptedMessage;
  }
}

export default SimpleCipher;