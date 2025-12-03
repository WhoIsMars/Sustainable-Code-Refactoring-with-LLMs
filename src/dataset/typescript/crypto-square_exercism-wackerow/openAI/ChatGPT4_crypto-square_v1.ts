export default class Crypto {
  private _normalizedInput: string;
  private _r: number;
  private _c: number;

  constructor(private _input: string) {
    this._normalizedInput = this._input.toLowerCase().replace(/[^a-z0-9]/g, '');
    this._r = Math.floor(Math.sqrt(this._normalizedInput.length));
    this._c = this._r ** 2 === this._normalizedInput.length ? this._r : this._r + 1;
  }

  public normalizePlaintext(): string {
    return this._normalizedInput;
  }

  get r(): number {
    return this._r;
  }

  get c(): number {
    return this._c;
  }

  public size = (): number => this._c;

  public plaintextSegments(): string[] {
    const segments: string[] = [];
    for (let i = 0; i < this._normalizedInput.length; i += this._c) {
      segments.push(this._normalizedInput.slice(i, i + this._c));
    }
    return segments;
  }

  public ciphertext(): string {
    const segments = this.plaintextSegments();
    const cipher: string[] = [];
    for (let c = 0; c < this._c; c++) {
      for (let r = 0; r < segments.length; r++) {
        if (segments[r][c]) {
          cipher.push(segments[r][c]);
        }
      }
    }
    return cipher.join('');
  }
}