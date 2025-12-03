"""Catalogs and counts the number of words used in a phrase"""
from collections import Counter
import re

def word_count(phrase):
    """Returns dictionary with a count of words used"""
    words = re.findall(r'\b\w+\b', phrase.lower())
    return Counter(words)