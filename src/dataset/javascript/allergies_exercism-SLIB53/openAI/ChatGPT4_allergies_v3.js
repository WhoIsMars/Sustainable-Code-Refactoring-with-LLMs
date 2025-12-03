export class Allergies {
  constructor(allergyScore) {
    this.allergyScore = allergyScore & 255; // Limit to 8 relevant bits
    this.allergyItems = [
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
    for (let i = 0; i < this.allergyItems.length; i++) {
      if (this.allergyScore & (1 << i)) {
        result.push(this.allergyItems[i]);
      }
    }
    return result;
  }

  allergicTo(item) {
    const index = this.allergyItems.indexOf(item);
    return index !== -1 && (this.allergyScore & (1 << index)) !== 0;
  }
}