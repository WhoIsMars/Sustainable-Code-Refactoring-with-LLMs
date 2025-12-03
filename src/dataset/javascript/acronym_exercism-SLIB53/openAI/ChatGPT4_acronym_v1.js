export const parse = phrase => {
  let result = '';
  for (let i = 0, len = phrase.length; i < len; i++) {
    const char = phrase[i];
    if ((char >= 'A' && char <= 'Z') || char === "'") {
      if (i === 0 || phrase[i - 1] === ' ' || phrase[i - 1] === '-') {
        result += char;
      }
    } else if (char >= 'a' && char <= 'z') {
      if (i === 0 || phrase[i - 1] === ' ' || phrase[i - 1] === '-') {
        result += char.toUpperCase();
      }
    }
  }
  return result;
};