export default class Acronym {
  public static parse(phrase: string): string {
    return phrase
      .split(/[\s-]+/)
      .map(word => word[0]?.toUpperCase() || '')
      .join('');
  }
}