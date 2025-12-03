import re

def abbreviate(phrase):
    """abbreviate creates an acronym for a phrase"""
    return ''.join(abbreviate_word(word) for word in re.split(r'\W+', phrase) if word)

def abbreviate_word(word):
    """abbreviate_word selects the letters in a word to use for abbreviation"""
    if word.isupper():
        return word[0]
    return ''.join(letter for letter in word if letter.isupper() or letter == word[0].upper())