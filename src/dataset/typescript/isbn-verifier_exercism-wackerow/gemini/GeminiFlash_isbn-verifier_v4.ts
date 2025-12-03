export default class ISBN {
  constructor(private _isbn: string) {}

  public isValid(): boolean {
    const isbn = this._isbn.replace(/-/g, '').toLowerCase().trim();

    if (isbn.length !== 10) {
      return false;
    }

    let sum = 0;
    for (let i = 0; i < 9; i++) {
      const digit = parseInt(isbn[i], 10);
      if (isNaN(digit)) {
        return false;
      }
      sum += digit * (10 - i);
    }

    const lastChar = isbn[9];
    let lastDigit: number;

    if (lastChar === 'x') {
      lastDigit = 10;
    } else {
      lastDigit = parseInt(lastChar, 10);
      if (isNaN(lastDigit)) {
        return false;
      }
    }

    sum += lastDigit;

    return sum % 11 === 0;
  }
}