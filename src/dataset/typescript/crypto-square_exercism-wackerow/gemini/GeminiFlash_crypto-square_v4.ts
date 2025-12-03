export default class Crypto {
  private readonly normalizedPlaintext: string;
  private readonly r: number;
  private readonly c: number;

  constructor(private _input: string) {
    this.normalizedPlaintext = this.normalizeText();
    this.r = Math.floor(Math.sqrt(this.normalizedPlaintext.length));
    this.c = this.r * this.r === this.normalizedPlaintext.length ? this.r : this.r + 1;
  }

  private normalizeText(): string {
    return this._input.toLowerCase().replace(/[^a-z0-9]/g, '');
  }

  public normalizePlaintext(): string {
    return this.normalizedPlaintext;
  }

  get rows(): number {
    return this.r;
  }

  get columns(): number {
    return this.c;
  }

  public size = (): number => Math.max(this.r, this.c)

  public plaintextSegments(): string[] {
    const segments: string[] = [];
    for (let i = 0; i < this.normalizedPlaintext.length; i += this.c) {
      segments.push(this.normalizedPlaintext.substring(i, i + this.c));
    }
    return segments;
  }

  public ciphertext(): string {
    let cipher = '';
    for (let col = 0; col < this.c; col++) {
      for (let row = 0; row < this.r + 1; row++) {
        const char = this.plaintextSegments()[row]?.[col];
        if (char) {
          cipher += char;
        }
      }
    }
    return cipher;
  }
}