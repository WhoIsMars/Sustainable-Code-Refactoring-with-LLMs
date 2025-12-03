def abbreviate(words):
    return ''.join(char.upper() for char in words if char.isalpha() and (char.isupper() or not words[words.index(char) - 1].isalpha()))