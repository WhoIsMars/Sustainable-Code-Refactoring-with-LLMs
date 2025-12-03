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

  constructor(allergies: number) {
    this._allergies = allergies & 255; // 2^8 - 1 = 255
  }

  public allergicTo(allergy: string): boolean {
    const index = Allergies._keyMap.get(allergy);
    return index !== undefined && (this._allergies & (1 << index)) !== 0;
  }

  public list(): string[] {
    const result: string[] = [];
    for (let i = 0; i < Allergies._key.length; i++) {
      if ((this._allergies & (1 << i)) !== 0) {
        result.push(Allergies._key[i]);
      }
    }
    return result;
  }
}