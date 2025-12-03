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

  private static readonly _allergyValues: number[] = Allergies._key.map((_, index) => 2 ** index);

  constructor(allergies: number) {
    this._allergies = allergies % (2 ** Allergies._key.length);
  }

  public allergicTo(allergy: string): boolean {
    const index = Allergies._key.indexOf(allergy);
    if (index === -1) {
      return false;
    }
    return (this._allergies & Allergies._allergyValues[index]) !== 0;
  }

  public list(): string[] {
    const result: string[] = [];
    for (let i = 0; i < Allergies._key.length; i++) {
      if ((this._allergies & Allergies._allergyValues[i]) !== 0) {
        result.push(Allergies._key[i]);
      }
    }
    return result;
  }
}