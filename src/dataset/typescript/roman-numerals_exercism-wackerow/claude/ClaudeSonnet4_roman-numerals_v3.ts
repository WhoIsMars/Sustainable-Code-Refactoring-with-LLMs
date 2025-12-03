export default class RomanNumerals {
  private static readonly values = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1];
  private static readonly symbols = ['M', 'CM', 'D', 'CD', 'C', 'XC', 'L', 'XL', 'X', 'IX', 'V', 'IV', 'I'];
  
  public static roman(base10: number): string {
    let workingNumeral = base10;
    let romanNumeral = '';
    
    for (let i = 0; i < this.values.length; i++) {
      const count = Math.floor(workingNumeral / this.values[i]);
      if (count > 0) {
        romanNumeral += this.symbols[i].repeat(count);
        workingNumeral -= this.values[i] * count;
      }
    }
    
    return romanNumeral;
  }
}