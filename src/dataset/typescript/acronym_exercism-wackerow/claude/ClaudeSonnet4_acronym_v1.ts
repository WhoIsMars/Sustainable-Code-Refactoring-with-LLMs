export default class Acronym {
  public static parse(phrase: string): string {
    let acronym = '';
    let prevChar = ' ';
    
    for (let i = 0; i < phrase.length; i++) {
      const char = phrase[i];
      
      if (char === ':') break;
      
      if (char >= 'A' && char <= 'Z' || 
          (prevChar === ' ' || prevChar === '-') && char >= 'a' && char <= 'z') {
        acronym += char >= 'a' && char <= 'z' ? String.fromCharCode(char.charCodeAt(0) - 32) : char;
      }
      
      prevChar = char;
    }
    
    return acronym;
  }
}