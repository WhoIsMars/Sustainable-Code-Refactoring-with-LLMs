import string

def is_pangram(phrase):
    """is_pangram determines if every letter of the alphabet are in a phrase"""
    phrase = phrase.lower()
    return all(letter in phrase for letter in string.ascii_lowercase)