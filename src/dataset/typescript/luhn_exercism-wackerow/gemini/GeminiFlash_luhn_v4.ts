export default class Luhn {
  public static valid(_numbers: string): boolean {
    const numbers = _numbers.replace(/\s/g, '');

    if (numbers.length < 2 || !/^\d+$/.test(numbers)) {
      return false;
    }

    let sum = 0;
    for (let i = numbers.length - 1; i >= 0; i--) {
      let digit = parseInt(numbers[i], 10);
      if (isNaN(digit)) return false;

      if ((numbers.length - 1 - i) % 2 !== 0) {
        digit *= 2;
        if (digit > 9) {
          digit -= 9;
        }
      }
      sum += digit;
    }

    return sum % 10 === 0;
  }
}