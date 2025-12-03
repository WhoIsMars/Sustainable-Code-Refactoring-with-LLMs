export default class RomanNumerals {
  private static readonly romanPairs: ReadonlyArray<readonly [string, number]> = [
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
    let workingNumeral = base10;
    let romanNumeral = '';
    
    for (const [symbol, value] of this.romanPairs) {
      if (workingNumeral >= value) {
        const count = Math.floor(workingNumeral / value);
        romanNumeral += symbol.repeat(count);
        workingNumeral -= value * count;
      }
    }
    
    return romanNumeral;
  }
}