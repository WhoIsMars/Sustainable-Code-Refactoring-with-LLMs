export const isIsogram = (str) => {
  const letters = str.toLowerCase();
  const seen = new Set();

  for (let i = 0; i < letters.length; i++) {
    const char = letters[i];
    if (/[a-z]/.test(char)) {
      if (seen.has(char)) {
        return false;
      }
      seen.add(char);
    }
  }

  return true;
};