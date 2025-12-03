export default class PhoneNumber {
  constructor(private _input: string) {}

  public number(): string | undefined {
    const sanitized = this._input.replace(/[^a-z0-9]/gi, '').replace(/^1/, '');
    return /^[2-9]\d{2}[2-9]\d{6}$/.test(sanitized) ? sanitized : undefined;
  }
}