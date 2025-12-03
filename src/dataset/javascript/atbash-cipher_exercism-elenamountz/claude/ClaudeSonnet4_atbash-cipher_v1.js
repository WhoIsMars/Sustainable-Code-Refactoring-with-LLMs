const abc = 'abcdefghijklmnopqrstuvwxyz';
const zyx = 'zyxwvutsrqponmlkjihgfedcba';

const charMap = new Map();
for (let i = 0; i < 26; i++) {
  charMap.set(abc[i], zyx[i]);
}

export const encode = (plaintext) => {
  const plain = plaintext.toLowerCase().replace(/[^a-z0-9]/g, '');
  const result = [];
  let counter = 0;

  for (let i = 0; i < plain.length; i++) {
    const char = plain[i];
    
    if (counter % 5 === 0 && counter > 0) {
      result.push(' ');
    }
    
    if (char >= '0' && char <= '9') {
      result.push(char);
    } else {
      result.push(charMap.get(char));
    }
    counter++;
  }
  
  return result.join('');
}