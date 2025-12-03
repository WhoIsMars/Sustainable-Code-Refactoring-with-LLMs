class RotationalCipher {
    rotate(text, diff) {
        const lowerA = 'a'.charCodeAt(0);
        const lowerZ = 'z'.charCodeAt(0);
        const upperA = 'A'.charCodeAt(0);
        const upperZ = 'Z'.charCodeAt(0);
        const alphabetSize = 26;

        return text.split('').map(char => {
            const code = char.charCodeAt(0);
            if (code >= lowerA && code <= lowerZ) {
                return String.fromCharCode(lowerA + (code - lowerA + diff) % alphabetSize);
            } else if (code >= upperA && code <= upperZ) {
                return String.fromCharCode(upperA + (code - upperA + diff) % alphabetSize);
            }
            return char;
        }).join('');
    }
}

module.exports = RotationalCipher;