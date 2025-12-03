module.exports = function(chars) {
    if (!chars || chars.length === 0) return '';
    if (chars.length === 1) return chars;
    
    const charArray = Array.isArray(chars) ? chars : Array.from(chars);
    return charArray.reverse().join('');
};