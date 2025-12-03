export const parse = phrase => {
  let result = '';
  let inWord = false;
  
  for (let i = 0; i < phrase.length; i++) {
    const char = phrase[i];
    const code = char.charCodeAt(0);
    
    if ((code >= 65 && code <= 90) || (code >= 97 && code <= 122) || char === "'") {
      if (!inWord) {
        result += code >= 97 ? String.fromCharCode(code - 32) : char;
        inWord = true;
      }
    } else {
      inWord = false;
    }
  }
  
  return result;
}