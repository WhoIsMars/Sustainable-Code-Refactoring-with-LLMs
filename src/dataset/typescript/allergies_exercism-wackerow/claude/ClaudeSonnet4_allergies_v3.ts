export default class Allergies {
  private readonly _allergies: number;
  private static readonly _key: readonly string[] = [
    'eggs',
    'peanuts',
    'shellfish',
    'strawberries',
    'tomatoes',
    'chocolate',
    'pollen',
    'cats',
  ];
  private static readonly _allergyMap = new Map(
    Allergies._key.map((allergy, index) => [allergy, 1 << index])
  );

  constructor(allergies: number) {
    this._allergies = allergies & 255;
  }

  public allergicTo(allergy: string): boolean {
    const mask = Allergies._allergyMap.get(allergy);
    return mask !== undefined && (this._allergies & mask) !== 0;
  }

  public list(): string[] {
    const result: string[] = [];
    let mask = 1;
    for (const allergy of Allergies._key) {
      if (this._allergies & mask) {
        result.push(allergy);
      }
      mask <<= 1;
    }
    return result;
  }
}