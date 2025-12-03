export const parse = phrase => {
  let result = "";
  for (let i = 0; i < phrase.length; i++) {
    const char = phrase[i];
    if ((char >= 'A' && char <= 'Z') || (char >= 'a' && char <= 'z') || char === "'") {
      if (i === 0 || phrase[i - 1] === ' ' || phrase[i - 1] === '-') {
        result += char.toUpperCase();
      }
    }
  }
  return result;
};