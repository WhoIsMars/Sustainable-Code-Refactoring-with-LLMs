export default class Acronym {
  public static parse(phrase: string): string {
    const result: string[] = [];
    let takeNext = true;
    
    for (let i = 0; i < phrase.length; i++) {
      const char = phrase[i];
      
      if (char === ':') break;
      
      if (char === ' ' || char === '-') {
        takeNext = true;
      } else if (takeNext && char >= 'A' && char <= 'z') {
        result.push(char.toUpperCase());
        takeNext = false;
      } else if (char >= 'A' && char <= 'Z') {
        result.push(char);
        takeNext = false;
      }
    }
    
    return result.join('');
  }
}