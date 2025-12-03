function translate(phrase) {
    return phrase.split(' ').map(pigize).join(' ');
}

function pigize(word) {
    const regex = /^([^aeioy]*qu|.*?)([aeiouy].*)$/;
    const matches = regex.exec(word);
    return matches ? `${matches[2]}${matches[1]}ay` : word;
}

module.exports = { translate };