import re

def abbreviate(phrase):
    """abbreviate creates an acronym for a phrase"""
    words = re.findall(r'\b\w+\b', phrase)
    return ''.join(abbreviate_word(word) for word in words)

def abbreviate_word(word):
    """abbreviate_word selects the letters in a word to use for abbriviation"""
    if not word:
        return ''
    first_letter = word[0].upper()
    remaining_upper = ''.join(letter for letter in word[1:] if letter.isupper())
    return first_letter + remaining_upper