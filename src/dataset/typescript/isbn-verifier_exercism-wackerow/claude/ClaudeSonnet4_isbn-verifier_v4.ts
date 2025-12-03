export default class ISBN {
  constructor(private _isbn: string) {}

  public isValid(): boolean {
    const sanitized = this._isbn.replace(/-/g, '');
    
    if (sanitized.length !== 10) return false;
    
    let sum = 0;
    for (let i = 0; i < 9; i++) {
      const char = sanitized.charCodeAt(i);
      if (char < 48 || char > 57) return false;
      sum += (char - 48) * (10 - i);
    }
    
    const lastChar = sanitized.charCodeAt(9);
    if (lastChar === 120 || lastChar === 88) {
      sum += 10;
    } else if (lastChar >= 48 && lastChar <= 57) {
      sum += lastChar - 48;
    } else {
      return false;
    }
    
    return sum % 11 === 0;
  }
}