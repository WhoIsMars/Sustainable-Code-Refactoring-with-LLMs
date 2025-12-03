const abc = 'abcdefghijklmnopqrstuvwxyz';
const zyx = 'zyxwvutsrqponmlkjihgfedcba';

const charMap = new Map();
for (let i = 0; i < 26; i++) {
  charMap.set(abc[i], zyx[i]);
}

export const encode = (plaintext) => {
  const result = [];
  let counter = 0;
  
  for (let i = 0; i < plaintext.length; i++) {
    const char = plaintext[i];
    const lower = char.toLowerCase();
    
    if (lower >= 'a' && lower <= 'z') {
      if (counter % 5 === 0 && counter > 0) {
        result.push(' ');
      }
      result.push(charMap.get(lower));
      counter++;
    } else if (char >= '0' && char <= '9') {
      if (counter % 5 === 0 && counter > 0) {
        result.push(' ');
      }
      result.push(char);
      counter++;
    }
  }
  
  return result.join('');
};