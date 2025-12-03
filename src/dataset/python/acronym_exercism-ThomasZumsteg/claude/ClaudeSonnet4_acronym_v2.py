from re import split

def abbreviate(phrase):
    """abbreviate creates an acronym for a phrase"""
    result = []
    for word in split('\W+', phrase):
        if word:  # Skip empty strings
            if all(c.isupper() for c in word):
                result.append(word[0])
            else:
                result.append(word[0].upper())
                result.extend(c for c in word[1:] if c.isupper())
    return ''.join(result)

def abbreviate_word(word):
    """abbreviate_word selects the letters in a word to use for abbriviation"""
    if all(letter.isupper() for letter in word):
        return word[0]
    return word[0].upper() + ''.join(letter for letter in word[1:] if letter.isupper())