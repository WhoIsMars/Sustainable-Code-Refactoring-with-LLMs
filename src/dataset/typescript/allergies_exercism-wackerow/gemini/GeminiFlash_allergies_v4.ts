export default class Allergies {
  private _allergies: number;
  private static readonly ALLERGENS: string[] = [
    'eggs',
    'peanuts',
    'shellfish',
    'strawberries',
    'tomatoes',
    'chocolate',
    'pollen',
    'cats',
  ];

  constructor(score: number) {
    this._allergies = score % 256;
  }

  public allergicTo(allergen: string): boolean {
    const index = Allergies.ALLERGENS.indexOf(allergen);
    if (index === -1) {
      return false;
    }
    return (this._allergies & (1 << index)) !== 0;
  }

  public list(): string[] {
    const result: string[] = [];
    for (let i = 0; i < Allergies.ALLERGENS.length; i++) {
      if ((this._allergies & (1 << i)) !== 0) {
        result.push(Allergies.ALLERGENS[i]);
      }
    }
    return result;
  }
}