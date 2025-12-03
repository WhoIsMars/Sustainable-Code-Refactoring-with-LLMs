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
  }

  list() {
    const result = [];
    for (let i = 0; i < 8; i++) {
      if (this.allergyScore & (1 << i)) {
        result.push(Allergies.ALLERGENS[i]);
      }
    }
    return result;
  }

  allergicTo(item) {
    const allergenValue = Allergies.ALLERGEN_MAP.get(item);
    return allergenValue ? !!(this.allergyScore & allergenValue) : false;
  }
}