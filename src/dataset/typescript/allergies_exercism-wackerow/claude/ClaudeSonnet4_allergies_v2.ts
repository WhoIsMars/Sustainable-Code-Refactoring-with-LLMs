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
  private static readonly _keyMap = new Map(
    Allergies._key.map((allergy, index) => [allergy, 1 << index])
  );

  constructor(allergies: number) {
    this._allergies = allergies & 255; // 2^8 - 1 = 255
  }

  public allergicTo(allergy: string): boolean {
    const mask = Allergies._keyMap.get(allergy);
    return mask !== undefined && (this._allergies & mask) !== 0;
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