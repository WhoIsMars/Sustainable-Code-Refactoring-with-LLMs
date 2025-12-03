function translate(phrase) {
    return phrase.replace(/\b([^aeioy]*qu|[^aeiouy]*)([aeiouy]\w*)\b/g, (_, prefix, rest) => rest + prefix + "ay");
}

module.exports = { translate };