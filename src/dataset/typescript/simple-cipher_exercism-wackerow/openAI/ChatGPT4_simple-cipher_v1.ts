class SimpleCipher {
  private static readonly _abc = 'abcdefghijklmnopqrstuvwxyz';
  private static readonly _abcLength = SimpleCipher._abc.length;
  public key: string;

  constructor(_key?: string) {
    if (_key) {
      this.key = _key;
    } else {
      const keyArray = Array.from({ length: 128 }, () =>
        SimpleCipher._abc[Math.floor(Math.random() * SimpleCipher._abcLength)]
      );
      this.key = keyArray.join('');
    }
  }

  encode(message: string): string {
    return this.transform(message.toLowerCase(), (m, k) => (m + k) % SimpleCipher._abcLength);
  }

  decode(encryptedMessage: string): string {
    return this.transform(encryptedMessage, (m, k) => (m - k + SimpleCipher._abcLength) % SimpleCipher._abcLength);
  }

  private transform(input: string, operation: (m: number, k: number) => number): string {
    const keyLength = this.key.length;
    return Array.from(input, (char, i) => {
      const mIndex = SimpleCipher._abc.indexOf(char);
      if (mIndex === -1) return char; // Preserve non-alphabet characters
      const kIndex = SimpleCipher._abc.indexOf(this.key[i % keyLength]);
      return SimpleCipher._abc[operation(mIndex, kIndex)];
    }).join('');
  }
}

export default SimpleCipher;