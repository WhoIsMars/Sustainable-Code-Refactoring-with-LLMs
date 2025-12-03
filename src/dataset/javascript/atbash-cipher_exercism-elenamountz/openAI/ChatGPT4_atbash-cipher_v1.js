const abc = 'abcdefghijklmnopqrstuvwxyz';
const zyx = [...abc].reverse().join('');
const abcMap = new Map([...abc].map((char, i) => [char, zyx[i]]));

const change = (letter) => abcMap.get(letter) || letter;

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