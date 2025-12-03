from re import split

def abbreviate(phrase):
    """abbreviate creates an acronym for a phrase"""
    result = []
    for word in split(r'\W+', phrase):
        if word:  # Skip empty strings
            if all(c.isupper() for c in word):
                result.append(word[0])
            else:
                abbrev = word[0].upper()
                for c in word[1:]:
                    if c.isupper():
                        abbrev += c
                result.append(abbrev)
    return ''.join(result)

def abbreviate_word(word):
    """abbreviate_word selects the letters in a word to use for abbriviation"""
    if all(c.isupper() for c in word):
        return word[0]
    abbrev = word[0].upper()
    for c in word[1:]:
        if c.isupper():
            abbrev += c
    return abbrev