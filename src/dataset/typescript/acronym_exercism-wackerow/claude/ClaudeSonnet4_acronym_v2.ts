export default class Acronym {
  public static parse(phrase: string): string {
    let acronym = '';
    let takeNext = true;
    
    for (let i = 0; i < phrase.length; i++) {
      const char = phrase[i];
      
      if (char === ':') break;
      
      if (takeNext && char >= 'A' && char <= 'Z') {
        acronym += char;
        takeNext = false;
      } else if (takeNext && char >= 'a' && char <= 'z') {
        acronym += String.fromCharCode(char.charCodeAt(0) - 32);
        takeNext = false;
      } else if (char === ' ' || char === '-') {
        takeNext = true;
      }
    }
    
    return acronym;
  }
}