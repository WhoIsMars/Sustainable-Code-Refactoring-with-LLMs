export default class PhoneNumber {
  private _sanitized: string | undefined;

  constructor(private _input: string) {}

  public number(): string | undefined {
    if (this._sanitized !== undefined) {
      return this._sanitized;
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
      
      let isValid = true;
      for (let i = 1; i < 10; i++) {
        if (i === 3) continue;
        if (sanitized[i] < '0' || sanitized[i] > '9') {
          isValid = false;
          break;
        }
      }
      
      this._sanitized = isValid ? sanitized : undefined;
    } else {
      this._sanitized = undefined;
    }

    return this._sanitized;
  }
}