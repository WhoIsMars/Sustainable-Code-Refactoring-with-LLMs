const abc = 'abcdefghijklmnopqrstuvwxyz';
const zyx = abc.split('').reverse().join('');

const encode = (plaintext) => {
  let ciphertext = '';
  const plain = plaintext.toLowerCase().replace(/[^a-z0-9]/gi, '');
  let counter = 0;

  for (let i = 0; i < plain.length; i++) {
    const letter = plain[i];

    if (counter > 0 && counter % 5 === 0) {
      ciphertext += ' ';
    }

    if (/[0-9]/.test(letter)) {
      ciphertext += letter;
    } else if (/[a-z]/.test(letter)) {
      ciphertext += zyx[abc.indexOf(letter)];
    }

    counter++;
  }

  return ciphertext;
};

export { encode };