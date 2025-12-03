export default class Acronym {
  public static parse(phrase: string): string {
    let acronym = '';
    const words = phrase.replace(/:.*$/, '').split(/[\s-]+/);
    for (const word of words) {
      if (word.length > 0) {
        acronym += word[0].toUpperCase();
      }
    }
    return acronym;
  }
}