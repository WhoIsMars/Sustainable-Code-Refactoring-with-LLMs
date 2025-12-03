"""Catalogs and counts the number of words used in a phrase"""
from collections import Counter
import re

# Compile regex pattern once at module level
_WORD_PATTERN = re.compile(r'[\W_]+', re.UNICODE)

def word_count(phrase):
    """Returns dictionary with a count of words used"""
    if not phrase:
        return Counter()
    
    # Use pre-compiled pattern and filter empty strings during split
    words = (word for word in _WORD_PATTERN.split(phrase.lower()) if word)
    return Counter(words)