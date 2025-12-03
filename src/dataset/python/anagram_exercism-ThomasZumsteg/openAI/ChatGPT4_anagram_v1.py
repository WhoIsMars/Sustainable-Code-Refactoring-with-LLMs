"""Finds anagrams of a word in a list of words"""

def detect_anagrams(anagram, word_list):
    """Finds any words in [word_list] that are anagrams of [anagram]"""
    anagram_lower = anagram.lower()
    anagram_signature = sorted(anagram_lower)
    return [word for word in word_list if word.lower() != anagram_lower and sorted(word.lower()) == anagram_signature]