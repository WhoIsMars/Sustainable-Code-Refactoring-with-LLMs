module.exports = {
    encode: function(text) {
        let result = '';
        let count = 1;
        for (let i = 0; i < text.length; i++) {
            if (i + 1 < text.length && text[i] === text[i + 1]) {
                count++;
            } else {
                if (count > 1) {
                    result += count + text[i];
                } else {
                    result += text[i];
                }
                count = 1;
            }
        }
        return result;
    },
    decode: function(text) {
        let result = '';
        let number = '';
        for (let i = 0; i < text.length; i++) {
            if (!isNaN(parseInt(text[i]))) {
                number += text[i];
            } else {
                const num = parseInt(number);
                if (isNaN(num)) {
                    result += text[i];
                } else {
                    result += text[i].repeat(num);
                }
                number = '';
            }
        }
        return result;
    }
};