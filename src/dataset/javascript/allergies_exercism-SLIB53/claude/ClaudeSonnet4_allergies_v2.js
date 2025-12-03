export class Allergies {
  constructor(allergyScore) {
    this.allergyScore = allergyScore;
    this.allergens = [
      'eggs',
      'peanuts',
      'shellfish',
      'strawberries',
      'tomatoes',
      'chocolate',
      'pollen',
      'cats'
    ];
  }

  list() {
    const result = [];
    for (let i = 0; i < 8; i++) {
      if (this.allergyScore & (1 << i)) {
        result.push(this.allergens[i]);
      }
    }
    return result;
  }

  allergicTo(item) {
    const index = this.allergens.indexOf(item);
    return index !== -1 && (this.allergyScore & (1 << index)) !== 0;
  }
}