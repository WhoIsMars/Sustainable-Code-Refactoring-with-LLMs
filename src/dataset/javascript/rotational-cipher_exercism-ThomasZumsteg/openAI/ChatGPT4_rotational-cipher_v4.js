var shift = function (chr, diff, lowerBound, upperBound) {
    const range = upperBound - lowerBound + 1;
    return String.fromCharCode(((chr.charCodeAt(0) - lowerBound + diff) % range + range) % range + lowerBound);
};

class RotationalCipher {
    rotate(text, diff) {
        let encoded = '';
        const lowerA = 'a'.charCodeAt(0), lowerZ = 'z'.charCodeAt(0);
        const upperA = 'A'.charCodeAt(0), upperZ = 'Z'.charCodeAt(0);

        for (let c = 0; c < text.length; c++) {
            const char = text[c];
            if (char >= 'a' && char <= 'z') {
                encoded += shift(char, diff, lowerA, lowerZ);
            } else if (char >= 'A' && char <= 'Z') {
                encoded += shift(char, diff, upperA, upperZ);
            } else {
                encoded += char;
            }
        }
        return encoded;
    }
}

module.exports = RotationalCipher;