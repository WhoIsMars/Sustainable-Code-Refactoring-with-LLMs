export default class PhoneNumber {
  private _sanitized: string | undefined;

  constructor(private _input: string) {}

  private sanitize(): string | undefined {
    if (this._sanitized !== undefined) {
      return this._sanitized;
    }

    let sanitized = '';
    for (let i = 0; i < this._input.length; i++) {
      const char = this._input[i];
      if (char >= '0' && char <= '9') {
        sanitized += char;
      }
    }

    if (sanitized.length === 11 && sanitized[0] === '1') {
      sanitized = sanitized.substring(1);
    }

    this._sanitized = sanitized;
    return this._sanitized;
  }


  public number(): string | undefined {
    const sanitized = this.sanitize();

    if (!sanitized || sanitized.length !== 10) {
      return undefined;
    }

    if (sanitized[0] < '2' || sanitized[3] < '2') {
      return undefined;
    }

    for (let i = 0; i < sanitized.length; i++) {
      if (isNaN(Number(sanitized[i]))) {
        return undefined;
      }
    }

    return sanitized;
  }
}