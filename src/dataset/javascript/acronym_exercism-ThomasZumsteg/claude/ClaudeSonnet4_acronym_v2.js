module.exports = {
    parse: parse
};

function parse(phrase) {
    let result = '';
    let word = '';
    let inWord = false;
    
    for (let i = 0; i < phrase.length; i++) {
        const char = phrase[i];
        const isWordChar = (char >= 'A' && char <= 'Z') || (char >= 'a' && char <= 'z') || (char >= '0' && char <= '9');
        
        if (isWordChar) {
            if (!inWord) {
                if (word) {
                    const firstChar = word.charCodeAt(0);
                    result += String.fromCharCode(firstChar >= 97 ? firstChar - 32 : firstChar);
                    
                    for (let j = 1; j < word.length; j++) {
                        const code = word.charCodeAt(j);
                        if (code >= 65 && code <= 90) {
                            result += word[j];
                        }
                    }
                }
                word = char;
                inWord = true;
            } else {
                word += char;
            }
        } else {
            inWord = false;
        }
    }
    
    if (word) {
        const firstChar = word.charCodeAt(0);
        result += String.fromCharCode(firstChar >= 97 ? firstChar - 32 : firstChar);
        
        for (let j = 1; j < word.length; j++) {
            const code = word.charCodeAt(j);
            if (code >= 65 && code <= 90) {
                result += word[j];
            }
        }
    }
    
    return result;
}