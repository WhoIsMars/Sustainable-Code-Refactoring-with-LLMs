export default class Luhn {
  public static valid(input: string): boolean {
    let sum = 0;
    let alternate = false;
    let nDigits = 0;

    for (let i = input.length - 1; i >= 0; i--) {
      const char = input[i];

      if (/\s/.test(char)) {
        continue;
      }

      if (/\D/.test(char)) {
        return false;
      }

      nDigits++;
      let n = parseInt(char, 10);

      if (alternate) {
        n *= 2;
        if (n > 9) {
          n -= 9;
        }
      }

      sum += n;
      alternate = !alternate;
    }

    return nDigits > 1 && sum % 10 === 0;
  }
}