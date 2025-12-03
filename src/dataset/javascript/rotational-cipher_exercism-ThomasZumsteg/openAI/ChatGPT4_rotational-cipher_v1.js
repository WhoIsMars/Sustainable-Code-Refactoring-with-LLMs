class RotationalCipher {
    rotate(text, diff) {
        const lowerA = 'a'.charCodeAt(0), lowerZ = 'z'.charCodeAt(0);
        const upperA = 'A'.charCodeAt(0), upperZ = 'Z'.charCodeAt(0);
        const alphabetSize = 26;

        return text.split('').map(char => {
            const charCode = char.charCodeAt(0);
            if (charCode >= lowerA && charCode <= lowerZ) {
                return String.fromCharCode(((charCode - lowerA + diff) % alphabetSize) + lowerA);
            } else if (charCode >= upperA && charCode <= upperZ) {
                return String.fromCharCode(((charCode - upperA + diff) % alphabetSize) + upperA);
            }
            return char;
        }).join('');
    }
}

module.exports = RotationalCipher;