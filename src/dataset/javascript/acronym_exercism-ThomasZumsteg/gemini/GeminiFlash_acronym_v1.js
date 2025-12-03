module.exports = {
    parse: parse
};

function parse(phrase) {
    let result = "";
    const words = phrase.split(/\W+/);

    for (let i = 0; i < words.length; i++) {
        const word = words[i];
        if (word.length === 0) continue;

        const firstChar = word.charAt(0).toUpperCase();
        let acronym = firstChar;

        if (!/^[A-Z]+$/.test(word)) {
            for (let j = 1; j < word.length; j++) {
                const char = word.charAt(j);
                if (char >= 'A' && char <= 'Z') {
                    acronym += char;
                }
            }
        }
        result += acronym;
    }

    return result;
}