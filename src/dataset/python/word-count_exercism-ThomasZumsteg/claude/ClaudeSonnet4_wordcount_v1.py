"""Catalogs and counts the number of words used in a phrase"""
import re

def word_count(phrase):
    """Returns dictionary with a count of words used"""
    if not phrase:
        return {}
    
    word_counts = {}
    for word in re.findall(r'[a-zA-Z0-9]+', phrase.lower()):
        word_counts[word] = word_counts.get(word, 0) + 1
    
    return word_counts