export default class Luhn {
  public static valid(numbers: string): boolean {
    // Remove spaces and validate input
    const sanitized = numbers.replace(/\s/g, '');
    if (sanitized.length < 2 || !/^\d+$/.test(sanitized)) {
      return false;
    }

    let sum = 0;
    const length = sanitized.length;

    // Process digits from right to left
    for (let i = 0; i < length; i++) {
      let digit = +sanitized[length - 1 - i];
      if (i % 2 === 1) {
        digit *= 2;
        if (digit > 9) digit -= 9;
      }
      sum += digit;
    }

    // Valid if sum is divisible by 10
    return sum % 10 === 0;
  }
}