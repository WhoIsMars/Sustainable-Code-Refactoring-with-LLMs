def abbreviate(words):
    result = []
    i = 0
    length = len(words)
    
    while i < length:
        char = words[i]
        if char.isalpha():
            result.append(char.upper())
            i += 1
            # Skip remaining letters in the word
            while i < length and (words[i].isalpha() or words[i] == "'"):
                i += 1
        else:
            i += 1
    
    return ''.join(result)