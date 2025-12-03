"""Finds anagrams of a word in a list of words"""

def detect_anagrams(anagram, word_list):
    """Finds any words in [word_list] that are anagrams of [anagram]"""
    anagram_lower = anagram.lower()
    anagram_sorted = sorted(anagram_lower)
    
    result = []
    for word in word_list:
        word_lower = word.lower()
        if word_lower != anagram_lower and sorted(word_lower) == anagram_sorted:
            result.append(word)
    
    return result