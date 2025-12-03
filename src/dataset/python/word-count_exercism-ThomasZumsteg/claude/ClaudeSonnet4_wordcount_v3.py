"""Catalogs and counts the number of words used in a phrase"""
from collections import Counter
import re

_WORD_PATTERN = re.compile(r'[\W_]+', re.UNICODE)

def word_count(phrase):
    """Returns dictionary with a count of words used"""
    if not phrase:
        return Counter()
    
    words = _WORD_PATTERN.split(phrase.lower())
    return Counter(word for word in words if word)