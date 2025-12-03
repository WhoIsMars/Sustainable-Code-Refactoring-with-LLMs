export const parse = phrase => {
  let result = "";
  const upperPhrase = phrase.toUpperCase();
  for (let i = 0; i < upperPhrase.length; i++) {
    const char = upperPhrase[i];
    if (char >= 'A' && char <= 'Z') {
      result += char;
      while (i + 1 < upperPhrase.length && upperPhrase[i + 1] >= 'A' && upperPhrase[i + 1] <= 'Z') {
        i++;
      }
    } else if (char === "'") {
      continue;
    }
  }
  return result;
};