export const isIsogram = (str) => {
  const seen = new Set();
  for (const char of str.toLowerCase()) {
    if (/[a-z]/.test(char)) {
      if (seen.has(char)) return false;
      seen.add(char);
    }
  }
  return true;
};