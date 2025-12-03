export const isIsogram = (str) => {
  str = str.toLowerCase();
  const seen = new Set();
  for (let i = 0; i < str.length; i++) {
    const char = str[i];
    if (/[a-z]/.test(char)) {
      if (seen.has(char)) {
        return false;
      }
      seen.add(char);
    }
  }
  return true;
};