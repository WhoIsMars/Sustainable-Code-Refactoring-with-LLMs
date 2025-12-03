class SimpleCipher {
  private static readonly ALPHABET = 'abcdefghijklmnopqrstuvwxyz';
  private static readonly ALPHABET_LENGTH = 26;
  public key: string;

  constructor(_key?: string) {
    if (_key) {
      this.key = _key;
    } else {
      const keyChars = new Array(128);
      for (let i = 0; i < 128; i++) {
        keyChars[i] = SimpleCipher.ALPHABET[Math.floor(Math.random() * SimpleCipher.ALPHABET_LENGTH)];
      }
      this.key = keyChars.join('');
    }
  }

  encode(message: string): string {
    const result = new Array(message.length);
    const keyLength = this.key.length;
    
    for (let i = 0; i < message.length; i++) {
      const charCode = message.charCodeAt(i);
      const adjustment = charCode >= 97 && charCode <= 122 ? charCode - 97 : message.toLowerCase().charCodeAt(i) - 97;
      const keyAdjustment = this.key.charCodeAt(i % keyLength) - 97;
      result[i] = SimpleCipher.ALPHABET[(adjustment + keyAdjustment) % SimpleCipher.ALPHABET_LENGTH];
    }
    
    return result.join('');
  }

  decode(encryptedMessage: string): string {
    const result = new Array(encryptedMessage.length);
    const keyLength = this.key.length;
    
    for (let i = 0; i < encryptedMessage.length; i++) {
      const adjustment = encryptedMessage.charCodeAt(i) - 97;
      const keyAdjustment = this.key.charCodeAt(i % keyLength) - 97;
      result[i] = SimpleCipher.ALPHABET[(adjustment - keyAdjustment + SimpleCipher.ALPHABET_LENGTH) % SimpleCipher.ALPHABET_LENGTH];
    }
    
    return result.join('');
  }
}

export default SimpleCipher;