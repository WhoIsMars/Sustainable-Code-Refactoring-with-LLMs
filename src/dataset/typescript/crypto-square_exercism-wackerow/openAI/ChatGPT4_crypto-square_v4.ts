export default class Crypto {
  private _normalizedInput: string;

  constructor(private _input: string) {
    this._normalizedInput = this._input.toLowerCase().replace(/[^a-z0-9]/g, '');
  }

  public normalizePlaintext(): string {
    return this._normalizedInput;
  }

  get r(): number {
    return Math.floor(Math.sqrt(this._normalizedInput.length));
  }

  get c(): number {
    const length = this._normalizedInput.length;
    const r = this.r;
    return r * r === length ? r : r + 1;
  }

  public size(): number {
    return Math.max(this.r, this.c);
  }

  public plaintextSegments(): string[] {
    const segments: string[] = [];
    const length = this._normalizedInput.length;
    const cols = this.c;
    for (let i = 0; i < length; i += cols) {
      segments.push(this._normalizedInput.slice(i, i + cols));
    }
    return segments;
  }

  public ciphertext(): string {
    const segments = this.plaintextSegments();
    const cols = this.c;
    const rows = segments.length;
    let cipher = '';
    for (let c = 0; c < cols; c++) {
      for (let r = 0; r < rows; r++) {
        if (segments[r][c] !== undefined) {
          cipher += segments[r][c];
        }
      }
    }
    return cipher;
  }
}