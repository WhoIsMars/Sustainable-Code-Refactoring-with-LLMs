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
    return Math.ceil(this._normalizedInput.length / this.r);
  }

  public size = (): number => Math.max(this.r, this.c);

  public plaintextSegments(): string[] {
    const segments: string[] = [];
    const len = this._normalizedInput.length;
    const cols = this.c;
    for (let i = 0; i < len; i += cols) {
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