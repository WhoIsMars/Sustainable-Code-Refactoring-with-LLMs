export default class RomanNumerals {
  private static keys: [string, number][] = [
    ['M', 1000],
    ['CM', 900],
    ['D', 500],
    ['CD', 400],
    ['C', 100],
    ['XC', 90],
    ['L', 50],
    ['XL', 40],
    ['X', 10],
    ['IX', 9],
    ['V', 5],
    ['IV', 4],
    ['I', 1]
  ];

  public static roman(base10: number): string {
    let romanNumeral = '';
    for (const [key, value] of this.keys) {
      const count = Math.floor(base10 / value);
      if (count > 0) {
        romanNumeral += key.repeat(count);
        base10 %= value;
      }
      if (base10 === 0) break;
    }
    return romanNumeral;
  }
}