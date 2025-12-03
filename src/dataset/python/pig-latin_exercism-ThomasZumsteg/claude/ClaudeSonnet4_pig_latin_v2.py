from re import compile

def translate(phrase):
    """translate converts a phrase to piglatin"""
    return ' '.join(translate_word(word) for word in phrase.split())

# Pre-compile regex patterns for better performance
COMPILED_CASES = (
    compile(r'(.*?[^q])(u.*)'),  # q case
    compile(r'(^y[^aeiou].*?)()'),  # y case
    compile(r'(.*?)([aeoi].*)')  # default case
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