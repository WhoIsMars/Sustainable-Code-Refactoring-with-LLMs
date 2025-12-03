module.exports = {
    parse: parse
};

function parse(phrase) {
    const words = phrase.split(/\W+/);
    let result = '';

    for (let i = 0; i < words.length; i++) {
        const word = words[i];
        if (!word) continue; // Skip empty strings

        const firstChar = word.charAt(0).toUpperCase();
        if (word.length > 0 && /^[A-Z]+$/.test(word)) {
            result += firstChar;
        } else {
            let cleanedWord = '';
            for (let j = 1; j < word.length; j++) {
                const char = word[j];
                if (char >= 'A' && char <= 'Z') {
                    cleanedWord += char;
                }
            }
            result += firstChar + cleanedWord;
        }
    }

    return result;
}