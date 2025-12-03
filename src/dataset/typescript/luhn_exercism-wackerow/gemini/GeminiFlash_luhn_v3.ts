export default class Luhn {
  public static valid(numbers: string): boolean {
    const sanitizedNumbers = numbers.replace(/\s/g, '');

    if (sanitizedNumbers.length < 2 || !/^\d+$/.test(sanitizedNumbers)) {
      return false;
    }

    let sum = 0;
    const length = sanitizedNumbers.length;

    for (let i = length - 1; i >= 0; i--) {
      let digit = parseInt(sanitizedNumbers[i], 10);

      if (isNaN(digit)) {
        return false;
      }

      if ((length - 1 - i) % 2 !== 0) {
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