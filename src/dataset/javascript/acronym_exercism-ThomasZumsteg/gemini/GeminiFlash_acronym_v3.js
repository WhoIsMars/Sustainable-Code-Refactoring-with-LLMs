module.exports = {
    parse: parse
};

function parse(phrase) {
    const words = phrase.split(/\W+/);
    let result = '';

    for (let i = 0; i < words.length; i++) {
        const word = words[i];
        if (!word) continue;

        const firstChar = word.charAt(0).toUpperCase();
        let acronymPart = firstChar;

        if (!/^[A-Z]+$/.test(word)) {
            let remainingChars = '';
            for (let j = 1; j < word.length; j++) {
                const char = word[j];
                if (char >= 'A' && char <= 'Z') {
                    remainingChars += char;
                }
            }
            acronymPart += remainingChars;
        }
        result += acronymPart;
    }

    return result;
}