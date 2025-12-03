const abc = 'abcdefghijklmnopqrstuvwxyz';
const zyx = 'zyxwvutsrqponmlkjihgfedcba';

const change = (letter) => zyx[abc.indexOf(letter)];

export const encode = (plaintext) => {
  const plain = plaintext.toLowerCase().replace(/[^a-z0-9]/g, '');
  let ciphertext = '';
  let counter = 0;

  for (const letter of plain) {
    if (counter > 0 && counter % 5 === 0) {
      ciphertext += ' ';
    }
    ciphertext += /\d/.test(letter) ? letter : change(letter);
    counter++;
  }
  return ciphertext;
};