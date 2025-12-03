export default class ISBN {
  constructor(private _isbn: string) {}

  public isValid(): boolean {
    const sanitized = this._isbn.replace(/-/g, '').toLowerCase().trim();
    if (sanitized.length !== 10) {
      return false;
    }
    let sum = 0;
    for (let i = 0; i < 9; i++) {
      const digit = sanitized.charCodeAt(i) - 48;
      if (digit < 0 || digit > 9) {
        return false;
      }
      sum += digit * (10 - i);
    }

    const lastChar = sanitized.charCodeAt(9);
    let lastDigit: number;
    if (lastChar === 120) { // 'x'
      lastDigit = 10;
    } else {
      lastDigit = lastChar - 48;
      if (lastDigit < 0 || lastDigit > 9) {
        return false;
      }
    }

    sum += lastDigit;
    return sum % 11 === 0;
  }
}