const abc = 'abcdefghijklmnopqrstuvwxyz';
const zyx = 'zyxwvutsrqponmlkjihgfedcba';

const encode = (plaintext) => {
  let ciphertext = '';
  const plain = plaintext.toLowerCase().replace(/[^a-z0-9]/g, '');
  let counter = 0;
  const plainLength = plain.length;

  for (let i = 0; i < plainLength; i++) {
    const letter = plain[i];

    if (counter % 5 === 0 && ciphertext.length !== 0) {
      ciphertext += ' ';
    }

    const charCode = letter.charCodeAt(0);

    if (charCode >= 48 && charCode <= 57) {
      ciphertext += letter;
    } else if (charCode >= 97 && charCode <= 122) {
      ciphertext += zyx[charCode - 97];
    }

    counter++;
  }

  return ciphertext;
};

export { encode };