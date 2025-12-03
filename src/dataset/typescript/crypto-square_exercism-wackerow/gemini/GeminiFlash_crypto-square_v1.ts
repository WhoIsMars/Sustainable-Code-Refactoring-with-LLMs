export default class Crypto {
  private normalizedPlaintext: string;
  private _r: number;
  private _c: number;

  constructor(private _input: string) {
    this.normalizedPlaintext = this.normalizeText(_input);
    this._r = Math.floor(Math.sqrt(this.normalizedPlaintext.length));
    this._c = this._r * this._r === this.normalizedPlaintext.length ? this._r : this._r + 1;
  }

  private normalizeText(text: string): string {
    return text.toLowerCase().replace(/[^a-z0-9]/g, '');
  }

  public normalizePlaintext(): string {
    return this.normalizedPlaintext;
  }

  get r(): number {
    return this._r;
  }

  get c(): number {
    return this._c;
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
    const segments = this.plaintextSegments();
    let cipher = '';
    for (let c = 0; c < this.c; c++) {
      for (let r = 0; r < segments.length; r++) {
        if (segments[r][c]) {
          cipher += segments[r][c];
        }
      }
    }
    return cipher;
  }
}