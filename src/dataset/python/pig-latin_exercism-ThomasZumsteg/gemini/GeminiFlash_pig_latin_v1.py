import re

def translate(phrase):
    """translate converts a phrase to piglatin"""
    return ' '.join(translate_word(word) for word in phrase.split())

def translate_word(word):
    """translate_word converts a word to piglatin"""
    if not word:
        return word + "ay"

    if word.startswith('y') and not any(c in word[1:] for c in 'aeiou'):
        return word[1:] + word[0] + "ay"

    match = re.match(r'([^aeiou]*)([aeiou].*)', word)
    if match:
        consonants = match.group(1)
        vowels = match.group(2)
        if consonants:
            if consonants.endswith('q') and vowels.startswith('u'):
                return vowels + consonants + "ay"
            return vowels + consonants + "ay"
    return word + "ay"