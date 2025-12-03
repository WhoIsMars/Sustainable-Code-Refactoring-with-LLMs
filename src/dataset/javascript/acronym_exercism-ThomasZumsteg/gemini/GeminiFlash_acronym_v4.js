module.exports = {
    parse: parse
};

function parse(phrase) {
    return phrase.split(/\W+/)
        .map(word => {
            if (!word) return '';
            const firstChar = word.charAt(0).toUpperCase();
            const rest = word.slice(1);

            if (word.length > 1 && /^[A-Z]+$/.test(word)) {
                return firstChar;
            }

            let result = firstChar;
            for (let i = 0; i < rest.length; i++) {
                const char = rest[i];
                if (char >= 'A' && char <= 'Z') {
                    result += char;
                }
            }
            return result;
        })
        .join('');
}