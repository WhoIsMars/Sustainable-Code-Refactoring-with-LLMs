export default class PhoneNumber {
  private _sanitized: string | undefined;

  constructor(private _input: string) {}

  private sanitize(): string | undefined {
    if (this._sanitized !== undefined) {
      return this._sanitized;
    }

    let sanitized = this._input.replace(/[^0-9]/g, '');

    if (sanitized.length === 11 && sanitized.startsWith('1')) {
      sanitized = sanitized.slice(1);
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

    return sanitized;
  }
}