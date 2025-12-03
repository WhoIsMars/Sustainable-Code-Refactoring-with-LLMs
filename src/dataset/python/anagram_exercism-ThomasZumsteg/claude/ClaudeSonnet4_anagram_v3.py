"""Finds anagrams of a word in a list of words"""

def detect_anagrams(anagram, word_list):
    """Finds any words in [word_list] that are anagrams of [anagram]"""
    anagram_lower = anagram.lower()
    anagram_sorted = sorted(anagram_lower)
    anagram_len = len(anagram_lower)
    
    result = []
    for word in word_list:
        word_lower = word.lower()
        if (len(word_lower) == anagram_len and 
            word_lower != anagram_lower and 
            sorted(word_lower) == anagram_sorted):
            result.append(word)
    
    return result