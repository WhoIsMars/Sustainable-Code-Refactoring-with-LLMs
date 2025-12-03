export default class Allergies {
  private _allergies: number;
  private static readonly ALLERGENS: readonly string[] = [
    'eggs',
    'peanuts',
    'shellfish',
    'strawberries',
    'tomatoes',
    'chocolate',
    'pollen',
    'cats',
  ];
  private static readonly ALLERGEN_MAP: ReadonlyMap<string, number> = new Map(
    Allergies.ALLERGENS.map((allergen, index) => [allergen, 1 << index])
  );

  constructor(score: number) {
    this._allergies = score % 256;
  }

  public allergicTo(allergen: string): boolean {
    const allergenValue = Allergies.ALLERGEN_MAP.get(allergen);
    return allergenValue !== undefined && (this._allergies & allergenValue) !== 0;
  }

  public list(): string[] {
    const result: string[] = [];
    for (const allergen of Allergies.ALLERGENS) {
      if (this.allergicTo(allergen)) {
        result.push(allergen);
      }
    }
    return result;
  }
}