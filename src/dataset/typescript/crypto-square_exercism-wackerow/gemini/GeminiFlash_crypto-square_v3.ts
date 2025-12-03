export default class Crypto {
  private normalizedPlaintext: string;
  private rValue: number;
  private cValue: number;

  constructor(private _input: string) {
    this.normalizedPlaintext = this._input.toLowerCase().replace(/[^a-z0-9]/g, '');
    this.rValue = Math.floor(Math.sqrt(this.normalizedPlaintext.length));
    this.cValue = this.rValue ** 2 === this.normalizedPlaintext.length ? this.rValue : this.rValue + 1;
  }

  public normalizePlaintext(): string {
    return this.normalizedPlaintext;
  }

  get r(): number {
    return this.rValue;
  }

  get c(): number {
    return this.cValue;
  }

  public size = (): number => Math.max(this.r, this.c)

  public plaintextSegments(): string[] {
    const segments: string[] = [];
    for (let i = 0; i < this.normalizedPlaintext.length; i += this.c ) {
      segments.push(this.normalizedPlaintext.substring(i, this.c + i));
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