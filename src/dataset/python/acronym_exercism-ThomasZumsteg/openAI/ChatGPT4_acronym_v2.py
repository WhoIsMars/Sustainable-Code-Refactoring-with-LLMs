import re

def abbreviate(phrase):
    """abbreviate creates an acronym for a phrase"""
    return ''.join(abbreviate_word(word) for word in re.findall(r'\b\w+\b', phrase))

def abbreviate_word(word):
    """abbreviate_word selects the letters in a word to use for abbreviation"""
    return word[0].upper() + ''.join(letter for letter in word[1:] if letter.isupper())