export default class Crypto {
  private readonly normalizedPlaintext: string;
  private readonly r: number;
  private readonly c: number;
  private readonly sizeValue: number;

  constructor(private _input: string) {
    this.normalizedPlaintext = this.normalizePlaintextInternal();
    this.r = Math.floor(Math.sqrt(this.normalizedPlaintext.length));
    this.c = this.r * this.r === this.normalizedPlaintext.length ? this.r : this.r + 1;
    this.sizeValue = Math.max(this.r, this.c);
  }

  private normalizePlaintextInternal(): string {
    return this._input.toLowerCase().replace(/[^a-z0-9]/g, '');
  }

  public normalizePlaintext(): string {
    return this.normalizedPlaintext;
  }

  public getR(): number {
    return this.r;
  }

  public getC(): number {
    return this.c;
  }

  public size = (): number => this.sizeValue;

  public plaintextSegments(): string[] {
    const segments: string[] = [];
    for (let i = 0; i < this.normalizedPlaintext.length; i += this.c) {
      segments.push(this.normalizedPlaintext.substring(i, this.c));
    }
    return segments;
  }

  public ciphertext(): string {
    const segments = this.plaintextSegments();
    let cipher = '';
    for (let c = 0; c < this.c; c++) {
      for (let r = 0; r < this.r; r++) {
        if (segments[r] && segments[r][c]) {
          cipher += segments[r][c];
        }
      }
    }
    return cipher;
  }
}