export default class Allergies {
  private _allergies: number;
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
  private static readonly _keyMap: ReadonlyMap<string, number> = new Map(
    Allergies._key.map((allergy, index) => [allergy, index])
  );
  private static readonly _maxValue = 255;

  constructor(allergies: number) {
    this._allergies = allergies & Allergies._maxValue;
  }

  public allergicTo(allergy: string): boolean {
    const index = Allergies._keyMap.get(allergy);
    return index !== undefined && (this._allergies & (1 << index)) !== 0;
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