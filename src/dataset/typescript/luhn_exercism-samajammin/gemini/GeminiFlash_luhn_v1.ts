export default class Luhn {
  public static valid(input: string): boolean {
    const stripped = input.replace(/\s/g, '');

    if (stripped.length <= 1 || !/^\d+$/.test(stripped)) {
      return false;
    }

    let sum = 0;
    let alternate = false;

    for (let i = stripped.length - 1; i >= 0; i--) {
      let n = parseInt(stripped.charAt(i), 10);

      if (alternate) {
        n *= 2;
        if (n > 9) {
          n -= 9;
        }
      }

      sum += n;
      alternate = !alternate;
    }

    return sum % 10 === 0;
  }
}