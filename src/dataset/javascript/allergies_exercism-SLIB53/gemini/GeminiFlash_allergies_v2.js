export class Allergies {
  constructor(allergyScore) {
    this.allergyScore = allergyScore;
    this.allergens = ['eggs', 'peanuts', 'shellfish', 'strawberries', 'tomatoes', 'chocolate', 'pollen', 'cats'];
  }

  list() {
    const result = [];
    for (let i = 0; i < this.allergens.length; i++) {
      if (this.allergyScore & (1 << i)) {
        result.push(this.allergens[i]);
      }
    }
    return result;
  }

  allergicTo(item) {
    for (let i = 0; i < this.allergens.length; i++) {
      if (this.allergens[i] === item && (this.allergyScore & (1 << i))) {
        return true;
      }
    }
    return false;
  }
}