import re

def translate(phrase):
    """translate converts a phrase to piglatin"""
    return ' '.join(translate_word(word) for word in phrase.split())

COMPILED_CASES = (
    re.compile(r'(.*?[^q])(u.*)'),
    re.compile(r'(^y[^aeiou].*?)()'),
    re.compile(r'(.*?)([aeoi].*)')
)

def translate_word(word):
    """translate_word converts a word to piglatin"""
    for pattern in COMPILED_CASES:
        match = pattern.match(word)
        if match:
            group1, group2 = match.groups()
            if group1 + "ay" != word:
                return group2 + group1 + "ay"
    return word + "ay"