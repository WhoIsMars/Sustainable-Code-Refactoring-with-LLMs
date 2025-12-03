from re import split

def abbreviate(phrase):
    """abbreviate creates an acronym for a phrase"""
    return ''.join(abbreviate_word(word) for word in split(r'\W+', phrase) if word)

def abbreviate_word(word):
    """abbreviate_word selects the letters in a word to use for abbriviation"""
    if not word:
        return ''
    
    first_char = word[0].upper()
    
    if len(word) == 1:
        return first_char
    
    has_lowercase = any(c.islower() for c in word)
    if not has_lowercase:
        return first_char
    
    return first_char + ''.join(c for c in word[1:] if c.isupper())