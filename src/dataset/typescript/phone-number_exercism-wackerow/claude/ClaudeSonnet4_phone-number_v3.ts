export default class PhoneNumber {
  private _sanitized: string | undefined;
  private _isValid: boolean | undefined;

  constructor(private _input: string) {}

  public number(): string | undefined {
    if (this._isValid !== undefined) {
      return this._isValid ? this._sanitized : undefined;
    }

    let sanitized = '';
    for (let i = 0; i < this._input.length; i++) {
      const char = this._input[i];
      if ((char >= '0' && char <= '9') || (char >= 'a' && char <= 'z') || (char >= 'A' && char <= 'Z')) {
        sanitized += char;
      }
    }

    if (sanitized.length === 11 && sanitized[0] === '1') {
      sanitized = sanitized.slice(1);
    }

    if (sanitized.length === 10 && 
        sanitized[0] >= '2' && sanitized[0] <= '9' &&
        sanitized[3] >= '2' && sanitized[3] <= '9') {
      
      let isValidFormat = true;
      for (let i = 1; i < 10; i++) {
        if (i === 3) continue;
        if (sanitized[i] < '0' || sanitized[i] > '9') {
          isValidFormat = false;
          break;
        }
      }
      
      if (isValidFormat) {
        this._sanitized = sanitized;
        this._isValid = true;
        return sanitized;
      }
    }

    this._isValid = false;
    return undefined;
  }
}