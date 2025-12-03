from re import split

def abbreviate(phrase):
    """abbreviate creates an acronym for a phrase"""
    result = []
    for word in split(r'\W+', phrase):
        if word:
            if word.isupper():
                result.append(word[0])
            else:
                result.append(word[0].upper())
                result.extend(char for char in word[1:] if char.isupper())
    return ''.join(result)

def abbreviate_word(word):
    """abbreviate_word selects the letters in a word to use for abbriviation"""
    if word.isupper():
        return word[0]
    return word[0].upper() + ''.join(letter for letter in word[1:] if letter.isupper())