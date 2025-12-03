export const parse = phrase => {
  let result = '';
  let shouldTakeNext = true;
  
  for (let i = 0; i < phrase.length; i++) {
    const char = phrase[i];
    const upperChar = char >= 'a' && char <= 'z' ? String.fromCharCode(char.charCodeAt(0) - 32) : char;
    
    if ((upperChar >= 'A' && upperChar <= 'Z') || upperChar === "'") {
      if (shouldTakeNext) {
        result += upperChar;
        shouldTakeNext = false;
      }
    } else {
      shouldTakeNext = true;
    }
  }
  
  return result;
}