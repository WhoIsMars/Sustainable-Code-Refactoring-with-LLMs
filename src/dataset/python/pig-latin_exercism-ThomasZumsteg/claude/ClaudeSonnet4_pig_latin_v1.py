from re import compile

def translate(phrase):
    """translate converts a phrase to piglatin"""
    return ' '.join(translate_word(word) for word in phrase.split())

# Pre-compile regex patterns for better performance
COMPILED_CASES = (
    compile(r'(.*?[^q])(u.*)'),  # q case
    compile(r'(^y[^aeiou].*)()')  # y case
)
VOWEL_PATTERN = compile(r'(.*?)([aeoi].*)')  # default case

def translate_word(word):
    """translate_word converts a word to piglatin"""
    # Check first two optimized cases
    for pattern in COMPILED_CASES:
        match = pattern.search(word)
        if match and match.group(1) + "ay" != word:
            return match.group(2) + match.group(1) + "ay"
    
    # Check vowel case
    match = VOWEL_PATTERN.search(word)
    if match and match.group(1) + "ay" != word:
        return match.group(2) + match.group(1) + "ay"
    
    return word + "ay"