const abc = 'abcdefghijklmnopqrstuvwxyz';
const zyx = abc.split('').reverse().join('');
const charCodeA = 'a'.charCodeAt(0);
const charCode0 = '0'.charCodeAt(0);

const change = (letter) => zyx[letter.charCodeAt(0) - charCodeA];

export const encode = (plaintext) => {
  let ciphertext = '';
  let counter = 0;
  const plain = plaintext.toLowerCase().replace(/[^a-z0-9]/g, '');

  for (let i = 0; i < plain.length; i++) {
    const letter = plain[i];

    if (counter > 0 && counter % 5 === 0) {
      ciphertext += ' ';
    }

    const charCode = letter.charCodeAt(0);

    if (charCode >= charCode0 && charCode <= charCode0 + 9) {
      ciphertext += letter;
    } else if (charCode >= charCodeA && charCode <= charCodeA + 25) {
      ciphertext += change(letter);
    } else {
      continue;
    }

    counter++;
  }

  return ciphertext;
};