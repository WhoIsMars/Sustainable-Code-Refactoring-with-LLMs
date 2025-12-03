export default class Allergies {
  private _allergies: number;
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

  private static readonly _allergyMap: { [key: string]: number } = Allergies._key.reduce((acc, allergy, index) => {
    acc[allergy] = 1 << index;
    return acc;
  }, {});

  constructor(allergies: number) {
    this._allergies = allergies % (1 << Allergies._key.length);
  }

  public allergicTo(allergy: string): boolean {
    const allergyValue = Allergies._allergyMap[allergy];
    return allergyValue !== undefined && (this._allergies & allergyValue) !== 0;
  }

  public list(): string[] {
    const result: string[] = [];
    for (const allergy of Allergies._key) {
      if (this.allergicTo(allergy)) {
        result.push(allergy);
    }
  }
    return result;
  }
}