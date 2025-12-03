export default class Acronym {
  public static parse(phrase: string): string {
    let acronym = '';
    let addNext = true;

    for (const char of phrase) {
      if (char === ':') break;
      if (addNext && /[A-Za-z]/.test(char)) {
        acronym += char.toUpperCase();
        addNext = false;
      }
      addNext = char === ' ' || char === '-';
    }

    return acronym;
  }
}