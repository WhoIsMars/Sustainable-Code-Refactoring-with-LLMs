class SimpleCipher {
  private static readonly _abc = 'abcdefghijklmnopqrstuvwxyz';
  private static readonly _abcLength = SimpleCipher._abc.length;
  public key: string;

  constructor(_key?: string) {
    this.key = _key || Array.from({ length: 128 }, () => SimpleCipher._abc[Math.floor(Math.random() * SimpleCipher._abcLength)]).join('');
  }

  private static mod(n: number, m: number): number {
    return (n + m) % m;
  }

  private static getIndex(char: string): number {
    return SimpleCipher._abc.indexOf(char);
  }

  encode(message: string): string {
    return message.toLowerCase().split('').map((char, i) => {
      const adjustment = SimpleCipher.getIndex(char);
      const keyAdjustment = SimpleCipher.getIndex(this.key[i % this.key.length]);
      return SimpleCipher._abc[SimpleCipher.mod(adjustment + keyAdjustment, SimpleCipher._abcLength)];
    }).join('');
  }

  decode(encryptedMessage: string): string {
    return encryptedMessage.split('').map((char, i) => {
      const adjustment = SimpleCipher.getIndex(char);
      const keyAdjustment = SimpleCipher.getIndex(this.key[i % this.key.length]);
      return SimpleCipher._abc[SimpleCipher.mod(adjustment - keyAdjustment, SimpleCipher._abcLength)];
    }).join('');
  }
}

export default SimpleCipher;