export const isIsogram = (str) => {
  const seen = new Set();
  for (let i = 0; i < str.length; i++) {
    const char = str[i].toLowerCase();
    if (char >= 'a' && char <= 'z') {
      if (seen.has(char)) {
        return false;
      }
      seen.add(char);
    }
  }
  return true;
};