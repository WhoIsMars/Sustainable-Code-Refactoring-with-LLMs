class SimpleCipher {
  private static readonly _abc = 'abcdefghijklmnopqrstuvwxyz';
  private static readonly _abcLength = SimpleCipher._abc.length;
  public key: string;

  constructor(_key?: string) {
    this.key = _key || Array.from({ length: 128 }, () => SimpleCipher._abc[Math.floor(Math.random() * SimpleCipher._abcLength)]).join('');
  }

  private static mod(n: number, m: number): number {
    return (n % m + m) % m;
  }

  private static transform(message: string, key: string, encode: boolean): string {
    const abc = SimpleCipher._abc;
    const abcLength = SimpleCipher._abcLength;
    const keyLength = key.length;
    return Array.from(message.toLowerCase()).map((char, i) => {
      const charIndex = abc.indexOf(char);
      if (charIndex === -1) return char;
      const keyIndex = abc.indexOf(key[i % keyLength]);
      const shift = encode ? charIndex + keyIndex : charIndex - keyIndex;
      return abc[SimpleCipher.mod(shift, abcLength)];
    }).join('');
  }

  encode(message: string): string {
    return SimpleCipher.transform(message, this.key, true);
  }

  decode(encryptedMessage: string): string {
    return SimpleCipher.transform(encryptedMessage, this.key, false);
  }
}

export default SimpleCipher;