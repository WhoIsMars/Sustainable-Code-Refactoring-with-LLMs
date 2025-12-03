import re

def translate(phrase):
    """translate converts a phrase to piglatin"""
    return ' '.join(translate_word(word) for word in phrase.split())

CASES = [
    re.compile(r'(.*?[^q])(u.*)'),  # q case
    re.compile(r'(^y[^aeiou].*)'),  # y case
    re.compile(r'(.*?)([aeoi].*)')  # default case
]

def translate_word(word):
    """translate_word converts a word to piglatin"""
    for case in CASES:
        match = case.match(word)
        if match:
            prefix, suffix = match.groups(default="")
            if prefix + "ay" != word:
                return suffix + prefix + "ay"
    return word + "ay"