from re import compile

def translate(phrase):
    """translate converts a phrase to piglatin"""
    return ' '.join(translate_word(word) for word in phrase.split())

COMPILED_CASES = (
    (compile(r'(.*?[^q])(u.*)'), 1, 2),  # q case
    (compile(r'(^y[^aeiou].*)()'), 1, 2),  # y case
    (compile(r'(.*?)([aeiou].*)'), 1, 2)   # default case
)

def translate_word(word):
    """translate_word converts a word to piglatin"""
    for regex, group1, group2 in COMPILED_CASES:
        match = regex.match(word)
        if match:
            g1 = match.group(group1)
            g2 = match.group(group2)
            if g1 + "ay" != word:
                return g2 + g1 + "ay"
    return word + "ay"