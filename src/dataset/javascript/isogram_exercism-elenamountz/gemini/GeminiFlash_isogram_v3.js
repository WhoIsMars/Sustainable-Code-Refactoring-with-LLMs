export const isIsogram = (str) => {
  const lowerStr = str.toLowerCase();
  const seen = new Set();

  for (let i = 0; i < lowerStr.length; i++) {
    const char = lowerStr[i];
    if (/[a-z]/.test(char)) {
      if (seen.has(char)) {
        return false;
      }
      seen.add(char);
    }
  }

  return true;
};