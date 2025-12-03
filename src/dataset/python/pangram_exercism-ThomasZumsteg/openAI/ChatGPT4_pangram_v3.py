def is_pangram(phrase):
    """is_pangram determines if every letter of the alphabet are in a phrase"""
    phrase_set = set(phrase.lower())
    return all(letter in phrase_set for letter in 'abcdefghijklmnopqrstuvwxyz')