import re

def abbreviate(phrase):
    """abbreviate creates an acronym for a phrase"""
    words = re.findall(r'\b\w+\b', phrase)
    return ''.join(abbreviate_word(word) for word in words)

def abbreviate_word(word):
    """abbreviate_word selects the letters in a word to use for abbriviation"""
    if word.isupper():
        return word[0]
    result = word[0].upper()
    for letter in word[1:]:
        if letter.isupper():
            result += letter
    return result