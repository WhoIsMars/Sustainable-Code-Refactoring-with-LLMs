export default class Acronym {
  public static parse(phrase: string): string {
    const result: string[] = [];
    const length = phrase.length;
    let prevChar = '';
    
    for (let i = 0; i < length; i++) {
      const char = phrase[i];
      
      if (char === ':') break;
      
      if (char >= 'A' && char <= 'Z') {
        result.push(char);
      } else if ((char >= 'a' && char <= 'z') && (prevChar === ' ' || prevChar === '-')) {
        result.push(String.fromCharCode(char.charCodeAt(0) - 32));
      }
      
      prevChar = char;
    }
    
    return result.join('');
  }
}