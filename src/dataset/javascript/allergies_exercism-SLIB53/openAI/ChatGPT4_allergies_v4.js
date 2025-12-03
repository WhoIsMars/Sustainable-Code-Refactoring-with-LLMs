export class Allergies {
  constructor(allergyScore) {
    this.allergyScore = allergyScore;
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
    this.allergyList = this.allergyItems.filter((_item, i) => this.allergyScore & (1 << i));
  }

  list() {
    return this.allergyList;
  }

  allergicTo(item) {
    return this.allergyList.includes(item);
  }
}