module.exports = {
    encode: function(text) {
        let encoded = "";
        let count = 1;
        for (let i = 0; i < text.length; i++) {
            if (i + 1 < text.length && text[i] === text[i + 1]) {
                count++;
            } else {
                encoded += (count > 1 ? count : "") + text[i];
                count = 1;
            }
        }
        return encoded;
    },
    decode: function(text) {
        let decoded = "";
        let i = 0;
        while (i < text.length) {
            let numStr = "";
            while (i < text.length && /\d/.test(text[i])) {
                numStr += text[i];
                i++;
            }
            const char = text[i];
            const num = numStr ? parseInt(numStr, 10) : 1;
            decoded += char.repeat(num);
            i++;
        }
        return decoded;
    }
};