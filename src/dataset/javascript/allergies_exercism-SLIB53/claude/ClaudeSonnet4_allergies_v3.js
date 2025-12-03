export class Allergies {
  static ALLERGENS = [
    'eggs',
    'peanuts',
    'shellfish',
    'strawberries',
    'tomatoes',
    'chocolate',
    'pollen',
    'cats'
  ];

  static ALLERGEN_MAP = new Map([
    ['eggs', 1],
    ['peanuts', 2],
    ['shellfish', 4],
    ['strawberries', 8],
    ['tomatoes', 16],
    ['chocolate', 32],
    ['pollen', 64],
    ['cats', 128]
  ]);

  constructor(allergyScore) {
    this.allergyScore = allergyScore;
    this._cachedList = null;
  }

  list() {
    if (this._cachedList === null) {
      this._cachedList = [];
      for (let i = 0; i < Allergies.ALLERGENS.length; i++) {
        if (this.allergyScore & (1 << i)) {
          this._cachedList.push(Allergies.ALLERGENS[i]);
        }
      }
    }
    return this._cachedList;
  }

  allergicTo(item) {
    const allergenValue = Allergies.ALLERGEN_MAP.get(item);
    return allergenValue ? (this.allergyScore & allergenValue) !== 0 : false;
  }
}