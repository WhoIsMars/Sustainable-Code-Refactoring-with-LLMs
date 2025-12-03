"""Finds anagrams of a word in a list of words"""

def detect_anagrams(anagram, word_list):
    """Finds any words in [word_list] that are anagrams of [anagram]"""
    anagram_lower = anagram.lower()
    letters = sorted(anagram_lower)
    anagram_len = len(anagram)

    return [word for word in word_list
            if len(word) == anagram_len and word.lower() != anagram_lower and sorted(word.lower()) == letters]