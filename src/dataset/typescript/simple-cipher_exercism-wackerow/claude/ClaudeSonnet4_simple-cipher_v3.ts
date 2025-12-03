class SimpleCipher {
  private static readonly ALPHABET_SIZE = 26;
  private static readonly A_CHAR_CODE = 97;
  
  public key: string;

  constructor(_key?: string) {
    if (_key) {
      this.key = _key;
    } else {
      const keyArray = new Array(128);
      for (let i = 0; i < 128; i++) {
        keyArray[i] = String.fromCharCode(SimpleCipher.A_CHAR_CODE + Math.floor(Math.random() * SimpleCipher.ALPHABET_SIZE));
      }
      this.key = keyArray.join('');
    }
  }

  encode(message: string): string {
    const result = new Array(message.length);
    const keyLength = this.key.length;
    
    for (let i = 0; i < message.length; i++) {
      const msgCharCode = message.charCodeAt(i) | 32;
      const keyCharCode = this.key.charCodeAt(i % keyLength);
      const adjustment = msgCharCode - SimpleCipher.A_CHAR_CODE;
      const keyAdjustment = keyCharCode - SimpleCipher.A_CHAR_CODE;
      result[i] = String.fromCharCode(SimpleCipher.A_CHAR_CODE + ((adjustment + keyAdjustment) % SimpleCipher.ALPHABET_SIZE));
    }
    
    return result.join('');
  }

  decode(encryptedMessage: string): string {
    const result = new Array(encryptedMessage.length);
    const keyLength = this.key.length;
    
    for (let i = 0; i < encryptedMessage.length; i++) {
      const msgCharCode = encryptedMessage.charCodeAt(i);
      const keyCharCode = this.key.charCodeAt(i % keyLength);
      const adjustment = msgCharCode - SimpleCipher.A_CHAR_CODE;
      const keyAdjustment = keyCharCode - SimpleCipher.A_CHAR_CODE;
      result[i] = String.fromCharCode(SimpleCipher.A_CHAR_CODE + ((adjustment - keyAdjustment + SimpleCipher.ALPHABET_SIZE) % SimpleCipher.ALPHABET_SIZE));
    }
    
    return result.join('');
  }
}

export default SimpleCipher;