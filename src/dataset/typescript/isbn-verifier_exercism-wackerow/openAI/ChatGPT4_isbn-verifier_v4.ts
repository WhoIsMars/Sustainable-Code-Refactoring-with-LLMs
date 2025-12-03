export default class ISBN {
  constructor(private _isbn: string) {}

  public isValid(): boolean {
    const sanitized = this._isbn.replace(/-/g, '').trim();
    if (!/^\d{9}[\dXx]$/.test(sanitized)) return false;

    let sum = 0;
    for (let i = 0; i < 10; i++) {
      const char = sanitized[i];
      const value = char === 'X' || char === 'x' ? 10 : +char;
      sum += value * (10 - i);
    }

    return sum % 11 === 0;
  }
}