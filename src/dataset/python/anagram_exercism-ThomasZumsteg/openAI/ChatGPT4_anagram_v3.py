"""Finds anagrams of a word in a list of words"""

from collections import Counter

def detect_anagrams(anagram, word_list):
    """Finds any words in [word_list] that are anagrams of [anagram]"""
    anagram_counter = Counter(anagram.lower())
    anagram_lower = anagram.lower()
    return [word for word in word_list
            if word.lower() != anagram_lower
            and Counter(word.lower()) == anagram_counter]