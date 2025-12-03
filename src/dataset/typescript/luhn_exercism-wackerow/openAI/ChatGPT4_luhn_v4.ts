export default class Luhn {
  public static valid(_numbers: string): boolean {
    const numbers = _numbers.replace(/\s/g, '');
    if (numbers.length < 2 || /[^0-9]/.test(numbers)) return false;

    let sum = 0;
    const len = numbers.length;

    for (let i = len - 1; i >= 0; i--) {
      let digit = +numbers[i];
      if ((len - i) % 2 === 0) {
        digit *= 2;
        if (digit > 9) digit -= 9;
      }
      sum += digit;
    }

    return sum % 10 === 0;
  }
}