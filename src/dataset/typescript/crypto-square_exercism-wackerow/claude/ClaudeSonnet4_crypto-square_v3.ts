export default class Crypto {
  private _normalizedText: string | null = null;
  private _r: number | null = null;
  private _c: number | null = null;

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
      const r = this.r;
      const normalizedLength = this.normalizePlaintext().length;
      this._c = r * r === normalizedLength ? r : r + 1;
    }
    return this._c;
  }
  
  public size = (): number => Math.max(this.r, this.c)

  public plaintextSegments(): string[] {
    const normalized = this.normalizePlaintext();
    const c = this.c;
    const segments: string[] = [];
    
    for (let i = 0; i < normalized.length; i += c) {
      segments.push(normalized.slice(i, i + c));
    }
    return segments;
  }

  public ciphertext(): string {
    const segments = this.plaintextSegments();
    const r = this.r;
    const c = this.c;
    let cipher = '';
    
    for (let col = 0; col < c; col++) {
      for (let row = 0; row < r && row < segments.length; row++) {
        const char = segments[row][col];
        if (char) {
          cipher += char;
        }
      }
    }
    return cipher;
  }
}