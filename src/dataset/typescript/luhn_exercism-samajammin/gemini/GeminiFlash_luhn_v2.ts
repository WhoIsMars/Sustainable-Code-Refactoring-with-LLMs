export default class Luhn {
  public static valid(input: string): boolean {
    const stripped = input.replace(/\s/g, '');
    const len = stripped.length;

    if (len <= 1 || !/^\d+$/.test(stripped)) {
      return false;
    }

    let sum = 0;
    for (let i = len - 1; i >= 0; i--) {
      let digit = parseInt(stripped[i], 10);
      if ((len - 1 - i) % 2 !== 0) {
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