module.exports = function(chars) {
    if (!chars || chars.length === 0) return '';
    if (chars.length === 1) return chars;
    
    const result = new Array(chars.length);
    for (let i = 0; i < chars.length; i++) {
        result[i] = chars[chars.length - 1 - i];
    }
    return result.join('');
};