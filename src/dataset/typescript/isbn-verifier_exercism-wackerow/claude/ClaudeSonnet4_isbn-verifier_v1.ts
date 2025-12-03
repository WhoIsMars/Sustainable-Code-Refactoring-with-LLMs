export default class ISBN {
  constructor(private _isbn: string) {}

  public isValid(): boolean {
    let sanitized = '';
    for (let i = 0; i < this._isbn.length; i++) {
      const char = this._isbn[i];
      if (char !== '-') {
        sanitized += char >= 'A' && char <= 'Z' ? String.fromCharCode(char.charCodeAt(0) + 32) : char;
      }
    }
    
    if (sanitized.length !== 10) return false;
    
    let sum = 0;
    for (let i = 0; i < 9; i++) {
      const digit = sanitized.charCodeAt(i) - 48;
      if (digit < 0 || digit > 9) return false;
      sum += digit * (10 - i);
    }
    
    const lastChar = sanitized[9];
    if (lastChar === 'x') {
      sum += 10;
    } else {
      const lastDigit = lastChar.charCodeAt(0) - 48;
      if (lastDigit < 0 || lastDigit > 9) return false;
      sum += lastDigit;
    }
    
    return sum % 11 === 0;
  }
}