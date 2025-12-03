export const parse = phrase => {
  let result = '';
  let inWord = false;
  
  for (let i = 0; i < phrase.length; i++) {
    const char = phrase[i];
    const upperChar = char >= 'a' && char <= 'z' ? String.fromCharCode(char.charCodeAt(0) - 32) : char;
    
    if ((upperChar >= 'A' && upperChar <= 'Z') || upperChar === "'") {
      if (!inWord) {
        result += upperChar;
        inWord = true;
      }
    } else {
      inWord = false;
    }
  }
  
  return result;
}