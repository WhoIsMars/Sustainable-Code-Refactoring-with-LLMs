export default class RomanNumerals {
  private static readonly keys: { [s: string]: number } = {
    'M': 1000,
    'CM': 900,
    'D': 500,
    'CD': 400,
    'C': 100,
    'XC': 90,
    'L': 50,
    'XL': 40,
    'X': 10,
    'IX': 9,
    'V': 5,
    'IV': 4,
    'I': 1
  };

  public static roman(base10: number): string {
    let workingNumeral = base10;
    let romanNumeral = '';
    const keys = Object.keys(this.keys);

    for (let i = 0; i < keys.length; i++) {
      const key = keys[i];
      const value = this.keys[key];

      while (workingNumeral >= value) {
        romanNumeral += key;
        workingNumeral -= value;
      }

      if (workingNumeral === 0) {
        break; // Optimization: Exit early if the number is fully converted
      }
    }

    return romanNumeral;
  }
}