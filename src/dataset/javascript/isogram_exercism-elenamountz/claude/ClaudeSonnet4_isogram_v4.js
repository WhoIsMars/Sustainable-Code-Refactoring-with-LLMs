export const isIsogram = (str) => {
  const seen = new Set();
  for (let i = 0; i < str.length; i++) {
    const char = str[i];
    if (char >= 'a' && char <= 'z') {
      if (seen.has(char)) return false;
      seen.add(char);
    } else if (char >= 'A' && char <= 'Z') {
      const lowerChar = String.fromCharCode(char.charCodeAt(0) + 32);
      if (seen.has(lowerChar)) return false;
      seen.add(lowerChar);
    }
  }
  return true;
};