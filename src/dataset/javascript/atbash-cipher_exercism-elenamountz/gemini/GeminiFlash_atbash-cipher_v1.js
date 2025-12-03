const abc = 'abcdefghijklmnopqrstuvwxyz';
const zyx = 'zyxwvutsrqponmlkjihgfedcba';

const encodeChar = (char) => {
    const index = abc.indexOf(char);
    return index !== -1 ? zyx[index] : char;
};

export const encode = (plaintext) => {
    let ciphertext = '';
    let counter = 0;
    const plain = plaintext.toLowerCase().replace(/[^a-z0-9]/g, '');

    for (let i = 0; i < plain.length; i++) {
        const char = plain[i];

        if (counter > 0 && counter % 5 === 0) {
            ciphertext += ' ';
        }

        if (/[0-9]/.test(char)) {
            ciphertext += char;
        } else {
            ciphertext += encodeChar(char);
        }

        counter++;
    }

    return ciphertext;
};