export default class Crypto {
  private _normalizedText: string | null = null;
  private _r: number | null = null;
  private _c: number | null = null;
  private _segments: string[] | null = null;

  constructor(private _input: string) {}

  public normalizePlaintext(): string {
    if (this._normalizedText === null) {
      this._normalizedText = this._input.toLowerCase().replace(/[^a-z0-9]/g, '');
    }
    return this._normalizedText;
  }

  get r(): number {
    if (this._r === null) {
      this._r = Math.floor(Math.sqrt(this.normalizePlaintext().length));
    }
    return this._r;
  }

  get c(): number {
    if (this._c === null) {
      const normalizedLength = this.normalizePlaintext().length;
      this._c = this.r ** 2 === normalizedLength ? this.r : this.r + 1;
    }
    return this._c;
  }
  
  public size = (): number => Math.max(this.r, this.c)

  public plaintextSegments(): string[] {
    if (this._segments === null) {
      const normalized = this.normalizePlaintext();
      const c = this.c;
      this._segments = [];
      for (let i = 0; i < normalized.length; i += c) {
        this._segments.push(normalized.slice(i, i + c));
      }
    }
    return this._segments;
  }

  public ciphertext(): string {
    const segments = this.plaintextSegments();
    const result: string[] = [];
    const maxC = this.c;
    const maxR = segments.length;
    
    for (let c = 0; c < maxC; c++) {
      for (let r = 0; r < maxR; r++) {
        const char = segments[r]?.[c];
        if (char) {
          result.push(char);
        }
      }
    }
    return result.join('');
  }
}