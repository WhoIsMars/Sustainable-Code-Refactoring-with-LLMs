var shift = function(chr, diff) {
    const charCode = chr.charCodeAt(0);
    return String.fromCharCode(charCode + diff);
}

class RotationalCipher {
    rotate(text, diff) {
        let encoded = '';
        const textLength = text.length;

        for (let i = 0; i < textLength; i++) {
            const char = text[i];
            const charCode = char.charCodeAt(0);
            let rot = 0;

            if (charCode >= 97 && charCode <= 122) {
                const shiftedCharCode = charCode + diff;
                rot = (shiftedCharCode <= 122) ? diff : (diff - 26);
            } else if (charCode >= 65 && charCode <= 90) {
                const shiftedCharCode = charCode + diff;
                rot = (shiftedCharCode <= 90) ? diff : (diff - 26);
            }

            encoded += shift(char, rot);
        }

        return encoded;
    }
}

module.exports = RotationalCipher;