export default class Luhn {
  public static valid(_numbers: string): boolean {
    const numbers = _numbers.replace(/\s/g, '');
    if (numbers.length < 2 || /[^0-9]/.test(numbers)) {
      return false;
    }

    let sum = 0;
    const length = numbers.length;

    for (let i = 0; i < length; i++) {
      let digit = +numbers[length - 1 - i];
      if (i % 2 === 1) {
        digit *= 2;
        if (digit > 9) digit -= 9;
      }
      sum += digit;
    }

    return sum % 10 === 0;
  }
}