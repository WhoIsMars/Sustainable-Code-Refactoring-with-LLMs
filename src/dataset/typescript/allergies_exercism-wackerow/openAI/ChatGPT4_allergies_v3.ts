export default class Allergies {
  private readonly _allergies: number;
  private static readonly _key: string[] = [
    'eggs',
    'peanuts',
    'shellfish',
    'strawberries',
    'tomatoes',
    'chocolate',
    'pollen',
    'cats',
  ];

  constructor(allergies: number) {
    this._allergies = allergies & ((1 << Allergies._key.length) - 1);
  }

  public allergicTo(allergy: string): boolean {
    const index = Allergies._key.indexOf(allergy);
    return index !== -1 && (this._allergies & (1 << index)) !== 0;
  }

  public list(): string[] {
    const result: string[] = [];
    for (let i = 0; i < Allergies._key.length; i++) {
      if (this._allergies & (1 << i)) {
        result.push(Allergies._key[i]);
      }
    }
    return result;
  }
}