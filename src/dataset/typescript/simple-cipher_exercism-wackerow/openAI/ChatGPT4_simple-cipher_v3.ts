class SimpleCipher {
  private static readonly _abc = 'abcdefghijklmnopqrstuvwxyz';
  public key: string;

  constructor(_key?: string) {
    this.key = _key || Array.from({ length: 128 }, () => SimpleCipher._abc[Math.floor(Math.random() * SimpleCipher._abc.length)]).join('');
  }

  encode(message: string): string {
    return this.transform(message.toLowerCase(), (m, k) => (m + k) % SimpleCipher._abc.length);
  }

  decode(encryptedMessage: string): string {
    return this.transform(encryptedMessage, (m, k) => (m - k + SimpleCipher._abc.length) % SimpleCipher._abc.length);
  }

  private transform(input: string, operation: (m: number, k: number) => number): string {
    const abc = SimpleCipher._abc;
    const keyLength = this.key.length;
    return Array.from(input, (char, i) => {
      const mIndex = abc.indexOf(char);
      if (mIndex === -1) return char;
      const kIndex = abc.indexOf(this.key[i % keyLength]);
      return abc[operation(mIndex, kIndex)];
    }).join('');
  }
}

export default SimpleCipher;