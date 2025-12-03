def is_isogram(string):
    string = string.lower()
    letters = set()
    for char in string:
        if 'a' <= char <= 'z':
            if char in letters:
                return False
            letters.add(char)
    return True