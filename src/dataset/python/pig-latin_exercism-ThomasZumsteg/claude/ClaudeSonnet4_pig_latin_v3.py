from re import compile

def translate(phrase):
    """translate converts a phrase to piglatin"""
    return ' '.join(translate_word(word) for word in phrase.split())

COMPILED_CASES = (
    compile(r'(.*?[^q])(u.*)'),
    compile(r'(^y[^aeiou].*?)()'),
    compile(r'(.*?)([aeoi].*)')
)

def translate_word(word):
    """translate_word converts a word to piglatin"""
    for pattern in COMPILED_CASES:
        match = pattern.search(word)
        if match:
            group1, group2 = match.groups()
            if group1 + "ay" != word:
                return group2 + group1 + "ay"
    return word + "ay"